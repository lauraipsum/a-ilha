#ifndef __LOADER__
#define __LOADER__

//headers
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
//globals

float elephantrot;
char ch='1';
//other functions and main
//wavefront .obj loader code begins
GLuint loadObj(char *fname)
{
    GLuint elephant;
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    elephant=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POINTS);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
    return elephant;
}
//wavefront .obj loader code ends here


#endif