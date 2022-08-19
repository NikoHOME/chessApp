#ifndef BOARD_H
#define BOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utility>
#include <vector>
#include <iostream>



class Board;

class Piece
{
    private:
        Board & parent;
        void condCheck(short addX,short addY);
        bool checkChecks(short futureX,short futureY,bool isKing);
        bool checkCheckFunc(short addX, short addY, short moveType);
    public:
        short posX,posY,type,legalMovesAmmount,previousPosX=-1,previousPosY=-1,enPassantLegal=-1,castleLegal=-1;
        int lastMoveNumber=-1;
        short colourCond;
        bool isOnBoard;
        std::vector <std::pair<short,short>> legalMoves;
        void updateLegalMoves();
        void movePiece(short x, short y);
        Piece(short x, short y,short t,Board & p) : posX(x),posY(y),type(t),parent(p),isOnBoard(true) 
        {
            switch(type)
            {
                case 10: case 11:
                    legalMoves.resize(4);
                    break;
                case 20: case 21:
                    legalMoves.resize(8);
                    break;
                case 30: case 31:
                    legalMoves.resize(13);
                    break;
                case 40: case 41:
                    legalMoves.resize(14);
                    break;
                case 50: case 51:
                    legalMoves.resize(27);
                    break;
                case 60: case 61:
                    legalMoves.resize(8);
                    break;

            }

            if(t%10==1) colourCond=0;
            else colourCond=1;
        };


};


class Board{
    private :
        short tab[8][8]= 
        {
            {40,10,0,0,0,0,11,41},
            {20,10,0,0,0,0,11,21},
            {30,10,0,0,0,0,11,31},
            {50,10,0,0,0,0,11,51},
            {60,10,0,0,0,0,11,61},
            {30,10,0,0,0,0,11,31},
            {20,10,0,0,0,0,11,21},
            {40,10,0,0,0,0,11,41}

        };
        
    public :
        short getPiece(short x,short y);
        short getPieceNumber(short x,short y);
        int turnNumber=0;
        void updateBoard(short x,short y,short value);
        void Debug();
        bool whiteKingInCheck=false;
        bool blackKingInCheck=false;
        void reset()
        {
            short tempTab[8][8]= 
            {
                {40,10,0,0,0,0,11,41},
                {20,10,0,0,0,0,11,21},
                {30,10,0,0,0,0,11,31},
                {50,10,0,0,0,0,11,51},
                {60,10,0,0,0,0,11,61},
                {30,10,0,0,0,0,11,31},
                {20,10,0,0,0,0,11,21},
                {40,10,0,0,0,0,11,41}

            };
            for(int i=0;i<8;i++) for(int j=0;j<8;j++)
            {
                tab[i][j]=tempTab[i][j];
            }
            short tempMove[64]=
            {
                0,1, 1,1, 2,1, 3,1, 4,1, 5,1, 6,1, 7,1,
                1,0, 6,0,
                2,0, 5,0,
                0,0, 7,0,
                3,0, 4,0,

                0,6, 1,6, 2,6, 3,6, 4,6, 5,6, 6,6, 7,6,
                1,7, 6,7,
                2,7, 5,7,
                0,7, 7,7,
                3,7, 4,7             
            };
            for(int i=0;i<64;i+=2)
            {
                Pieces[i/2].posX=tempMove[i];
                Pieces[i/2].posY=tempMove[i+1];
                Pieces[i/2].isOnBoard=true;
            }
            for(int i=0;i<32;++i)
            {
                Pieces[i].updateLegalMoves();
            }

            turnNumber=0;
        }

        Piece Pieces[32] = 
            {
                Piece(0,1,10,*this),Piece(1,1,10,*this),Piece(2,1,10,*this),Piece(3,1,10,*this),
                Piece(4,1,10,*this),Piece(5,1,10,*this),Piece(6,1,10,*this),Piece(7,1,10,*this),
                Piece(1,0,20,*this),Piece(6,0,20,*this),
                Piece(2,0,30,*this),Piece(5,0,30,*this),
                Piece(0,0,40,*this),Piece(7,0,40,*this),
                Piece(3,0,50,*this),
                Piece(4,0,60,*this),

                Piece(0,6,11,*this),Piece(1,6,11,*this),Piece(2,6,11,*this),Piece(3,6,11,*this),
                Piece(4,6,11,*this),Piece(5,6,11,*this),Piece(6,6,11,*this),Piece(7,6,11,*this),
                Piece(1,7,21,*this),Piece(6,7,21,*this),
                Piece(2,7,31,*this),Piece(5,7,31,*this),
                Piece(0,7,41,*this),Piece(7,7,41,*this),
                Piece(3,7,51,*this),
                Piece(4,7,61,*this)

            };

};


#endif //