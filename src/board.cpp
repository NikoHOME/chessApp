#include "board.h"
#include <iostream>

short Board::getPiece(short x, short y)
{
    return tab[x][y];
}

void Board :: updateBoard(short x,short y,short value)
{
    tab[x][y]=value;
}

void Board ::Debug()
{
    for(int i=7;i>=0;--i) 
    {   
        for(int j=0;j<8;++j)
        {
            switch(tab[j][i])
            {
                case 0:
                    std::cout<<"-  ";
                    break;
                case 10:
                    std::cout<<"Pw ";
                    break;
                case 11:
                    std::cout<<"Pb ";
                    break;
                case 20:
                    std::cout<<"Nw ";
                    break;
                case 21:
                    std::cout<<"Nb ";
                    break;
                case 30:
                    std::cout<<"Bw ";
                    break;
                case 31:
                    std::cout<<"Bb ";
                    break;
                case 40:
                    std::cout<<"Rw ";
                    break;
                case 41:
                    std::cout<<"Rb ";
                    break;
                case 50:
                    std::cout<<"Qw ";
                    break;
                case 51:
                    std::cout<<"Qb ";
                    break;
                case 60:
                    std::cout<<"Kw ";
                    break;
                case 61:
                    std::cout<<"Kb ";
                    break;
            }
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}


void Piece :: condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    switch(type)
    {
        case 20: case 21: case 60: case 61:
            
            if((parent.getPiece(tempX,tempY)==0 || parent.getPiece(tempX,tempY)%10==colourCond) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                legalMoves[legalMovesAmmount]={tempX,tempY};
                ++legalMovesAmmount;
            }
            break;
        default:    
            while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                legalMoves[legalMovesAmmount]={tempX,tempY};
                ++legalMovesAmmount;
                tempX+=addX;
                tempY+=addY;
            }   
            if(parent.getPiece(tempX,tempY)%10==colourCond && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                legalMoves[legalMovesAmmount]={tempX,tempY};
                ++legalMovesAmmount;
            }   
            break;         
           

    }

}


void Piece :: updateLegalMoves()
{
    legalMovesAmmount=0;

    switch(type)
    {
        case 10:
            if(parent.getPiece(posX,posY+1)==0)
            {
                legalMoves[legalMovesAmmount]={posX,posY+1};
                ++legalMovesAmmount;
            }
            if(parent.getPiece(posX,posY+2)==0 && posY==1)
            {
                legalMoves[legalMovesAmmount]={posX,posY+2};
                ++legalMovesAmmount;
            }
            if(posX!=7) if(parent.getPiece(posX+1,posY+1)!=0 && parent.getPiece(posX+1,posY+1)%10==colourCond)
            {
                legalMoves[legalMovesAmmount]={posX+1,posY+1};
                ++legalMovesAmmount;
            }
            if(posX!=0) if(parent.getPiece(posX-1,posY+1)!=0 && parent.getPiece(posX-1,posY+1)%10==colourCond)
            {
                legalMoves[legalMovesAmmount]={posX-1,posY+1};
                ++legalMovesAmmount;
            }
            break;
        case 11:
            if(parent.getPiece(posX,posY-1)==0)
            {
                legalMoves[legalMovesAmmount]={posX,posY-1};
                ++legalMovesAmmount;
            }
            if(parent.getPiece(posX,posY-2)==0 && posY==6)
            {
                legalMoves[legalMovesAmmount]={posX,posY-2};
                ++legalMovesAmmount;
            }
            if(posX!=0) if(parent.getPiece(posX-1,posY-1)!=0 && parent.getPiece(posX-1,posY-1)%10==colourCond)
            {
                legalMoves[legalMovesAmmount]={posX-1,posY-1};
                ++legalMovesAmmount;
            }
            if(posX!=7) if(parent.getPiece(posX+1,posY-1)!=0 && parent.getPiece(posX+1,posY-1)%10==colourCond)
            {
                legalMoves[legalMovesAmmount]={posX+1,posY-1};
                ++legalMovesAmmount;
            }
            break;
        case 20: case 21:
            condCheck(1,2);
            condCheck(1,-2);
            condCheck(-1,2);
            condCheck(-1,-2);

            condCheck(2,1);
            condCheck(2,-1);
            condCheck(-2,1);
            condCheck(-2,-1);   
            break;
        case 30: case 31:
            condCheck(1,1);
            condCheck(1,-1);
            condCheck(-1,1);
            condCheck(-1,-1);  
            break;
        case 40: case 41:
            condCheck(1,0);
            condCheck(-1,0);
            condCheck(0,1);
            condCheck(0,-1);
            break;
        case 50: case 51:
            condCheck(1,1);
            condCheck(1,-1);
            condCheck(-1,1);
            condCheck(-1,-1);

            condCheck(1,0);
            condCheck(-1,0);
            condCheck(0,1);
            condCheck(0,-1);
            break;  
        case 60: case 61:
            condCheck(1,1);
            condCheck(1,-1);
            condCheck(-1,1);
            condCheck(-1,-1);

            condCheck(1,0);
            condCheck(-1,0);
            condCheck(0,1);
            condCheck(0,-1);
            break;
    }
}


void Piece :: movePiece(short x, short y)
{    
    parent.updateBoard(x,y,type);
    parent.updateBoard(posX,posY,0);

    posX=x;
    posY=y;
    updateLegalMoves();
    
}


