#include "board.h"
#include <iostream>

short Board::getPiece(short x, short y)
{
    return tab[x][y];
}

short Board::getPieceNumber(short x, short y)
{

    for(int i=0;i<32;++i)
    {
        if(Pieces[i].posX==x && Pieces[i].posY==y) 
        {
            return i;
        }
    }
    return -1;
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
    enPassantLegal=-1;
    switch(type)
    {
        case 10:
            if(parent.getPiece(posX,posY+1)==0)
            {
                legalMoves[legalMovesAmmount]={posX,posY+1};
                ++legalMovesAmmount;
            }
            if(parent.getPiece(posX,posY+2)==0 && parent.getPiece(posX,posY+1)==0 && posY==1)
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
            //En Peasant
            if(posX!=7 && posY==4) 
            {
                if(parent.getPiece(posX+1,posY)==11 && parent.getPiece(posX+1,posY+1)==0)
                {
                    short temp = parent.getPieceNumber(posX+1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==6)
                    {
                        legalMoves[legalMovesAmmount]={posX+1,posY+1};
                        enPassantLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
            }
            if(posX!=0 && posY==4) 
            {

                if(parent.getPiece(posX-1,posY)==11 && parent.getPiece(posX-1,posY+1)==0)
                {

                    short temp = parent.getPieceNumber(posX-1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==6)
                    {
                        legalMoves[legalMovesAmmount]={posX-1,posY+1};
                        enPassantLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
            }

            break;
        case 11:
            if(parent.getPiece(posX,posY-1)==0)
            {
                legalMoves[legalMovesAmmount]={posX,posY-1};
                ++legalMovesAmmount;
            }
            if(parent.getPiece(posX,posY-2)==0 &&  parent.getPiece(posX,posY-1)==0 && posY==6)
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
            //En peasant
            if(posX!=7 && posY==3) 
            {
                if(parent.getPiece(posX+1,posY)==10 && parent.getPiece(posX+1,posY-1)==0)
                {
                    short temp = parent.getPieceNumber(posX+1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==1)
                    {
                        legalMoves[legalMovesAmmount]={posX+1,posY-1};
                        enPassantLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
            }
            if(posX!=0 && posY==3) 
            {
                if(parent.getPiece(posX-1,posY)==10 && parent.getPiece(posX-1,posY-1)==0)
                {
                    short temp = parent.getPieceNumber(posX-1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==1)
                    {
                        legalMoves[legalMovesAmmount]={posX-1,posY-1};
                        enPassantLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
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

            if(previousPosX==-1)
            {
                if(type==60)
                {
                    if(parent.Pieces[12].previousPosX==-1 && parent.getPiece(1,0)==0 && parent.getPiece(2,0)==0 && parent.getPiece(3,0)==0)
                    {
                        legalMoves[legalMovesAmmount]={2,0};
                        castleLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                    if(parent.Pieces[13].previousPosX==-1 && parent.getPiece(5,0)==0 && parent.getPiece(6,0)==0)
                    {
                        legalMoves[legalMovesAmmount]={6,0};
                        castleLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
                else
                {
                    if(parent.Pieces[28].previousPosX==-1 && parent.getPiece(1,7)==0 && parent.getPiece(2,7)==0 && parent.getPiece(3,7)==0)
                    {
                        legalMoves[legalMovesAmmount]={2,7};
                        castleLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                    if(parent.Pieces[29].previousPosX==-1 && parent.getPiece(5,7)==0 && parent.getPiece(6,7)==0)
                    {
                        legalMoves[legalMovesAmmount]={6,7};
                        castleLegal=legalMovesAmmount;
                        ++legalMovesAmmount;
                    }
                }
            }

            break;
    }
}


void Piece :: movePiece(short x, short y)
{    
    previousPosX=posX;
    previousPosY=posY;
    parent.updateBoard(x,y,type);
    parent.updateBoard(posX,posY,0);
    ++parent.turnNumber;
    lastMoveNumber=parent.turnNumber;
    posX=x;
    posY=y;
    
}


