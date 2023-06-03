#pragma once
#include "Man.h"
#include<iostream>
void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (1) {
		//获取鼠标点击信息；
		msg = GetMouseMsg();
		//通过chess对象，调用 判断落子是否有效，以及落子功能
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {//左键单击且有效
			cout << pos.row << "," << pos.col << endl;
			chess->chessDown(&pos, CHESS_BLACK);
			break;
		}//如果点的是悔棋
		else if (msg.x >= 850 && msg.x <= 960 && msg.y >= 80 && msg.y <= 130 && msg.uMsg == WM_LBUTTONDOWN) {
			chess->retractChess();
			break;
		}
		else {
			continue;
		}
	}
}
