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

void PawnW :: updateLegalMoves()
{
    legalMovesAmmount=0;
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
    if(posX!=7) if(parent.getPiece(posX+1,posY+1)!=0)
    {
        legalMoves[legalMovesAmmount]={posX+1,posY+1};
        ++legalMovesAmmount;
    }
    if(posX!=0) if(parent.getPiece(posX-1,posY+1)!=0)
    {
        legalMoves[legalMovesAmmount]={posX-1,posY+1};
        ++legalMovesAmmount;
    }
    
}
void PawnW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,10);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void PawnB :: updateLegalMoves()
{
    legalMovesAmmount=0;
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
    if(posX!=7) if(parent.getPiece(posX+1,posY-1)!=0)
    {
        legalMoves[legalMovesAmmount]={posX+1,posY-1};
        ++legalMovesAmmount;
    }
    if(posX!=0) if(parent.getPiece(posX-1,posY-1)!=0)
    {
        legalMoves[legalMovesAmmount]={posX-1,posY-1};
        ++legalMovesAmmount;
    }
    
}

void PawnB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,11);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void KnightW ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    if((parent.getPiece(tempX,tempY)==0 || parent.getPiece(tempX,tempY)%10==1) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }   
}



void KnightW:: updateLegalMoves()
{
    legalMovesAmmount=0;
    
    condCheck(1,2);
    condCheck(1,-2);
    condCheck(-1,2);
    condCheck(-1,-2);

    condCheck(2,1);
    condCheck(2,-1);
    condCheck(-2,1);
    condCheck(-2,-1);
}

void KnightW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,20);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void KnightB ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    if(parent.getPiece(tempX,tempY)%10==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }   
}


void KnightB:: updateLegalMoves()
{
    legalMovesAmmount=0;
    
    condCheck(1,2);
    condCheck(1,-2);
    condCheck(-1,2);
    condCheck(-1,-2);

    condCheck(2,1);
    condCheck(2,-1);
    condCheck(-2,1);
    condCheck(-2,-1);
}

void KnightB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,21);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void BishopW ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==1)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}

void BishopW :: updateLegalMoves()
{
    legalMovesAmmount=0;

    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);
    
}

void BishopW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,30);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void BishopB ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}

void BishopB :: updateLegalMoves()
{
    legalMovesAmmount=0;
    
    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);
}

void BishopB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,31);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}


void RookW ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==1)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}


void RookW :: updateLegalMoves()
{
    legalMovesAmmount=0;

    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);

}

void RookW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,40);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void RookB ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}

void RookB :: updateLegalMoves()
{
    legalMovesAmmount=0;


    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);
}

void RookB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,41);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void QueenW ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==1)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}

void QueenW :: updateLegalMoves()
{
    legalMovesAmmount=0;


    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);

    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);

}

void QueenW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,50);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void QueenB ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
        tempX+=addX;
        tempY+=addY;
    }   
    if(parent.getPiece(tempX,tempY)%10==0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }
}

void QueenB :: updateLegalMoves()
{
    legalMovesAmmount=0;


    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);

    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);

}

void QueenB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,51);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void KingW ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    if((parent.getPiece(tempX,tempY)==0 || parent.getPiece(tempX,tempY)%10==1) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }    
}

void KingW :: updateLegalMoves()
{
    legalMovesAmmount=0;
    
    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);

    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);
}

void KingW :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,60);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}

void KingB ::condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    if(parent.getPiece(tempX,tempY)%10==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
    {
        legalMoves[legalMovesAmmount]={tempX,tempY};
        ++legalMovesAmmount;
    }   
}

void KingB :: updateLegalMoves()
{
    legalMovesAmmount=0;
    
    condCheck(1,0);
    condCheck(-1,0);
    condCheck(0,1);
    condCheck(0,-1);

    condCheck(1,1);
    condCheck(1,-1);
    condCheck(-1,1);
    condCheck(-1,-1);
}

void KingB :: movePiece(short x, short y)
{
    parent.updateBoard(x,y,61);
    parent.updateBoard(posX,posY,0);
    posX=x;
    posY=y;
    updateLegalMoves();
}
