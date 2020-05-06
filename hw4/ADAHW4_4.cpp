#include <iostream>
#include <cstring>
#include "hex.h"
using namespace std;

typedef std::pair<int, int> pii;
const int maxn = 11;

int board[maxn][maxn];
int weight[maxn][maxn];
int n;

void init(int _n){
	n = _n;
    memset(board, 0, sizeof board);
    memset(weight, 0, sizeof weight);
}

void attackweight(pii mypre){
	if (mypre.first-1 >= 0 && mypre.second+1 < n && board[mypre.first-1][mypre.second+1] == 0)
		weight[mypre.first-1][mypre.second+1] += 8;
	if (mypre.first-1 >= 0 && board[mypre.first-1][mypre.second] == 0)
		weight[mypre.first-1][mypre.second] += 8;
	if (mypre.first+1 < n && mypre.second-1 >= 0 && board[mypre.first+1][mypre.second-1] == 0)
		weight[mypre.first+1][mypre.second-1] += 8;
	if (mypre.first+1 < n && board[mypre.first+1][mypre.second] == 0)
		weight[mypre.first+1][mypre.second] += 8;
}

void defenseweight(pii p){
	if (p.first + p.second == n - 1){
		int thres;
		if (n % 2 == 0)
			thres = n / 2;
		else
			thres = n / 2 + 1;
		if (p.first < thres){
			if (p.second-1 >= 0 && board[p.first][p.second-1] == 0)
				weight[p.first][p.second-1] += 20;
		}
		else {
			if (p.second+1 < n && board[p.first][p.second+1] == 0)
				weight[p.first][p.second+1] += 20;
		}
	}
	else if (p.first + p.second > n - 1){
		if (p.second-1 >= 0 && board[p.first][p.second-1] == 0)
			weight[p.first][p.second-1] += 20;
	}
	else {
		if (p.second+1 < n && board[p.first][p.second+1] == 0)
			weight[p.first][p.second+1] += 20;
	}
}

pii decide(pii p){
	static pii mypre;
	//printf("first:%d second:%d\n", mypre.first, mypre.second);
	pii decision;
	if (p == make_pair(-1, -1)){
		if (n % 2 != 0){
			board[n/2][n/2] = 2;
			decision = make_pair(n/2, n/2);
		}
		else {
			board[n/2-1][n/2] = 2;
			decision = make_pair(n/2-1, n/2);
		}
		mypre = decision;
		return decision;
	}
	board[p.first][p.second] = 1;
	attackweight(mypre);
	defenseweight(p);
	/*for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			printf("%d %d %d\n", i, j, weight[i][j]);
	}*/
	int M = -1, x, y;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (weight[i][j] >= M && board[i][j] == 0){
				M = weight[i][j];
				int cnt = 0;
				if (i-1 >= 0){
					if (board[i-1][j] == 2)
						cnt++;
					if (j+1 < n){
						if (board[i-1][j+1] == 2)
							cnt++;
					}
				}
				if (j-1 >= 0){
					if (board[i][j-1] == 2)
						cnt++;
				}
				if (j+1 < n){
					if (board[i][j+1] == 2)
						cnt++;
				}
				if (i+1 < n){
					if (board[i+1][j] == 2)
						cnt++;
					if (j-1 >= 0){
						if (board[i+1][j-1] == 2)
							cnt++;
					}
				}
				if (cnt <= 4){
					x = i;
					y = j;
				}
			}
		}
	}
	board[x][y] = 2;
	decision = make_pair(x, y);
	mypre = decision;
	return decision;
}