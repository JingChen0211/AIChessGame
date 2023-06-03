#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

typedef enum {
	CHESS_WHITE = -1,  // �׷�
	CHESS_BLACK = 1    // �ڷ�
} chess_kind_t;
//ÿ����λ�õ��г�



struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

class Chess
{
public:
	Chess(int gradeSize);

	// ���̵ĳ�ʼ�����������̵�ͼƬ��Դ����ʼ�����̵��������
	void init();

	// �ж���ָ������(x,y)λ�ã��Ƿ�����Ч���
	// �������Ч���������Ч�����λ��(�У��У������ڲ���pos��
	bool clickBoard(int x, int y, ChessPos* pos);

	// �����̵�ָ��λ�ã�pos��, ���ӣ�kind��
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// ��ȡ���̵Ĵ�С��14�ߡ�10�ߡ�4�ߣ�
	int getGradeSize();

	// ��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// �ж�����Ƿ����
	bool checkOver();
	
	//�ٴμ������λ����ȷ
	bool checkClick(int row, int col);

	//����
	void retractChess();
private:
	// ���̳ߴ�
	int gradeSize;	// 15, 11, 7
	int margin_x;//���߽� 7: 342px
	int margin_y;  //�����߽�   7: 197px
	float chessSize = 56.4; //���Ӵ�С�����̷����С��56.4px
	float height = 49.5;
	ChessPos lastPos; //�������λ��

	IMAGE chessBlackImg;//��ʾ����
	IMAGE chessWhiteImg;//��ʾ����

	// �洢��ǰ��Ϸ���̺����ӵ����,�հ�Ϊ0������1������-1
	vector<vector<int>> chessMap;

	// ��ʾ���巽, true:���巽  false: AI ���巽��AI����
	bool playerFlag;

	//�����Ԫ��λ�õ�����
	vector<int> zeroRow;

	//���ڼ���λ�õ�����
	vector<float> rowLoc;
	//�ڽ���������֮���޸����̵���������
	void updateGameMap(ChessPos* pos);

	bool checkWin();

};