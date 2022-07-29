#define GLFW_DLL
#define STB_IMAGE_IMPLEMENTATION

#include <windows.h>
#include "board.h"
#include "logic.h"

Board chessBoard;


int 	resolutionX=1200,resolutionY=900;
float 	resulutionRatio = (float)resolutionY/(float)resolutionX;
float 	incrementY = 0.225f;
float 	incrementX = incrementY*resulutionRatio;
float 	paddingY = 0.025;
float 	paddingX = paddingY*resulutionRatio;

GLfloat baseX1=-0.9f,
		baseX2=baseX1+incrementX,
		baseX3=baseX1+incrementX*8,
		baseX4=baseX3+incrementX/2,
		baseY1=-0.9f,
		baseY2=baseY1+incrementY;
vec2	cord1 = {0.0f,0.0f},
		cord2 = {0.0f,1.0f},
		cord3 = {1.0f,1.0f},
		cord4 = {1.0f,0.0f};

vec3 baseWhite={1.0f,1.0f,1.0f};

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

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec3 color;\n"
	"layout (location = 2) in vec2 textureCord;\n"
    "out vec3 outColor;\n"
	"out vec2 outTextureCord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos,1.0f);\n"
    "   outColor = color;\n"
	"   outTextureCord = vec2(textureCord);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "in vec3 outColor;\n"
	"in vec2 outTextureCord;\n"

	"uniform sampler2D outTexture;\n"
    "void main()\n"
    "{\n"
    "   fragColor = texture(outTexture, outTextureCord)*vec4(outColor, 1.0) ;\n"
//    "   fragColor = vec4(outColor, 1.0);\n"
    "}\n\0";



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

std::vector <nodes> pieceVertices,legalsVertices;
std::vector <indices> pieceIndices,legalsIndices;

// Declare runtime variables
double windowPosX,windowPosY;
bool onBoard,onLegal,isSelecting=false,isWhiteTurn=true,boardChanged=true;
short currentSelection=-1,legalSelection=-1,previousSelection=-1,tempmin,tempmax;
short tickspersecond = 1000/5;

float posX,posY;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//chessBoard.Debug();
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    	if(!isSelecting)
		{
			currentSelection=-1;
			if(isWhiteTurn)
			{
				tempmin=0;
				tempmax=16;
			}
			else
			{
				tempmin=16;
				tempmax=32;
			}
			for(short i=tempmin;i<tempmax;++i)
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
				boardChanged=true;
				for(int i=0;i<chessBoard.Pieces[currentSelection].legalMovesAmmount;++i)
				{
					posX=chessBoard.Pieces[currentSelection].legalMoves[i].first*incrementX;
    				posY=chessBoard.Pieces[currentSelection].legalMoves[i].second*incrementY;
					legalsVertices.push_back
					({
						square(posX,posY,baseWhite)	
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
				isWhiteTurn=!isWhiteTurn;
				boardChanged=true;
				// Check if we are taking a piece
				int tempPosX=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].first,
					tempPosY=chessBoard.Pieces[currentSelection].legalMoves[legalSelection].second;
				short temp = chessBoard.getPieceNumber(tempPosX,tempPosY);
				// If so remove it from the board
				if(temp!=-1)
				{
					chessBoard.Pieces[temp].isOnBoard=false;
					chessBoard.Pieces[temp].posX=-1;
					chessBoard.Pieces[temp].posY=-1;
					pieceVertices[temp]=
					{
						voidSquare()
					};
				}
				// Move to the selected square
				posX=tempPosX*incrementX;
    			posY=tempPosY*incrementY;

				chessBoard.Pieces[currentSelection].movePiece(tempPosX,tempPosY);
				pieceVertices[currentSelection] =
				{
					paddingSquare(posX,posY,paddingX,paddingY,baseWhite)
				};

				//Reset legal overlay and come back to selecting mode
				isSelecting=false;
				legalsVertices.clear();
				legalsIndices.clear();
				// Check if the move was an en Passant
				if(legalSelection==chessBoard.Pieces[currentSelection].enPassantLegal)
				{
					if(chessBoard.Pieces[currentSelection].colourCond==1)	
					{
						temp = chessBoard.getPieceNumber(tempPosX,tempPosY-1); 	
						chessBoard.updateBoard(tempPosX,tempPosY-1,0);
					}
					else
					{
						temp = chessBoard.getPieceNumber(tempPosX,tempPosY+1);
						chessBoard.updateBoard(tempPosX,tempPosY+1,0);
					} 												
					chessBoard.Pieces[temp].isOnBoard=false;
					chessBoard.Pieces[temp].posX=-1;
					chessBoard.Pieces[temp].posY=-1;
					pieceVertices[temp]=
					{
						voidSquare()
					};
				}
				// Check if the move was a Castle
				else if(legalSelection==chessBoard.Pieces[currentSelection].castleLegal)
				{
					if(chessBoard.Pieces[currentSelection].colourCond==1)	
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


					pieceVertices[temp] =
					{
						paddingSquare(posX,posY,paddingX,paddingY,baseWhite)
					};
					chessBoard.Pieces[temp].movePiece(tempPosX,tempPosY);
				}
				//Check if the move was a promotion
				if(chessBoard.Pieces[currentSelection].type==10 && chessBoard.Pieces[currentSelection].posY == 7)
				{
					chessBoard.Pieces[currentSelection].type=50;
					chessBoard.updateBoard(chessBoard.Pieces[currentSelection].posX,chessBoard.Pieces[currentSelection].posY,50);
				}	
				else if(chessBoard.Pieces[currentSelection].type==11 && chessBoard.Pieces[currentSelection].posY == 0)
				{
					chessBoard.Pieces[currentSelection].type=51;
					chessBoard.updateBoard(chessBoard.Pieces[currentSelection].posX,chessBoard.Pieces[currentSelection].posY,51);
				}
				//chessBoard.Debug();
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
				boardChanged=true;
				legalsVertices.clear();
				legalsIndices.clear();
			}
		}
}




