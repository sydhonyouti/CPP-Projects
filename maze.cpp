/******************************************************************************************************************************
 Author: Sydney Honyouti
 Date: 11/8/2020
 Program: Maze Program - This program will read a maze text file and determine if there is a way out of the maze.
 The Push, Pop, and Empty function will be used to run through the maze file. The results of the maze will be ouputted in a 
 new text file called mazeSolutions.txt.
 *****************************************************************************************************************************/
 //Application file
#include <iostream>
#include <fstream>
#include "Stack.h";
#include <cstdlib>
#include <vld.h>
using namespace std;

int main()
{
	//Maze constants
	//Max a maze can be is 80 x 80
	const int MAXROW = 80;
	const int MAXCOL = 80;
	char maze[MAXROW][MAXCOL];
	int rowIn, colIn, startRow, startCol, rowSize, colSize, tempRowSize, tempColSize;
	int mazeCount = 0;
	bool success = false;
	ifstream MazeFile("mazeFile.txt");
	ofstream MazeSolution("mazeSolutions.txt");

	MazeSolution << "Solutions to A-MAZE-ING Stacks Assignment" << endl;
	MazeSolution << "Sydney Honyouti" << endl << endl;

	if (!MazeFile)
	{
		cout << "There's no file. \n";
		return 0;
	}
	else
	{
		//reading in row and column size
		MazeFile >> rowSize >> colSize;
		//putting row size and column size in a temporary variable for later use
		tempRowSize = rowSize;
		tempColSize = colSize;
		do
		{
			for (rowIn = 0; rowIn < rowSize; rowIn++)
			{
				for (colIn = 0; colIn < colSize; colIn++)
					//reading maze from file
					MazeFile >> maze[rowIn][colIn];
			}
			//reads in the start of the maze mark
			MazeFile >> startRow >> startCol;
			mazeCount++;

			//create a stack to hold possible moves
			Stack PossMoves;

			//application can use Coordinate to hold row and column
			Coordinate Current;

			//initialize current coordinate in maze to what the maze file initializes it
			Current.ROW = startRow;
			Current.COL = startCol;

			if (maze[Current.ROW][Current.COL] == 'E')
			{
				success = true;
				//outputting solution
				MazeSolution << "MAZE NUMBER " << mazeCount << endl << endl;
				for (Current.ROW = 0; Current.ROW < tempRowSize; Current.ROW++)
				{
					for (Current.COL = 0; Current.COL < tempColSize; Current.COL++)
						MazeSolution << maze[Current.ROW][Current.COL];
					MazeSolution << endl;
				}
				MazeSolution << endl << "There IS a way out! \n" << endl;
			}
			else
			{
				//Pushing current coordinate
				PossMoves.Push(Current);
				//breadcrumb to indicate you already visited the spot
				maze[Current.ROW][Current.COL] = '.';

				//While the stack isn't empty
				while (!PossMoves.Empty())
				{
					//Pop stack to get the current location
					PossMoves.Pop(Current);

					//Checking to see if Current is E
					if (maze[Current.ROW][Current.COL] == 'E')
					{
						success = true;
						//outputting the maze
						if (success)
						{
							MazeSolution << "MAZE NUMBER " << mazeCount << endl << endl;
							for (Current.ROW = 0; Current.ROW < tempRowSize; Current.ROW++)
							{
								for (Current.COL = 0; Current.COL < tempColSize; Current.COL++)
									MazeSolution << maze[Current.ROW][Current.COL];
								MazeSolution << endl;
							}
							MazeSolution << endl << "There IS a way out! \n" << endl;
						}
					}

					//North
					else if (maze[Current.ROW - 1][Current.COL] == '0' || maze[Current.ROW - 1][Current.COL] == 'E')
					{
						if (maze[Current.ROW - 1][Current.COL] == '0')
						{
							PossMoves.Push(Current);

							//breadcrumb
							maze[Current.ROW - 1][Current.COL] = '.';

							//Update the Coordinates in the maze array
							maze[Current.ROW--][Current.COL];

							//Push it back into the stack
							PossMoves.Push(Current);
						}
						else
							success = true;
					}

					//East
					else if (maze[Current.ROW][Current.COL + 1] == '0' || maze[Current.ROW][Current.COL + 1] == 'E')
					{
						if (maze[Current.ROW][Current.COL + 1] == '0')
						{
							PossMoves.Push(Current);
							maze[Current.ROW][Current.COL + 1] = '.';
							maze[Current.ROW][Current.COL++];
							PossMoves.Push(Current);
						}
						else
							success = true;
					}

					//South
					else if (maze[Current.ROW + 1][Current.COL] == '0' || maze[Current.ROW + 1][Current.COL] == 'E')
					{
						if (maze[Current.ROW + 1][Current.COL] == '0')
						{
							PossMoves.Push(Current);
							maze[Current.ROW + 1][Current.COL] = '.';
							maze[Current.ROW++][Current.COL];
							PossMoves.Push(Current);
						}
						else
							success = true;
					}

					//West
					else if (maze[Current.ROW][Current.COL - 1] == '0' || maze[Current.ROW][Current.COL - 1] == 'E')
					{
						if (maze[Current.ROW][Current.COL - 1] == '0')
						{
							PossMoves.Push(Current);
							maze[Current.ROW][Current.COL - 1] = '.';
							maze[Current.ROW][Current.COL--];
							PossMoves.Push(Current);
						}
						else
							success = true;
					}
				}
				//outputting the maze
				if (success)
				{
					MazeSolution << "MAZE NUMBER " << mazeCount << endl << endl;
					for (Current.ROW = 0; Current.ROW < tempRowSize; Current.ROW++)
					{
						for (Current.COL = 0; Current.COL < tempColSize; Current.COL++)
							MazeSolution << maze[Current.ROW][Current.COL];
						MazeSolution << endl;
					}
					MazeSolution << endl << "There IS a way out! \n" << endl;
				}
				else if (!success)
				{
					MazeSolution << "MAZE NUMBER " << mazeCount << endl << endl;
					for (Current.ROW = 0; Current.ROW < tempRowSize; Current.ROW++)
					{
						for (Current.COL = 0; Current.COL < tempColSize; Current.COL++)
							MazeSolution << maze[Current.ROW][Current.COL];
						MazeSolution << endl;
					}
					MazeSolution << endl << "There IS NOT a way out! \n" << endl;
				}
			}
	
			//clearing the maze and reseting success variable
			for (Current.ROW = 0; Current.ROW < tempRowSize; Current.ROW++)
			{
				for (Current.COL = 0; Current.COL < tempColSize; Current.COL++)
					maze[Current.ROW][Current.COL] = NULL;
			}
			success = false;
			//reading in the maze size
			MazeFile >> rowSize >> colSize;
			tempRowSize = rowSize;
			tempColSize = colSize;

		} while (rowSize != -1 && colSize != -1);
	}
	MazeSolution.close();
	MazeFile.close();
}