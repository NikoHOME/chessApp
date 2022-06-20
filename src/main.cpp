#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "board.h"

Board chessBoard;

void UpdatePieces()
{
	for(int j=0;j<32;++j) 
	{
		if(chessBoard.Pieces[j].isOnBoard) 
		{
			chessBoard.Pieces[j].updateLegalMoves();
		}
	}
}




int main()
{	
	
	glfwInit();

	//tell glfw what versions we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	
	//create window and select it
	GLFWwindow* window = glfwCreateWindow(800,600,"chess",NULL,NULL);
	if(window == NULL) {std::cout<<"Failed to create window\n"; glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);

	//load glad
	gladLoadGL();

	//tell it the render dimensions
	glViewport(0,0,800,600);


	// White Pieces
	//	0-7 Pawns  8-9 Knights 10-11 Bishops 12-13 Rooks 14 Queen 15 King
	// Black Pieces
	//	16-23 Pawns  24-25 Knights 26-27 Bishops 28-29 Rooks 30 Queen 31 King

	chessBoard.Debug();

	
	chessBoard.Pieces[20].movePiece(5,4);
	chessBoard.Pieces[0].movePiece(0,2);
	chessBoard.Pieces[12].movePiece(4,4);

	chessBoard.Debug();

	UpdatePieces();


	struct nodes{
		GLfloat x1,y1,z1,
				x2,y2,z2,
				x3,y3,z3,
				x4,y4,z4;

	};
	struct indices{

		unsigned int i1,i2,i3,i4,i5,i6;

	};

	nodes boardVertices[] = 
	{
		{0.9f,0.9f,0.0f,
		0.9f,-0.9f,0.0f,
		-0.9f,-0.9f,0.0f,
		-0.9f,0.9f,0.0f}
	};
	std::vector <nodes> pieceVertices;
	std::vector <indices> pieceIndices;

	GLuint piecesAB,piecesEAB,piecesVA,boardAB,boardVA;

	glGenBuffers(1,&piecesAB);
	glGenBuffers(1,&piecesEAB);
	glGenVertexArrays(1,&piecesVA);

	glBindVertexArray(piecesVA);
	glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,piecesEAB);

	glBufferData(GL_ARRAY_BUFFER,64*3*sizeof(GLfloat),nullptr,GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 64*3*sizeof(int), nullptr, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1,&boardVA);
	glGenBuffers(1,&boardAB);

	glBindVertexArray(boardVA);
	glBindBuffer(GL_ARRAY_BUFFER,boardAB);

	glBufferData(GL_ARRAY_BUFFER,12*sizeof(GLfloat),boardVertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	float increment = 0.225f;
	float posX,posY;
	for(int i=0;i<8;++i) 
    {
        for(int j=0;j<8;++j) 
        {
			switch(chessBoard.getPiece(i,j))
			{
				case 0:
					posX=j*increment;
                	posY=i*increment;
					break;
				case 10: case 11:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;
				case 20: case 21:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;	
				case 30: case 31:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;
				case 40: case 41:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;
				case 50: case 51:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;
				case 60: case 61:
					posX=j*increment;
                	posY=i*increment;
					pieceVertices.push_back
					({
						-0.9f+posX, -0.9f+posY, 0.0f, 
                    	-0.9f+posX, -0.675f+posY, 0.0f,  
                    	-0.675f+posX, -0.675f+posY, 0.0f,
                    	-0.675f+posX, -0.9f+posY, 0.0f
					});
					break;
			}
					
        }
    }

	for(unsigned int i=0;i<pieceVertices.size()*4;i+=4)
    {
        pieceIndices.push_back({
        
            i,i+1,i+3,
            i+1,i+3,i+2
		});
        
    }
	std::cout<<pieceIndices.size()<<"\n";
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.00f,0.5f,0.5f,1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(boardVA);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		
		
		glBindVertexArray(piecesVA);
		glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*pieceVertices.size()*12,&pieceVertices[0]);
		glBindBuffer(GL_ARRAY_BUFFER,piecesEAB);	
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*pieceIndices.size()*6,&pieceIndices[0]);
		glDrawElements(GL_TRIANGLES, pieceIndices.size()*6, GL_UNSIGNED_INT,0);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	
	}

	glfwDestroyWindow(window);
	glfwTerminate();




	return 0;
}