// kakao2018-2.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class CStageFailRate {
public:
	CStageFailRate(int stage, double failRate) {
		nStage = stage;
		fFailRate = failRate;
	}
	int nStage = 0;
	double fFailRate = 0.0;

	bool operator<(CStageFailRate& sf) const {
		return this->fFailRate == sf.fFailRate ?  this->nStage < sf.nStage : this->fFailRate > sf.fFailRate;
	}
};

vector<int> solution(int N, vector<int> stages) {
	// input : ���������� N , �� ����ڰ� �ӹ��� �ִ� �������� �迭
	// output : �������� ���� �������������� �������� �迭 (������ ����������ȣ�� ������)
	// ������� : 
	//		������: ���������� ���������� ���� Ŭ�������� ���� �÷��̾��� �� / ���������� ������ �÷��̾� ��
	//		���������� ���� N�� 1 �̻� 500 ������ �ڿ����̴�.
	//		stages�� ���̴� 1 �̻� 200, 000 �����̴�.
	//		stages���� 1 �̻� N + 1 ������ �ڿ����� ����ִ�.
	//		�� �ڿ����� ����ڰ� ���� ���� ���� ���������� ��ȣ�� ��Ÿ����.
	//		��, N + 1 �� ������ ��������(N ��° ��������) ���� Ŭ���� �� ����ڸ� ��Ÿ����.
	//		���� �������� ���� ���������� �ִٸ� ���� ��ȣ�� ���������� ���� ������ �ϸ� �ȴ�.
	//		���������� ������ ������ ���� ��� �ش� ���������� �������� 0 ���� �����Ѵ�.

	vector<int> answer;	
	vector<int> stageUserCnts(N+2);
	vector<CStageFailRate> stageFailRates;

	for (int stage : stages) stageUserCnts[stage]++;

	int upToUserCnt = stages.size();
	for (int i = 1; i <= N; i++) {
		if (upToUserCnt <= 0)	stageFailRates.push_back(CStageFailRate(i, 0));
		else					stageFailRates.push_back(CStageFailRate(i, (double)stageUserCnts[i] / (double)upToUserCnt));
		upToUserCnt -= stageUserCnts[i];
	}

	sort(stageFailRates.begin(), stageFailRates.end());
	for (CStageFailRate sf : stageFailRates) 
		answer.push_back(sf.nStage);

	return answer;
}

int main()
{
	// 5[2, 1, 2, 6, 2, 4, 3, 3][3, 4, 2, 1, 5]
	vector<int> stages = {2, 1, 2, 6, 2, 4, 3, 3};
	vector<int> res = solution(5, stages);
	for (int d : res) 
		printf("%d ", d);

	printf("\n");

	// 4[4, 4, 4, 4, 4][4, 1, 2, 3]
	stages = { 4, 4, 4, 4, 4};
	res = solution(4, stages);
	for (int d : res)
		printf("%d ", d);
	return 0;
}

