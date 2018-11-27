// kakao2018-3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> cdt;
void findkey(int idx, int bit, vector<vector<string> > &relation) {

	if (idx == relation[0].size()) return;

	set<string> cmp;
	for (int i = 0; i < relation.size(); i++) {
		string key;
		for (int j = 0; j < relation[i].size(); j++) {
			if ((bit & (1 << j))) {
				key += relation[i][j];
			}
		}
		cmp.insert(key);
	}
	if (cmp.size() == relation.size()) {
		bool f = true;
		for (int i = 0; i < cdt.size(); i++) {
			if ((cdt[i] & bit) == cdt[i]) {
				f = false;
				break;
			}
			if ((cdt[i] & bit) == bit) {
				f = false;
				cdt[i] = bit;
				break;
			}
		}
		if (f) {
			cdt.push_back(bit);
		}
	}
	findkey(idx + 1, bit, relation);
	findkey(idx + 1, (bit | (1 << (idx + 1))), relation);
}

int solution(vector<vector<string>> relation) {
	findkey(0, 0, relation);
	findkey(0, 1, relation);

	for (int v : cdt) cout << bitset<8>(v) << endl;

	return cdt.size();
}

// 유니크가 되는 최소 조합의 갯수
// input : 2차원 문자열 배열 
// output : 후보키 갯수
// 제약 : 
// relation은 2차원 문자열 배열이다.
// relation의 컬럼(column)의 길이는 1 이상 8 이하이며, 각각의 컬럼은 릴레이션의 속성을 나타낸다.
// relation의 로우(row)의 길이는 1 이상 20 이하이며, 각각의 로우는 릴레이션의 튜플을 나타낸다.
// relation의 모든 문자열의 길이는 1 이상 8 이하이며, 알파벳 소문자와 숫자로만 이루어져 있다.
// relation의 모든 튜플은 유일하게 식별 가능하다.(즉, 중복되는 튜플은 없다.)

int main()
{
	// [[100, ryan, music, 2], [200, apeach, math, 2], [300, tube, computer, 3], [400, con, computer, 4], [500, muzi, music, 3], [600, apeach, music, 2]]	2
	vector<vector<string>> data = { 
		vector<string>({"100", "ryan", "music", "2"}),
		vector<string>({"200", "apeach", "math", "2"}),
		vector<string>({"300", "tube", "computer", "3"}),
		vector<string>({"400", "con", "computer", "4"}),
		vector<string>({"500", "muzi", "music", "3"}),
		vector<string>({"600", "apeach", "music", "2"})
	};
	int res = solution(data);

	printf("%d\n", res);
}

