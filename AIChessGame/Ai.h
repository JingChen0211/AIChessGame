#pragma once
#include "Chess.h"
class AI
{
public:
	void init(Chess* chess);
	void go();
private:
	Chess* chess;
	// �洢������λ�������������ΪAI��������
	vector<vector<int>> scoreMap;
	//ʵ�����ּ���
	void calculateScore();
	//˼��
	ChessPos think();  //privateȨ��
};