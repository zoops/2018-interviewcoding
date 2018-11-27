// kakao2018-5.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Node {
public:
	int no;
	int level;
	int pos;

	int parent;
	int left;
	int right;
	Node() {}
	Node(int l, int p, int n) { level = l, pos = p; no = n; left = right = parent = -1; }
	bool operator < (const Node &n) const { return level == n.level ? pos < n.pos : level > n.level; }
};

bool isValid(const vector<Node>& nodes, int target, int source) {
	int p = nodes[target].parent;
	if (p == -1) return true;
	if (nodes[p].left == target) if (nodes[p].pos < nodes[source].pos) return false;
	if (nodes[p].right == target) if (nodes[p].pos > nodes[source].pos) return false;
	return isValid(nodes, p, source);
}

void preOrder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	ans.push_back(nodes[idx].no);
	if (nodes[idx].left > 0) preOrder(nodes, nodes[idx].left, ans);
	if (nodes[idx].right > 0) preOrder(nodes, nodes[idx].right, ans);
}

void postOrder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	if (nodes[idx].left > 0) postOrder(nodes, nodes[idx].left, ans);
	if (nodes[idx].right > 0) postOrder(nodes, nodes[idx].right, ans);
	ans.push_back(nodes[idx].no);
}

void inOrder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	if (nodes[idx].left > 0) inOrder(nodes, nodes[idx].left, ans);
	ans.push_back(nodes[idx].no);
	if (nodes[idx].right > 0) inOrder(nodes, nodes[idx].right, ans);
}

void levelOrder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	for (Node n : nodes) {
		ans.push_back(n.no);
	}
}

vector<Node> makeTree(const vector<vector<int>> nodeinfo) {
	vector<Node> nodes;
	int no = 1;
	for (vector<int> elem : nodeinfo) nodes.push_back(Node(elem[1], elem[0], no++));
	std::sort(nodes.begin(), nodes.end());

	queue<int> tree;
	tree.push(0);
	for (int i = 1; i < nodes.size(); i++) {
		int idx = tree.front();
		if (nodes[idx].left != -1 && nodes[idx].right != -1) tree.pop(), idx = tree.front();
		if (nodes[idx].left == -1) {
			if (nodes[idx].pos > nodes[i].pos && isValid(nodes, idx, i)) {
				nodes[idx].left = i, nodes[i].parent = idx;
				tree.push(i);
				continue;
			}
			else nodes[idx].left = -2;
		}
		if (nodes[idx].right == -1) {
			if (nodes[idx].pos < nodes[i].pos && isValid(nodes, idx, i)) {
				nodes[idx].right = i, nodes[i].parent = idx;
				tree.push(i);
				continue;
			}
			else nodes[idx].right = -2;
		}
		tree.pop(), i--;    //Retry node
	}
	return nodes;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(4);
	
	vector<Node> nodes = makeTree(nodeinfo);
	preOrder(nodes, 0, answer[0]);
	postOrder(nodes, 0, answer[1]);

	inOrder(nodes, 0, answer[2]);
	levelOrder(nodes, 0, answer[3]);

	return answer;
}

// input : 노드들의 좌표가 담긴 배열 nodeinfo
// ouput : 전위 순회, 후위 순회한 결과를 2차원 배열에 순서대로 담아 return
// 트리를 구성하는 모든 노드의 x, y 좌표 값은 정수이다.
// 모든 노드는 서로 다른 x값을 가진다.
// 같은 레벨(level)에 있는 노드는 같은 y 좌표를 가진다.
// 자식 노드의 y 값은 항상 부모 노드보다 작다.
// 임의의 노드 V의 왼쪽 서브 트리(left subtree)에 있는 모든 노드의 x값은 V의 x값보다 작다.
// 임의의 노드 V의 오른쪽 서브 트리(right subtree)에 있는 모든 노드의 x값은 V의 x값보다 크다.

int main()
{
	// {{5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2}} {{7, 4, 6, 9, 1, 8, 5, 2, 3}, {9, 6, 5, 8, 1, 4, 3, 2, 7}}
	vector<vector<int>> nodeinfo = { {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} };
	vector<vector<int>> output = solution(nodeinfo);

	for (vector<int> v : output) {
		for(int n : v) std::cout << n << ", ";

		std::cout << endl;
	}
}
