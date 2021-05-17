#pragma once
#include <iostream>
#include <vector>       // required to work with vectors
#include <algorithm> 

#include <nana/gui/widgets/picture.hpp>
#include <nana/gui.hpp>
#include "Card.h"
/*************************
* Author: Hoang Do
* Version: 1.1
* File name: Image.h
* Purpose: This file to store the images
*******************************/
using namespace std;
using namespace nana;
using namespace paint;
using namespace FinalProject;

class Image : public Card {

public:
	//std::vector<Image> vec;
	inline Image() {}

	image cardBack = image("catBack4.bmp");
	//First index will be backCard
	vector<paint::image> cardImages = { 
		image("card1.bmp"), image("card2.bmp"), image("card3.bmp"), image("card4.bmp"),
		image("card5.bmp"), image("card6.bmp"), image("card7.bmp"), image("card8.bmp"),
		image("card9.bmp"),image("card10.bmp")
	};



	 ~Image() {};

};
