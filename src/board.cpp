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




bool Piece :: checkCheck(short addX,short addY)
{

    short   kingOffsetX,kingOffsetY,tempPiece,tempPieceType,tempX,tempY;
    if(type%10==0)
    {
        kingOffsetX=parent.Pieces[15].posX-posX;
        kingOffsetY=parent.Pieces[15].posY-posY;
    }
    else
    {
        kingOffsetX=parent.Pieces[31].posX-posX;
        kingOffsetY=parent.Pieces[31].posY-posY;
    }

    
    if(kingOffsetX>0) addX=1;
    else addX=-1;
    if(kingOffsetY>0) addY=1;
    else addY=-1;
    
    if(kingOffsetX==0) addX=0;
    if(kingOffsetY==0) addY=0;




    if( abs(kingOffsetX)==abs(kingOffsetY) || kingOffsetX==0 || kingOffsetY==0)
    {
        tempX=posX+addX;
        tempY=posY+addY;
        while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
        {
            tempX+=addX;
            tempY+=addY;
        }   
        if(colourCond==1)
        {
            addX=-addX;
            addY=-addY;
            std::cout<<parent.getPiece(tempX,tempY)<<"\n";
            if(parent.getPiece(tempX,tempY)==60 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                tempX=posX+addX;
                tempY=posY+addY;
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }
                if(tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0) 
                {
                    tempPiece=parent.getPieceNumber(tempX,tempY);
                    tempPieceType=parent.Pieces[tempPiece].type;
                    if(abs(kingOffsetX)==abs(kingOffsetY) && (tempPieceType==21 || tempPieceType==51))
                    {
                        std::cout<<"ALERT";
                        return true;
                    }
                    else if((kingOffsetX==0 || kingOffsetY==0) && (tempPieceType==51 || tempPieceType==41))
                    {
                        std::cout<<"ALERT";
                        return true;
                    }
                }
            }
        }
        else
        {
            addX=-addX;
            addY=-addY;
            if(parent.getPiece(tempX,tempY)==61 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                tempX+=addX;
                tempY+=addY;
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }
                if(tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0) 
                {
                    tempPiece=parent.getPieceNumber(tempX,tempY);
                }
                if(tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0) 
                {
                    tempPiece=parent.getPieceNumber(tempX,tempY);
                    tempPieceType=parent.Pieces[tempPiece].type;
                    if(abs(kingOffsetX)==abs(kingOffsetY) && (tempPieceType==20 || tempPieceType==50))
                    {
                        std::cout<<"ALERT";
                        return true;
                    }
                    else if((kingOffsetX==0 || kingOffsetY==0) && (tempPieceType==50 || tempPieceType==40))
                    {
                        std::cout<<"ALERT";
                        return true;
                    }
                }
            }   
        }
          
    }
    


    if(type==50) 
    {
         if( abs(kingOffsetX)==abs(kingOffsetY) || kingOffsetX==0 || kingOffsetY==0) std::cout<<kingOffsetX<<" "<<kingOffsetY<<"\n";
    }
    return false;
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
                if(type==50) checkCheck(addX,addY);
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


