// g++ main.cpp -o main -lglut -lGLU -lGL -lSDL2 
// ./main

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "heightmap.h"
#include "texture.h"
#include <GL/glxext.h>


float posCameraX,posCameraY,posCameraZ,anguloCamera,anguloCameraVertical;
unsigned int tex;

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);
   tex = loadTexture("resources/sand-texture-hd.bmp");
   //inicializa posição da câmera
   posCameraX = 0.3;
   posCameraY = 0.1;
   posCameraZ = 0;
   anguloCamera  = 0;
   anguloCameraVertical = 0;

   loadHeightMap("resources/heightmap.bmp");

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

void grid(){

   glBegin(GL_LINES);

      //eixo X
   glColor3f (1.0, 0.0, 0.0);
   glVertex3f(-1.0, 0.0, 0.0);
   glVertex3f(1.0, 0.0, 0.0);

       //eixo y
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    
      //eixo z
    glColor3f (0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);

      // loop para criar linhas horizontais
    for(float i=-1.0; i<=1.0; i+=0.1) {
        if(i==0.0) continue; // pular a linha amarela
        if(i==-0.1 || i==0.1) glColor3f(0.0, 0.0, 0.0); // ajustar a cor para essas linhas
        else glColor3f(0.5, 0.5, 0.5); // todas as outras linhas são cinzas
        glVertex3f(-1.0, 0.0, i);
        glVertex3f(1.0, 0.0, i);
    }

      // loop para criar linhas verticais
    for(float i=-1.0; i<=1.0; i+=0.1) {
        if(i==0.0 || i==-1.0 || i==1.0) continue; // pular a linha amarela e as extremas
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(i, 0.0, -1.0);
        glVertex3f(i, 0.0, 1.0);
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

   grid();
   glBindTexture(GL_TEXTURE_2D, tex);
   glTranslatef(0.0, 0.0,0.0);
   glTranslatef(-1.0, -0.099, -1.0);
   glScalef(0.25, 0.25, 0.25);
   renderHeightMap(0.08, 2.0);
   
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
