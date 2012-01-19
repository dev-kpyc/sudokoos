/*
 * Square.cpp
 *
 *  Created on: 2011-12-26
 *      Author: kevin
 */

#include "Square.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Square::Square() : filled(false), num(0)
{
	possibility[0] = false;
	for (int i=1; i<10; i++)
		possibility[i] = true;
}
Square::~Square()
{
	if (nbrs != NULL)
	{
		delete [] nbrs;
	}
}

void Square::Init(Square** adj)
{
	nbrs = adj;
}

bool Square::Set(int n)
{
	if (n > 9 || n < 1) return false;
	// If square is empty and n is a possibility
	if (filled) return false;
	if (possibility[n])
	{
		num = n;
		filled = true;
		// Update neighbours
		for (int i=0; i<10; i++) if (i != n) possibility[i]=false;
		UpdatePossibilites();
		return true;
	}
	else
	{
		// n is not a possibility
		return false;
	}
}

void Square::UpdatePossibilites()
{
	for (int i=0; i<24; i++)
	{
		nbrs[i]->possibility[num] = false;
	}
}

void Square::GetPossibilites()
{
	for (int i=0; i<24; i++)
	{
		if (nbrs[i]->filled)
		{
			possibility[nbrs[i]->num] = false;
		}
	}
}

bool Square::SinglePossibility()
{
	int n=0;

		for (int i=1; i<10; i++)
		{
			if (possibility[i]) n++;
		}

		if (n == 0)
		{
			// If no possibilities were found, error
			// Either algorithms were wrong or
			// Invalid Sudoku Grid
			std::cerr << "Invalid Sudoku Grid" << std::endl << "Exiting";
			exit(1);
		}
		// Only one possibility, so we give the square this value
		else if (n == 1)
		{
			int candidate;
			for (int i=1; i<10; i++)
			if (possibility[i])
			{
				candidate=i;
				break;
			}
			Set(candidate);
			return true;
		}
		else
		{
			return false;
		}
		return false;
}

bool Square::GroupExclusion()
{
	// check row
	bool hpossibility[10];
	for (int i=1; i<10; i++) hpossibility[i]=false;

	for (int i=0; i<8; i++)
	{
		for (int p=1; p<10; p++)
		{
			if (!nbrs[i]->possibility[p]) hpossibility[p]=true;
		}
	}
	for (int j=1; j<10; j++)
	if (!hpossibility[j])
	{
		Set(j);
		return true;
	}

	bool vpossibility[10];
	for (int i=1; i<10; i++) vpossibility[i]=false;

	for (int i=8; i<16; i++)
	{
		for (int p=1; p<10; p++)
		{
			if (nbrs[i]->possibility[p]) vpossibility[p]=true;
		}
	}
	for (int j=1; j<10; j++)
	if (!vpossibility[j])
	{
		Set(j);
		return true;
	}

	bool bpossibility[10];
	for (int i=1; i<10; i++) bpossibility[i]=false;

	for (int i=16; i<24; i++)
	{
		for (int p=1; p<10; p++)
		{
			if (nbrs[i]->possibility[p]) bpossibility[p]=true;
		}
	}
	for (int j=1; j<10; j++)
	if (!bpossibility[j])
	{
		Set(j);
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, Square& S)
{
	if (S.filled) out << S.num;
	else out << ' ';
	return out;
}

