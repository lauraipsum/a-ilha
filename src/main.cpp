#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "grid.h"

float posCameraX,posCameraY,posCameraZ;

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   //inicializa posição da câmera
   posCameraX = 0.3;
   posCameraY = 0.1;
   posCameraZ = 0;
}

static float zoomFactor = 1.0;

void setProjectionMatrix(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);
    glTranslatef(0.0, 0.0, -5.0*zoomFactor);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Rotaciona a posição da camera em torno do eixo y
// Exercício: use coordenadas polares para posicionar a câmera em uma esfera ao redor do objeto
void specialKeys(int key, int x, int y)
{
   float angulo = 2*M_PI/180;
   switch (key) {
       case GLUT_KEY_LEFT : 
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;
       case GLUT_KEY_RIGHT : 
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);                      
            break;
       case GLUT_KEY_UP:
            posCameraX += posCameraX * 0.1;
            posCameraZ += posCameraZ * 0.1;
            break;
       case GLUT_KEY_DOWN:
            posCameraX -= posCameraX * 0.1;
            posCameraZ -= posCameraZ * 0.1;
            break;
          
   }
   glutPostRedisplay();
}

void normalKeys(unsigned char key, int x, int y){
   switch (key)
   {
   case 's':
      zoomFactor += 0.02;
      setProjectionMatrix(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
      glutPostRedisplay();
      break;
   case 'w':
      zoomFactor -= 0.02;
      if(zoomFactor < 0.1){zoomFactor = 0.1;}
      setProjectionMatrix(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
      glutPostRedisplay();
      break;
      

   }
}


           
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
 
   gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   //glColor3f (0.7, 0.7, 1.0);
   // glutSolidTeapot(0.5);
   // glutWireSphere(0.5,6,6);
  
   //visualização dos eixos
   //exercício: faça um plano sob a chaleira
   grid();
   
 
   //troca de buffers, o flush é implícito aqui
   glutSwapBuffers();
}

//função chamada quando a tela é redimensionada 
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
   setProjectionMatrix(w, h);

   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
  
   init ();
  
   glutDisplayFunc(display); 
   glutSpecialFunc(specialKeys);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(normalKeys);
   
   glutMainLoop();
   
   return 0;
}
