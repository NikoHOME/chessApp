#ifndef LOGIC_H
#define LOGIC_H
#define cor1 {0.0f,0.0f}
#define cor2 {0.0f,1.0f}
#define cor3 {1.0f,1.0f}
#define cor4 {1.0f,0.0f}
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

struct vec3
{
	GLfloat x,y,z;
};
// Vec2 for texture coordinates
struct vec2
{
	GLfloat x,y;
};
// Object draw information
struct nodes{
	GLfloat x1,y1,z1; vec3 colour1; vec2 cord1;
	GLfloat x2,y2,z2; vec3 colour2; vec2 cord2;
	GLfloat x3,y3,z3; vec3 colour3; vec2 cord3;
	GLfloat x4,y4,z4; vec3 colour4; vec2 cord4;
};
// Object indices information
struct indices{
	unsigned int i1,i2,i3,i4,i5,i6;
};

nodes rectangle(GLfloat X1,GLfloat Y1,GLfloat X2,GLfloat Y2,vec3 colour);
nodes centredRectangle(GLfloat X1,GLfloat Y1,GLfloat pX,GLfloat pY,vec3 colour);
nodes paddingRectangle(GLfloat X1,GLfloat Y1,GLfloat X2,GLfloat Y2,GLfloat pX,GLfloat pY,vec3 colour);
void generateButtonTray(nodes* menuVertices,std::vector <nodes>* buttonVertices,std::vector<indices>* buttonIndices,GLfloat menuX1,GLfloat menuY1,GLfloat menuX2, GLfloat menuY2,short buttonNum,GLfloat buttonSize,GLfloat buttonOffset,GLfloat buttonPadding, vec3 menuColour, vec3 buttonColour);

nodes voidSquare();

void addTexture(GLuint* texture,std::string input);
void generateBufferData(GLuint* inputAB,GLuint* inputEAB,GLuint* inputVA,unsigned int bufferSize);
void generateStaticBufferData(GLuint* inputAB,GLuint* inputEAB,GLuint* inputVA,nodes* inputVertices,indices* inputIndices,unsigned int bufferSize);


class Button
{
    private :
        float posX1,posY1,posX2,posY2;
        GLuint VA,AB,EAB;
    public :
        Button(float x1, float x2, float y1, float y2, float paddingX, float paddingY, vec3 colour){
            posX1=x1+paddingX;
            posY1=y1+paddingY;
            posX2=x2-paddingX;
            posY2=y2-paddingY;
            nodes vertices[] = 
    	    {
    		    posX1, posY1, 0.0f, colour, cor1,
                posX1, posY2, 0.0f, colour, cor2,
                posX2, posY1, 0.0f, colour, cor3,
                posX2, posY2, 0.0f, colour, cor4	
	        };
            indices indices[] = 
            {
            	0,1,3,
            	1,3,2	
            };
            generateStaticBufferData(&AB,&EAB,&VA,vertices,indices,1);
        };
};


#endif //