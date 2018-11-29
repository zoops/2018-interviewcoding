// fibo.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "bigint.h"
using namespace std;

typedef BigInt::Rossi BINT;

BINT fibo(int n)
{
	if (n <= 2)	return BINT(1);
	else return fibo(n - 1) + fibo(n - 2);
}

vector<BINT> g_cache = { BINT(1), BINT(1) };
int g_last_pos = 1;
BINT fibo2(int n) {

	if (g_cache.size() < n) {
		for (int i = g_last_pos + 1; i < n; ++i) {
			BINT tmp = g_cache[i - 1] + g_cache[i - 2];
			g_cache.push_back(tmp);
			std::cout << tmp.toStrDec() << endl;
		}
		g_last_pos = n - 1;
	}
	return g_cache[n - 1];
}

int main()
{
    std::cout << fibo(27) << endl; 

	std::cout << fibo2(150).toStrDec() << endl;
}
