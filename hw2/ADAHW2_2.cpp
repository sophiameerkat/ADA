#include <iostream>
#include <algorithm>
#include <deque>
#include <math.h>
#define ll long long int
using namespace std;

int t, length, max_move, note[100005];
ll dp[100005][305], tdp[305], ans;
deque< pair<ll, int> > tmpdp;

void cal(){
	for (int i = 0; i < length; i++)//初始化一開始為0
		dp[0][i] = 0;
	for (int i = 1; i < t; i++){//每一次
		ll min_tmp = dp[i - 1][note[i]];
		for (int j = 0; j < length; j++){//每一個按鍵
			ll m = abs(note[i] - note[i - 1]) - max_move;//計算第一種case要花多少effort
			if (m < 0)//如果是負的，代表不用花費effort，歸零
				m = 0;
			dp[i][j] = dp[i - 1][j] + m;//case1:前一次動的這次也動
			ll index;
			if (abs(j - note[i]) <= max_move)
				index = 0;
			else
				index = abs(j - note[i]) - max_move;
			if (index + dp[i - 1][j] < min_tmp)
				min_tmp = index + dp[i - 1][j];
			//printf("j:%d index:%lld min_tmp:%lld\n", j, index, min_tmp);
			dp[i][note[i - 1]] = min(min_tmp, dp[i][note[i - 1]]);//case2:前一次沒動的這次動，比較小才取代
		}
		for (int j = 0; j < length; j++)
			tdp[j] = dp[i][j];
		for (int j = 0; j <= max_move; j++)
			tmpdp.push_back(make_pair(tdp[j], j));
		sort(tmpdp.begin(), tmpdp.end());
		dp[i][0] = tmpdp[0].first;
		for (int j = 1; j < length; j++){
			if (j + max_move < length){
				while (!tmpdp.empty() && (tmpdp.back().first >= tdp[j + max_move]))
					tmpdp.pop_back();
				tmpdp.push_back(make_pair(tdp[j + max_move], j + max_move));
			}
			if (j - max_move - 1 >= 0){
				while (!tmpdp.empty() && (tmpdp.front().second <= j - max_move - 1))
					tmpdp.pop_front();
			}
			dp[i][j] = tmpdp[0].first;
		}
		/*for (int j = 0; j < length; j++)
			printf("%lld ", dp[i][j]);
		printf("\n");*/
		if (!tmpdp.empty())
			tmpdp.clear();
	}
	ans = dp[t - 1][0];
	for (int i = 1; i < length; i++){//在最後那列找最小的effort
		if (dp[t - 1][i] < ans)
			ans = dp[t - 1][i];
	}
	cout << ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> t >> length >> max_move;
	for (int i = 0 ; i < t; i++)
		cin >> note[i];
	cal();
	return 0;
}