/*
 * Board.cpp
 *
 *  Created on: 2011-12-26
 *      Author: kevin
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <exception>
#include "Board.h"
#include "Square.h"

using namespace std;

Board::Board() : numfilled(0)
{
	grid = new Square* [9];
	for (int i=0; i<9; i++)
	{
		grid[i] = new Square[9];
	}
}

Board::~Board()
{
	for (int i=0; i<9; i++)
		delete [] grid[i];
	delete [] grid;
}
// ALLOCATES NEW MEMORY
// Gets a 20 element array of neighbours for the Square at [row][col]
Square** Board::getNbrs(int row, int col)
{
	Square** nbrs = new Square*[24];
	int n = 0;
	// add all squares on the same row
	for (int i=0; i<9; i++)
	{
		if (i != row)
		{
			nbrs[n] = &grid[i][col];
			n++;
		}
	}
	// add all squares on the same column
	for (int j=0; j<9; j++)
	{
		if (j != col)
		{
			nbrs[n] = &grid[row][j];
			n++;
		}
	}
	// add all squares in the same 'box'
	for (int k=(row/3)*3; k<(((row/3)*3)+3); k++)
	{
			for (int l=(col/3)*3; l<(((col/3)*3)+3); l++)
			{
				if (k != row || l != col)
				{
					nbrs[n] = &grid[k][l];
					n++;
				}
			}

	}

	return nbrs;



}

void Board::Initialize(const char* file)
{
	char c;
	for (int i=0; i<9; i++)
	for (int j=0; j<9; j++)
	{
		grid[i][j].Init(getNbrs(i,j));
	}

	ifstream in(file);
	int k=0;
	int l=0;

	if (in.is_open())
	{
		while (in.good())
		{
			c = in.get();
			if (isdigit(c))
			{
				grid[l][k].Set(c-'0');
				numfilled++;
				k++;
				if (k%10 == 0)
				{
					k=0;
					l++;
				}

			}
			else if (isspace(c))
			{
				k++;
				if (k%10 == 0)
				{
					k=0;
					l++;
				}
			}

		}

		return;
	}
	else
	{
		std::cerr << "File " << file << " could not be opened. Exiting" << std::endl;
		exit(2);
	}

}

void Board::Solve()
{
	int prevfilled = 0;
	// Solver stops if it passes a cycle of the board without solving anything
	// or if the puzzle is completed
	while (numfilled < 81 && prevfilled < numfilled)
	{
		prevfilled = numfilled;

		for (int i=0; i<9; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (!grid[i][j].IsFilled() && grid[i][j].SinglePossibility()) numfilled++;
				else if (!grid[i][j].IsFilled() && grid[i][j].GroupExclusion()) numfilled++;
			}
		}

	}
}

ostream& operator<<(ostream& out, Board& B)
{
	for (int i=0; i<9; i++)
	{
		if (i == 0) out << "-------------" << std::endl;
		for (int j=0; j<9; j++)
		{
			if (j==0) out << '|';
			out << B.grid[i][j];
			if (((j+1) % 3) == 0) out << '|';
		}
		out << std::endl;
		if (((i+1) % 3) == 0) out << "-------------" << std::endl;
	}
	return out;
}