int main()
{	
	
	glfwInit();
	// Tell glfw what versions we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Create window and select it
	GLFWwindow* window = glfwCreateWindow(resolutionX,resolutionY,"chess",NULL,NULL);
	//if(window == NULL) {std::cout<<"Failed to create window\n"; glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);

	// load glad
	gladLoadGL();
	// Enable Blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	// Tell it the render dimensions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Generate vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	// Generate fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	// Texture alligment fix
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Turn Vsync on (for performance)
	//glfwSwapInterval(1);

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
	//chessBoard.Debug();
	// Update pieces legal moves
	for(int j=0;j<32;++j) 
	{
		if(chessBoard.Pieces[j].isOnBoard) 
		{
			chessBoard.Pieces[j].updateLegalMoves();
		}
	}
	// Create baord
	vec3 boardColour = {0.9f,0.9f,0.9f};
	indices baseIndices[6] = 
	{
		0,1,3,
		1,3,2	
	};
	nodes boardVertices[] = 
	{
		baseX1, baseY1, 0.0f, boardColour, cord1,
        baseX1, -baseY1, 0.0f, boardColour, cord2,
        baseX3,-baseY1, 0.0f, boardColour, cord3,
        baseX3, baseY1, 0.0f, boardColour, cord4	
	};
	// Create Button Tray
	vec3 trayColour = {0.4f,0.4f,0.4f};
	nodes trayVertices[] = 
	{
		baseX4, baseY1, 0.0f, trayColour, cord1,
        baseX4, -baseY1, 0.0f, trayColour, cord2,
        -baseX1,-baseY1, 0.0f, trayColour, cord3,
        -baseX1, baseY1, 0.0f, trayColour, cord4	
	};
	// Declare GL objects
	GLuint piecesAB,piecesEAB,piecesVA,boardAB,boardVA,boardEAB,legalsAB,legalsEAB,legalsVA,trayAB,trayEAB,trayVA;

	GLuint whitePawn,blackPawn,
	whiteBishop,blackBishop,
	whiteKnight,blackKnight,
	whiteKing,blackKing,
	whiteQueen,blackQueen,
	whiteRook,blackRook,
	legalDot,blank,boardImage;

	// Create all textures
	addTexture(&whitePawn,"../img/pawnW.png");
	addTexture(&blackPawn,"../img/pawnB.png");
	addTexture(&whiteKnight,"../img/knightW.png");
	addTexture(&blackKnight,"../img/knightB.png");
	addTexture(&whiteBishop,"../img/bishopW.png");
	addTexture(&blackBishop,"../img/bishopB.png");
	addTexture(&whiteKing,"../img/kingW.png");
	addTexture(&blackKing,"../img/kingB.png");
	addTexture(&whiteQueen,"../img/queenW.png");
	addTexture(&blackQueen,"../img/queenB.png");
	addTexture(&whiteRook,"../img/rookW.png");
	addTexture(&blackRook,"../img/rookB.png");
	addTexture(&legalDot,"../img/dot.png");
	addTexture(&blank,"../img/blank.png");
	addTexture(&boardImage,"../img/chessBoard.png");
	
	// Generate draw data
	generateStaticBufferData(&boardAB,&boardEAB,&boardVA,boardVertices,baseIndices,1);
	generateStaticBufferData(&trayAB,&trayEAB,&trayVA,trayVertices,baseIndices,1);
	generateBufferData(&piecesAB,&piecesEAB,&piecesVA,64);
	generateBufferData(&legalsAB,&legalsEAB,&legalsVA,32);


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	// Create starting pieces

	for(int i=0;i<32;++i)
	{
		posX=chessBoard.Pieces[i].posX*incrementX;
        posY=chessBoard.Pieces[i].posY*incrementY;


		pieceVertices.push_back
		({
			paddingSquare(posX,posY,paddingX,paddingY,baseWhite)
		});
    }

	for(unsigned int i=0;i<pieceVertices.size()*4;i+=4)
    {
        pieceIndices.push_back({
        
            i,i+1,i+3,
            i+1,i+3,i+2
		});
        
    }
	
	// Select shader and texture
	glUseProgram(shaderProgram);
	//glBindTexture(GL_TEXTURE_2D,whitePawn);

	int whiteLegalsSum=0,blackLegalsSum=0;

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	double lastTime = glfwGetTime(),frameRate=60,currentTime;
	int nbFrames = 0;

	while(!glfwWindowShouldClose(window))
	{
		// Limit Draw Rate
		currentTime = glfwGetTime();
		if ( currentTime - lastTime >= 1.0/frameRate ){ // If last prinf() was more than 1 sec ago
			lastTime += 1.0/frameRate;


			// Set basic colour
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Draw board
			if(boardChanged)
			{
				//chessBoard.Debug();
				glBindVertexArray(boardVA);
				glBindTexture(GL_TEXTURE_2D, boardImage);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);

				glBindVertexArray(trayVA);
				glBindTexture(GL_TEXTURE_2D,blank);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);



				// Update pieces data
				glBindVertexArray(piecesVA);
				glBindBuffer(GL_ARRAY_BUFFER,piecesAB);
				glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*pieceVertices.size()*32,&pieceVertices[0]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,piecesEAB);	
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*pieceIndices.size()*6,&pieceIndices[0]);

				// Draw pieces
				for(int i=0;i<8;++i)
				{
					switch(chessBoard.Pieces[i].type)
					{
						case 10:
							glBindTexture(GL_TEXTURE_2D, whitePawn);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 20:
							glBindTexture(GL_TEXTURE_2D, whiteKnight);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 30:
							glBindTexture(GL_TEXTURE_2D, whiteBishop);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 40:
							glBindTexture(GL_TEXTURE_2D, whiteRook);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 50:
							glBindTexture(GL_TEXTURE_2D, whiteQueen);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
					}
				}
				glBindTexture(GL_TEXTURE_2D, whiteKnight);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(8*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, whiteBishop);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(10*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, whiteRook);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(12*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, whiteQueen);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(14*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, whiteKing);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(15*sizeof(indices)));

				for(int i=16;i<24;++i)
				{
					switch(chessBoard.Pieces[i].type)
					{
						case 11:
							glBindTexture(GL_TEXTURE_2D, blackPawn);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 21:
							glBindTexture(GL_TEXTURE_2D, blackKnight);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 31:
							glBindTexture(GL_TEXTURE_2D, blackBishop);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 41:
							glBindTexture(GL_TEXTURE_2D, blackRook);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
						case 51:
							glBindTexture(GL_TEXTURE_2D, blackQueen);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(i*sizeof(indices)));
							break;
					}
				}
				glBindTexture(GL_TEXTURE_2D, blackKnight);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(24*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, blackBishop);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(26*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, blackRook);
				glDrawElements(GL_TRIANGLES, 2*6, GL_UNSIGNED_INT,(void*)(28*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, blackQueen);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(30*sizeof(indices)));
				glBindTexture(GL_TEXTURE_2D, blackKing);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)(31*sizeof(indices)));
				//glBindTexture(GL_TEXTURE_2D,0);

				// Update legal moves overlay data
				glBindVertexArray(legalsVA);
				glBindBuffer(GL_ARRAY_BUFFER,legalsAB);
				glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(GLfloat)*legalsVertices.size()*32,&legalsVertices[0]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,legalsEAB);	
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(unsigned int)*legalsIndices.size()*6,&legalsIndices[0]);

				// Draw legal moves
				//glBindTexture(GL_TEXTURE_2D, 1.0f);
				glBindTexture(GL_TEXTURE_2D, legalDot);
				glDrawElements(GL_TRIANGLES, legalsIndices.size()*6, GL_UNSIGNED_INT,0);
				glBindTexture(GL_TEXTURE_2D,0);

				// Swap buffers
				std::cout<<chessBoard.whiteKingInCheck<<" "<<chessBoard.blackKingInCheck<<"\n";
				glfwSwapBuffers(window);
				boardChanged=false;
			}

			// Get cursor possition and check if is on the board
			glfwGetCursorPos(window, &windowPosX, &windowPosY);

			windowPosY=resolutionY-windowPosY;
			windowPosX-=resolutionX/2;	windowPosX*=2;	windowPosX/=resolutionX;
			windowPosY-=resolutionY/2;	windowPosY*=2;	windowPosY/=resolutionY;

			if(baseX1<=windowPosX && -baseX1>=windowPosX && baseY1<=windowPosY && -baseY1>=windowPosY) onBoard=true;

			if(chessBoard.whiteKingInCheck)
			{
				whiteLegalsSum=0;
				for(int i=0;i<16;++i)
				{
					whiteLegalsSum+=chessBoard.Pieces[i].legalMovesAmmount;
				}
				if(whiteLegalsSum==0) 
				{
					std::cout<<"CHECKMATE - Black Won\n";
					break;
				}
			}
			else if(chessBoard.blackKingInCheck)
			{
				blackLegalsSum=0;
				for(int i=16;i<32;++i)
				{
					blackLegalsSum+=chessBoard.Pieces[i].legalMovesAmmount;
				}
				if(blackLegalsSum==0) 
				{
					std::cout<<"CHECKMATE - White Won\n";
					break;
				}			
			}

		}
		 



		//Call events
		glfwPollEvents();
		Sleep(1);
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

