/*************************************************************************
 * Author: Hoang Do
 * Student number: 040961749
 * Date created: 04/05/2021
 * Lab section: 304
 * Name file: Game.cpp
 * Purpose: Store, write and read file for scores 
 *************************************************************************/

#pragma once
#include "Game.h"
#include <iostream>    // using IO functions
#include <math.h>
#include <string>   
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <algorithm>
using namespace std;
using namespace FinalProject;
/*
	Purpose: This is only for checking scored only
*/

//struct Data f[50];


FinalProject::Game::Game()
{
	m_ticks = 0;
	m_users = "";
}

Game::Game(int ticks, string users)
{
	m_ticks = ticks;
	m_users = users;
}

FinalProject::Game::~Game()
{
}

int Game::getScore()
{
	return m_ticks;
}

void Game::setScore(int score)
{
	m_ticks = score;
}

string Game::getName()
{
	return m_users;
}

void Game::setName(string user)
{
	m_users = user;
}

void Game::writeToFile()
{
	// open a file in write mode.
	ofstream out;
	out.open("logcpp.txt", std::ios_base::app);
	cout <<"score:" << m_ticks << " Users: " << m_users << endl;
	//ofstream out("Score\\" + getScore() + ".txt");
	out << m_ticks << " " << m_users <<""<< endl;
	out.close();

}

string Game::readFromFile()
{
	string str = "";
	string info = "";
	int scoreTemp = 0;
	string name = "";
	ifstream File("logcpp.txt");
	map<int, string> f;
	cout << "Read from file: " << endl;

	int i = 0;
	while (File >> str) {
		//info += " " + str + "";
		name = "";
		scoreTemp = stoi(str);
		File >> str;
		name += str;
		f[scoreTemp] = name;
		//info += " " + str + "\n";
		cout << "score: " << scoreTemp << " name: " << name << endl;
		i++;
	}

	//Declare new pair array
	std::pair<int, string> highest = *f.rbegin();
	//Start the comparision
	i = 0;
	std::map<int, string>::iterator it = f.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
		if(i < 5) {
			info += " " + to_string(it->first) + " " + it->second + "\n";
		}
		i++;
	} while (f.value_comp()(*it++, highest));


	info += "\n";

	File.close();

	return info;

}


