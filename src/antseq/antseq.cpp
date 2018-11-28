// antseq.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> antSeq(const string& initSeq, const int& n)
{
	vector<string> output;
	string lastSeq = initSeq ;
	int tries = 0;

	while (tries++ < n) {
		char ch = lastSeq[0];
		
		int len = 0;
		string seq;
		for (char e : lastSeq) {
			if (ch == e) {
				len++;
			}
			else {
				seq.push_back(ch);
				seq += to_string(len);
				ch = e;
				len = 1;
			}
		}
		// last 
		seq.push_back(ch);
		seq += to_string(len);

		lastSeq = seq;
		output.push_back(seq);
	}
	return output;
}

int main(int argc, char** argv)
{
	string first = string("1");
	cout << first << endl;

	vector<string> output = antSeq(first, 10);
	for (string s : output) cout << s << endl;

	return 0;
}