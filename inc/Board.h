/*
 * board.h
 *
 *  Created on: 2011-12-26
 *      Author: kevin
 */
#include <iostream>
#include "Square.h"
#ifndef BOARD_H_

class Board
{
	Square** grid;
	short int numfilled;

private:
	// allocate a new array of size 24 containing all squares belonging to the same
	// 'zone' as the square located at row, col
	// 0-7 = row
	// 8-15 = column
	// 16-23 = box
	Square** getNbrs(int row, int col);

public:
	Board();
	~Board();
	// Initialize the Board from 'file'.txt
	// Set initial conditions, adjacencies etc.
	void Initialize(const char* file);
	// Attempt to solve the puzzle by using square algorithms
	void Solve();
	friend std::ostream& operator<<(std::ostream& out, Board& B);
};


#define BOARD_H_


#endif /* BOARD_H_ */
