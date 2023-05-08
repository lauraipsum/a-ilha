#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "heightmap.h"
#include "texture.h"
#include <GL/glxext.h>
#include <stdlib.h>     
#include <cstdlib> // para srand() e rand()
#include <ctime> // para time()
#include "metodoEntrada.h"
#include "loader.h"

criaJogo entrada;
GLuint model1,model2,model3,model4;
float posCameraX,posCameraY,posCameraZ,anguloCamera,anguloCameraVertical,propIlha = 80, largIlha, compIlha, lagos;
int largura, altura, comprimento, terrestre1, terrestre2, plantas1, plantas2;
unsigned int tex, xceu, xxceu, yceu, yyceu, zceu, zzceu;

float   diagonalTotal, diagonalHmap, tamHmap;

long lastUpdateTime = 0;

// Variáveis globais para armazenar a posição atual do teapot
float teapotX = 0.0f;
float teapotY = 0.0f;
float teapotZ = 0.0f;



void init(void) 
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    //carregamento de textura
    tex = loadTexture("resources/texturas/sand-texture-hd.bmp");
    xceu = loadTexture("resources/bluecloud_lf.bmp");
    xxceu = loadTexture("resources/bluecloud_rt.bmp");
    yceu = loadTexture("resources/bluecloud_dn.bmp");
    yyceu = loadTexture("resources/bluecloud_up.bmp");
    zceu = loadTexture("resources/bluecloud_bk.bmp");
    zzceu = loadTexture("resources/bluecloud_ft.bmp");

   //inicializa posição da câmera
   posCameraX = 1.0;
   posCameraY = 1.0;
   posCameraZ = 0;
   anguloCamera = 0;
   anguloCameraVertical = 0;

    //lê arquivo de entrada e atribui as informações lidas
    entrada.readfile("entrada.txt");

    largura = entrada.getL();
    altura = entrada.getA();
    comprimento = entrada.getC();
    terrestre1 = entrada.getT1();
    terrestre2 = entrada.getT2();
    plantas1 = entrada.getP1();
    plantas2 = entrada.getP2();

    diagonalTotal = sqrt(pow(largura,2)+pow(comprimento,2));
    diagonalHmap = 100*sqrt(2);
    tamHmap = ((diagonalTotal*100)/diagonalHmap)/100;

    loadHeightMap("resources/heightmap.bmp");
    model1 = loadObj("modelos/capybara.obj");
    model2 = loadObj("modelos/Tree1.obj");
    model3 = loadObj("modelos/Tree.obj");
    model4 = loadObj("modelos/cat.obj");

}



void specialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT :
            anguloCamera -= 5.0;
            break;

        case GLUT_KEY_RIGHT :
            anguloCamera += 5.0;
            break;

        case GLUT_KEY_UP :
            anguloCameraVertical += 5.0;
            break;

        case GLUT_KEY_DOWN :
            anguloCameraVertical -= 5.0;
            break;

    }
    glutPostRedisplay();
}


void mouseMovement(int x, int y)
{
    static int last_x = x;
    static int last_y = y;

    int delta_x = x - last_x;
    int delta_y = y - last_y;

    anguloCamera += delta_x;
    anguloCameraVertical += delta_y;

    last_x = x;
    last_y = y;

    glutPostRedisplay();
}



void regularKeys(unsigned char key, int x, int y)
{
    switch (key) {

      case 'w':
            posCameraX += 0.1 * sin(anguloCamera * M_PI / 180.0); // mover a câmera para frente
            posCameraZ -= 0.1 * cos(anguloCamera * M_PI / 180.0); // mover a câmera para frente
            posCameraY += 0.1 * sin(anguloCameraVertical * M_PI / 180.0); // mover a câmera para cima
         break;

      case 's':
            posCameraX -= 0.1 * sin(anguloCamera * M_PI / 180.0); // mover a câmera para trás
            posCameraZ += 0.1 * cos(anguloCamera * M_PI / 180.0); // mover a câmera para trás
            posCameraY -= 0.1 * sin(anguloCameraVertical * M_PI / 180.0); // mover a câmera para baixo
         break;

        case 'a':
            posCameraX -= 0.1 * cos(anguloCamera * M_PI / 180.0); // mover a câmera para a esquerda
            posCameraZ -= 0.1 * sin(anguloCamera * M_PI / 180.0);
            break;

        case 'd':
            posCameraX += 0.1 * cos(anguloCamera * M_PI / 180.0); // mover a câmera para a direita
            posCameraZ += 0.1 * sin(anguloCamera * M_PI / 180.0);
            break;

    }
    glutPostRedisplay();
}

