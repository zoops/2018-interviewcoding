// kakao2018-1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <cstring>
#include <vector>
#include <map>

#pragma warning(disable:4996)
using namespace std;

class CLog{
public:
	CLog(string cmd, string uid) {
		sCmd = cmd;
		sUid = uid;
	}
	string sCmd;
	string sUid;
};

vector<string> solution(vector<string> record) {
	vector<string> answer;
	// record => Enter uid nick or Leave uid or Change uid nick
	// ��ҹ��� ����, 1~10 ����
	// input (record 10���� ����) : ["Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan"]
	// result (answer) : ["Prodo���� ���Խ��ϴ�.", "Ryan���� ���Խ��ϴ�.", "Prodo���� �������ϴ�.", "Prodo���� ���Խ��ϴ�."]

	map<string, string>  nickMap;

	vector<CLog> logs;
	for( string var : record) {		
		int idx = 0;
		string cmd[3];
		for (char c : var) {
			if (c == ' ') idx++;
			else cmd[idx] += c;
		}
		if (cmd[2].empty() == false) nickMap[cmd[1]] = cmd[2];
		if (cmd[0].compare("Change") != 0) logs.push_back(CLog(cmd[0], cmd[1]));
	}

	for( CLog log : logs) {
		if (log.sCmd.compare("Enter") == 0) answer.push_back(nickMap[log.sUid] + "���� ���Խ��ϴ�.");
		else if (log.sCmd.compare("Leave") == 0) answer.push_back(nickMap[log.sUid] + "���� �������ϴ�.");
	}
	return answer;
}

vector<string> tok(string s, string delimiter) {
	vector<string> res;
	char *str = const_cast<char *>(s.c_str());
	char *tok;
	tok = std::strtok(str, delimiter.c_str());
	while (tok != NULL) {
		res.push_back(tok);
		tok = std::strtok(NULL, delimiter.c_str());
	}
	return res;
}

vector<string> solutionUsingStrtok(vector<string> record) {
	vector<string> answer;
	map<string, string>  nickMap;

	vector<CLog> logs;
	for (string var : record) {
		vector<string> cmd = tok(var, " ");
		if (cmd.size() > 2) nickMap[cmd[1]] = cmd[2];
		if (cmd[0].compare("Change") != 0) logs.push_back(CLog(cmd[0], cmd[1]));
	}

	for (CLog log : logs) {
		if (log.sCmd.compare("Enter") == 0) answer.push_back(nickMap[log.sUid] + "���� ���Խ��ϴ�.");
		else if (log.sCmd.compare("Leave") == 0) answer.push_back(nickMap[log.sUid] + "���� �������ϴ�.");
	}
	return answer;
}
int main()
{
	vector<string> record;
	record.push_back("Enter uid1234 Muzi");
	record.push_back("Enter uid4567 Prodo");
	record.push_back("Leave uid1234");
	record.push_back("Enter uid1234 Prodo");
	record.push_back("Change uid4567 Ryan");
	
	vector<string> res = solution(record);

	for (string var : res)
		printf("%s\n", var.c_str());

	printf("\n");

	res = solutionUsingStrtok(record);
	for (string var : res)
		printf("%s\n", var.c_str());

	return 0;
}

