//===========================================================================
//HW_2.cpp
//This program is designed to create a grid world that is playable by the user.
//A start and a goal is defined, then the user may move an agent towards the
//goal. The user may also have the omnipotent program guide the agent to the goal.
//
//Input:
//	N/A
//			
//Output:
//  N/A
//
//===========================================================================

/*
DEBUG HELPER

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
int chkpnt = 0;
cout << "checkpoint " << chkpnt << endl;
chkpnt++;
//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
cout << "checkpoint " << chkpnt << endl;
chkpnt++;
//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

*/

//#define NDEBUG
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cassert>
#include <random>
#include <vector>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <Windows.h>

using namespace std;

// Function Prototypes
void welcome();

// Classes
class board
{
public:
	deque<int> x_pos;
	deque<int> y_pos;
	deque<int> score;
	int heat_map[100][100][1];
	int max = 100;
	int start_pos[3];
	int goal_pos[3];
	int board_size[3];
	int move_count;

	void create_board();
	void display_board();
	int move_agent_u();
	int move_agent_h();
};

//===========================================================================					MAIN
int main()
{
	welcome();

	board GW;
	GW.create_board();

	cout << "\t\tUser Play or Hard Code Play? (U/h)" << endl;
	char letter;
	cin >> letter;

	int boo = 0;
	switch (letter)
	{
	case 'U':
	case 'u':
	default:
		while (boo != -1)
		{
			GW.display_board();
			boo = GW.move_agent_u();
		}
		break;
	case 'h':
	case 'H':
		while (boo != -1)
		{
			GW.display_board();
			boo = GW.move_agent_h();
		}
	}

	return 0;
}

//===========================================================================					welcome
void welcome()
{
	cout << "\n\n\t\t       Welcome to the Grid World\n\n\n" << endl;
	system("PAUSE");
}

//===========================================================================					board::create_board
void board::create_board()
{
	system("CLS");

	// Initialize Score
	score.push_front(0);
	// Initialize Move Count
	move_count = 0;

	// ======================================
	// Get grid width
	cout << "How wide do you want the world to be?" << endl;
	cin >> board_size[1];
	// Check width
	while (board_size[1] < 0 || board_size[1] > max)
	{
		cout << "\n\t\t    ***" << board_size[1] << " is not a valid width***\n\n " <<
			"Please pick a new world width.\n" << endl;
		cin >> board_size[1];
	}

	// Get grid height
	cout << "How tall do you want the world to be?" << endl;
	cin >> board_size[2];
	// Check height
	while (board_size[2] < 0 || board_size[2] > max)
	{
		cout << "\n\t\t    ***" << board_size[2] << " is not a valid height***\n\n " <<
			"Please pick a new world height.\n" << endl;
		cin >> board_size[2];
	}

	// ======================================
	// Start Position
	cout << "Define start position" << endl;

	cout << "X Coordinate?" << endl;
	cin >> start_pos[1];
	// Check start location
	while (start_pos[1] < 0 || start_pos[1] > board_size[1])
	{
		cout << "\n\t\t    ***" << start_pos[1] << " is not a valid start position***\n\n " <<
			"Please pick a new start position.\n" << endl;
		cin >> start_pos[1];
	}

	cout << "Y Coordinate?" << endl;
	cin >> start_pos[2];
	// Check start location
	while (start_pos[2] < 0 || start_pos[2] > board_size[2])
	{
		cout << "\n\t\t    ***" << start_pos[2] << " is not a valid start position***\n\n " <<
			"Please pick a new start position.\n" << endl;
		cin >> start_pos[2];
	}

	// Set agent initial position to start position
	x_pos.push_front(start_pos[1]);
	y_pos.push_front(start_pos[2]);

	// ======================================
	// Goal Position
	cout << "Define goal position" << endl;
	int temp = 0;
	do
	{
		if (temp == -1)
		{
			cout << "\n\t\t    ***[" << goal_pos[1] << "," << goal_pos[2] <<
				"] is not a valid goal position***\n\n" << "Goal is on top of start.\n\n"
				"Please pick a new goal position.\n" << endl;
		}
		cout << "X Coordinate?" << endl;
		cin >> goal_pos[1];
		// Check goal location
		while (goal_pos[1] < 0 || goal_pos[1] > board_size[1])
		{
			cout << "\n\t\t    ***" << goal_pos[1] << " is not a valid goal position***\n\n " <<
				"Please pick a new goal position.\n" << endl;
			cin >> goal_pos[1];
		}

		cout << "Y Coordinate?" << endl;
		cin >> goal_pos[2];
		// Check start location
		while (goal_pos[2] < 0 || goal_pos[2] > board_size[2])
		{
			cout << "\n\t\t    ***" << goal_pos[2] << " is not a valid goal position***\n\n " <<
				"Please pick a new goal position.\n" << endl;
			cin >> goal_pos[2];
		}

		temp = -1;
	} while (goal_pos[1] == start_pos[1] && goal_pos[2] == start_pos[2]);

	// ======================================
	// Create Heat Map

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			if (i < board_size[1] && j < board_size[2])
			{
				heat_map[i][j][0] = 0;
			}
			else
			{
				heat_map[i][j][0] = -1;
			}
		}
	}

	system("PAUSE");
}

