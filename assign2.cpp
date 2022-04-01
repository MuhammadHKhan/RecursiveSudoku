#include <iostream>
#include <fstream>

using namespace std;
//this function is a recursive boolean function that will 
//check to see if a certain number can be used on the spot
//in the sudoku board. If not, there will be a loop that will keep iterating from 
//1 - 9 to see if the number can be used in the spot.
//the function will check for row, column, and sector to see 
//if a number only appears once in those areas.
//when the game reaches the last row and column, it will return
//true, otherwise, keep recursing until the board is filled
bool assignNum(int board[9][9], int x, int y)//pass in the board, row, and column
{
	if (x == 8)
	{
		if (y == 9) //check to see if the last column has been checked
		{           //along with the row
			return true; //base case
		}
	}

	if (y == 9) //if the last column is reached already, set it back to zero
	{         //and increase the row count, the x variable
		y = 0;
		x = x + 1;
	}
	//if the number is already on the board, go to the next column by incrementing y
	if (board[x][y] != 0)
	{
		return assignNum(board, x, y + 1); //check the next number in the row
	}
	//this loop will check numbers from 1 - 9 for each space in the board that is occupied
	//by a zero
	for (int i = 1; i <= 9; i++)
	{
		bool tof = true;//bool variable to check if the row, col, and sector have been passed
		int rr;     //help with the sector loop 
		int cc;     //help with the sector loop
		int rowCount;   //will be used in the sector loop
		int colCount;   //will be used in the sector loop

		rr = x % 3;   //row modulo 3 will give what sector we are in
		rowCount = x - rr;  //subtract rr from the row to stay in the designated sector
		cc = y % 3;   //col modulo 3 will give what sector we are in 
		colCount = y - cc;  //subtract cc from the col to stay in the designated sector 

		for (int j = 0; j < 9; j++)
		{
			if (board[x][j] == i) //check each column to see if there is the same number
				tof = false;
		}

		for (int j = 0; j < 9; j++)
		{
			if (board[j][y] == i)//check each row to see if there is the same number
				tof = false;
		}

		for (int j = 0; j < 3; j++)//check the current sector to see if the number exists
		{                         //if the number exists, then make tof false, which will keep
			for (int k = 0; k < 3; k++)//that spot at zero
			{
				if (board[rowCount + j][colCount + k] == i)
				{
					tof = false;
				}
			}
		}
		//if no similar number was found in the row, column, and sector, then update that spot
		if (tof == true)
		{
			board[x][y] = i;//update the spot with the current number
			if (assignNum(board, x, y + 1))//check for the next column
			{
				return true;  //keep recursing
			}
		}
		//if tof turned out to be false, keep the spot on the board a zero
		board[x][y] = 0;
	}
	return false; //keep recursing until the board is solved
}

int main()
{
	ifstream ifile; //file that is going to be read in
	bool check = true; //help for file opening loop
	string filename = ""; //user will enter filename
	int board[9][9];		//this will be the sudoku array
	int readIn = 0; //program will read in numbers from the file

	//loop that will try to open the sudoku initial file
	while (check)
	{
		cout << "Enter initial sudoku board file: ";
		cin >> filename;
		if (filename == "NO")
			return 0;
		ifile.open(filename);
		if (ifile)
			check = false;
	}

	//now, read in the numbers from the file into the array
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//now read in the numbers from the file
			ifile >> readIn;
			board[i][j] = readIn;
		}
	}

	cout << "\nInitial board read in\n\n";

	//for testing purposes, print out the board
	cout << "-------------------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "|";
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 0)
			{
				cout << " - ";
			}
			else
			{
				cout << " " << board[i][j] << " ";
			}
			if (j == 2 || j == 5)
			{
				cout << "|";
			}
		}
		cout << "|" << endl;
		if (i == 2 || i == 5 || i == 8)
		{
			cout << "-------------------------------" << endl;
		}
	}

	cout << "\nSudoku puzzle solved\n";

	if (assignNum(board, 0, 0))
	{
		cout << "-------------------------------" << endl;
		for (int i = 0; i < 9; i++)
		{
			cout << "|";
			for (int j = 0; j < 9; j++)
			{
				cout << " " << board[i][j] << " ";
				if (j == 2 || j == 5)
				{
					cout << "|";
				}
			}
			cout << "|" << endl;
			if (i == 2 || i == 5 || i == 8)
			{
				cout << "-------------------------------" << endl;
			}
		}
	}

	ifile.close();
	return 0;
}
