#include <iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, Space = 32 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

const int board = 9;

class sudoku
{
	int X = 0, Y = 0;
	int Xi = 0, Yi = 0;
	int nums[board][board];
	bool fill = true;
public:
	sudoku()
	{
		for (size_t i = 0; i < board; i++)
		{
			for (size_t j = 0; j < board; j++)
			{
				nums[i][j] = 0;
			}
		}
	}

	void showBoard()
	{
		for (int i = 0; i < board; i++)
		{
			for (size_t j = 0; j < board; j++)
			{
				setCursor(X, Y);
				if (i == Yi and j == Xi)
				{
					setColor(Black, White);
				}
				cout << nums[i][j];
				setColor(White, Black);
				X += 2;
			}
			Y++;
			X = 0;
		}
		X = 0;
		Y = 0;
	}
	void Fill(int a[board][board])
	{
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				nums[j][i] = a[j][i];
			}
		}
	}
	void fillBoard()
	{
		int key;
		do
		{
			showBoard();
			key = _getch();
			switch (key)
			{
			case Up:
				if (Yi != 0)
				{
					Yi--;
				}
				else
				{
					Yi = 8;
				}
				break;
			case Down:
				if (Yi == 8)
				{
					Yi = 0;
				}
				else
				{
					Yi++;
				}
				break;
			case Right:
				if (Xi == 8)
				{
					Xi = 0;
				}
				else
				{
					Xi++;
				}
				break;
			case Left:
				if (Xi == 0)
				{
					Xi = 8;
				}
				else
				{
					Xi--;
				}
				break;
			}
			if (key >= 48 and key < 58)
			{
				nums[Yi][Xi] = key - 48;
			}

		} while (key != Enter);

	}
	bool canPlace(int x, int y, int number)
	{
		for (size_t i = 0; i < board; i++)
		{
			for (size_t j = 0; j < board; j++)
			{
				if (nums[x][j] == number or nums[i][y] == number)
				{
					return false;
				}
			}
			
		}
		int startx = x - x % 3;
		int starty = y - y % 3;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (nums[i + startx][j + starty] == number)
				{
					return false;
				}
			}
		}
		return true;
	}
	bool slove()
	{
		
		for (size_t x = 0; x < board; x++)
		{
			for (size_t y = 0; y < board; y++)
			{
				if (nums[x][y] == 0)
				{
					fill = false;
				}
			}
		}
		if (fill)
		{
			return true;
		}
		for (size_t x = 0; x < board; x++)
		{
			for (size_t y = 0; y < board; y++)
			{
				if (nums[x][y] == 0)
				{
					for (size_t number = 1; number <= 9; number++)
					{
						if (canPlace(x, y, number))
						{
							nums[x][y] = number;
							showBoard();
							if (slove())
							{
								return true;
							}
							nums[x][y] = 0;
						}
					}

					return false;
				}
				
			}
		}
	}
};

int main()
{
	sudoku sud;

	int arr[board][board] = { {4,7,3,0,2,5,8,0,1},
							  {9,2,6,0,8,7,3,4,5},
							  {8,5,1,0,3,4,7,2,6},
							  {2,1,9,0,7,6,5,3,8},
							  {7,3,4,0,5,9,1,6,2},
							  {6,8,5,0,1,3,4,7,9},
							  {1,9,7,0,6,8,2,5,4},
							  {5,6,8,0,4,2,9,1,3},
							  {3,4,2,0,9,1,6,8,7} };

	sud.Fill(arr);

	sud.fillBoard();
	sud.slove();

	if (sud.slove())
	{
		setCursor(0, 10);
		cout << "Poluchilos";
	}
	else
	{
		setCursor(0, 10);
		cout << "Ne poluchilos";

	}


	
}