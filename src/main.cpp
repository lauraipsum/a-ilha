//Por Beatriz Trinchão Andrade

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

float posCameraX,posCameraY,posCameraZ;

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   //inicializa posição da câmera
   posCameraX = 0.3;
   posCameraY = 0.1;
   posCameraZ = 0;
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
        // linha amarela
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.0,0.0,1.0);
        glVertex3f(1.0, 0.0, 1.0);
        //continuacao de linha amarela
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0,1.0);
        glVertex3f(-1.0, 0.0, 1.0);

        // linha azul claro
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 1.0);

        //continuacao de linha azul clara
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -1.0);
         
        //aqui começa o desenho das linhas verticais


        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0, 0.0, 1.0);
        glVertex3f(-1.0, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.9, 0.0, 1.0);
        glVertex3f(-0.9, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.8, 0.0, 1.0);
        glVertex3f(-0.8, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.7, 0.0, 1.0);
        glVertex3f(-0.7, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.6, 0.0, 1.0);
        glVertex3f(-0.6, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.5, 0.0, 1.0);
        glVertex3f(-0.5, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.4, 0.0, 1.0);
        glVertex3f(-0.4, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.3, 0.0, 1.0);
        glVertex3f(-0.3, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.2, 0.0, 1.0);
        glVertex3f(-0.2, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.1, 0.0, 1.0);
        glVertex3f(-0.1, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.1, 0.0, 1.0);
        glVertex3f(0.1, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.2, 0.0, 1.0);
        glVertex3f(0.2, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.3, 0.0, 1.0);
        glVertex3f(0.3, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.4, 0.0, 1.0);
        glVertex3f(0.4, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 1.0);
        glVertex3f(0.5, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.6, 0.0, 1.0);
        glVertex3f(0.6, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.7, 0.0, 1.0);
        glVertex3f(0.7, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.8, 0.0, 1.0);
        glVertex3f(0.8, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.9, 0.0, 1.0);
        glVertex3f(0.9, 0.0, -1.0);
        
         //linhas horizontais

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -1.0);
        glVertex3f(-1.0, 0.0, -1.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.9);
        glVertex3f(-1.0, 0.0, -0.9);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.8);
        glVertex3f(-1.0, 0.0, -0.8);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.7);
        glVertex3f(-1.0, 0.0, -0.7);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.6);
        glVertex3f(-1.0, 0.0, -0.6);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.5);
        glVertex3f(-1.0, 0.0, -0.5);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.4);
        glVertex3f(-1.0, 0.0, -0.4);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.3);
        glVertex3f(-1.0, 0.0, -0.3);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.2);
        glVertex3f(-1.0, 0.0, -0.2);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, -0.1);
        glVertex3f(-1.0, 0.0, -0.1);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.1);
        glVertex3f(-1.0, 0.0, 0.1);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.2);
        glVertex3f(-1.0, 0.0, 0.2);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.2);
        glVertex3f(-1.0, 0.0, 0.2);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.2);
        glVertex3f(-1.0, 0.0, 0.2);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.3);
        glVertex3f(-1.0, 0.0, 0.3);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.4);
        glVertex3f(-1.0, 0.0, 0.4);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.5);
        glVertex3f(-1.0, 0.0, 0.5);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.6);
        glVertex3f(-1.0, 0.0, 0.6);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.7);
        glVertex3f(-1.0, 0.0, 0.7);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.8);
        glVertex3f(-1.0, 0.0, 0.8);

        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.9);
        glVertex3f(-1.0, 0.0, 0.9);

    glEnd();
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
   //gluPerspective(50.0, 1, 0.5, 1000.0);

   glMatrixMode(GL_MODELVIEW);
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
   
   glutMainLoop();
   
   return 0;
}
