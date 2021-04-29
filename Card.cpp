/*************************************************************************
 * Author: Hoang Do
 * Student number: 040961749
 * Date created: 04/05/2021
 * Lab section: 304
 * Name file: Card.cpp
 * Purpose: Store the image, index and states
 *************************************************************************/

#include "Card.h"
#include <iostream>    // using IO functions
#include <string>   

/*
	Purpose: This is only for checking card is matched!!
*/
using namespace std;
using namespace FinalProject;



FinalProject::Card::Card()
{
	index = 0;
	row = 0;
	column = 0;
	state = -2;
	currentIMG = image();
}

FinalProject::Card::Card(int index, int state, image currIMG)
{
	
	this->index = index;
	this->state = state;
	this->currentIMG = currIMG;
}

FinalProject::Card::~Card()
{
}

int FinalProject::Card::getIndex()
{
	return index;
}

void FinalProject::Card::setIndex(int index)
{
	this->index = index;
}

int FinalProject::Card::getstate()
{
	return state;
}

void FinalProject::Card::setState(int m_state)
{
	this->state = m_state;
}

void FinalProject::Card::calLocation(int index)
{
	//Using index to find row and column



}

image FinalProject::Card::getImage()
{
	return currentIMG;
}

void FinalProject::Card::setImage(image img)
{
	this->currentIMG = img;
}

bool FinalProject::Card::operator==(Card& other)
{
	return this->getImage() == other.getImage();
}

std::ostream& FinalProject::operator<<(std::ostream& out, const Card& f)
{
	return out;
}
