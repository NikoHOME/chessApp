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


bool Piece :: checkCheckFunc(short addX, short addY, short moveType) //0 pawn //1 knight //2 bishop & queen //3 rook & queen // 3 Digit for King 1st real moveType 2nd kingposX 3rd kingposY
{
    short kingPosX,kingPosY,tempX,tempY;
    if(colourCond==1)
    {
        if(moveType>10)
        {
            kingPosY=moveType%10;
            moveType/=10;
            kingPosX=moveType%10;
            moveType/=10;
        }
        else
        {
            kingPosX=parent.Pieces[15].posX;
            kingPosY=parent.Pieces[15].posY;
        }
        tempX=kingPosX+addX;
        tempY=kingPosY+addY;
        switch(moveType)
        {
            case 0:
                if(parent.getPiece(tempX,tempY)==11  && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }
                break;
            case 1:
                if(parent.getPiece(tempX,tempY)==21  && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }
                break;
            case 2:
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }   
                if((parent.getPiece(tempX,tempY)==31 || parent.getPiece(tempX,tempY)==51) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }  
                break; 
            case 3:
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }   
                if((parent.getPiece(tempX,tempY)==41 || parent.getPiece(tempX,tempY)==51) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }  
                break; 
        }  
    }
    else
    {
        if(moveType>10)
        {
            kingPosY=moveType%10;
            moveType/=10;
            kingPosX=moveType%10;
            moveType/=10;
        }
        else
        {
            kingPosX=parent.Pieces[31].posX;
            kingPosY=parent.Pieces[31].posY;
        }
        tempX=kingPosX+addX;
        tempY=kingPosY+addY;
        switch(moveType)
        {
            case 0:
                if(parent.getPiece(tempX,tempY)==10  && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }
                break;
            case 1:
                if(parent.getPiece(tempX,tempY)==20  && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }
                break;
            case 2:
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }   
                if((parent.getPiece(tempX,tempY)==30 || parent.getPiece(tempX,tempY)==50) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }  
                break; 
            case 3:
                while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    tempX+=addX;
                    tempY+=addY;
                }   
                if((parent.getPiece(tempX,tempY)==40 || parent.getPiece(tempX,tempY)==50) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
                {
                    return true;
                }  
                break; 
        }   
    }
    return  false;
}


