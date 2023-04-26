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

//Função que recebe o diretório da imagem .bmp
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

//Renderiza height map com base na largura a altura desejada
void renderHeightMap(float size, float h){
    for(int i = 0; i < heights.size()-1; ++i){
        for(int j = 0; j < heights[i].size()-1; ++j){
            glBegin(GL_TRIANGLES);
            glColor3f(heights[i][j], heights[i][j], heights[i][j]);
            glVertex3f(i*size, heights[i][j]*h, j*size); //v1
            glVertex3f((i+1)*size, heights[i+1][j]*h, j*size); //v2
            glVertex3f((i+1) *size, heights[i+1][j+1]*h, size*(j+1)); //v3
            
            glVertex3f((i) *size, heights[i][j+1]*h, size*(j+1)); //v4
            glVertex3f(i*size, heights[i][j]*h, j*size); //v1
            glVertex3f((i+1) *size, heights[i+1][j+1]*h, size*(j+1)); //v3
            glEnd();
        }
    }
}

float getHeightFromMap(float x, float z)
{
    
    // Encontra a célula do heightmap correspondente às coordenadas (x, z)
    int i = (int)floor(x);
    int j = (int)floor(z);

    // Verifica se (x, z) está dentro dos limites do heightmap
    if (i < 0 || i >= heights.size()-1 || j < 0 || j >= heights[0].size()-1) {
        return 0.0;
    }

    // Calcula a altura interpolando os valores do heightmap
    float h00 = heights[i][j];
    float h01 = heights[i][j+1];
    float h10 = heights[i+1][j];
    float h11 = heights[i+1][j+1];

    float fx = x - i;
    float fz = z - j;

    float h0 = h00 + fx*(h10 - h00);
    float h1 = h01 + fx*(h11 - h01);

    return (h0 + fz*(h1 - h0)) ;
}


#endif
