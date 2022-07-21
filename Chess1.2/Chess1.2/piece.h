#pragma once
#include <iostream>
using namespace std;
class lastmove
{
public:
	//Piece piece;
	int i_c, i_r, f_c, f_r;
	bool doublemove;
	int counter;

	lastmove();
};
class Piece
{
public:
	enum class p_type
	{
		EMPTY,
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING,
		WALL
	};
	p_type piecetype;
	bool first_move;
	bool color;
private:

	int row, column;



public:
	Piece();
	//p_type gettype();
	int char_to_int(char c);
	Piece(int c, int r, bool col, bool first, p_type type);
	void move(char init_c, int init_r, char finish_c, int finish_r, Piece tab[8][8], bool trn, bool white[8][8], bool black[8][8], bool ctrl[8][8], Piece simul[8][8], lastmove& lst, bool flip);
	//void move_and_capture(Piece board[8][8], int initchar, int initrow, int finishchar, int finishrow, bool trn);
	bool is_legal(int ic, int ir, int fc, int fr, Piece type, bool trn, Piece tab[8][8], lastmove& lst);
	bool is_legal_check(int ic, int ir, int fc, int fr, Piece type, bool trn, Piece tab[8][8]);
	//bool check_gone(Piece tab[8][8],bool ctrl[8][8]);
	void white_control(Piece tab[8][8], bool white[8][8]);
	void black_control(Piece tab[8][8], bool black[8][8]);
	friend ostream& operator<<(ostream& out, const Piece& piece);
	bool check_options(Piece tab[8][8], bool trn);
	bool finalcheck(Piece tab[8][8], bool trn);
	bool is_legal_2(int ic, int ir, int fc, int fr, Piece piece, bool trn, Piece tab[8][8]);
};

