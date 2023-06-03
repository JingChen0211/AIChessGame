#pragma once
#include <iostream>
#include "ChessGame.h"

int main() {
	//Chess(int gradeSize);
	Chess chess(15);//15 9 5 
	Man man;
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}