#pragma once
#include "Ai.h"
#include "Chess.h"
#include <iostream>
void AI::init(Chess* chess)
{
    this->chess = chess;

    int size = chess->getGradeSize();
    for (int i = 0; i < size; i++) {
        vector<int> row;
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }
        scoreMap.push_back(row);
    }
}

void AI::go()
{
    ChessPos pos = think();
    Sleep(1000); //��װ˼��
    chess->chessDown(&pos, CHESS_WHITE);
    std::cout << "ai: " << pos.row << ", " << pos.col << endl;
}

void AI::calculateScore()
{
    // ͳ����һ��ߵ������ɵ���
    int personNum = 0;  // ��������ӵĸ���
    int botNum = 0;     // AI�����ӵĸ���
    int emptyNum = 0;   // ������հ�λ�ĸ���

    // �����������
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap[i].size(); j++) {
            scoreMap[i][j] = 0;
        }
    }

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
        {
            // �հ׵����
            if (chess->getChessData(row, col) == 0 && chess->checkClick(row,col)) {
                // ������Χ��������
                for (int y = -1; y <= 1; y++) {
                    for (int x = -1; x <= 1; x++)
                    {
                        // ԭ���겻��,ֻ����6�������ų�3��,����yΪ0ʱֻ����xΪ1
                        if ((y == 0 && x != 1) || (y == -1 && x == 1) || (y == 1 && x == -1)) continue;
                        // ����
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        
                        // ÿ����������4����
                        // �Ժ������֣�������������
                        for (int i = 1; i <= 4; i++)
                        {
                            int curRow = row + i * x;
                            int curCol = col + i * y;
                            if (curRow >= 0 && curRow < size &&
                                curCol >= 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 1) // ������ҵ���
                            {
                                personNum++;
                            }
                            else if (curRow >= 0 && curRow < size &&
                                curCol >= 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 0) // �հ�λ
                            {
                                emptyNum++;
                                break;
                            }
                            else            // ���߽�
                                break;
                        }
                        // �����������
                        for (int i = 1; i <= 4; i++)
                        {
                            int curRow = row - i * x;
                            int curCol = col - i * y;
                            if (curRow >= 0 && curRow < size &&
                                curCol >= 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 1) // ������ҵ���
                            {
                                personNum++;
                            }
                            else if (curRow >= 0 && curRow < size &&
                                curCol >= 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 0) // �հ�λ
                            {
                                emptyNum++;
                                break;
                            }
                            else            // ���߽�
                                break;
                        }

                        if (personNum == 1)                      // ɱ��
                            scoreMap[row][col] += 10;
                        else if (personNum == 2)                 // ɱ��
                        {
                            if (emptyNum == 1)
                                scoreMap[row][col] += 30;
                            else if (emptyNum == 2)
                                scoreMap[row][col] += 40;
                        }
                        else if (personNum == 3)                 // ɱ��
                        {
                            // �����λ��һ�������ȼ���һ��
                            if (emptyNum == 1)
                                scoreMap[row][col] += 60;
                            else if (emptyNum == 2)
                                scoreMap[row][col] += 200;
                        }
                        else if (personNum == 4)                 // ɱ��
                            scoreMap[row][col] += 20000;

                        // ����һ�����
                        emptyNum = 0;

                        // �԰�������
                        for (int i = 1; i <= 4; i++)
                        {
                            int curRow = row + i * x;
                            int curCol = col + i * y;
                            if (curRow > 0 && curRow < size &&
                                curCol > 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == -1) // ��ҵ���
                            {
                                botNum++;
                            }
                            else if (curRow > 0 && curRow < size &&
                                curCol > 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 0) // �հ�λ
                            {
                                emptyNum++;
                                break;
                            }
                            else            // ���߽�
                                break;
                        }

                        for (int i = 1; i <= 4; i++)
                        {
                            int curRow = row - i * y;
                            int curCol = col - i * x;
                            if (curRow > 0 && curRow < size &&
                                curCol > 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == -1) // ��ҵ���
                            {
                                botNum++;
                            }
                            else if (curRow > 0 && curRow < size &&
                                curCol > 0 && curCol < size &&
                                chess->getChessData(curRow, curCol) == 0) // �հ�λ
                            {
                                emptyNum++;
                                break;
                            }
                            else            // ���߽�
                                break;
                        }

                        if (botNum == 0)                      // ��ͨ����
                            scoreMap[row][col] += 5;
                        else if (botNum == 1)                 // ���
                            scoreMap[row][col] += 10;
                        else if (botNum == 2)
                        {
                            if (emptyNum == 1)                // ����
                                scoreMap[row][col] += 25;
                            else if (emptyNum == 2)
                                scoreMap[row][col] += 50;  // ����
                        }
                        else if (botNum == 3)
                        {
                            if (emptyNum == 1)                // ����
                                scoreMap[row][col] += 55;
                            else if (emptyNum == 2)
                                scoreMap[row][col] += 10000; // ����
                        }
                        else if (botNum >= 4)
                            scoreMap[row][col] += 30000;   // ���壬Ӧ�þ���������ȼ�
                        
                    }
                }
            }
        }
}

ChessPos AI::think()
{
    // ��������
    calculateScore();

    // ���������ҳ���������λ��
    int maxScore = 0;
    vector<ChessPos> maxPoints;
    int k = 0;

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++)
        {
            // ǰ������������ǿյ�
            if (chess->getChessData(row, col) == 0 && chess->checkClick(row, col)) {
                if (scoreMap[row][col] > maxScore)          // ��������������
                {
                    maxScore = scoreMap[row][col];
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(row, col));
                }
                else if (scoreMap[row][col] == maxScore) {   // ����ж������������������
                    maxPoints.push_back(ChessPos(row, col));
                }
            }
        }
    }
    // ������ӣ�����ж����Ļ�
    if (maxPoints.size() != 0) {
        int index = rand() % maxPoints.size();
        return maxPoints[index];
    }
}