//gera um paralelepipedo com textura de céu, formando uma skybox e limitando a cena
void skybox(void){
    
    bool b1 = glIsEnabled(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, yyceu);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1); 
        glVertex3f(largura/2 , altura/2, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , altura/2, -comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , altura/2, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , altura/2, comprimento/2);  
    glEnd();

    glBindTexture(GL_TEXTURE_2D, yceu);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(largura/2 , -altura/2, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(-largura/2 , -altura/2, comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , -altura/2, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(largura/2 , -altura/2, -comprimento/2);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, zceu);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(largura/2 , altura/2, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(-largura/2 , altura/2, comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , -altura/2, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(largura/2 , -altura/2, comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, zzceu);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , -altura/2, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , -altura/2, -comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , altura/2, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , altura/2, -comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, xceu);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , altura/2, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(-largura/2 , altura/2, -comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , -altura/2, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , -altura/2, comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, xxceu);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(largura/2 , altura/2, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , altura/2, comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , -altura/2, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(largura/2 , -altura/2, -comprimento/2);
    glEnd();
    glEnable(GL_LIGHTING);
    if(!b1)
        glDisable(GL_TEXTURE_2D);
}

//gera um paralelepípedo com textura e transparência, simulando o oceano
void oceano(void){
    glDisable(GL_LIGHTING);

    glColor4f(0, 0, 1, 0.4);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);        
        glVertex3f(largura/2 , 0, -comprimento/2);
        glTexCoord2f(0,1);        
        glVertex3f(-largura/2 , 0, -comprimento/2);
        glTexCoord2f(0,0);        
        glVertex3f(-largura/2 , 0, comprimento/2);
        glTexCoord2f(1,0);        
        glVertex3f(largura/2 , 0, comprimento/2);
    glEnd();

    glBegin(GL_QUADS); //
        glVertex3f(largura/2 , 0, comprimento/2);
        glVertex3f(-largura/2 , 0, comprimento/2);
        glVertex3f(-largura/2 , -altura/2, comprimento/2);
        glVertex3f(largura/2 , -altura/2, comprimento/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(largura/2 , -altura/2, -comprimento/2);
        glVertex3f(-largura/2 , -altura/2, -comprimento/2);
        glVertex3f(-largura/2 , 0, -comprimento/2);
        glVertex3f(largura/2 , 0, -comprimento/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-largura/2 , 0, comprimento/2);
        glVertex3f(-largura/2 , 0, -comprimento/2);
        glVertex3f(-largura/2 , -altura/2, -comprimento/2);
        glVertex3f(-largura/2 , -altura/2, comprimento/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(largura/2 , 0, -comprimento/2);
        glVertex3f(largura/2 , 0, comprimento/2);
        glVertex3f(largura/2 , -altura/2, comprimento/2);
        glVertex3f(largura/2 , -altura/2, -comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, tex);
    glColor4f(0, 0, 0.4, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);        
        glVertex3f(largura/2 , -(altura/2) + 0.5, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(-largura/2 , -(altura/2) + 0.5, -comprimento/2);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , -(altura/2) + 0.5, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(largura/2 , -(altura/2) + 0.5, comprimento/2);
    glEnd();

    glEnable(GL_LIGHTING);
}

//renderiza a ilha a partir de um heightmap e a desloca da borda da cena
void ilha(void){
    bool b1 = glIsEnabled(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTranslatef((-largura/2)+0.5, -0.5, (-comprimento/2)+0.5);
    renderHeightMap(tamHmap*propIlha/100, altura*0.1); 
    glEnable(GL_LIGHTING); 
    if(!b1)
        glDisable(GL_TEXTURE_2D);

}

//gera a grid usada como base para a renderização do projeto
void grid(){

   glBegin(GL_LINES);
      //eixo X
   glColor3f (largura/2, 0.0, 0.0);
   glVertex3f(-largura/2, 0.0, 0.0);
   glVertex3f(largura/2, 0.0, 0.0);

       //eixo y
    glColor3f (0.0, altura/2, 0.0);
    glVertex3f(0.0, -altura/2, 0.0);
    glVertex3f(0.0, altura/2, 0.0);
    
      //eixo z
    glColor3f (0.0, 0.0, comprimento/2);
    glVertex3f(0.0, 0.0, -comprimento/2);
    glVertex3f(0.0, 0.0, comprimento/2);

      // loop para criar linhas horizontais
    for(float i=-comprimento/2; i<=comprimento/2; i+=0.1) {
        if(i==0.0) continue; // pular a linha amarela
        if(i==-0.1 || i==0.1) glColor3f(0.0, 0.0, 0.0); // ajustar a cor para essas linhas
        else glColor3f(0.5, 0.5, 0.5); // todas as outras linhas são cinzas
        glVertex3f(-largura/2, 0.0, i);
        glVertex3f(largura/2, 0.0, i);
    }

      // loop para criar linhas verticais
    for(float i=-largura/2; i<=largura/2; i+=0.1) {
        if(i==0.0 || i==-1.0 || i==1.0) continue; // pular a linha amarela e as extremas
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(i, 0.0, -comprimento/2);
        glVertex3f(i, 0.0, comprimento/2);
    }

    glEnd();
}


/*
void genTerrestre1(){

    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static bool moveForward = true; // flag para controlar a direção do movimento
    static float y = height + 0.2f; // obtém a altura do terreno na posição x,z e adiciona 0.2 para posicionar o teapot acima do solo

    // Atualiza a posição do teapot
    if (getHeightFromMap(i, j) != -1){
        if (moveForward) {
            z += 0.1f;
            x += 0.1f;
            y = height + 0.2f;
        } else {
            z -= 0.1f;
            x -= 0.1f;
            y = height + 0.2f;
        }
    } else {
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }
    // Verifica se a nova posição ultrapassa os limites da ilha
    if (z < 0.0f || z > comprimento * propIlha / 100) {
        // Se ultrapassar, inverte a direção do movimento e retorna para o início da ilha
        moveForward = !moveForward;
        z = 0.0f;
    } else if (x < 0.0f || x > largura * propIlha / 100){
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }

    // Renderiza o teapot na nova posição
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180.0f, 90.0f, 300.0f, 200.0f);

    glScalef(0.09f, 0.09f, 0.09f);
    glColor3f(1,0,0);
    glCallList(model1);
    glPopMatrix();
    glEnable(GL_LIGHTING); 
    glEnable(GL_TEXTURE_2D);

}*/

void genTerrestre1(){
    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    static float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static bool moveForward = true; // flag para controlar a direção do movimento
    static float y = height + 0.2f; // obtém a altura do terreno na posição x,z e adiciona 0.2 para posicionar o teapot acima do solo

    // Atualiza a posição do teapot
    if (moveForward) {
        z += 0.1f;
        x += 0.1f;
    } else {
        z -= 0.1f;
        x -= 0.1f;
    }

    // Verifica se a nova posição ultrapassa os limites da ilha
    if (z < 0.0f || z > comprimento * propIlha / 100) {
        // Se ultrapassar, inverte a direção do movimento e retorna para o início da ilha
        moveForward = !moveForward;
        z = 0.0f;
    } else if (x < 0.0f || x > largura * propIlha / 100){
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }

    // Renderiza o teapot na nova posição
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180.0f, 90.0f, 300.0f, 200.0f);

    glScalef(0.09f, 0.09f, 0.09f);
    glColor3f(1,0,0);
    glCallList(model1);
    glPopMatrix();
    glEnable(GL_LIGHTING); 

}

/*
void genTerrestre2(){
    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static bool moveForward = true; // flag para controlar a direção do movimento
    static float y = height + 0.2f; // obtém a altura do terreno na posição x,z e adiciona 0.2 para posicionar o teapot acima do solo

    // Atualiza a posição do teapot
    if (getHeightFromMap(i, j) != -1){
        if (moveForward) {
            z += 0.1f;
            x += 0.1f;
            y = height + 0.2f;
        } else {
            z -= 0.1f;
            x -= 0.1f;
            y = height + 0.2f;
        }
    } else {
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }

    // Verifica se a nova posição ultrapassa os limites da ilha
    if (z < 0.0f || z > comprimento * propIlha / 100) {
        // Se ultrapassar, inverte a direção do movimento e retorna para o início da ilha
        moveForward = !moveForward;
        z = 0.0f;
    } else if (x < 0.0f || x > largura * propIlha / 100){
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }

    // Renderiza o teapot na nova posição
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180.0f, 90.0f, 300.0f, 200.0f);
    
    glScalef(0.02f, 0.02f, 0.02f);
    glColor3f(0,0,1);
    glCallList(model4);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING); 

} */


void genTerrestre2(){
    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    static float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static bool moveForward = true; // flag para controlar a direção do movimento
    static float y = height + 0.2f; // obtém a altura do terreno na posição x,z e adiciona 0.2 para posicionar o teapot acima do solo

    // Atualiza a posição do teapot
    if (moveForward) {
        z += 0.1f;
        x += 0.1f;
    } else {
        z -= 0.1f;
        x -= 0.1f;
    }

    // Verifica se a nova posição ultrapassa os limites da ilha
    if (z < 0.0f || z > comprimento * propIlha / 100) {
        // Se ultrapassar, inverte a direção do movimento e retorna para o início da ilha
        moveForward = !moveForward;
        z = 0.0f;
    } else if (x < 0.0f || x > largura * propIlha / 100){
        moveForward = !moveForward;
        x = rand() % (int)(largura * propIlha / 100);
    }

    // Renderiza o teapot na nova posição
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180.0f, 90.0f, 300.0f, 200.0f);
    
    glScalef(0.02f, 0.02f, 0.02f);
    glColor3f(0,0,1);
    glCallList(model4);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glEnable(GL_LIGHTING); 

}

// recebe um inteiro diferenciador de posição
void genPlanta1(int dif){
    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    static float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static bool moveForward = true; // flag para controlar a direção do movimento
    static float y = height + 0.1f; // obtém a altura do terreno na posição x,z e adiciona 0.1 para posicionar o teapot acima do solo

   
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z+dif);

    glScalef(0.2f, 0.2f, 0.2f);
    glColor3f(0.5,1,0.5);
    glCallList(model2);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING); 

}

// recebe um inteiro diferenciador de posição
void genPlanta2(int dif){
    // Gera um número aleatório de 0 a heights.size() - 1 para escolher uma linha do heightmap
    int i = rand() % heights.size();

    // Gera um número aleatório de 0 a heights[i].size() - 1 para escolher uma coluna do heightmap
    int j = rand() % heights[i].size();

    // Obtém a altura do solo na posição aleatória (i, j)
    float height = getHeightFromMap(i, j);

    static float x = rand() % (int)(largura * propIlha / 100); // gera uma posição x aleatória dentro da ilha
    static float z = 0.0f; // posição atual ao longo do eixo Z
    static float y = height + 0.1f; // obtém a altura do terreno na posição x,z e adiciona 0.1 para posicionar o teapot acima do solo

   
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x, y, z+dif);

    glScalef(0.2f, 0.2f, 0.2f);
    glColor3f(0,1,0);
    glCallList(model3);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING); 

}

