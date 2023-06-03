#pragma once
#include "Chess.h"
#include <conio.h>
#include<iostream>

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Chess::init()
{
	//������Ϸ����
	initgraph(1080, 1080, EW_SHOWCONSOLE);
	//��ʾ����ͼƬ
	switch (gradeSize)
	{
	case 15:
		loadimage(0, "res/Chessboard7.jpeg");
		break;
	case 9:
		loadimage(0, "res/Chessboard5.jpg");
		break;
	case 5:
		loadimage(0, "res/ChessBoard3.jpg");
		break;
	default:
		break;
	}

	//���غ���Ͱ����ͼƬ
	loadimage(&chessBlackImg, "res/BlackChess.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/WhiteChess.png", chessSize, chessSize, true);

	//��ӻ��幦�ܰ�ť
	rectangle(850, 80, 960, 130); // ����һ�����ΰ�ť
	outtextxy(890, 95, "����"); // �ڰ�ť������ʾ�ı�
	
	//���ÿ�ʼ��λ��
	//�����Ԫ��λ�õ�����
	switch (gradeSize)
	{
	case 15: {
		zeroRow = { 342,314,286,255,228,198,171,145,171,198,228,255,286,314,342 };

		//���ڼ���λ�õ�����
		rowLoc = { 342.0,314.0,286.0,255.0,228.0,198.0,171.0,145.0, 114.6, 85.2, 58.8, 29.4, 4, -25.6, -52.8 };
		break;
	}
	case 9: {
		zeroRow = { 429,400,370,342,313,342,370,400,429};

		//���ڼ���λ�õ�����
		rowLoc = { 429.0,400.0,370.0,342.0,313.0,285.6,257.2,169.2,203.4 };
		break;
	}
	case 5: {
		zeroRow = { 483,454,426,454,483 };

		//���ڼ���λ�õ�����
		rowLoc = { 483.0,454.0,426.0,397.6,370.2};
		break;
	}
	default:
		break;
	}

	//��������
	for (int i = 0; i < gradeSize; i++){
		for (int j = 0; j < gradeSize; j++){
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;//����
}

Chess::Chess(int gradeSize)
{
	this->gradeSize = gradeSize;
	switch (gradeSize)
	{
	case 15: {
		this->margin_x = 342;
		this->margin_y = 197;
		break;
	}
	case 9: {
		this->margin_x = 429;
		this->margin_y = 345;
		break;
	}
	case 5: {
		this->margin_x = 483;
		this->margin_y = 443;
		break;
	}
	default:
		break;
	}
	playerFlag = CHESS_BLACK;//���ɺ�����

	for (int i = 0; i < gradeSize; i++) {
		vector<int>row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (y - margin_y) / height;
	int row = (x - rowLoc[col]) / chessSize;
	if (col < 0 || row < 0 || col > gradeSize || row>gradeSize) {
		return false;
	}
	int leftTopPosX = zeroRow[col] + chessSize * row;
	int leftTopPosY = margin_y + chessSize * col;

	int selectPos = false;

	do {
		//������Ͻ�
		if ((x - leftTopPosX) < (chessSize / 2)&& (y - height * col - margin_y)<height/2) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0 && checkClick(pos->row, pos->col)) {
				selectPos = true;
			}
			
			break;
		}
		//������Ͻ�
		if ((x - leftTopPosX) > (chessSize / 2) && (y - height * col - margin_y) < height / 2) {
			pos->row = row+1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0 && checkClick(pos->row, pos->col)) {
				selectPos = true;
			}
			break;
		}
		//����·�
		if ((y - height * col - margin_y) > height / 2) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0 && checkClick(pos->row, pos->col)) {
				selectPos = true;
			}
			break;
		}
	} while (0);

	return selectPos;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	int x = rowLoc[pos->col] + pos->row * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->col * height - 0.5 * chessSize;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(800);
		if (playerFlag == false) {  //����Ӯ�����Ӯ��,��ʱ����Ѿ���ת���ֵ���������
			loadimage(0, "res/victory.jpg",1652,1000);
		}
		else {
			loadimage(0, "res/defeat.jpg",1652,648);
		}

		_getch(); 
		return true;
	}
	bool flag = true;
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			if (chessMap[i][j] == 0 && checkClick(i,j)) {
				flag = false;
				return flag;
			}
		}
	}
	if (flag == true) {
		cout << "ƽ��";
	}
	return false;
}

void Chess::retractChess()
{
	// ���������Ϣ
		// �������ڰ�ť��Χ�ڱ����
		// ִ����Ӧ�Ĳ���
		// ���磬�����Ի�����ڿ���̨�����Ϣ
		//MessageBox(NULL, "Button Clicked!", "Message", MB_OK);
		std::cout << "ok";
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? 1 : -1;
	playerFlag = !playerFlag; // ����
}

bool Chess::checkClick(int row, int col)
{
	bool flag = true;
	do {
		if (row > gradeSize-1 || col > gradeSize - 1 || row < 0 || col < 0) {
			return false;
		}
		//�������Ͻǲ��������
		if (col < gradeSize/2 + 1 && row >= col + gradeSize / 2 + 1) {
			return false;
		}
		//�������½ǲ��������
		if (col >= gradeSize / 2 + 1 && row < col - gradeSize / 2 ) {
			return false;
		}
	} while (0);
	return flag;
}

bool Chess::checkWin()
{
	// ��б�ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		//"/"���� ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ˮƽ����
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}