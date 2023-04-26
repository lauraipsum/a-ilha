#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "heightmap.h"
#include "texture.h"
#include <GL/glxext.h>


float posCameraX,posCameraY,posCameraZ,anguloCamera,anguloCameraVertical, 
        propIlha = 80, largIlha, compIlha, lagos;

int largura = 10, altura = 12, comprimento = 10, terrestres1, terrestres2, plantas1, plantas2;

unsigned int tex, xceu, xxceu, yceu, yyceu, zceu, zzceu;

float   diagonalTotal = sqrt(pow(largura,2)+pow(comprimento,2)),
        diagonalHmap = 100*sqrt(2),
        tamHmap = ((diagonalTotal*100)/diagonalHmap)/100;

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);

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
   anguloCamera  = 0;
   anguloCameraVertical = 0;

   loadHeightMap("resources/hmap3.bmp");
   glEnable(GL_DEPTH_TEST);

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
            posCameraX -= 0.1; // mover a câmera para a esquerda
            break;

        case 'd':
            posCameraX += 0.1;
            break;

    }
    glutPostRedisplay();
}

void skybox(void){
    
    bool b1 = glIsEnabled(GL_TEXTURE_2D); //new, we left the textures turned on, if it was turned on
    glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    //glDisable(GL_DEPTH_TEST);   //turn off depth texting
    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, yyceu);
    glBegin(GL_QUADS); //top
        glTexCoord2f(0,0); 
        glVertex3f(largura/2 , 2*altura/3, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , 2*altura/3, -comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , 2*altura/3, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , 2*altura/3, comprimento/2);  
    glEnd();

    glBindTexture(GL_TEXTURE_2D, yceu);
    glBegin(GL_QUADS); //down
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , -altura/3, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , -altura/3, -comprimento/2);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, zceu);
    glBegin(GL_QUADS); //
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , 2*altura/3, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , 2*altura/3, comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , -altura/3, comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, zzceu);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , -altura/3, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , 2*altura/3, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , 2*altura/3, -comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, xxceu);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-largura/2 , 2*altura/3, comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(-largura/2 , 2*altura/3, -comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, xceu);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(largura/2 , 2*altura/3, -comprimento/2);
        glTexCoord2f(1,0);
        glVertex3f(largura/2 , 2*altura/3, comprimento/2);
        glTexCoord2f(1,1);
        glVertex3f(largura/2 , -altura/3, comprimento/2);
        glTexCoord2f(0,1);
        glVertex3f(largura/2 , -altura/3, -comprimento/2);
    glEnd();
    glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
    //glEnable(GL_DEPTH_TEST);
    if(!b1)
        glDisable(GL_TEXTURE_2D);
}

void oceano(void){
    glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    //glDisable(GL_DEPTH_TEST);   //turn off depth texting
    glBegin(GL_QUADS);
        glColor4f(0.3, 0.3, 1.0, 0.3);
        glVertex3f(largura/2 , 1, -comprimento/2);
        glVertex3f(-largura/2 , 1, -comprimento/2);
        glVertex3f(-largura/2 , 1, comprimento/2);
        glVertex3f(largura/2 , 1, comprimento/2);

        glVertex3f(largura/2 , -altura/3, comprimento/2);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glVertex3f(largura/2 , -altura/3, -comprimento/2);

        glVertex3f(largura/2 , 1, comprimento/2);
        glVertex3f(-largura/2 , 1, comprimento/2);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);
        glVertex3f(largura/2 , -altura/3, comprimento/2);

        glVertex3f(largura/2 , -altura/3, -comprimento/2);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glVertex3f(-largura/2 , 1, -comprimento/2);
        glVertex3f(largura/2 , 1, -comprimento/2);

        glVertex3f(-largura/2 , 1, comprimento/2);
        glVertex3f(-largura/2 , 1, -comprimento/2);
        glVertex3f(-largura/2 , -altura/3, -comprimento/2);
        glVertex3f(-largura/2 , -altura/3, comprimento/2);

        glVertex3f(largura/2 , 1, -comprimento/2);
        glVertex3f(largura/2 , 1, comprimento/2);
        glVertex3f(largura/2 , -altura/3, comprimento/2);
        glVertex3f(largura/2 , -altura/3, -comprimento/2);
    glEnd();
        
    glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
    // glEnable(GL_DEPTH_TEST);
}

void ilha(void){
    bool b1 = glIsEnabled(GL_TEXTURE_2D); //new, we left the textures turned on, if it was turned on
    glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    //glDisable(GL_DEPTH_TEST);   //turn off depth texting
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glTranslatef(-largura/2, 0.3888, -comprimento/2);
        //glTranslatef((largura/2)(100-propIlha)/200, 0.0,(comprimento/2)(100-propIlha)/200);
        renderHeightMap(tamHmap*propIlha/100, 1);
    
    glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
    // glEnable(GL_DEPTH_TEST);
    if(!b1)
        glDisable(GL_TEXTURE_2D);

}

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
           
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   float centroX = posCameraX + sin(anguloCamera * M_PI / 180.0);
   float centroY = posCameraY + sin(anguloCameraVertical * M_PI / 180.0);
   float centroZ = posCameraZ - cos(anguloCamera * M_PI / 180.0);
   gluLookAt(posCameraX, posCameraY, posCameraZ, centroX, centroY, centroZ, 0, 1, 0);

   skybox();
   grid();
   oceano();
   ilha();
   
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