#pragma once
#include "Chess.h"
class AI
{
public:
	void init(Chess* chess);
	void go();
private:
	Chess* chess;
	// 存储各个点位的评分情况，作为AI下棋依据
	vector<vector<int>> scoreMap;
	//实现评分计算
	void calculateScore();
	//思考
	ChessPos think();  //private权限
};