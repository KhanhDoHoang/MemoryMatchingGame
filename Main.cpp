/*************************************************************************
 * Author: Hoang Do
 * Student number: 040961749
 * Date created: 04/05/2021
 * Lab section: 304
 * Name file: Main.cpp
 * Purpose: A memory game with 20 cards need to be opened and found the other which matches
 * Subsmission date: 16/05/2021
 *************************************************************************/

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include "Card.h"
#include "Game.h"
#include "Image.h"

#include <time.h>
#include <algorithm>  
#include <iostream>
#include <map>
#include <iterator>
#include <list>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace nana;
using namespace FinalProject;
using namespace audio;
namespace fs = std::filesystem;
//Hold highscores(temp)
string scores;
string fileName;

//Text input
string eddittext = "";
string::iterator iter = eddittext.begin();

//Objects
//Score system
int ticks = 0;

// assigning a value to each state a card can be in.
const int FACE_UP = -1;
const int FACE_DOWN = -2;
const int REMOVED = -3;

//Deck
vector<image> imgCard;
//Card deck
vector<Card> cardboard;
//Save the current cards

//Score
//Game score;
string labelText = "\n";

void clicked(int clicks)
{
	printf("I flipped card #%d\n", clicks);	
	ticks++;
	cout << "Tickers: " << ticks << endl;
}

int flipCheck = 0;
int lastIndex = 0;
Image pic;
image check;
//Check DONE
int unFin = 0; //=============>CHECKING DONE
bool doneGame = false; //=============>CHECKING DONE

int position[20];
int positionIMG[10];