//===========================================================================					board::display_board
void board::display_board()
{
	system("CLS");

	// Top Border
	cout << "++";
	for (int i = 0; i < board_size[1]; i++)
	{
		cout << "++";
	}
	cout << "+" << endl;

	// Board and Side Borders
	for (int j = 1; j < board_size[2] + 1; j++)
	{
		cout << "+ ";
		for (int i = 1; i < board_size[1] + 1; i++)
		{
			if (i == goal_pos[1] && j == goal_pos[2])
			{
				cout << "G ";
			}
			else if (i == x_pos[0] && j == y_pos[0])
			{
				if (i == goal_pos[1] && j == goal_pos[2])
				{
				}
				else
				{
					cout << "A ";
				}
			}
			else if (i == start_pos[1] && j == start_pos[2])
			{
				if (i == x_pos[0] && j == y_pos[0])
				{
				}
				else
				{
					cout << "S ";
				}
			}
			else
			{
				cout << "  ";
			}
		}
		cout << "+" << endl;
	}

	// Bottom Border
	cout << "++";
	for (int i = 0; i < board_size[1]; i++)
	{
		cout << "++";
	}
	cout << "+" << endl;
}

//===========================================================================					board::move_agent_u
int board::move_agent_u()
{
	cout << "\nW -> Up\t\t\tMove #" << move_count
		<< "\nS -> Down\t\tStart: [" << start_pos[1] << "," << start_pos[2] << "]"
		<< "\nA -> Left\t\tGoal:  [" << goal_pos[1] << "," << goal_pos[2] << "]"
		<< "\nD -> Right\t\tAgent: [" << x_pos[0] << "," << y_pos[0] << "]"
		<< "\nQ -> Quit" << endl;
	char key = 't';
	int boo = 0;

	while ((!(key == 'w' || key == 'W'
		   || key == 'a' || key == 'A'
		   || key == 's' || key == 'S'
		   || key == 'd' || key == 'D'
		   || key == 'q' || key == 'Q')))
	{
		//pick up the char associated with the keypress
		key = _getch();
		switch (key)
		{
		case 'w':
		case 'W':
			x_pos.push_front(x_pos[0]);
			y_pos.push_front(y_pos[0] - 1);
			move_count++;
			break;
		case 'a':
		case 'A':
			x_pos.push_front(x_pos[0] - 1);
			y_pos.push_front(y_pos[0]);
			move_count++;
			break;
		case 's':
		case 'S':
			x_pos.push_front(x_pos[0]);
			y_pos.push_front(y_pos[0] + 1);
			move_count++;
			break;
		case 'd':
		case 'D':
			x_pos.push_front(x_pos[0] + 1);
			y_pos.push_front(y_pos[0]);
			move_count++;
			break;
		case 'q':
		case 'Q':
			boo = -1;
			break;
		default:
			x_pos.push_front(x_pos[0]);
			y_pos.push_front(y_pos[0]);
			break;
		}
	}
	if (x_pos[0] <= 0 || x_pos[0] > board_size[1] || y_pos[0] <= 0 || y_pos[0] > board_size[2])
	{
		x_pos.pop_front();
		y_pos.pop_front();
		move_count = move_count - 1;
	}
	return boo;

}

//===========================================================================					board::move_agent_h
int board::move_agent_h()
{
	cout << "\nW -> Up\t\t\tMove #" << move_count
		<< "\nS -> Down\t\tStart: [" << start_pos[1] << "," << start_pos[2] << "]"
		<< "\nA -> Left\t\tGoal:  [" << goal_pos[1] << "," << goal_pos[2] << "]"
		<< "\nD -> Right\t\tAgent: [" << x_pos[0] << "," << y_pos[0] << "]"
		<< "\nQ -> Quit" << endl;
	int boo = 0;
	int dist;

	if (x_pos[0] != goal_pos[1])
	{
		dist = goal_pos[1] - x_pos[0];
		if (dist > 0)
		{
			x_pos.push_front(x_pos[0] + 1);
			y_pos.push_front(y_pos[0]);
			move_count++;
		}
		else
		{
			x_pos.push_front(x_pos[0] - 1);
			y_pos.push_front(y_pos[0]);
			move_count++;
		}
	}
	else if (y_pos[0] != goal_pos[2])
	{
		dist = goal_pos[2] - y_pos[0];
		if (dist > 0)
		{
			x_pos.push_front(x_pos[0]);
			y_pos.push_front(y_pos[0] + 1);
			move_count++;
		}
		else
		{
			x_pos.push_front(x_pos[0]);
			y_pos.push_front(y_pos[0] - 1);
			move_count++;
		}
	}
	else
	{
		boo = -1;
		cout << "CONGRATULATIONS!\tYour computer made it to the goal!" << endl;
	}
	Sleep(250);
	return boo;
}