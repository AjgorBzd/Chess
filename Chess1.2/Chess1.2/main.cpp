#include <iostream>
#include <iomanip>
#include "piece.h"
using namespace std;
//szachy 2.0
bool rotateboard = false;
Piece board[8][8];
Piece simulation[8][8];
bool white_control[8][8];
bool black_control[8][8];
bool control_check[8][8];
bool turn = 1;
bool check = 0;
lastmove last;
void options();
void game();
void  mainmenu()
{
	char wybor;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << "***     CCCCC  H   H  EEEEE  SSSSS  SSSSS     ***" << endl;
	cout << "***     C      H   H  E      S      S         ***" << endl;
	cout << "***     C      HHHHH  EEEE   SSSSS  SSSSS     ***" << endl;
	cout << "***     C      H   H  E          S      S     ***" << endl;
	cout << "***     CCCCC  H   H  EEEEE  SSSSS  SSSSS     ***" << endl;
	cout << "***                                           ***" << endl;
	cout << "*************************************************" << endl;
	cout << "***************  by Igor Bzdawka  ***************" << endl;
	cout << "*************************************************" << endl << endl << endl << endl;
	cout << "Choose an option:" << endl << "1. Play a game of chess (duh)" << endl;
	cout << "2. Options..." << endl << "3. Exit the game :C" << endl;
	cout << "Choose a number: ";
	cin >> wybor;
	while (wybor != '1' && wybor != '2' && wybor != '3')
	{
		cout << "Wrong number, choose a proper number from 1 to 3: ";
		cin >> wybor;
	}

	if (wybor == '3')
	{
		cout << "Thank you for playing!!!" << endl;
		return;
	}
	if (wybor == '2')
	{
		options();
	}
	if (wybor == '1')
	{
		game();
	}
}
void options()
{
	char wybor;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << "***     CCCCC  H   H  EEEEE  SSSSS  SSSSS     ***" << endl;
	cout << "***     C      H   H  E      S      S         ***" << endl;
	cout << "***     C      HHHHH  EEEE   SSSSS  SSSSS     ***" << endl;
	cout << "***     C      H   H  E          S      S     ***" << endl;
	cout << "***     CCCCC  H   H  EEEEE  SSSSS  SSSSS     ***" << endl;
	cout << "***                                           ***" << endl;
	cout << "*************************************************" << endl;
	cout << "***************  by Igor Bzdawka  ***************" << endl;
	cout << "*************************************************" << endl << endl << endl << endl;
	cout << "Choose an option:" << endl << "0. Go back to the main menu" << endl;
	cout << "1. Rotate map for each player: ";
	if (rotateboard) cout << "ON" << endl;
	else cout << "OFF" << endl;
	cout << "Choose a number: ";
	cin >> wybor;
	while (wybor != '0' && wybor != '1')
	{
		cout << "Wrong number, choose a proper number from 0 to 1: ";
		cin >> wybor;
	}
	if (wybor == '0')
	{
		mainmenu();
		return;
	}
	else if (wybor == '1')
	{
		if (rotateboard) rotateboard = 0;
		else rotateboard = 1;
		options();
		return;
	}

}
bool is_check(Piece tab[8][8], bool white[8][8], bool black[8][8], bool trn)
{
	if (trn)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (tab[i][j].piecetype == Piece::p_type::KING && tab[i][j].color == true)
				{
					return black[i][j];
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (tab[i][j].piecetype == Piece::p_type::KING && tab[i][j].color == false)
				{
					return white[i][j];
				}
			}
		}
	}
}
void printboard_for_white(Piece brd[8][8])
{
	for (int i = 0; i < 40; i++)
	{
		cout << endl;
	}
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
void printboard_for_black(Piece brd[8][8])
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
void game()
{
	cout << "Let's play!" << endl;
	// PART 1 //
	//creating all white pieces
	Piece wr1(0, 0, 1, 0, Piece::p_type::ROOK);
	Piece wr2(7, 0, 1, 0, Piece::p_type::ROOK);
	Piece wn1(1, 0, 1, 0, Piece::p_type::KNIGHT);
	Piece wn2(6, 0, 1, 0, Piece::p_type::KNIGHT);
	Piece wb1(2, 0, 1, 0, Piece::p_type::BISHOP);
	Piece wb2(5, 0, 1, 0, Piece::p_type::BISHOP);
	Piece wq(3, 0, 1, 0, Piece::p_type::QUEEN);
	Piece wk(4, 0, 1, 0, Piece::p_type::KING);
	Piece wp1(0, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp2(1, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp3(2, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp4(3, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp5(4, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp6(5, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp7(6, 1, 1, 0, Piece::p_type::PAWN);
	Piece wp8(7, 1, 1, 0, Piece::p_type::PAWN);
	//creating all black pieces
	Piece br1(0, 7, 0, 0, Piece::p_type::ROOK);
	Piece br2(7, 7, 0, 0, Piece::p_type::ROOK);
	Piece bn1(1, 7, 0, 0, Piece::p_type::KNIGHT);
	Piece bn2(6, 7, 0, 0, Piece::p_type::KNIGHT);
	Piece bb1(2, 7, 0, 0, Piece::p_type::BISHOP);
	Piece bb2(5, 7, 0, 0, Piece::p_type::BISHOP);
	Piece bq(3, 7, 0, 0, Piece::p_type::QUEEN);
	Piece bk(4, 7, 0, 0, Piece::p_type::KING);
	Piece bp1(0, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp2(1, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp3(2, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp4(3, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp5(4, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp6(5, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp7(6, 6, 0, 0, Piece::p_type::PAWN);
	Piece bp8(7, 6, 0, 0, Piece::p_type::PAWN);
	//setting a board and white pieces
	board[0][0] = wr1;
	board[1][0] = wn1;
	board[2][0] = wb1;
	board[3][0] = wq;
	board[4][0] = wk;
	board[5][0] = wb2;
	board[6][0] = wn2;
	board[7][0] = wr2;
	board[0][1] = wp1;
	board[1][1] = wp2;
	board[2][1] = wp3;
	board[3][1] = wp4;
	board[4][1] = wp5;
	board[5][1] = wp6;
	board[6][1] = wp7;
	board[7][1] = wp8;
	//setting black pieces
	board[0][7] = br1;
	board[1][7] = bn1;
	board[2][7] = bb1;
	board[3][7] = bq;
	board[4][7] = bk;
	board[5][7] = bb2;
	board[6][7] = bn2;
	board[7][7] = br2;
	board[0][6] = bp1;
	board[1][6] = bp2;
	board[2][6] = bp3;
	board[3][6] = bp4;
	board[4][6] = bp5;
	board[5][6] = bp6;
	board[6][6] = bp7;
	board[7][6] = bp8;



	for (int j = 2; j < 6; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			Piece empt(i, j, 0, 0, Piece::p_type::EMPTY);

			board[i][j] = empt;
		}
	}
	/*
	//trial setup
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece fill(i, j, 0, 0, Piece::p_type::EMPTY);
			board[i][j] = fill;
		}
	}
	Piece test(3, 3, 0, 0, Piece::p_type::PAWN);
	board[4][3] = test;
	Piece obstacle(3, 3, 1, 0, Piece::p_type::WALL);
	board[5][2] = obstacle;
	*/


	printboard_for_white(board);
	char initc, finishc;
	char initr, finishr;
	while (true)
	{
		if (turn == 1) cout << "White's move" << endl;
		else cout << "Black's move" << endl;
		if (is_check(board, white_control, black_control, turn))
		{
			cout << "CHECK!" << endl;
			/*if (turn)
						{
							for (int i = 7; i >= 0; i--)
							{
								for (int j = 0; j < 8; j++)
								{
									cout << white_control[j][i] << " ";
								}
								cout << endl;
							}
							cout << endl;
						}
						else
						{
							for (int i = 7; i >= 0; i--)
							{
								for (int j = 0; j < 8; j++)
								{
									cout << black_control[j][i] << " ";
								}
								cout << endl;
							}
							cout << endl;
						}*/
		}
		cout << "Give the column and row of a piece you want to move:";
		cin >> initc >> initr;
		cout << "Give the coordinates of a place you want to move to:";
		cin >> finishc >> finishr;
		while (initc < 'a' || initc>'h' || initr < '1' || initr>'8' || finishc < 'a' || finishc>'h' || finishr < '1' || finishr>'8')
		{
			cout << "Wrong notation, try again." << endl;
			cout << "Give the column and row of a piece you want to move:";
			cin >> initc >> initr;
			cout << "Give the coordinates of a place you want to move to:";
			cin >> finishc >> finishr;
		}
		board[1][1].move(initc, int(initr) - 48, finishc, int(finishr) - 48, board, turn, white_control, black_control, control_check, simulation, last,rotateboard);
		if (rotateboard)
		{
			if (!turn) printboard_for_white(board);
			else printboard_for_black(board);
		}
		else printboard_for_white(board);
		// output of white and black
		/*
		for (int i =7; i >=0; i--)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << white_control[j][i]<<" ";
			}
			cout << endl;
		}
		cout << endl;
		*/
		/*
		for (int i = 7;i>=0;i--)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << black_control[j][i] << " ";
			}
			cout << endl;
		}
		*/
		turn == 1 ? turn = 0 : turn = 1;
		if (board[1][1].check_options(board, turn) == false) break;
	}
	check = board[1][1].finalcheck(board, turn);

	if (check)
	{
		if (turn == 1)
		{
			cout << "BLACK WINS!!!" << endl;
		}
		else
		{
			cout << "WHITE WINS!!!" << endl;
		}
	}
	else cout << "Stalemate." << endl;
	cout << endl << "Do you wish to play once again? y/n: ";
	char again;
	cin >> again;
	while (again != 'y' && again != 'n')
	{
		cout << "wrong option, try again: ";
		cin >> again;
	}
	if (again == 'y')
	{
		turn = 1;
		check = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				white_control[i][j] = 0;
				black_control[i][j] = 0;
				control_check[i][j] = 0;
			}
		}
		game();
	}
	if (again == 'n')
	{
		cout << "Thank you for playing!!!" << endl;
		return;
	}
}

int main()
{
	mainmenu();
}