// fastestMaxSum.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// maxAt(i) = max(0, maxAt(i - 1)) + A[i]
float fastestMaxSum(vector<float> d) {
	float ret = 0, psum = 0;

	for (int i = 0; i < d.size(); i++) {
		psum = std::max(0.0f, psum) + d[i];
		ret = std::max(ret, psum);
	}
	return ret;
}

int main()
{
	vector<float> d = { -7, 4, -3, 6, 3, -8, 3, 4 };
	float ret = fastestMaxSum(d);
    std::cout << ret << endl;

	d = { 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 };
	ret = fastestMaxSum(d);
	std::cout << ret << endl;		

	d = { -31, -41, -59, -26, -53, -58, -97, -93, -23, -84 };
	ret = fastestMaxSum(d);
	std::cout << ret << endl;
}
