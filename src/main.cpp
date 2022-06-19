#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "board.h"

Board chessBoard;

void UpdatePieces()
{
	for(auto j:chessBoard.Pw) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Pb) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Nw) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Nb) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Bw) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Bb) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Rw) if(j.isOnBoard) j.updateLegalMoves();
	for(auto j:chessBoard.Rb) if(j.isOnBoard) j.updateLegalMoves();

	if(chessBoard.Qw.isOnBoard) chessBoard.Qw.updateLegalMoves();
	if(chessBoard.Qb.isOnBoard) chessBoard.Qb.updateLegalMoves();
	if(chessBoard.Kw.isOnBoard) chessBoard.Kw.updateLegalMoves();
	if(chessBoard.Kb.isOnBoard) chessBoard.Kb.updateLegalMoves();
}




int main()
{	
	


	

//	PawnW	Pw0(0,1),Pw1(1,1),Pw2(2,1),Pw3(3,1),Pw4(4,1),Pw5(5,1),Pw6(6,1),Pw7(7,1);
//	PawnB	Pb0(0,6),Pb1(1,6),Pb2(2,6),Pb3(3,6),Pb4(4,6),Pb5(5,6),Pb6(6,6),Pb7(7,6);
//	Knight	Nw0(1,0),Nw1(6,0),Nb0(1,7),Nb1(6,7);
//	Bishop	Bw0(2,0),Bw1(5,0),Bb0(2,7),Bb1(5,7);
//	Rook	Rw0(0,0),Rw1(7,0),Rb0(0,7),Rb1(7,7);
//	Queen	Qw0(3,0),Qb0(3,7);
//	King	Kw0(4,0),Kb0(4,7);

	chessBoard.Debug();

	
	chessBoard.Pb[4].movePiece(5,4);
	chessBoard.Rw[0].movePiece(4,4);

	chessBoard.Debug();

	UpdatePieces();

	std::cout<<"\n";
	for(int i=0;i<chessBoard.Rw[0].legalMovesAmmount;++i)
	{
		std::cout<<chessBoard.Rw[0].legalMoves[i].first<<" "<<chessBoard.Rw[0].legalMoves[i].second<<"\n";
	}
	std::cout<<"\n";
	for(int i=0;i<chessBoard.Kb.legalMovesAmmount;++i)
	{
		std::cout<<chessBoard.Kb.legalMoves[i].first<<" "<<chessBoard.Kb.legalMoves[i].second<<"\n";
	}
	





	return 0;
}