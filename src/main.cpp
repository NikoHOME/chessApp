#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "board.h"

#include<chrono>

#define checktime sc::duration_cast<sc::milliseconds>(sc::system_clock::now().time_since_epoch()).count()


namespace sc=std::chrono;

Board chessBoard;

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos.x,pos.y,pos.z,1.0f);\n"
    "   outColor = color;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "in vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   fragColor = vec4(outColor, 1.0f);\n"
    "}\n\0";

int main()
{	
	
	glfwInit();

	//tell glfw what versions we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	int resolutionX=1000,resolutionY=800;
	float resulutionRatio = (float)resolutionY/(float)resolutionX;
	std::cout<<resulutionRatio<<"\n";
	
	//create window and select it
	GLFWwindow* window = glfwCreateWindow(resolutionX,resolutionY,"chess",NULL,NULL);
	if(window == NULL) {std::cout<<"Failed to create window\n"; glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);

	//load glad
	gladLoadGL();

	//tell it the render dimensions
	glViewport(0,0,resolutionX,resolutionY);
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);


	//create shader program
	GLuint shaderProgram = glCreateProgram();
	
	//attach shader
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	// White Pieces
	//	0-7 Pawns  8-9 Knights 10-11 Bishops 12-13 Rooks 14 Queen 15 King
	// Black Pieces
	//	16-23 Pawns  24-25 Knights 26-27 Bishops 28-29 Rooks 30 Queen 31 King

	chessBoard.Debug();



	for(int j=0;j<32;++j) 
	{
		if(chessBoard.Pieces[j].isOnBoard) 
		{
			chessBoard.Pieces[j].updateLegalMoves();
		}
	}
	struct vec3
	{
		GLfloat x,y,z;
	};


	struct nodes{
		GLfloat x1,y1,z1; vec3 colour1;
		GLfloat x2,y2,z2; vec3 colour2;
		GLfloat x3,y3,z3; vec3 colour3;
		GLfloat x4,y4,z4; vec3 colour4;

	};
	struct indices{

		unsigned int i1,i2,i3,i4,i5,i6;

	};

	float incrementY = 0.225f;
	float incrementX = incrementY*resulutionRatio;
	float paddingY = 0.025;
	float paddingX = paddingY*resulutionRatio;

	float 	baseX1=-0.9f*resulutionRatio,	baseX2=baseX1+incrementX,
			baseY1=-0.9f,					baseY2=baseY1+incrementY;

	vec3 pieceColour,
	whitePieceColour={1.0f,1.0f,1.0f},
	blackPieceColour={0.1f,0.1f,0.1f},
	boardColour={1.0f,1.0f,1.0f};

	nodes boardVertices[] = 
	{
		{baseX1,baseY1,0.0f,	boardColour,
		baseX1,-baseY1,0.0f,	boardColour,
		-baseX1,-baseY1,0.0f,	boardColour,
		-baseX1,baseY1,0.0f, 	boardColour}
	};
	std::vector <nodes> pieceVertices,legalsVertices;
	std::vector <indices> pieceIndices,legalsIndices;

	GLuint piecesAB,piecesEAB,piecesVA,boardAB,boardVA,legalsAB,legalsEAB,legalsVA;

	glGenVertexArrays(1,&boardVA);
	glGenBuffers(1,&boardAB);

	glBindVertexArray(boardVA);
	glBindBuffer(GL_ARRAY_BUFFER,boardAB);

	glBufferData(GL_ARRAY_BUFFER,24*sizeof(GLfloat),boardVertices,GL_STATIC_DRAW);
	auto tempSiz=sizeof(char)*16;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(GLfloat), (void*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);





	glGenBuffers(1,&piecesAB);
	glGenBuffers(1,&piecesEAB);
	glGenVertexArrays(1,&piecesVA);

	glBindVertexArray(piecesVA);
	glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,piecesEAB);

	glBufferData(GL_ARRAY_BUFFER,64*24*sizeof(GLfloat),nullptr,GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 64*6*sizeof(int), nullptr, GL_DYNAMIC_DRAW);


	glGenBuffers(1,&legalsAB);
	glGenBuffers(1,&legalsEAB);
	glGenVertexArrays(1,&legalsVA);

	glBindVertexArray(legalsVA);
	glBindBuffer(GL_ARRAY_BUFFER,legalsAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,legalsEAB);

	glBufferData(GL_ARRAY_BUFFER,30*24*sizeof(GLfloat),nullptr,GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 30*6*sizeof(int), nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	

	float posX,posY;
	for(int i=0;i<32;++i)
	{
		posX=chessBoard.Pieces[i].posX*incrementX;
        posY=chessBoard.Pieces[i].posY*incrementY;
		if(chessBoard.Pieces[i].type%10==0) pieceColour=whitePieceColour;
		else pieceColour=blackPieceColour;
		pieceVertices.push_back
		({
			baseX1+posX+paddingX, baseY1+posY+paddingY, 0.0f, pieceColour,
            baseX1+posX+paddingX, baseY2+posY-paddingY, 0.0f, pieceColour,
            baseX2+posX-paddingX, baseY2+posY-paddingY, 0.0f, pieceColour,
            baseX2+posX-paddingX, baseY1+posY+paddingY, 0.0f, pieceColour		
		});
    }

	for(unsigned int i=0;i<pieceVertices.size()*4;i+=4)
    {
        pieceIndices.push_back({
        
            i,i+1,i+3,
            i+1,i+3,i+2
		});
        
    }
	
	double windowPosX,windowPosY;
	bool onBoard,onLegal,isSelecting=false;
	int currentSelection=-1,mouseCall,legalSelection=-1,previousSelection=-1;

	int currentTime,previousTime=checktime,blockade;
	int tickspersecond = 1000/5;

	glUseProgram(shaderProgram);

	while(!glfwWindowShouldClose(window))
	{
		


		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(boardVA);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		

		glBindVertexArray(piecesVA);
		glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*pieceVertices.size()*24,&pieceVertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,piecesEAB);	
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*pieceIndices.size()*6,&pieceIndices[0]);

		glDrawElements(GL_TRIANGLES, pieceIndices.size()*6, GL_UNSIGNED_INT,0);


		glBindVertexArray(legalsVA);
		glBindBuffer(GL_ARRAY_BUFFER,legalsAB);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*legalsVertices.size()*24,&legalsVertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,legalsEAB);	
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*legalsIndices.size()*6,&legalsIndices[0]);

		glDrawElements(GL_TRIANGLES, legalsIndices.size()*6, GL_UNSIGNED_INT,0);

		glfwGetCursorPos(window, &windowPosX, &windowPosY);
		windowPosY=resolutionY-windowPosY;
		windowPosX-=resolutionX/2;
		windowPosX*=2;
		windowPosX/=resolutionX;
		windowPosY-=resolutionY/2;
		windowPosY*=2;
		windowPosY/=resolutionY;
		//std::cout<<windowPosX<<" "<<windowPosY<<"\n";
		if(baseX1<=windowPosX && -baseX1>=windowPosX && baseY1<=windowPosY && -baseY1>=windowPosY) onBoard=true;
		mouseCall = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		currentTime=checktime;
		if (mouseCall == GLFW_PRESS && onBoard && currentTime>=previousTime+tickspersecond)
		{	
			previousTime=currentTime;

			if(!isSelecting)
			{
				currentSelection=-1;
				for(int i=0;i<32;++i)
				{

					if( baseX1+chessBoard.Pieces[i].posX*incrementX<=windowPosX && baseX2+chessBoard.Pieces[i].posX*incrementX>=windowPosX &&
					 	baseY1+chessBoard.Pieces[i].posY*incrementY<=windowPosY && baseY2+chessBoard.Pieces[i].posY*incrementY>=windowPosY &&
						chessBoard.Pieces[i].isOnBoard)
					 {
						if(i!=currentSelection)
						{
							//std::cout<<i<<"\n";
							currentSelection=i;
							isSelecting=true;
							break;
						}
					 }
				}
				if(currentSelection!=-1)
				{
					legalsVertices.clear();
					legalsIndices.clear();
					isSelecting=true;
					for(int i=0;i<chessBoard.Pieces[currentSelection].legalMovesAmmount;++i)
					{
						posX=chessBoard.Pieces[currentSelection].legalMoves[i].first*incrementX;
        				posY=chessBoard.Pieces[currentSelection].legalMoves[i].second*incrementY;
						legalsVertices.push_back
						({
							baseX1+posX, baseY1+posY, 0.0f, boardColour, 
        				    baseX1+posX, baseY2+posY, 0.0f, boardColour,
        				    baseX2+posX, baseY2+posY, 0.0f, boardColour,
        				    baseX2+posX, baseY1+posY, 0.0f, boardColour		
						});
					}	

					for(unsigned int i=0;i<legalsVertices.size()*4;i+=4)
    				{
    				   legalsIndices.push_back({

    				        i,i+1,i+3,
    				        i+1,i+3,i+2
						});

    				}
				}
			}
			else
			{
				legalSelection=-1;
				if(legalsVertices.size()==0)
				{
					isSelecting=false;
				}
				for(int i=0;i<legalsVertices.size();++i)
				{
				
					if( legalsVertices[i].x1<=windowPosX && legalsVertices[i].x3>=windowPosX &&
					 	legalsVertices[i].y1<=windowPosY && legalsVertices[i].y3>=windowPosY)
					{
						legalSelection=i;
					}
				}

				if(legalSelection!=-1)
				{
					int tempPosX=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].first,
						tempPosY=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].second;

					short temp = chessBoard.getPieceNumber(tempPosX,tempPosY);
					if(temp!=-1)
					{
						chessBoard.Pieces[temp].isOnBoard=false;
						pieceVertices[temp]=
						{
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour
						};
					}
					
					


					posX=tempPosX*incrementX;
        			posY=tempPosY*incrementY;
					if(chessBoard.Pieces[currentSelection].type%10==0) pieceColour=whitePieceColour;
					else pieceColour=blackPieceColour;
					pieceVertices[currentSelection] =
					{
						baseX1+posX+paddingX, baseY1+posY+paddingY, 0.0f,  pieceColour,
        			    baseX1+posX+paddingX, baseY2+posY-paddingY, 0.0f,  pieceColour,
        			    baseX2+posX-paddingX, baseY2+posY-paddingY, 0.0f,  pieceColour,
        			    baseX2+posX-paddingX, baseY1+posY+paddingY, 0.0f,  pieceColour		
					};
					chessBoard.Pieces[currentSelection].movePiece(tempPosX,tempPosY);
					isSelecting=false;
					legalsVertices.clear();
					legalsIndices.clear();
					if(legalSelection==chessBoard.Pieces[currentSelection].enPassantLegal)
					{
						if(chessBoard.Pieces[currentSelection].type%10==0)	temp = chessBoard.getPieceNumber(tempPosX,tempPosY-1);
						else 												temp = chessBoard.getPieceNumber(tempPosX,tempPosY+1);

						chessBoard.Pieces[temp].isOnBoard=false;
						pieceVertices[temp]=
						{
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour,
							0.0f,0.0f,0.0f, pieceColour
						};
					}
					else if(legalSelection==chessBoard.Pieces[currentSelection].castleLegal)
					{
						if(chessBoard.Pieces[currentSelection].type%10==0)	
						{
							if(tempPosX==2) {temp=12;  tempPosX=3; tempPosY=0;}
							else 			{temp=13;  tempPosX=5; tempPosY=0;}
						}
						else
						{
							if(tempPosX==2) {temp=28;  tempPosX=3; tempPosY=7;}
							else 			{temp=29;  tempPosX=5; tempPosY=7;}
						} 												
						posX=tempPosX*incrementX;
        				posY=tempPosY*incrementY;
						if(chessBoard.Pieces[temp].type%10==0) pieceColour=whitePieceColour;
						else pieceColour=blackPieceColour;
						pieceVertices[temp] =
						{
							baseX1+posX+paddingX, baseY1+posY+paddingY, 0.0f, pieceColour, 
        			    	baseX1+posX+paddingX, baseY2+posY-paddingY, 0.0f, pieceColour,
        			    	baseX2+posX-paddingX, baseY2+posY-paddingY, 0.0f, pieceColour,
        			    	baseX2+posX-paddingX, baseY1+posY+paddingY, 0.0f, pieceColour		
						};
						chessBoard.Pieces[temp].movePiece(tempPosX,tempPosY);
					}

					for(int j=0;j<32;++j) 
					{
						if(chessBoard.Pieces[j].isOnBoard) 
						{
							chessBoard.Pieces[j].updateLegalMoves();
						}
					}
				}
				else
				{
					isSelecting=false;
					legalsVertices.clear();
					legalsIndices.clear();
				}

			}

			
		}


	

		glfwSwapBuffers(window);
		glfwPollEvents();
	
	}
	const GLuint temp[]={piecesAB,piecesEAB,boardAB},temp2[]={piecesVA,boardVA};
	glDeleteBuffers(3,temp);
	glDeleteVertexArrays(2,temp2);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();




	return 0;
}