int main() {
	static Game scoreBoard;
	std::srand(std::time(0));
	//Sounds
	static player wrongSound("Lose.wav");
	static player wonSound("Won.wav");
	static player doneSound("DoneGame.wav");
	static player gameSound("GameMusic.wav");
	static player matchSound("Matched.wav");

	////Image
	static paint::image back = pic.cardBack;

	//Only 1 thread
	static threads::pool pool(1);

	//define app window:
	static form fm{ API::make_center(1850, 1550) };

	//Define caption
	fm.caption("HoangDo C++ 2021 CST8219 - Final Project");
	static place plc(fm);
	drawing dw(fm);

	//Create layout
	plc.div("vertical gap=10 margin=15 <gap=10 margin=15 weight=30> <horizontal arrange=[90,10] < weight=1500 abc grid=[4,5] > <vertical gap=15 < vert weight=900 play1> < vert regist>>> ");

	//Create a button map
	static std::map<char, button*> cards;
	static list<button> buttons;
	//Iterate SETUP
	for (auto i = 0; i < 20; i++) {
		position[i] = i;
	}
	for (auto i = 0; i < 10; i++) {
		positionIMG[i] = i;
	}
	//SETUP Img
	for (auto i : positionIMG) {
		imgCard.push_back(pic.cardImages.at(i));
		//imgCard.push_back(pic.cardImages.at(i));
	}
	//SETUP Button
	for (auto i : positionIMG) {
		cardboard.push_back(*new Card(i, FACE_DOWN, imgCard.at(i)));
		cardboard.push_back(*new Card(i, FACE_DOWN, imgCard.at(i)));
	}
	bool replay = true;
	label lab{ fm }, boardScore{ fm };
	static int countStart = 0;
	static textbox usr{ fm };
	static button regist{fm, "Save My Score"};
	regist.enabled(false);

	usr.tip_string("User: ").multi_lines(false);
	//===========================DONE SETUP===============================//
	static element::bground bg;
	bg.image(paint::image("bground1.bmp"), true, {});
	static element::bground bg1;
	bg1.image(paint::image("card5.bmp"), true, {});
	bg.stretch_parts(4, 4, 4, 4);
	boardScore.format(true);
	labelText += scoreBoard.readFromFile();
	cout << "READ FROM FILE: " << labelText << endl;
	boardScore.caption("<size=14 bold center>LEADERBOARD</> <size=12 bold>" + labelText + "</>");
	boardScore.bgcolor(colors::light_pink);
	lab.caption(string("(Leaderboard will be updated when re-launch) <image=\"PlayGame.bmp\" size=(100,100)><bold red size=20>Do you want to play again? Click below button</>"));
	lab.bgcolor(colors::beige);

	button playAgain(fm, rectangle(230, 150, 400, 200));
	playAgain.caption("PLAY AGAIN!");
	playAgain.set_bground(bg);

	//Exit button
	button exit(fm, rectangle(330, 160, 400, 200));
	exit.caption("QUIT THE GAME");
	exit.set_bground(bg);

	plc["play1"] << boardScore << lab << playAgain << exit ;
	plc["regist"] << usr << regist;

	nana::paint::image img("bground1.bmp");

	dw.draw([&img](nana::paint::graphics& graph)
		{
			if (img.empty()) return;
			img.paste(graph, nana::point{});
		});
	dw.update();
	lab.format(true);

	if (countStart == 0) {

		cout << "I am in normal one" << endl;
		flipCheck = 0;
		lastIndex = 0;

		std::srand(std::time(0));
		std::random_shuffle(imgCard.begin(), imgCard.end());

		std::srand(std::time(0));
		std::random_shuffle(cardboard.begin(), cardboard.end());

		for (auto i : position) {
			ticks = 0;
			gameSound.play();
			gameSound.close();

			//construct an element in place at the beginning
			buttons.emplace_front((fm).handle());

			//access the first element
			auto& card_btn = buttons.front();
			cards[i] = &card_btn;

			//assign icon (img) to the button
			card_btn.icon(back);
			card_btn.set_bground(bg);
			plc["abc"] << card_btn;

			//track button click event and response

			card_btn.events().click(pool_push(pool, [&, i]() {

				if (cardboard[i].getstate() == REMOVED) {
					;
				}
				else {
					if (flipCheck == 0) {
						card_btn.icon(cardboard.at(i).getImage());
						clicked(i);
						//ticker();
						wonSound.play();
						lastIndex = i;
						flipCheck++;
					}
					if (lastIndex == i) {
						;
					}
					else {
						if (flipCheck == 1) {

							card_btn.icon(cardboard.at(i).getImage());
							//card_btn.icon(*imageMap.at(i));

							clicked(i);
							//ticker();
							wonSound.play();

							if (&imgCard.at(cardboard[lastIndex].getIndex()) == &imgCard.at(cardboard[i].getIndex())) {
								cardboard[lastIndex].setState(REMOVED);
								cardboard[i].setState(REMOVED);
								matchSound.play();
								cout << "Matched: " << endl;

							}
							else {
								cout << "Not matched: " << endl;
								cards[lastIndex]->icon(back);
								cards[i]->icon(back);
								wrongSound.play();
							}

							flipCheck = 0;
						}

					}
				} //done else

				for (auto i = 0; i < cardboard.size(); i++) {
					if (cardboard.at(i).getstate() != REMOVED) {
						unFin += 1;
					}
				}
				cout << "un fin: " << unFin << endl;
				if (unFin == 0) {
					//delete (new Game(ticks, "hello"));
					doneSound.play();

					regist.enabled(true);
					regist.events().click([] {
						cout << "Hello this is clicked";

						string str = "";
						str += usr.text();
						cout << "Text : " << str;
						
						scoreBoard.setScore(ticks);
						scoreBoard.setName(str);
						scoreBoard.writeToFile();

						usr.reset();
						});

					cout << "=====GAME DONE===" << endl;

				}
				unFin = 0;
				}));
		}
	} //done if

	playAgain.events().click([] {
		//cards = 0;
		ticks = 0;
		for (auto i : position) {
			cardboard[i].setState(FACE_DOWN);
		}
		for (auto i : position) {
			cards[i]->icon(back);
		}
		cout << "Size card" << cards.size() << endl;
		cout << "Size cardboard" << cardboard.size() << endl;
		cout << "CB begin" << &cardboard.front() << endl;
		cout << "CB begin" << &cardboard.back() << endl;

		countStart++;
		cout << "Hello world, Im clicked" << endl;
		flipCheck = 0;
		lastIndex = 0;

		std::srand(std::time(0));
		std::random_shuffle(cardboard.begin(), cardboard.end());

		for (auto i : position) {
			
			cout << "Iterated " << endl;
			buttons.emplace_front((fm).handle());

			//access the first element
			auto& card_btn = buttons.front();

			//assign icon (img) to the button
			card_btn.icon(back);
			card_btn.set_bground(bg);
			plc["abc"] << card_btn;
			card_btn.events().click(pool_push(pool, [&, i]() {
				if (cardboard[i].getstate() == REMOVED) {
					;
				}
				else {
					if (flipCheck == 0) {
						card_btn.icon(cardboard.at(i).getImage());
						clicked(i);
						wonSound.play();
						lastIndex = i;
						flipCheck++;
					}
					if (lastIndex == i) {
						;
					}
					else {
						if (flipCheck == 1) {

							card_btn.icon(cardboard.at(i).getImage());

							clicked(i);
							wonSound.play();

							if (&imgCard.at(cardboard[lastIndex].getIndex()) == &imgCard.at(cardboard[i].getIndex())) {
								cardboard[lastIndex].setState(REMOVED);
								cardboard[i].setState(REMOVED);
								matchSound.play();
								cout << "Matched: " << endl;

							}
							else {
								cout << "Not matched: " << endl;
								cards[lastIndex]->icon(back);
								cards[i]->icon(back);
								wrongSound.play();

							}//done else

							flipCheck = 0;
						}//done if
					}//done else

				}//done else

				for (auto i = 0; i < cardboard.size(); i++) {
					if (cardboard.at(i).getstate() != REMOVED) {
						unFin += 1;
					}
				}
				cout << "un fin: " << unFin << endl;
				if (unFin == 0) {
					doneSound.play();

					regist.enabled(true);
					regist.events().click([] {
						cout << "Hello this is clicked";

						string str = "";
						str += usr.text();
						cout << "Text : " << str;
						
						scoreBoard.setScore(ticks);
						scoreBoard.setName(str);
						scoreBoard.writeToFile();
						usr.reset();
						});

					cout << "=====GAME DONE===" << endl;

				}
				unFin = 0;
				}));//done click
				//plc.collocate();
		}//done for
		});//done click

		exit.enabled(true);
		exit.events().click([] {
			cout << "Hello this is clicked exit";
			/*cardboard.clear();
			imgCard.clear();
			cards.clear();*/
			fm.close();
			});

	plc.collocate();

	//show screen
	fm.show();

	//start to run
	exec();
	return 0;
}
