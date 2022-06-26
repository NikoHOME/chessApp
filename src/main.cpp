#define GLFW_DLL
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include <iostream>

#include "board.h"

#include<chrono>

#define checktime sc::duration_cast<sc::milliseconds>(sc::system_clock::now().time_since_epoch()).count()


namespace sc=std::chrono;

Board chessBoard;

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec3 color;\n"
	"layout (location = 2) in vec2 textureCord;\n"
    "out vec3 outColor;\n"
	"out vec2 outTextureCord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos.x,pos.y,pos.z,1.0f);\n"
    "   outColor = color;\n"
	"   outTextureCord = vec2(textureCord.x,textureCord.y);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "in vec3 outColor;\n"
	"in vec2 outTextureCord;\n"

	"uniform sampler2D outTexture;\n"
    "void main()\n"
    "{\n"
    "   fragColor = texture(outTexture, outTextureCord) * vec4(outColor, 1.0);\n"
//    "   fragColor = vec4(outColor, 1.0);\n"
    "}\n\0";

// Generate texture
void addTexture(GLuint* texture,std::string input)
{
	char* path;
	path = &input[0];
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}
// Generate Components for rendering
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





// Vec3 for colour
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

//Global variables
int 	resolutionX=1000,resolutionY=800;
float 	resulutionRatio = (float)resolutionY/(float)resolutionX;
float 	incrementY = 0.225f;
float 	incrementX = incrementY*resulutionRatio;
float 	paddingY = 0.025;
float 	paddingX = paddingY*resulutionRatio;

GLfloat baseX1=-0.9f*resulutionRatio,
		baseX2=baseX1+incrementX,
		baseY1=-0.9f,
		baseY2=baseY1+incrementY;
vec2	cord1 = {0.0f,0.0f},
		cord2 = {0.0f,1.0f},
		cord3 = {1.0f,1.0f},
		cord4 = {1.0f,0.0f};
//Create object draw information
nodes square(GLfloat X,GLfloat Y,vec3 colour)
{
	return						
	{
		baseX1+X, baseY1+Y, 0.0f, colour, cord1,
        baseX1+X, baseY2+Y, 0.0f, colour, cord2,
        baseX2+X, baseY2+Y, 0.0f, colour, cord3,
        baseX2+X, baseY1+Y, 0.0f, colour, cord4		
	};
}
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
}
//Create object information with padding
nodes paddingSquare(GLfloat X,GLfloat Y,GLfloat pX,GLfloat pY, vec3 colour)
{
	return						
	{
		baseX1+X+pX, baseY1+Y+pY, 0.0f, colour, cord1,
    	baseX1+X+pX, baseY2+Y-pY, 0.0f, colour, cord2,
    	baseX2+X-pX, baseY2+Y-pY, 0.0f, colour, cord3,
    	baseX2+X-pX, baseY1+Y+pY, 0.0f, colour, cord4	
	};
}