bool Piece :: checkChecks(short futureX,short futureY,bool isKing)
{
    short tempType=parent.getPiece(futureX,futureY),moveType=0;
    parent.updateBoard(futureX,futureY,type);
    parent.updateBoard(posX,posY,0);


    if(colourCond==1)
    {
        moveType=0;
        if(isKing)
        {
            moveType*=10;
            moveType+=futureX;
            moveType*=10;
            moveType+=futureY;
        }
        if(checkCheckFunc(1,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
        if(checkCheckFunc(-1,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    }
    else
    {
        moveType=0;
        if(isKing)
        {
            moveType*=10;
            moveType+=futureX;
            moveType*=10;
            moveType+=futureY;
        }
        if(checkCheckFunc(1,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
        if(checkCheckFunc(-1,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    }
    moveType=1;
    if(isKing)
    {
        moveType*=10;
        moveType+=futureX;
        moveType*=10;
        moveType+=futureY;
    }
    if(checkCheckFunc(1,2,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(1,-2,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-1,2,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-1,-2,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}

    if(checkCheckFunc(2,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(2,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-2,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); ;return true;}
    if(checkCheckFunc(-2,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    moveType=2;
    if(isKing)
    {
        moveType*=10;
        moveType+=futureX;
        moveType*=10;
        moveType+=futureY;
    }
    if(checkCheckFunc(1,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(1,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-1,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-1,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    moveType=3;
    if(isKing)
    {
        moveType*=10;
        moveType+=futureX;
        moveType*=10;
        moveType+=futureY;
    }
    if(checkCheckFunc(1,0,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(-1,0,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(0,1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}
    if(checkCheckFunc(0,-1,moveType)) {parent.updateBoard(futureX,futureY,tempType); parent.updateBoard(posX,posY,type); return true;}


    parent.updateBoard(futureX,futureY,tempType);
    parent.updateBoard(posX,posY,type);
    return false;
}






void Piece :: condCheck(short addX,short addY)
{
    short tempX=posX+addX,tempY=posY+addY;
    switch(type)
    {
        case 20: case 21:
            
            if((parent.getPiece(tempX,tempY)==0 || parent.getPiece(tempX,tempY)%10==colourCond) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                if(!checkChecks(tempX,tempY,false))
                {
                    legalMoves[legalMovesAmmount]={tempX,tempY};
                    ++legalMovesAmmount;
                }
            }
            break;
        case 60: case 61:
            if((parent.getPiece(tempX,tempY)==0 || parent.getPiece(tempX,tempY)%10==colourCond) && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                if(!checkChecks(tempX,tempY,true))
                {
                    legalMoves[legalMovesAmmount]={tempX,tempY};
                    ++legalMovesAmmount;
                }

            }
            break;
        default:    
            while(parent.getPiece(tempX,tempY)==0 && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                if(!checkChecks(tempX,tempY,false))
                {
                    legalMoves[legalMovesAmmount]={tempX,tempY};
                    ++legalMovesAmmount;
                }
                tempX+=addX;
                tempY+=addY;
            }   
            if(parent.getPiece(tempX,tempY)%10==colourCond && tempX<=7 && tempX>=0 && tempY<=7 && tempY>=0)
            {
                if(!checkChecks(tempX,tempY,false))
                {
                    legalMoves[legalMovesAmmount]={tempX,tempY};
                    ++legalMovesAmmount;
                }
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
                if(!checkChecks(posX,posY+1,false))
                {
                    legalMoves[legalMovesAmmount]={posX,posY+1};
                    ++legalMovesAmmount;
                }
            }
            if(parent.getPiece(posX,posY+2)==0 && parent.getPiece(posX,posY+1)==0 && posY==1)
            {
                if(!checkChecks(posX,posY+2,false))
                {
                    legalMoves[legalMovesAmmount]={posX,posY+2};
                    ++legalMovesAmmount;
                }
            }
            if(posX!=7) if(parent.getPiece(posX+1,posY+1)!=0 && parent.getPiece(posX+1,posY+1)%10==colourCond)
            {
                if(!checkChecks(posX+1,posY+1,false))
                {
                    legalMoves[legalMovesAmmount]={posX+1,posY+1};
                    ++legalMovesAmmount;
                }
            }
            if(posX!=0) if(parent.getPiece(posX-1,posY+1)!=0 && parent.getPiece(posX-1,posY+1)%10==colourCond)
            {
                if(!checkChecks(posX-1,posY+1,false))
                {
                    legalMoves[legalMovesAmmount]={posX-1,posY+1};
                    ++legalMovesAmmount;
                }
            }
            //En Peasant
            if(posX!=7 && posY==4) 
            {
                if(parent.getPiece(posX+1,posY)==11 && parent.getPiece(posX+1,posY+1)==0)
                {
                    short temp = parent.getPieceNumber(posX+1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==6)
                    {
                        parent.updateBoard(posX+1,posY,0);
                        if(!checkChecks(posX+1,posY+1,false))
                        {
                            legalMoves[legalMovesAmmount]={posX+1,posY+1};
                            enPassantLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(posX+1,posY,11);
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
                        parent.updateBoard(posX-1,posY,0);
                        parent.Debug();
                        if(!checkChecks(posX-1,posY+1,false))
                        {
                            legalMoves[legalMovesAmmount]={posX-1,posY+1};
                            enPassantLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(posX-1,posY,11);
                    }
                }
            }

            break;
        case 11:
            if(parent.getPiece(posX,posY-1)==0)
            {
                if(!checkChecks(posX,posY-1,false))
                {
                    legalMoves[legalMovesAmmount]={posX,posY-1};
                    ++legalMovesAmmount;
                }
            }
            if(parent.getPiece(posX,posY-2)==0 &&  parent.getPiece(posX,posY-1)==0 && posY==6)
            {
                if(!checkChecks(posX,posY-2,false))
                {
                    legalMoves[legalMovesAmmount]={posX,posY-2};
                    ++legalMovesAmmount;
                }
            }
            if(posX!=0) if(parent.getPiece(posX-1,posY-1)!=0 && parent.getPiece(posX-1,posY-1)%10==colourCond)
            {
                if(!checkChecks(posX-1,posY-1,false))
                {
                    legalMoves[legalMovesAmmount]={posX-1,posY-1};
                    ++legalMovesAmmount;
                }
            }
            if(posX!=7) if(parent.getPiece(posX+1,posY-1)!=0 && parent.getPiece(posX+1,posY-1)%10==colourCond)
            {
                if(!checkChecks(posX+1,posY-1,false))
                {
                    legalMoves[legalMovesAmmount]={posX+1,posY-1};
                    ++legalMovesAmmount;
                }
            }
            //En peasant
            if(posX!=7 && posY==3) 
            {
                if(parent.getPiece(posX+1,posY)==10 && parent.getPiece(posX+1,posY-1)==0)
                {
                    short temp = parent.getPieceNumber(posX+1,posY);
                    if(parent.Pieces[temp].lastMoveNumber==parent.turnNumber && parent.Pieces[temp].previousPosY==1)
                    {
                        parent.updateBoard(posX+1,posY,0);
                        if(!checkChecks(posX+1,posY-1,false))
                        {
                            legalMoves[legalMovesAmmount]={posX+1,posY-1};
                            enPassantLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(posX+1,posY,10);
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
                        parent.updateBoard(posX-1,posY,0);
                        if(!checkChecks(posX-1,posY-1,false))
                        {
                            legalMoves[legalMovesAmmount]={posX-1,posY-1};
                            enPassantLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(posX-1,posY,10);
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
            if(type==60)
            {
                if(checkChecks(4,0,0)) parent.whiteKingInCheck=true;
            }
            else
            {
                if(checkChecks(4,7,0)) parent.blackKingInCheck=true;
            }
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
                bool castleCheck=true;
                if(type==60)
                {
                    if(parent.Pieces[12].previousPosX==-1 && parent.getPiece(1,0)==0 && parent.getPiece(2,0)==0 && parent.getPiece(3,0)==0 && !parent.whiteKingInCheck)
                    {

                        parent.updateBoard(4,0,0);
                        parent.updateBoard(3,0,60);
                        if(checkChecks(3,0,true)) castleCheck=false;
                        parent.updateBoard(3,0,0);
                        parent.updateBoard(2,0,60);
                        if(checkChecks(2,0,true)) castleCheck=false;
                        if(castleCheck)
                        {
                            legalMoves[legalMovesAmmount]={2,0};
                            castleLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(2,0,0);
                        parent.updateBoard(4,0,60);
                    }
                    if(parent.Pieces[13].previousPosX==-1 && parent.getPiece(5,0)==0 && parent.getPiece(6,0)==0 && !parent.whiteKingInCheck)
                    {
                        parent.updateBoard(4,0,0);
                        parent.updateBoard(5,0,60);
                        if(checkChecks(5,0,true)) castleCheck=false;
                        parent.updateBoard(5,0,0);
                        parent.updateBoard(6,0,60);
                        if(checkChecks(6,0,true)) castleCheck=false;                        
                        if(castleCheck)
                        {
                            legalMoves[legalMovesAmmount]={6,0};
                            castleLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(6,0,0);
                        parent.updateBoard(4,0,60);                        
                    }
                }
                else
                {
                    if(parent.Pieces[28].previousPosX==-1 && parent.getPiece(1,7)==0 && parent.getPiece(2,7)==0 && parent.getPiece(3,7)==0 && !parent.blackKingInCheck)
                    {
                        parent.updateBoard(4,7,0);
                        parent.updateBoard(3,7,60);
                        if(checkChecks(3,7,true)) castleCheck=false;
                        parent.updateBoard(3,7,0);
                        parent.updateBoard(2,7,60);
                        if(checkChecks(2,7,true)) castleCheck=false;
                        if(castleCheck)
                        {
                            legalMoves[legalMovesAmmount]={2,7};
                            castleLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(2,7,0);
                        parent.updateBoard(4,7,60);
                    }
                    if(parent.Pieces[29].previousPosX==-1 && parent.getPiece(5,7)==0 && parent.getPiece(6,7)==0 && !parent.blackKingInCheck)
                    {
                        parent.updateBoard(4,7,0);
                        parent.updateBoard(5,7,60);
                        if(checkChecks(5,7,true)) castleCheck=false;
                        parent.updateBoard(5,7,0);
                        parent.updateBoard(6,7,60);
                        if(checkChecks(6,7,true)) castleCheck=false;                        
                        if(castleCheck)
                        {
                            legalMoves[legalMovesAmmount]={6,7};
                            castleLegal=legalMovesAmmount;
                            ++legalMovesAmmount;
                        }
                        parent.updateBoard(6,7,0);
                        parent.updateBoard(4,7,60);   
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


