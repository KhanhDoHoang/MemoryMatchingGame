#pragma once
#ifndef CARD_H
#define CARD_H

#include <nana/gui/widgets/picture.hpp>
#include <nana/gui.hpp>

#include <iostream>
#include <String.h>
#include <vector>      
#include <algorithm> 

using namespace nana;
using namespace paint;
using namespace std;
/*************************
* Author: Hoang Do
* Version: 1.1
* File name: Card.h
* Purpose: This is only for checking card states and index
*******************************/
namespace FinalProject {
	class Card{
	private:
		friend std::ostream& operator<<(std::ostream& out, const Card& f);
		int row;
		int column;
		int index;
		int state;
		image currentIMG;

		//This array holse the suit of each card
		//vector<Image> imageBoard;

	public:
		Card();
		Card(int index, int state, image currIMG);
		~Card();

		int getIndex();
		void setIndex(int index);
		
		int getstate();
		void setState(int m_state);

		void calLocation(int index);

		image getImage();
		void setImage(image img);

		bool operator==(Card& other);
		
		//virtual Image imageToShow(int row, int column) = 0;

	};
}

#endif