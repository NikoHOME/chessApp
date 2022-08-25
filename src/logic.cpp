#include "logic.h"
#define cord1 {0.0f,0.0f}
#define cord2 {0.0f,1.0f}
#define cord3 {1.0f,1.0f}
#define cord4 {1.0f,0.0f}


nodes rectangle(GLfloat X1,GLfloat Y1,GLfloat X2,GLfloat Y2,vec3 colour)
{
	return						
	{
		X1, Y1, 0.0f, colour, cord1,
        X1, Y2, 0.0f, colour, cord2,
        X2, Y2, 0.0f, colour, cord3,
        X2, Y1, 0.0f, colour, cord4		
	};
};

nodes centredRectangle(GLfloat X1,GLfloat Y1,GLfloat pX,GLfloat pY,vec3 colour)
{
	return						
	{
		X1-pX, Y1-pY, 0.0f, colour, cord1,
        X1-pX, Y1+pY, 0.0f, colour, cord2,
        X1+pX, Y1+pY, 0.0f, colour, cord3,
        X1+pX, Y1-pY, 0.0f, colour, cord4		
	};
};

nodes paddingRectangle(GLfloat X1,GLfloat Y1,GLfloat X2,GLfloat Y2,GLfloat pX,GLfloat pY,vec3 colour)
{
	return						
	{
		X1+pX, Y1+pY, 0.0f, colour, cord1,
        X1+pX, Y2-pY, 0.0f, colour, cord2,
        X2-pX, Y2-pY, 0.0f, colour, cord3,
        X2-pX, Y1+pY, 0.0f, colour, cord4		
	};
};

//Create removed object draw information
nodes voidSquare()
{
	return						
	{
		0.0f, 0.0f, 0.0f, {0.0f,0.0f,0.0f}, {0.0f,0.0f},
        0.0f, 0.0f, 0.0f, {0.0f,0.0f,0.0f}, {0.0f,0.0f},
        0.0f, 0.0f, 0.0f, {0.0f,0.0f,0.0f}, {0.0f,0.0f},
        0.0f, 0.0f, 0.0f, {0.0f,0.0f,0.0f}, {0.0f,0.0f}	
	};
};

void generateButtonTray(nodes* menuVertices,std::vector <nodes>* buttonVertices,std::vector<indices>* buttonIndices,GLfloat menuX1,GLfloat menuY1,GLfloat menuX2, GLfloat menuY2,short buttonNum,GLfloat buttonSize,GLfloat buttonOffset,GLfloat buttonPadding, vec3 menuColour, vec3 buttonColour)
{
	GLfloat center=(menuX1+menuX2)/2;
	*menuVertices = rectangle(menuX1,menuY1,menuX2,menuY2,menuColour);
	for(unsigned int i=0;i<4*buttonNum;i+=4)
	{
		buttonVertices->push_back(paddingRectangle(center,menuY2-buttonSize-buttonOffset,center,menuY2-buttonOffset,-buttonSize,0.0f,buttonColour));
		buttonIndices->push_back(
		{
			i,i+1,i+3,
			i+1,i+3,i+2
		});
		buttonOffset+=buttonPadding+buttonSize;
	}
};



void addTexture(GLuint* texture,std::string input)
{
	//std::string basePath = __FILE__;
	//basePath = basePath.substr(0, basePath.length() - 12);
	//basePath += input;
	//basePath=input;
	char* path;
	path = &input[0];
	//std::cout<<path<<"\n";
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture); 
	stbi_set_flip_vertically_on_load(true); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}



void generateBufferData(GLuint* inputAB,GLuint* inputEAB,GLuint* inputVA,unsigned int bufferSize)
{
	glGenBuffers(1,inputAB);
	glGenBuffers(1,inputEAB);
	glGenVertexArrays(1,inputVA);

	glBindVertexArray(*inputVA);
	glBindBuffer(GL_ARRAY_BUFFER,*inputAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*inputEAB);

	glBufferData(GL_ARRAY_BUFFER,bufferSize*32*sizeof(GLfloat),nullptr,GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize*6*sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
}

void generateStaticBufferData(GLuint* inputAB,GLuint* inputEAB,GLuint* inputVA,nodes* inputVertices,indices* inputIndices,unsigned int bufferSize)
{
	glGenBuffers(1,inputAB);
	glGenBuffers(1,inputEAB);
	glGenVertexArrays(1,inputVA);

	glBindVertexArray(*inputVA);
	glBindBuffer(GL_ARRAY_BUFFER,*inputAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*inputEAB);

	glBufferData(GL_ARRAY_BUFFER,bufferSize*32*sizeof(GLfloat),inputVertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize*6*sizeof(unsigned int), inputIndices, GL_STATIC_DRAW);
}