int main()
{	
	
	glfwInit();

	// Tell glfw what versions we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);




	
	// Create window and select it
	GLFWwindow* window = glfwCreateWindow(resolutionX,resolutionY,"chess",NULL,NULL);
	if(window == NULL) {std::cout<<"Failed to create window\n"; glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);

	// load glad
	gladLoadGL();

	// Tell it the render dimensions
	glViewport(0,0,resolutionX,resolutionY);
	
	// Generate vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	// Generate fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);


	// Create shader program
	GLuint shaderProgram = glCreateProgram();
	
	// Attach shaders
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


	// Update pieces legal moves
	for(int j=0;j<32;++j) 
	{
		if(chessBoard.Pieces[j].isOnBoard) 
		{
			chessBoard.Pieces[j].updateLegalMoves();
		}
	}




	vec3 pieceColour,
	whitePieceColour={1.0f,1.0f,1.0f},
	boardColour={1.0f,1.0f,1.0f};

	//1.0f, 1.0f, // top right
	//1.0f, 0.0f, // bottom right
	// 0.0f, 0.0f, // bottom left
	//  0.0f, 1.0f  // top left 

	// Create baord
	nodes boardVertices[] = 
	{
		baseX1, baseY1, 0.0f, boardColour, cord1,
        baseX1, -baseY1, 0.0f, boardColour, cord2,
        -baseX1,-baseY1, 0.0f, boardColour, cord3,
        -baseX1, baseY1, 0.0f, boardColour, cord4	
	};
	// Declare GL objects
	std::vector <nodes> pieceVertices,legalsVertices;
	std::vector <indices> pieceIndices,legalsIndices;

	GLuint piecesAB,piecesEAB,piecesVA,boardAB,boardVA,legalsAB,legalsEAB,legalsVA;

	GLuint whitePawn,blackPawn,
	whiteBishop,blackBishop,
	whiteKnight,blackKnight,
	whiteKing,blackKing,
	whiteQueen,blackQueen,
	whiteRook,blackRook;

	// Create all textures
	addTexture(&whitePawn,"img/pawnW.png");
	addTexture(&blackPawn,"img/pawnB.png");
	addTexture(&whiteKnight,"img/knightW.png");
	addTexture(&blackKnight,"img/knightB.png");
	addTexture(&whiteBishop,"img/bishopW.png");
	addTexture(&blackBishop,"img/bishopB.png");
	addTexture(&whiteKing,"img/kingW.png");
	addTexture(&blackKing,"img/kingB.png");
	addTexture(&whiteQueen,"img/queenW.png");
	addTexture(&blackQueen,"img/queenB.png");
	addTexture(&whiteRook,"img/rookW.png");
	addTexture(&blackRook,"img/rookB.png");
	
	// Generate board draw data

	glGenVertexArrays(1,&boardVA);
	glGenBuffers(1,&boardAB);

	glBindVertexArray(boardVA);
	glBindBuffer(GL_ARRAY_BUFFER,boardAB);

	glBufferData(GL_ARRAY_BUFFER,32*sizeof(GLfloat),boardVertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (void*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	// Generate dynamic draw data
	generateBufferData(&piecesAB,&piecesEAB,&piecesVA,64);
	generateBufferData(&legalsAB,&legalsEAB,&legalsVA,32);


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	// Create starting pieces
	float posX,posY;
	for(int i=0;i<32;++i)
	{
		posX=chessBoard.Pieces[i].posX*incrementX;
        posY=chessBoard.Pieces[i].posY*incrementY;
		pieceColour=whitePieceColour;

		pieceVertices.push_back
		({
			paddingSquare(posX,posY,paddingX,paddingY,pieceColour)
		});
    }

	for(unsigned int i=0;i<pieceVertices.size()*4;i+=4)
    {
        pieceIndices.push_back({
        
            i,i+1,i+3,
            i+1,i+3,i+2
		});
        
    }
	// Declare runtime variables
	double windowPosX,windowPosY;
	bool onBoard,onLegal,isSelecting=false;
	int currentSelection=-1,mouseCall,legalSelection=-1,previousSelection=-1;

	int currentTime,previousTime=checktime,blockade;
	int tickspersecond = 1000/5;
	
	// Select shader and texture
	glUseProgram(shaderProgram);

	while(!glfwWindowShouldClose(window))
	{
		// Set basic colour
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw board
		glBindVertexArray(boardVA);
		glBindTexture(GL_TEXTURE_2D, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);	

		
		// Update pieces data
		glBindVertexArray(piecesVA);
		glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*pieceVertices.size()*32,&pieceVertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,piecesEAB);	
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*pieceIndices.size()*6,&pieceIndices[0]);

		// Draw pieces
        glBindTexture(GL_TEXTURE_2D, whitePawn);
		glDrawElements(GL_TRIANGLES, pieceIndices.size()*6, GL_UNSIGNED_INT,0);
		glBindTexture(GL_TEXTURE_2D,0);

		// Update legal moves overlay data
		glBindVertexArray(legalsVA);
		glBindBuffer(GL_ARRAY_BUFFER,legalsAB);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*legalsVertices.size()*32,&legalsVertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,legalsEAB);	
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*legalsIndices.size()*6,&legalsIndices[0]);

		// Draw legal moves
		glBindTexture(GL_TEXTURE_2D, 1.0f);
		glDrawElements(GL_TRIANGLES, legalsIndices.size()*6, GL_UNSIGNED_INT,0);
		glBindTexture(GL_TEXTURE_2D,0);

		// Get cursor possition and check if is on the board
		glfwGetCursorPos(window, &windowPosX, &windowPosY);

		windowPosY=resolutionY-windowPosY;
		windowPosX-=resolutionX/2;	windowPosX*=2;	windowPosX/=resolutionX;
		windowPosY-=resolutionY/2;	windowPosY*=2;	windowPosY/=resolutionY;

		if(baseX1<=windowPosX && -baseX1>=windowPosX && baseY1<=windowPosY && -baseY1>=windowPosY) onBoard=true;

		mouseCall = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		currentTime=checktime;

		if (mouseCall == GLFW_PRESS && onBoard && currentTime>=previousTime+tickspersecond)
		{	
			// Set delay for next click
			previousTime=currentTime;
			// Select a piece from clicked tile
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
				// If found display legal moves
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
							square(posX,posY,boardColour)	
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
			// If piece is alredy selected check whith move is chosen
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
				// If move was chosen move the piece
				if(legalSelection!=-1)
				{
					// Check if we are taking a piece
					int tempPosX=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].first,
						tempPosY=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].second;

					short temp = chessBoard.getPieceNumber(tempPosX,tempPosY);
					// If so remove it from the board
					if(temp!=-1)
					{
						chessBoard.Pieces[temp].isOnBoard=false;
						pieceVertices[temp]=
						{
							voidSquare()
						};
					}
					// Move to the selected square
					posX=tempPosX*incrementX;
        			posY=tempPosY*incrementY;
					pieceColour=whitePieceColour;

					pieceVertices[currentSelection] =
					{
						paddingSquare(posX,posY,paddingX,paddingY,pieceColour)
					};
					chessBoard.Pieces[currentSelection].movePiece(tempPosX,tempPosY);
					//Reset legal overlay and come back to selecting mode
					isSelecting=false;
					legalsVertices.clear();
					legalsIndices.clear();
					// Check if the move was an en Passant
					if(legalSelection==chessBoard.Pieces[currentSelection].enPassantLegal)
					{
						if(chessBoard.Pieces[currentSelection].type%10==0)	temp = chessBoard.getPieceNumber(tempPosX,tempPosY-1);
						else 												temp = chessBoard.getPieceNumber(tempPosX,tempPosY+1);

						chessBoard.Pieces[temp].isOnBoard=false;
						pieceVertices[temp]=
						{
							voidSquare()
						};
					}
					// Check if the move was a Castle
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
						pieceColour=whitePieceColour;
	
						pieceVertices[temp] =
						{
							paddingSquare(posX,posY,paddingX,paddingY,pieceColour)
						};
						chessBoard.Pieces[temp].movePiece(tempPosX,tempPosY);
					}
					// Update legal moves
					for(int j=0;j<32;++j) 
					{
						if(chessBoard.Pieces[j].isOnBoard) 
						{
							chessBoard.Pieces[j].updateLegalMoves();
						}
					}
				}
				//If no move was chosen come back to selection mode
				else
				{
					isSelecting=false;
					legalsVertices.clear();
					legalsIndices.clear();
				}

			}

			
		}
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	
	}
	// Delete draw objects
	const GLuint temp[]={piecesAB,piecesEAB,boardAB},temp2[]={piecesVA,boardVA};
	glDeleteBuffers(3,temp);
	glDeleteVertexArrays(2,temp2);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();




	return 0;
}