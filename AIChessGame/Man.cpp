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
		//��ȡ�������Ϣ��
		msg = GetMouseMsg();
		//ͨ��chess���󣬵��� �ж������Ƿ���Ч���Լ����ӹ���
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {//�����������Ч
			cout << pos.row << "," << pos.col << endl;
			chess->chessDown(&pos, CHESS_BLACK);
			break;
		}//�������ǻ���
		else if (msg.x >= 850 && msg.x <= 960 && msg.y >= 80 && msg.y <= 130 && msg.uMsg == WM_LBUTTONDOWN) {
			chess->retractChess();
			break;
		}
		else {
			continue;
		}
	}
}
