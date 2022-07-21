#include "piece.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void printboard_piece(Piece brd[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		char term = i + 97;
		cout << "   " << term << "  ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) cout << "______";
	cout << endl;
	for (int j = 7; j >= 0; j--)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << "|" << brd[i][j];
		}
		cout << "|" << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "|_____";
		}
		cout << "| " << j + 1 << endl;
	}
}

void printboard_piece_blc(Piece brd[8][8])
{
	for (int i = 0; i < 40; i++)
	{
		cout << endl;
	}
	for (int i = 7; i >= 0; i--)
	{
		char term = i + 97;
		cout << "   " << term << "  ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) cout << "______";
	cout << endl;
	for (int j = 0; j < 8; j++)
	{
		for (int i = 7; i >= 0; i--)
		{
			cout << "|" << brd[i][j];
		}
		cout << "|" << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "|_____";
		}
		cout << "| " << j + 1 << endl;
	}
}

Piece::Piece(int c, int r, bool col, bool first, Piece::p_type type)
{
	row = r;
	column = c;
	color = col;
	first_move = first;
	piecetype = type;
}

Piece::Piece()
{
	row = -1;
	column = -1;
	color = 0;
	first_move = 0;
	piecetype = Piece::p_type::EMPTY;
}

int Piece::char_to_int(char c)
{
	int tmp;
	tmp = (int)c - 97;
	return tmp;
}