//função geradora dos terrestres conforme entrada
void Terrestres(){
    int i;
    for (i = 0; i < terrestre1; i++){
        genTerrestre1();
    }
    for (i = 0; i < terrestre2; i++){
        genTerrestre2();
    }
}

//função geradora das plantas conforme entrada
void Plantas(){
    int i;
    for (i = 0; i < plantas1; i++){
        genPlanta1(i);
    }
    for (i = 0; i < plantas2; i++){
        genPlanta2(i);
    }
}


void display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_ALWAYS);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float centroX = posCameraX + sin(anguloCamera * M_PI / 180.0);
    float centroY = posCameraY + sin(anguloCameraVertical * M_PI / 180.0);
    float centroZ = posCameraZ - cos(anguloCamera * M_PI / 180.0);
    gluLookAt(posCameraX, posCameraY, posCameraZ, centroX, centroY, centroZ, 0, 1, 0); //seta a posição inicial da câmera

    skybox();
    oceano();
    ilha();
    Terrestres();
    Plantas();
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glScalef(0.3, 0.3, 0.3);
    
    

    //troca de buffers, o flush é implícito aqui
    glutSwapBuffers();
    
}


//função chamada quando a tela é redimensionada 
void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect_ratio = (float)w / (float)h;
    gluPerspective(50.0, aspect_ratio, 0.5, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (900, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);

    init ();
    
    glutDisplayFunc(display); 

    glutSpecialFunc(specialKeys);
    glutMotionFunc(mouseMovement);
    glutKeyboardFunc(regularKeys); // registra a função regularKeys como callback para teclas normais
    glutReshapeFunc(reshape);

    glutMainLoop();
    
    return 0;
}