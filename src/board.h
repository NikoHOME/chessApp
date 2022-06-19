#ifndef BOARD_H
#define BOARD_H

#include<utility>

class Board;


class PawnW{
    private:
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[4];
        void updateLegalMoves();
        void movePiece(short x, short y);
        PawnW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class PawnB{
    private:
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[4];
        void updateLegalMoves();
        void movePiece(short x, short y);
        PawnB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class KnightW{
    private:
        Board & parent;
        void condCheck(short addX,short addY);
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[8];
        void updateLegalMoves();
        void movePiece(short x, short y);
        KnightW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class KnightB{
    private:
        Board & parent;
        void condCheck(short addX,short addY);
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[8];
        void updateLegalMoves();
        void movePiece(short x, short y);
        KnightB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class BishopW{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[13];
        void updateLegalMoves();
        void movePiece(short x, short y);
        BishopW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class BishopB{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[13];
        void updateLegalMoves();
        void movePiece(short x, short y);
        BishopB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class RookW{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[14];
        void updateLegalMoves();
        void movePiece(short x, short y);
        RookW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class RookB{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[14];
        void updateLegalMoves();
        void movePiece(short x, short y);
        RookB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};


class QueenW{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
        
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[27];
        void updateLegalMoves();
        void movePiece(short x, short y);
        QueenW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class QueenB{
    private:
        void condCheck(short addX,short addY);
        Board & parent;
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[27];
        void updateLegalMoves();
        void movePiece(short x, short y);
        QueenB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class KingW{
    private:
        Board & parent;
        void condCheck(short addX,short addY);
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[8];
        void updateLegalMoves();
        void movePiece(short x, short y);
        KingW(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
};

class KingB{
    private:
        Board & parent;
        void condCheck(short addX,short addY);
    public:
        short posX,posY,legalMovesAmmount;
        bool isOnBoard;
        std::pair<short,short> legalMoves[8];
        void updateLegalMoves();
        void movePiece(short x, short y);
        KingB(short x, short y,Board & p) : posX(x),posY(y),parent(p),isOnBoard(true) {};
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
        void updateBoard(short x,short y,short value);
        void Debug();
        PawnW Pw[8] =   {{ PawnW(0,1,*this) },      { PawnW(1,1,*this) },    { PawnW(2,1,*this) },    { PawnW(3,1,*this) },
                        { PawnW(4,1,*this) },       { PawnW(5,1,*this) },    { PawnW(6,1,*this) },    { PawnW(7,1,*this) }};
        PawnB Pb[8] =   {{ PawnB(0,6,*this) },      { PawnB(1,6,*this) },    { PawnB(2,6,*this) },    { PawnB(0,6,*this) },
                        { PawnB(4,6,*this) },       { PawnB(5,6,*this) },    { PawnB(6,6,*this) },    { PawnB(7,6,*this) }};
        KnightW Nw[2] = {{ KnightW(1,0,*this) },    { KnightW(6,0,*this) }};   
        KnightB Nb[2] = {{ KnightB(1,7,*this) },    { KnightB(6,7,*this) }};
        BishopW Bw[2] = {{ BishopW(2,0,*this) },    { BishopW(5,0,*this) }};
        BishopB Bb[2] = {{ BishopB(2,7,*this) },    { BishopB(5,7,*this) }};
        RookW   Rw[2] = {{ RookW(0,0,*this) },      { RookW(7,0,*this) }};
        RookB   Rb[2] = {{ RookB(0,7,*this) },      { RookB(7,7,*this) }};
        QueenW  Qw{ QueenW(3,0,*this) };
        QueenB  Qb{ QueenB(3,7,*this)};
        KingW   Kw{ KingW(4,0,*this) };
        KingB   Kb{ KingB(4,7,*this)};

        //	PawnW	Pw0(0,1),Pw1(1,1),Pw2(2,1),Pw3(3,1),Pw4(4,1),Pw5(5,1),Pw6(6,1),Pw7(7,1);
        //	PawnB	Pb0(0,6),Pb1(1,6),Pb2(2,6),Pb3(3,6),Pb4(4,6),Pb5(5,6),Pb6(6,6),Pb7(7,6);
        //	Knight	Nw0(1,0),Nw1(6,0),Nb0(1,7),Nb1(6,7);
        //	Bishop	Bw0(2,0),Bw1(5,0),Bb0(2,7),Bb1(5,7);
        //	Rook	Rw0(0,0),Rw1(7,0),Rb0(0,7),Rb1(7,7);
        //	Queen	Qw0(3,0),Qb0(3,7);
        //	King	Kw0(4,0),Kb0(4,7);
};



#endif //