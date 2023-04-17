#ifndef HEIGHTMAP
#define HEIGHTMAP

#include "iostream"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
std::vector<std::vector<float>> heights;
void loadHeightMap(const char* name){
    SDL_Surface* img=SDL_LoadBMP(name);
    if(!img){
        std::cout <<"image is not loaded!"<< std::endl;
    }

    std::vector<float> tmp;
    for(int i=0;  i < img->h; ++i){
        tmp.clear();
        for(int j=0; j < img->w; ++j){
            Uint32 pixel = ((Uint32*) img->pixels)[(i) * img->pitch/4+j];
            Uint8 r,g,b;
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            tmp.push_back((float) r/255.0);
        }
        heights.push_back(tmp);
    }

}

void renderHeightMap(float size, float h){
    for(int i = 0; i < heights.size()-1; ++i){
        for(int j = 0; j < heights[0].size()-1; ++j){
            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(heights[i][j], heights[i][j], heights[i][j]);
            glVertex3f(i*size, heights[i][j]*h, j*size);
            glVertex3f((i+1)*size, heights[i+1][j]*h, j*size);
            glVertex3f((i+1) *size, heights[i+1][j+1]*h, (j+1));
            glEnd();
        }
    }
}

#endif
