#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

typedef enum {
	CHESS_WHITE = -1,  // 白方
	CHESS_BLACK = 1    // 黑方
} chess_kind_t;
//每列首位置的行长



struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

class Chess
{
public:
	Chess(int gradeSize);

	// 棋盘的初始化：加载棋盘的图片资源，初始化棋盘的相关数据
	void init();

	// 判断在指定坐标(x,y)位置，是否是有效点击
	// 如果是有效点击，把有效点击的位置(行，列）保存在参数pos中
	bool clickBoard(int x, int y, ChessPos* pos);

	// 在棋盘的指定位置（pos）, 落子（kind）
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// 获取棋盘的大小（14线、10线、4线）
	int getGradeSize();

	// 获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// 判断棋局是否结束
	bool checkOver();
	
	//再次检查棋子位置正确
	bool checkClick(int row, int col);

	//悔棋
	void retractChess();
private:
	// 棋盘尺寸
	int gradeSize;	// 15, 11, 7
	int margin_x;//左侧边界 7: 342px
	int margin_y;  //顶部边界   7: 197px
	float chessSize = 56.4; //棋子大小（棋盘方格大小）56.4px
	float height = 49.5;
	ChessPos lastPos; //最近落子位置

	IMAGE chessBlackImg;//表示黑棋
	IMAGE chessWhiteImg;//表示白棋

	// 存储当前游戏棋盘和棋子的情况,空白为0，黑子1，白子-1
	vector<vector<int>> chessMap;

	// 标示下棋方, true:黑棋方  false: AI 白棋方（AI方）
	bool playerFlag;

	//存放首元素位置的数组
	vector<int> zeroRow;

	//用于计算位置的数组
	vector<float> rowLoc;
	//在界面上落子之后，修改棋盘的棋子数据
	void updateGameMap(ChessPos* pos);

	bool checkWin();

};