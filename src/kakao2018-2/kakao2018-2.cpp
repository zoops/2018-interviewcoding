// kakao2018-2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	// input : 스페이지수 N , 각 사용자가 머물러 있는 스페이지 배열
	// output : 실패율이 높은 스테이지순으로 스페이지 배열 (같으면 스테이지번호가 낮은순)
	// 제약사항 : 
	//		실패율: 스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수 / 스테이지에 도달한 플레이어 수
	//		스테이지의 개수 N은 1 이상 500 이하의 자연수이다.
	//		stages의 길이는 1 이상 200, 000 이하이다.
	//		stages에는 1 이상 N + 1 이하의 자연수가 담겨있다.
	//		각 자연수는 사용자가 현재 도전 중인 스테이지의 번호를 나타낸다.
	//		단, N + 1 은 마지막 스테이지(N 번째 스테이지) 까지 클리어 한 사용자를 나타낸다.
	//		만약 실패율이 같은 스테이지가 있다면 작은 번호의 스테이지가 먼저 오도록 하면 된다.
	//		스테이지에 도달한 유저가 없는 경우 해당 스테이지의 실패율은 0 으로 정의한다.

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

