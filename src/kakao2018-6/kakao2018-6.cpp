// kakao2018-6.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

string getUrl(string now) {
	string f = "<meta property=\"og:url\" content=\"";
	int st = now.find(f);
	int ed = now.find("\"", st + f.size());
	return string(now.begin() + st + f.size(), now.begin() + ed);
}

int getWordCnt(string word, string str) {
	if (str.empty()) return 0;
	str.push_back('*');
	int ret = 0;
	string cur = "";
	for (int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
		if (str[i] >= 'a'&&str[i] <= 'z') {
			cur += str[i];
		}
		else {
			if (word == cur)	ret++;
			cur = "";
		}
	}
	return ret;
}
int solution(string word, vector<string> arr) {
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);

	map<string, int> urlIndexMap;

	int pageCnt = arr.size();
	vector<int> basicScores(pageCnt), linkCnts(pageCnt);
	vector<double> matchScores(pageCnt);
	vector<vector<int> > adj = vector<vector<int> >(pageCnt);
	for (int i = 0; i < pageCnt; i++) {
		string link = getUrl(arr[i]);
		urlIndexMap[link] = i;
	}

	for (int i = 0; i < pageCnt; i++) {
		string f = "<a href=\"";
		int st = arr[i].find("<body>") + 6;
		while (true) {
			int nst = arr[i].find(f, st);
			if (nst == string::npos) break;

			basicScores[i] += getWordCnt(word, string(arr[i].begin() + st, arr[i].begin() + nst));
			
			int ed = arr[i].find("\"", nst + f.size());
			string now = string(arr[i].begin() + nst + f.size(), arr[i].begin() + ed);
			linkCnts[i]++;

			if (urlIndexMap.count(now) > 0)	
				adj[urlIndexMap[now]].push_back(i);
			
			st = arr[i].find("</a>", ed) + 4;
		}
		int ed = arr[i].find("</body>", st);
		basicScores[i] += getWordCnt(word, string(arr[i].begin() + st, arr[i].begin() + ed));
	}

	for (int i = 0; i < pageCnt; i++) {
		matchScores[i] += basicScores[i];
		for (auto &there : adj[i])
			matchScores[i] += (double)basicScores[there] / linkCnts[there];
	}
	vector<pair<double, int> > ans;
	for (int i = 0; i < pageCnt; i++) ans.push_back({ matchScores[i],i });

	std::sort(ans.begin(), ans.end(), [](pair<double, int> a, pair<double, int> b) {
		if (a.first == b.first)return a.second < b.second;
		return a.first > b.first;
	});

	return ans[0].second;
}

int main()
{
	vector<string> pages = { 
		"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"
	};

	string keyword = "blind";
	int res = solution(keyword, pages);
    std::cout << res << endl; 

	pages = {
		"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"
	};
	keyword = "Muzi";
	res = solution(keyword, pages);
	std::cout << res << endl;
}