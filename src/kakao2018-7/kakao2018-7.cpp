// kakao2018-7.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check1(vector<vector<int>>& board, int y, int x) {
	//  *  
	//  *  
	// ** 
	int n = board.size();
	if ((y + 2) >= n || (x - 1) < 0)	return false;

	int color = board[y][x];
	if (board[y + 1][x] == color
		&& board[y + 2][x] == color
		&& board[y + 2][x - 1] == color
		)
	{
		for (int yy = 0; yy <= (y + 1); yy++)
			if (board[yy][x - 1] != 0)
				return false;

		// 성공 
		board[y][x] = 0;
		board[y + 1][x] = 0;
		board[y + 2][x] = 0;
		board[y + 2][x - 1] = 0;
		return true;
	}
	return false;
}
bool check2(vector<vector<int>>& board, int y, int x) {
	// * 
	// * 
	// **
	int n = board.size();
	if ( (y + 2) >= n || (x + 1) >= n )	return false;

	int color = board[y][x];
	if (board[y + 1][x] == color
		&& board[y + 2][x] == color
		&& board[y + 2][x + 1] == color
		)
	{
		for (int yy = 0; yy <= (y + 1); yy++)
			if (board[yy][x + 1] != 0)
				return false;

		// 성공 
		board[y][x] = 0;
		board[y + 1][x] = 0;
		board[y + 2][x] = 0;
		board[y + 2][x + 1] = 0;
		return true;
	}
	return false;
}
bool check3(vector<vector<int>>& board, int y, int x) {
	// *  
	// ***
	int n = board.size();
	if ( (y + 1) >= n || (x + 2) >= n)	return false;

	int color = board[y][x];
	if (board[y + 1][x] == color
		&& board[y + 1][x + 1] == color
		&& board[y + 1][x + 2] == color
		)
	{
		for (int yy = 0; yy <= (y); yy++)
			if (board[yy][x + 1] != 0 || board[yy][x + 2] != 0 )
				return false;

		// 성공 
		board[y][x] = 0;
		board[y + 1][x] = 0;
		board[y + 1][x + 1] = 0;
		board[y + 1][x + 2] = 0;
		return true;
	}
	return false;
}
bool check4(vector<vector<int>>& board, int y, int x) {
	//   *
	// ***
	int n = board.size();
	if ((y + 1) >= n || (x - 2) < 0)	return false;

	int color = board[y][x];
	if (board[y + 1][x] == color
		&& board[y + 1][x - 1] == color
		&& board[y + 1][x - 2] == color
		)
	{
		for (int yy = 0; yy <= (y); yy++)
			if (board[yy][x - 1] != 0 || board[yy][x - 2] != 0)
				return false;

		// 성공 
		board[y][x] = 0;
		board[y + 1][x] = 0;
		board[y + 1][x - 1] = 0;
		board[y + 1][x - 2] = 0;
		return true;
	}
	return false;
}
bool check5(vector<vector<int>>& board, int y, int x) {
	//  *
	// ***
	int n = board.size();
	if ((y + 1) >= n || (x + 1) >= n || (x - 1) < 0)	return false;

	int color = board[y][x];
	if (board[y + 1][x] == color
		&& board[y + 1][x - 1] == color
		&& board[y + 1][x + 1] == color
		)
	{
		for (int yy = 0; yy <= (y); yy++)
			if (board[yy][x - 1] != 0 || board[yy][x + 1] != 0)
				return false;

		// 성공 
		board[y][x] = 0;
		board[y + 1][x] = 0;
		board[y + 1][x - 1] = 0;
		board[y + 1][x + 1] = 0;
		return true;
	}
	return false;
}

int solution(vector<vector<int> > board) {
	int n = board.size();
	int answer = 0;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++) {
			if (board[y][x] > 0) {

				// 5가지 모양 체크 
				//  *   *              
				//  *   *   *       *   *
				// **   **  ***   ***  ***
				if (check1(board, y, x) == true) { answer++; y > 0 ? y -= 1 : y; }
				else if (check2(board, y, x) == true)	{ answer++; y > 0 ? y -= 1 : y; }
				else if (check3(board, y, x) == true)	{ answer++; y > 0 ? y -= 1 : y; }
				else if (check4(board, y, x) == true)	{ answer++; y > 0 ? y -= 1 : y; }
				else if (check5(board, y, x) == true)	{ answer++; y > 0 ? y -= 1 : y; }
			}
		}
	}
	return answer;
}

int main()
{
	vector<vector<int>> board = 
		{ 
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
			{0, 0, 0, 0, 0, 0, 4, 0, 0, 0}, 
			{6, 0, 0, 7, 0, 4, 4, 0, 0, 0}, 
			{6, 7, 7, 7, 3, 0, 4, 0, 0, 0}, 
			{6, 6, 0, 2, 3, 0, 0, 0, 5, 5}, 
			{1, 2, 2, 2, 3, 3, 0, 0, 0, 5}, 
			{1, 1, 1, 0, 0, 0, 0, 0, 0, 5} 
		};
	int blockCnt = solution(board);
    std::cout << blockCnt << endl;
}