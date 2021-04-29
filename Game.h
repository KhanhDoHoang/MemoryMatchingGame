#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "Card.h"
#include <nana/gui.hpp>

/*************************
* Author: Hoang Do
* Version: 1.1
* File name: Card.h
* Purpose: a Game class which keeps track of the score
*******************************/
namespace FinalProject {
	class Game {
	private:
		int m_ticks;
		string m_users;

	public:

		Game();
		Game(int ticks, string users);
		~Game();
		/* This is for the score */

		int getScore();
		void setScore(int score);

		string getName();
		void setName(string user);

		//This function is for score calculation

		void writeToFile();

		string readFromFile();

	};
}



#endif