bool Piece::is_legal(int ic, int ir, int fc, int fr, Piece piece, bool trn, Piece tab[8][8], lastmove& lst)
{
	bool allowed = false;
	bool enpassant = false;
	bool enpass_col; // 0 = black, 1 = white
	bool enpass_side; // 0 = left, 1 = right
	bool zbitowprzelocie = false;
	bool upgrade = false;
	if (piece.color != trn)
	{
		cout << "Move your own piece!" << endl;
		return 0;
	}
	if ((tab[fc][fr].color == trn) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
	{
		cout << "2. You can't capture your own figure." << endl;
		return 0;
	}
	if (ic == fc && ir == fr)
	{
		cout << "You can't make no move." << endl;
		return 0;
	}
	if (ic < 0 || ic>7 || ir < 0 || ir>7 || fc < 0 || fc>7 || fr < 0 || fr>7)
	{
		cout << "You exceeded the chess board." << endl;
		return 0;
	}
	switch (piece.piecetype)
	{
	case Piece::p_type::WALL:
	{
		return 0;
	}
	case Piece::p_type::EMPTY:
	{
		cout << "You can't move an empty file!" << endl;
		return 0;
	}
	case Piece::p_type::PAWN:
	{
		//capturing with white pawn
		if (tab[ic][ir].color == 1 && ((fr - ir == 1 && fc - ic == 1) || (fr - ir == 1 && fc - ic == -1)) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
		{
			allowed = true;
			if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
			break;
		}
		//capturing with black pawn
		if (tab[ic][ir].color == 0 && ((fr - ir == -1 && fc - ic == -1) || (fr - ir == -1 && fc - ic == 1)) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
		{
			//cout << "ic= " << ic << " ir= " << ir << " fc= " << fc << " fr= " << fr << " piecetype of target: ";
			//if (tab[fc][fr].piecetype == Piece::p_type::EMPTY) cout << "empty" << endl;
			//else cout << "NONEMPTY" << endl;
			allowed = true;
			if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
			break;
		}
		if (piece.first_move == 0)
		{
			if (piece.color == 1)
			{
				//moving a white pawn in first move
				if (ic == fc && (fr - ir == 2 || fr - ir == 1))
				{
					if (fr - ir == 2)
					{
						if (tab[ic][ir + 1].piecetype != Piece::p_type::EMPTY || tab[ic][ir + 2].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							lst.doublemove = true;
							enpassant = true;
							if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
							break;
						}
					}
					else if (fr - ir == 1)
					{
						if (tab[ic][ir + 1].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
							break;
						}
					}
				}
				else return 0;
			}
			if (piece.color == 0)
				//moving a black pawn in first move
			{
				if (ic == fc && (ir - fr == 2 || ir - fr == 1))
				{
					if (ir - fr == 2)
					{
						if (tab[ic][fr].piecetype != Piece::p_type::EMPTY || tab[ic][fr + 1].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							lst.doublemove = true;
							enpassant = true;
							if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
							break;
						}
					}
					else if (ir - fr == 1)
					{
						if (tab[fc][fr].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
							break;
						}
					}
				}
				else return 0;
			}
		}
		if (piece.first_move == 1)
		{
			//moving a white pawn after its' first move
			if (piece.color == 1)
			{
				if (ic == fc && fr - ir == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY)
				{
					allowed = true;
					if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
					break;
				}
				else if (ir == 4 && fr - ir == 1 && abs(fc - ic) == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY) // en passant for white
				{
					cout << "Enpassant white ";
					if (fc - ic == 1 && tab[ic + 1][ir].piecetype == Piece::p_type::PAWN && lst.doublemove && lst.f_c == ic + 1 && lst.f_r == ir) //right
					{
						cout << "to the right" << endl;
						allowed = true;
						zbitowprzelocie = true;
						if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
						//enpass_col = true;
						//enpass_side = true;
						break;
					}
					else if (fc - ic == -1 && tab[ic - 1][ir].piecetype == Piece::p_type::PAWN && lst.doublemove && lst.f_c == ic - 1 && lst.f_r == ir) //left
					{
						cout << "to the left" << endl;
						allowed = true;
						zbitowprzelocie = true;
						if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
						//enpass_col = true;
						//enpass_side = false;
						break;
					}
				}
				else return 0;
			}
			//moving a black pawn after its' first move
			else
			{
				//cout << "ic= " << ic << " ir= " << ir << " fc= " << fc << " fr= " << fr << endl;
				if (ic == fc && ir - fr == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY)
				{
					if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
					allowed = true;
					break;
				}
				else if (ir == 3 && ir - fr == 1 && abs(fc - ic) == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY) // en passant for black
				{
					cout << "Enpassant black ";
					if (fc - ic == 1 && tab[ic + 1][ir].piecetype == Piece::p_type::PAWN && lst.doublemove && lst.f_c == ic + 1 && lst.f_r == ir) //right
					{
						cout << "to the right" << endl;
						allowed = true;
						zbitowprzelocie = true;
						if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
						//enpass_col = false;
						//enpass_side = true;
						break;
					}
					else if (fc - ic == -1 && tab[ic - 1][ir].piecetype == Piece::p_type::PAWN && lst.doublemove && lst.f_c == ic - 1 && lst.f_r == ir) //left
					{
						cout << "to the left" << endl;
						allowed = true;
						zbitowprzelocie = true;
						if ((trn && fr == 7) || (!trn && fr == 0)) upgrade = true;
						//enpass_col = false;
						//enpass_side = false;
						break;
					}
				}
				else return 0;
			}
		}

	}
	case Piece::p_type::ROOK:
	{
		if (ic == fc || ir == fr)
		{
			if (ic == fc && fr - ir > 0)
			{

				for (int i = ir + 1; i < fr; i++)
				{
					if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ic == fc && fr - ir < 0)
			{
				for (int i = fr + 1; i < ir; i++)
				{
					if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ir == fr && fc - ic > 0)
			{
				for (int i = ic + 1; i < fc; i++)
				{
					if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ir == fr && fc - ic < 0)
			{
				for (int i = fc + 1; i < ic; i++)
				{
					if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
		}
		else return 0;
	}
	case Piece::p_type::BISHOP:
	{
		if (abs(fc - ic) == abs(fr - ir))
		{
			if (fc - ic > 0 && fr - ir > 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY)
					{
						cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic > 0 && fr - ir < 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY)
					{
						cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic < 0 && fr - ir > 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY)
					{
						cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic < 0 && fr - ir < 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY)
					{
						cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
		}
		else return 0;
	}
	case Piece::p_type::KNIGHT:
	{
		if ((abs(fc - ic) == 1 && abs(fr - ir) == 2) || (abs(fc - ic) == 2 && abs(fr - ir) == 1))
		{
			allowed = true;
			break;
		}
		else return 0;
	}
	case Piece::p_type::QUEEN:
	{
		if ((ic == fc || ir == fr) ^ (abs(fc - ic) == abs(fr - ir)))
		{
			if (ic == fc || ir == fr)
			{
				if (ic == fc && fr - ir > 0)
				{

					for (int i = ir + 1; i < fr; i++)
					{
						if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ic == fc && fr - ir < 0)
				{
					for (int i = fr + 1; i < ir; i++)
					{
						if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ir == fr && fc - ic > 0)
				{
					for (int i = ic + 1; i < fc; i++)
					{
						if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ir == fr && fc - ic < 0)
				{
					for (int i = fc + 1; i < ic; i++)
					{
						if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
			}
			if (abs(fc - ic) == abs(fr - ir))
			{
				if (fc - ic > 0 && fr - ir > 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic > 0 && fr - ir < 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic < 0 && fr - ir > 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic < 0 && fr - ir < 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
			}
		}
		else return 0;
	}
	case Piece::p_type::KING:
	{
		if (abs(fc - ic) < 2 && abs(fr - ir) < 2)
		{
			allowed = true;
			break;
		}
		else if (fr == ir && abs(fc - ic) == 2)
		{
			bool ctr[8][8];
			for (int i = 7; i >= 0; i--)
			{
				for (int j = 0; j < 8; j++)
				{
					ctr[i][j] = 0;
				}
			}
			//cout << "Roszada" << endl;
			if (trn) // white castle
			{
				black_control(tab, ctr);
				/*for (int i = 7; i >=0; i--)
				{
					for (int j = 0; j < 8; j++)
					{
						cout<< ctr[j][i]<<" ";
					}
					cout << endl;
				}*/
				if (ic == fc + 2 && tab[ic][ir].first_move == 0 && tab[0][0].first_move == 0) //O-O-O left
				{
					//cout << "Lewa" << endl;
					if (ctr[2][0] == false && ctr[3][0] == false && ctr[4][0] == false && tab[1][0].piecetype == Piece::p_type::EMPTY && tab[2][0].piecetype == Piece::p_type::EMPTY && tab[3][0].piecetype == Piece::p_type::EMPTY)
					{
						//cout << "Mozna" << endl;
						allowed = true;
						break;
					}
					else break;
				}
				else if (ic == fc - 2 && tab[ic][ir].first_move == 0 && tab[0][0].first_move == 0) //O-O right
				{
					//cout << "Prawa" << endl;
					if (ctr[4][0] == false && ctr[5][0] == false && ctr[6][0] == false && tab[5][0].piecetype == Piece::p_type::EMPTY && tab[6][0].piecetype == Piece::p_type::EMPTY)
					{
						//cout << "Mozna" << endl;
						allowed = true;
						break;
					}
					else break;
				}
				else break;
			}
			else // black castle
			{
				white_control(tab, ctr);
				if (ic == fc + 2 && tab[ic][ir].first_move == 0 && tab[0][0].first_move == 0) //O-O-O left
				{
					if (ctr[2][7] == false && ctr[3][7] == false && ctr[4][7] == false && tab[1][7].piecetype == Piece::p_type::EMPTY && tab[2][7].piecetype == Piece::p_type::EMPTY && tab[3][7].piecetype == Piece::p_type::EMPTY)
					{
						allowed = true;
						break;
					}
					else break;
				}
				else if (ic == fc - 2 && tab[ic][ir].first_move == 0 && tab[0][0].first_move == 0) //O-O right
				{
					if (ctr[4][7] == false && ctr[5][7] == false && ctr[6][7] == false && tab[5][7].piecetype == Piece::p_type::EMPTY && tab[6][7].piecetype == Piece::p_type::EMPTY)
					{
						allowed = true;
						break;
					}
					else break;
				}
				else break;
			}
		}
		else return 0;
	}
	}
	if (allowed)
	{
		//simulating movement in order to check if there will be check after a move of trn
		Piece simulator[8][8];
		bool white_sim[8][8];
		bool black_sim[8][8];
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				simulator[x][y] = tab[x][y];
				white_sim[x][y] = 0;
				black_sim[x][y] = 0;
			}
		}

		//cout << "BEFORE MOVE: " << endl;
		//printboard_piece(simulator);

		if (simulator[fc][fr].piecetype != Piece::p_type::EMPTY && simulator[fc][fr].color != trn) simulator[fc][fr].piecetype = Piece::p_type::EMPTY;
		Piece tmp = simulator[fc][fr];
		simulator[ic][ir].first_move = 1;
		simulator[fc][fr] = simulator[ic][ir];
		simulator[ic][ir] = tmp;

		white_control(simulator, white_sim);
		black_control(simulator, black_sim);

		//cout << "AFTER MOVE: " << endl;
		//printboard_piece(simulator);

		int kingx = 0, kingy = 0;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (simulator[x][y].color == trn && simulator[x][y].piecetype == Piece::p_type::KING)
				{
					kingx = x;
					kingy = y;
				}
			}
		}

		if (trn) // checking white king
		{
			//cout << "White king position: " << kingx << " " << kingy << endl;
			//cout << "Black player attacks: " << endl;
			//cout << "Is white king attacked: ";
			if (black_sim[kingx][kingy]) // white is on check 
			{
				//cout << "Yes" << endl;
				cout << "That leaves you on check!" << endl;
				return 0;
			}
			else
			{
				if (!enpassant) lst.doublemove = false;
				if (zbitowprzelocie)
				{
					tab[fc][ir].piecetype = Piece::p_type::EMPTY;
				}
				if (upgrade)
				{
					cout << "Choose a piece to promote your pawn to (Q/q = Queen, K/k = Knight, R/r = Rook, B/b = Bishop) :";
					char promo;
					cin >> promo;
					while (!(promo == 'Q' || promo == 'q' || promo == 'K' || promo == 'k' || promo == 'R' || promo == 'r' || promo == 'B' || promo == 'b'))
					{
						cout << "Wrong name of a figure, try again: ";
						cin >> promo;
					}
					switch (promo)
					{
					case 'Q':
					{
						//cout << "Queen" << endl;
						tab[ic][ir].piecetype = Piece::p_type::QUEEN;
						break;
					}
					case 'q':
					{
						//cout << "Queen" << endl;
						tab[ic][ir].piecetype = Piece::p_type::QUEEN;
						break;
					}
					case 'K':
					{
						//cout << "Knight" << endl;
						tab[ic][ir].piecetype = Piece::p_type::KNIGHT;
						break;
					}
					case 'k':
					{
						//cout << "Knight" << endl;
						tab[ic][ir].piecetype = Piece::p_type::KNIGHT;
						break;
					}
					case 'R':
					{
						//cout << "Rook" << endl;
						tab[ic][ir].piecetype = Piece::p_type::ROOK;
						break;
					}
					case 'r':
					{
						//cout << "Rook" << endl;
						tab[ic][ir].piecetype = Piece::p_type::ROOK;
						break;
					}
					case 'B':
					{
						//cout << "Bishop" << endl;
						tab[ic][ir].piecetype = Piece::p_type::BISHOP;
						break;
					}
					case 'b':
					{
						//cout << "Bishop" << endl;
						tab[ic][ir].piecetype = Piece::p_type::BISHOP;
						break;
					}
					}
				}
				return 1;
			}
		}
		else // checking black king
		{
			//cout << "Black king position: " << kingx << " " << kingy << endl;
			//cout << "White player attacks: " << endl;
			//cout << "Is black king attacked: ";
			if (white_sim[kingx][kingy]) // black is on check 
			{
				cout << "That leaves you on check!" << endl;
				return 0;
			}
			else
			{
				if (!enpassant) lst.doublemove = false;
				if (zbitowprzelocie)
				{
					tab[fc][ir].piecetype = Piece::p_type::EMPTY;
				}
				if (upgrade)
				{
					cout << "Choose a piece to promote your pawn to (Q/q = Queen, K/k = Knight, R/r = Rook, B/b = Bishop) :";
					char promo;
					cin >> promo;
					while (!(promo == 'Q' || promo == 'q' || promo == 'K' || promo == 'k' || promo == 'R' || promo == 'r' || promo == 'B' || promo == 'b'))
					{
						cout << "Wrong name of a figure, try again: ";
						cin >> promo;
					}
					switch (promo)
					{
					case 'Q':
					{
						//cout << "Queen" << endl;
						tab[ic][ir].piecetype = Piece::p_type::QUEEN;
						break;
					}
					case 'q':
					{
						//cout << "Queen" << endl;
						tab[ic][ir].piecetype = Piece::p_type::QUEEN;
						break;
					}
					case 'K':
					{
						//cout << "Knight" << endl;
						tab[ic][ir].piecetype = Piece::p_type::KNIGHT;
						break;
					}
					case 'k':
					{
						//cout << "Knight" << endl;
						tab[ic][ir].piecetype = Piece::p_type::KNIGHT;
						break;
					}
					case 'R':
					{
						//cout << "Rook" << endl;
						tab[ic][ir].piecetype = Piece::p_type::ROOK;
						break;
					}
					case 'r':
					{
						//cout << "Rook" << endl;
						tab[ic][ir].piecetype = Piece::p_type::ROOK;
						break;
					}
					case 'B':
					{
						//cout << "Bishop" << endl;
						tab[ic][ir].piecetype = Piece::p_type::BISHOP;
						break;
					}
					case 'b':
					{
						//cout << "Bishop" << endl;
						tab[ic][ir].piecetype = Piece::p_type::BISHOP;
						break;
					}
					}
				}
				return 1;
			}
		}


	}
	else return 0;

}

bool Piece::is_legal_2(int ic, int ir, int fc, int fr, Piece piece, bool trn, Piece tab[8][8])
{
	bool allowed = false;
	if (piece.color != trn)
	{
		return 0;
	}
	if ((tab[fc][fr].color == trn) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
	{
		//cout << "2. You can't capture your own figure." << endl;
		return 0;
	}
	if (ic == fc && ir == fr)
	{
		//cout << "You can't make no move." << endl;
		return 0;
	}
	if (ic < 0 || ic>7 || ir < 0 || ir>7 || fc < 0 || fc>7 || fr < 0 || fr>7)
	{
		//cout << "You exceeded the chess board." << endl;
		return 0;
	}
	switch (piece.piecetype)
	{
	case Piece::p_type::WALL:
	{
		return 0;
	}
	case Piece::p_type::EMPTY:
	{
		//cout << "You can't move an empty file!" << endl;
		return 0;
	}
	case Piece::p_type::PAWN:
	{
		//capturing with white pawn
		if ((tab[ic][ir].color == 1 && (fr - ir == 1 && fc - ic == 1) || (fr - ir == 1 && fc - ic == -1)) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
		{
			allowed = true;
			break;
		}
		//capturing with black pawn
		if (tab[ic][ir].color == 0 && (fr - ir == -1 && fc - ic == -1) || (fr - ir == -1 && fc - ic == 1) && tab[fc][fr].piecetype != Piece::p_type::EMPTY)
		{
			allowed = true;
			break;
		}
		if (piece.first_move == 0)
		{
			if (piece.color == 1)
			{
				//moving a white pawn in first move
				if (ic == fc && (fr - ir == 2 || fr - ir == 1))
				{
					if (fr - ir == 2)
					{
						if (tab[ic][ir + 1].piecetype != Piece::p_type::EMPTY || tab[ic][ir + 2].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							break;
						}
					}
					else if (fr - ir == 1)
					{
						if (tab[ic][ir + 1].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							break;
						}
					}
				}
				else return 0;
			}
			if (piece.color == 0)
				//moving a black pawn in first move
			{
				if (ic == fc && (ir - fr == 2 || ir - fr == 1))
				{
					if (ir - fr == 2)
					{
						if (tab[ic][fr].piecetype != Piece::p_type::EMPTY || tab[ic][fr + 1].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							break;
						}
					}
					else if (ir - fr == 1)
					{
						if (tab[fc][fr].piecetype != Piece::p_type::EMPTY) return 0;
						else
						{
							allowed = true;
							break;
						}
					}
				}
				else return 0;
			}
		}
		if (piece.first_move == 1)
		{
			if (piece.color == 1)
			{
				//moving a white pawn after its' first move
				if (ic == fc && fr - ir == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY)
				{
					allowed = true;
					break;
				}
				else return 0;
			}
			else
				//moving a black pawn after its' first move
			{
				if (ic == fc && ir - fr == 1 && tab[fc][fr].piecetype == Piece::p_type::EMPTY)
				{
					allowed = true;
					break;
				}
				else return 0;
			}
		}
	}
	case Piece::p_type::ROOK:
	{
		if (ic == fc || ir == fr)
		{
			if (ic == fc && fr - ir > 0)
			{

				for (int i = ir + 1; i < fr; i++)
				{
					if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ic == fc && fr - ir < 0)
			{
				for (int i = fr + 1; i < ir; i++)
				{
					if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ir == fr && fc - ic > 0)
			{
				for (int i = ic + 1; i < fc; i++)
				{
					if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
			if (ir == fr && fc - ic < 0)
			{
				for (int i = fc + 1; i < ic; i++)
				{
					if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
				}
				allowed = true;
				break;
			}
		}
		else return 0;
	}
	case Piece::p_type::BISHOP:
	{
		if (abs(fc - ic) == abs(fr - ir))
		{
			if (fc - ic > 0 && fr - ir > 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY)
					{
						//cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic > 0 && fr - ir < 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY)
					{
						//cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic < 0 && fr - ir > 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY)
					{
						//cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
			if (fc - ic < 0 && fr - ir < 0)
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY)
					{
						//cout << "There's a piece in between." << endl;
						return 0;
					}
				}
				allowed = true;
				break;
			}
		}
		else return 0;
	}
	case Piece::p_type::KNIGHT:
	{
		if ((abs(fc - ic) == 1 && abs(fr - ir) == 2) || (abs(fc - ic) == 2 && abs(fr - ir) == 1))
		{
			allowed = true;
			break;
		}
		else return 0;
	}
	case Piece::p_type::QUEEN:
	{
		if ((ic == fc || ir == fr) ^ (abs(fc - ic) == abs(fr - ir)))
		{
			if (ic == fc || ir == fr)
			{
				if (ic == fc && fr - ir > 0)
				{

					for (int i = ir + 1; i < fr; i++)
					{
						if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ic == fc && fr - ir < 0)
				{
					for (int i = fr + 1; i < ir; i++)
					{
						if (tab[ic][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ir == fr && fc - ic > 0)
				{
					for (int i = ic + 1; i < fc; i++)
					{
						if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (ir == fr && fc - ic < 0)
				{
					for (int i = fc + 1; i < ic; i++)
					{
						if (tab[i][ir].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
			}
			if (abs(fc - ic) == abs(fr - ir))
			{
				if (fc - ic > 0 && fr - ir > 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic > 0 && fr - ir < 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic < 0 && fr - ir > 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
				if (fc - ic < 0 && fr - ir < 0)
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					allowed = true;
					break;
				}
			}
		}
		else return 0;
	}
	case Piece::p_type::KING:
	{
		if (abs(fc - ic) < 2 && abs(fr - ir) < 2)
		{
			allowed = true;
			break;
		}
		else return 0;
	}
	}
	if (allowed)
	{
		//simulating movement in order to check if there will be check after a move of trn
		Piece simulator[8][8];
		bool white_sim[8][8];
		bool black_sim[8][8];
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				simulator[x][y] = tab[x][y];
				white_sim[x][y] = 0;
				black_sim[x][y] = 0;
			}
		}

		//cout << "BEFORE MOVE: " << endl;
		//printboard_piece(simulator);

		if (simulator[fc][fr].piecetype != Piece::p_type::EMPTY && simulator[fc][fr].color != trn) simulator[fc][fr].piecetype = Piece::p_type::EMPTY;
		Piece tmp = simulator[fc][fr];
		simulator[ic][ir].first_move = 1;
		simulator[fc][fr] = simulator[ic][ir];
		simulator[ic][ir] = tmp;

		white_control(simulator, white_sim);
		black_control(simulator, black_sim);

		//cout << "AFTER MOVE: " << endl;
		//printboard_piece(simulator);

		int kingx = 0, kingy = 0;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (simulator[x][y].color == trn && simulator[x][y].piecetype == Piece::p_type::KING)
				{
					kingx = x;
					kingy = y;
				}
			}
		}

		if (trn) // checking white king
		{
			//cout << "White king position: " << kingx << " " << kingy << endl;
			//cout << "Black player attacks: " << endl;
			//cout << "Is white king attacked: ";
			if (black_sim[kingx][kingy]) // white is on check 
			{
				//cout << "Yes" << endl;
				//cout << "That leaves you on check!" << endl;
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else // checking black king
		{
			//cout << "Black king position: " << kingx << " " << kingy << endl;
			//cout << "White player attacks: " << endl;
			//cout << "Is black king attacked: ";
			if (white_sim[kingx][kingy]) // black is on check 
			{
				//cout << "That leaves you on check!" << endl;
				return 0;
			}
			else
			{
				return 1;
			}
		}


	}
	else return 0;

}

void Piece::move(char init_c, int init_r, char finish_c, int finish_r, Piece tab[8][8], bool trn, bool white[8][8], bool black[8][8], bool ctrl[8][8], Piece simul[8][8], lastmove& lst, bool flip)
{
	int initchar = char_to_int(init_c);
	int initrow = init_r - 1;
	int finishchar = char_to_int(finish_c);
	int finishrow = finish_r - 1;
	if (initchar >= 0 && initchar < 8 && initrow >= 0 && initrow < 8 && finishchar >= 0 && finishchar < 8 && finishrow >= 0 && finishrow < 8)
	{
		if (is_legal(initchar, initrow, finishchar, finishrow, tab[initchar][initrow], trn, tab, lst))
		{
			//moving or beating algorithm
			if (tab[finishchar][finishrow].piecetype != Piece::p_type::EMPTY && tab[finishchar][finishrow].color != trn) tab[finishchar][finishrow].piecetype = Piece::p_type::EMPTY;
			Piece tmp = tab[finishchar][finishrow];
			tab[initchar][initrow].first_move = 1;
			tab[finishchar][finishrow] = tab[initchar][initrow];
			tab[initchar][initrow] = tmp;
			if (tab[finishchar][finishrow].piecetype == Piece::p_type::KING && finishrow == initrow && finishchar == initchar - 2)
			{
				if (trn)
				{
					tmp = tab[finishchar + 1][finishrow];
					tab[0][0].first_move = 1;
					tab[finishchar + 1][finishrow] = tab[0][0];
					tab[0][0] = tmp;
				}
				else
				{
					tmp = tab[finishchar + 1][finishrow];
					tab[0][7].first_move = 1;
					tab[finishchar + 1][finishrow] = tab[0][7];
					tab[0][7] = tmp;
				}
			}
			if (tab[finishchar][finishrow].piecetype == Piece::p_type::KING && finishrow == initrow && finishchar == initchar + 2)
			{
				if (trn)
				{
					tmp = tab[finishchar - 1][finishrow];
					tab[7][0].first_move = 1;
					tab[finishchar - 1][finishrow] = tab[7][0];
					tab[7][0] = tmp;
				}
				else
				{
					tmp = tab[finishchar - 1][finishrow];
					tab[7][7].first_move = 1;
					tab[finishchar - 1][finishrow] = tab[7][7];
					tab[7][7] = tmp;
				}
			}
			//if	
			lst.counter++;
			lst.i_c = initchar;
			lst.i_r = initrow;
			lst.f_c = finishchar;
			lst.f_r = finishrow;
			//lst.piece = tab[finishchar][finishrow];
		}
		else
		{
			char ic, fc;
			int ir, fr;
			cout << "Illegal move. Choose another move" << endl;
			if (flip)
			{
				if (trn) printboard_piece(tab);
				else printboard_piece_blc(tab);
			}
			else
			{
				printboard_piece(tab);
			}
			if (trn == 1) cout << "White's move" << endl;
			else cout << "Black's move" << endl;
			cout << "Give the column and row of a piece you want to move:";
			cin >> ic >> ir;
			cout << "Give the coordinates of a place you want to move to:";
			cin >> fc >> fr;
			move(ic, ir, fc, fr, tab, trn, white, black, ctrl, simul, lst,flip);
			return;
		}
		white_control(tab, white);
		black_control(tab, black);
	}

}

void Piece::white_control(Piece tab[8][8], bool white[8][8])
{
	//reseting the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) white[i][j] = 0;
	}
	//checking every field
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[j][i].color == true && tab[j][i].piecetype != Piece::p_type::EMPTY)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						if (Piece::is_legal_check(j, i, l, k, tab[j][i], true, tab))
						{
							white[l][k] = 1;
						}
					}
				}
			}
		}
	}
}

void Piece::black_control(Piece tab[8][8], bool black[8][8])
{
	//reseting the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) black[i][j] = 0;
	}
	//checking every field
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[j][i].color == false && tab[j][i].piecetype != Piece::p_type::EMPTY)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						if (Piece::is_legal_check(j, i, l, k, tab[j][i], false, tab))
						{
							black[l][k] = 1;
						}
					}
				}
			}
		}
	}
}

ostream& operator<<(ostream& out, const Piece& piece)
{

	switch (piece.piecetype)
	{
	case Piece::p_type::WALL:
	{
		out << "Obstc";
		return out;
	}
	case Piece::p_type::EMPTY:
	{
		out << "-----";
		return out;
	}
	case Piece::p_type::PAWN:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Pa ";
		return out;
	}
	case Piece::p_type::BISHOP:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Bi ";
		return out;
	}
	case Piece::p_type::KNIGHT:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Kn ";
		return out;
	}
	case Piece::p_type::KING:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Ki ";
		return out;
	}
	case Piece::p_type::QUEEN:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Qu ";
		return out;
	}
	case Piece::p_type::ROOK:
	{
		piece.color == 1 ? out << " W" : out << " B";
		out << "Ro ";
		return out;
	}
	}

}

bool Piece::is_legal_check(int ic, int ir, int fc, int fr, Piece piece, bool trn, Piece tab[8][8])
{
	switch (piece.piecetype)
	{
	case Piece::p_type::PAWN:
	{
		if (piece.color == true)
		{
			if ((fr == ir + 1) && (abs(fc - ic) == 1)) return 1;
		}
		else if (piece.color == false)
		{
			if ((ir == fr + 1) && (abs(fc - ic) == 1)) return 1;
		}
		else return 0;
		break;
	}
	case Piece::p_type::ROOK:
	{
		if ((fr == ir || fc == ic))
		{
			if (fc == ic && fr > ir)
			{
				for (int i = ir + 1; i < fr; i++)
				{
					if (tab[fc][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			else if (fc == ic && fr < ir)
			{
				for (int i = ir - 1; i > fr; i--)
				{
					if (tab[fc][i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			else if (fr == ir && fc > ic)
			{
				for (int i = ic + 1; i < fc; i++)
				{
					if (tab[i][fr].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			else if (fr == ir && fc < ic)
			{
				for (int i = ic - 1; i > fc; i--)
				{
					if (tab[i][fr].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			else return 0;
		}
		else return 0;
		break;
	}
	case Piece::p_type::BISHOP:
	{
		if (abs(fc - ic) == abs(fr - ir))
		{
			if ((fc - ic) > 0 && (fr - ir) > 0) //topright
			{
				for (int i = 1; i < fc - ic; i++)
				{
					if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			if ((fc - ic) > 0 && (fr - ir) < 0) //bottomright
			{
				for (int i = 1; i < fc - ic; i++)
				{
					if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			if ((fc - ic) < 0 && (fr - ir) > 0)//topleft
			{
				for (int i = 1; i < fr - ir; i++)
				{
					if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
			if ((fc - ic) < 0 && (fr - ir) < 0)//bottomleft
			{
				for (int i = 1; i < ir - fr; i++)
				{
					if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
				}
				return 1;
			}
		}
		else return 0;
		break;
	}
	case Piece::p_type::KING:
	{
		if ((abs(fc - ic) == 1 || abs(fc - ic) == 0) && (abs(fr - ir) == 1 || abs(fr - ir) == 0))
		{
			if (fr == ir && ic == fc) return 0;
			else return 1;
		}
		else return 0;
		break;
	}
	case Piece::p_type::QUEEN:
	{
		if (fc == ic || fr == ir)
		{
			if ((fr == ir || fc == ic))
			{
				if (fc == ic && fr > ir)
				{
					for (int i = ir + 1; i < fr; i++)
					{
						if (tab[fc][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				else if (fc == ic && fr < ir)
				{
					for (int i = ir - 1; i > fr; i--)
					{
						if (tab[fc][i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				else if (fr == ir && fc > ic)
				{
					for (int i = ic + 1; i < fc; i++)
					{
						if (tab[i][fr].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				else if (fr == ir && fc < ic)
				{
					for (int i = ic - 1; i > fc; i--)
					{
						if (tab[i][fr].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				else return 0;
			}
			else return 0;
			break;
		}
		else if (abs(fc - ic) == abs(fr - ir))
		{
			if (abs(fc - ic) == abs(fr - ir))
			{
				if ((fc - ic) > 0 && (fr - ir) > 0) //topright
				{
					for (int i = 1; i < fc - ic; i++)
					{
						if (tab[ic + i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				if ((fc - ic) > 0 && (fr - ir) < 0) //bottomright
				{
					for (int i = 1; i < fc - ic; i++)
					{
						if (tab[ic + i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				if ((fc - ic) < 0 && (fr - ir) > 0)//topleft
				{
					for (int i = 1; i < fr - ir; i++)
					{
						if (tab[ic - i][ir + i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
				if ((fc - ic) < 0 && (fr - ir) < 0)//bottomleft
				{
					for (int i = 1; i < ir - fr; i++)
					{
						if (tab[ic - i][ir - i].piecetype != Piece::p_type::EMPTY) return 0;
					}
					return 1;
				}
			}
		}
		else return 0;
		break;
	}
	case Piece::p_type::KNIGHT:
	{
		if ((abs(fc - ic) == 1 && abs(fr - ir) == 2) || (abs(fc - ic) == 2 && abs(fr - ir) == 1)) return 1;
		else return 0;
		break;
	}
	case Piece::p_type::EMPTY:
	{
		return 0;
		break;
	}
	}
	return 0;
}

bool Piece::check_options(Piece tab[8][8], bool trn)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j].color == trn && tab[i][j].piecetype != Piece::p_type::EMPTY)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						if (is_legal_2(i, j, k, l, tab[i][j], trn, tab)) return true;
					}
				}
			}
		}
	}
	return false;
}

bool Piece::finalcheck(Piece tab[8][8], bool trn)
{
	bool wht[8][8];
	bool blc[8][8];

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			wht[i][j] = 0;
			blc[i][j] = 0;
		}
	}

	white_control(tab, wht);
	black_control(tab, blc);

	if (trn)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (tab[i][j].piecetype != Piece::p_type::EMPTY && tab[i][j].color == trn && blc[i][j] == 1)
				{
					return true;
				}
			}
		}
		return false;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (tab[i][j].piecetype != Piece::p_type::EMPTY && tab[i][j].color == trn && wht[i][j] == 1)
				{
					return true;
				}
			}
		}
		return false;
	}
}

lastmove::lastmove()
{
	counter = 0;
	i_c = i_r = f_c = f_r = -1;
	doublemove = false;
	Piece tmp;
	//piece = tmp;
}