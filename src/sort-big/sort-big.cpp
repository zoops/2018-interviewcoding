// sort-big.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const string &a, const string &b) {
	return (a + b).compare(b + a) > 0;
}

string solution(vector<int> numbers) {
	string answer = "";

	vector<string> unit;
	for (int v : numbers) unit.push_back(std::to_string(v));

	std::sort(unit.begin(), unit.end(), comp);
	if (unit.size() > 0 && unit[0].compare("0") == 0)	answer = "0";
	else for (string s : unit) answer += s;

	return answer;
}

int main()
{
	//[6, 10, 2]	6210
	//[3, 30, 34, 5, 9]	9534330
	vector<int> input = { 0, 6, 0, 10, 2, 0 };
	string output = solution(input);
    std::cout << output << endl;

	input = { 3, 30, 34, 5, 9 };
	output = solution(input);
	std::cout << output << endl;
}
