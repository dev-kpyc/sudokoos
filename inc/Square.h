/*
 * square.h
 *
 *  Created on: 2011-12-26
 *      Author: kevin
 */
#include <iostream>
#include <map>

#ifndef SQUARE_H_
class Square
{
	bool filled;
	int num;
	bool possibility[10];
	Square** nbrs;

private:
	// get possibilities by checking the filled in squares on neighbours
	void GetPossibilites();
	// update possibilities on neighbours
	void UpdatePossibilites();
public:
	Square();
	~Square();
	// initialize the square with its neighbours
	void Init(Square** adj);
	// set the value of the square, if possible. otherwise return false.
	// update neighbours with new possibilites
	bool Set(int n);
	bool IsFilled() { return filled; }

	//Implements the 'single possibility' strategy
	//If it works fills in the square, and returns true
	bool SinglePossibility();
	//Implements the 'group exclusion' strategy
	//If it works fills in the square, and returns true
	bool GroupExclusion();

	friend std::ostream& operator<<(std::ostream& out, Square& S);
};

#define SQUARE_H_


#endif /* SQUARE_H_ */
