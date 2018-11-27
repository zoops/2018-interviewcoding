// kakao2018-4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long INT64;
using namespace std;

class CFoodInfo {
public:
	INT64 no = 0;
	INT64 amount = 0;
	CFoodInfo() {}
	CFoodInfo(INT64 n, INT64 a) {
		no = n;
		amount = a;
	}
	bool operator <(const CFoodInfo &n) const {
		return this->amount == n.amount ? this->no < n.no : this->amount < n.amount;
	}
};

bool comp(const CFoodInfo &a, const CFoodInfo &b) {
	return a.no < b.no;
}

int solution(vector<int> food_times, INT64 k) {
	INT64 sum = 0;

	vector< CFoodInfo> foods;
	for (int i = 0; i < food_times.size(); i++) {
		foods.push_back(CFoodInfo(i+1, food_times[i]));
		sum += food_times[i];
	}
	if (sum <= k) return -1;

	std::sort(foods.begin(), foods.end());

	for (int i = 0; i < food_times.size(); i++) {
		INT64 time = 0;
		if (i == 0) time = foods[i].amount * (food_times.size() - i);
		else time = (foods[i].amount - foods[i - 1].amount) * (food_times.size() - i);

		if (k <= time) {
			sort(foods.begin() + i, foods.end(), comp);
			k %= (food_times.size() - i);
			k += i;
			return foods[k].no;
		}
		k -= time;
	}
	return -1;
}

int main()
{
	// [3, 1, 2]	5	1
	vector<int> times = { 3,1,2 };
	int res = solution(times, 5);
    std::cout << res << endl; 
}
