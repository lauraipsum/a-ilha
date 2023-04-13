#ifndef GRID_H
#define GRID_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

void grid(void){

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
#endif