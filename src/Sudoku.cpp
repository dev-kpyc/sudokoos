/*
 * sudoku.cpp
 *
 *  Created on: 2011-12-26
 *      Author: kevin
 */

#include "Square.h"
#include "Board.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Board Sudoku;

	if (argc == 1) Sudoku.Initialize("sudoku.txt");
	else	Sudoku.Initialize(argv[1]);

	std::cout << Sudoku << std::endl;
	Sudoku.Solve();
	std::cout << Sudoku;

	return 0;
}
