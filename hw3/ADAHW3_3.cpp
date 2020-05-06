#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
#define INF 1e18
using namespace std;

int T, N, M;
vector< pair<int, int> >p;
vector< pair< pair<int, int>, int > >e;
vector< pair<int, int> >edge[500002 * 2 + 100002 * 2];
int s1[500002], t1[500002], s2[500002], t2[500002];
ll dp[500002 * 2 + 100002 * 2];
bool use[500002 * 2 + 100002 * 2];
bool vis[500002 * 2 + 100002 * 2];
bool st[500002 * 2 + 100002 * 2];

void construct_edge(){
	for (int i = 0; i < p.size() - 1; i++){
		if (p[i].first == p[i + 1].first)
			e.push_back(make_pair(make_pair(i, i + 1), p[i + 1].second - p[i].second));
		else{
			dp[i + 1] = p[i + 1].second;
		}
	}
	for (int i = 0; i < M; i++){
		int p1 = lower_bound(p.begin(), p.end(), make_pair(s1[i], t1[i])) - p.begin();
		int p2 = lower_bound(p.begin(), p.end(), make_pair(s2[i], t2[i])) - p.begin();
		e.push_back(make_pair(make_pair(p1, p2), 1));
	}
}

bool find_cycle(int current){
	if (vis[current] == false){
		vis[current] = true;
		st[current] = true;
		for (int i = 0; i < edge[current].size(); i++){
			if (st[edge[current][i].first] == true)
				return true;
			else if (vis[edge[current][i].first] == false && find_cycle(edge[current][i].first) == true)
				return true;
		}
	}
	return st[current] = false;
}

void longest_path(int current){
	use[current] = true;
	if (!edge[current].empty()){
		for (int i = 0; i < edge[current].size(); i++){
			if (use[edge[current][i].first] == false)
				longest_path(edge[current][i].first);
			dp[current] = max(dp[current], dp[edge[current][i].first] + edge[current][i].second);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int i = 0; i < T; i++){
		cin >> N >> M;
		for (int j = 1; j <= N; j++){
			int length;
			cin >> length;
			p.push_back(make_pair(j, 0));
			p.push_back(make_pair(j, length));
		}
		for (int j = 0; j < M; j++){
			cin >> s1[j] >> t1[j] >> s2[j] >> t2[j];
			p.push_back(make_pair(s1[j], t1[j]));
			p.push_back(make_pair(s2[j], t2[j]));
		}
		sort(p.begin(), p.end());
		p.resize(unique(p.begin(), p.end()) - p.begin());
		for (int i = 0; i < 500002 * 2 + 100002 * 2; i++){
			dp[i] = 0;
			use[i] = false;
		}

		dp[0] = p[0].second;
		/*printf("point:\n");
		for (int i = 0; i < p.size(); i++)
			printf("%d %d %d\n", i, p[i].first, p[i].second);*/
		construct_edge();
		/*printf("edge:\n");
		for (int i = 0; i < e.size(); i++)
			printf("%d %d %d %d\n", i, e[i].first.first, e[i].first.second, e[i].second);*/
		for (int j = 0; j < e.size(); j++)
			edge[e[j].first.first].push_back(make_pair(e[j].first.second, e[j].second));
		/*printf("adj:\n");
		for (int i = 0; i < N * 3; i++){
			if (!edge[i].empty()){
				for (int j = 0; j < edge[i].size(); j++)
					printf("%d %d %d\n", i, edge[i][j].first, edge[i][j].second);
			}
		}*/
		for (int i = 0; i < 500002 * 2 + 100002 * 2; i++){
			vis[i] = false;
			st[i] = false;
		}
		int flag = 0;
		for (int i = 0; i < M * 2 + N * 2; i++){
			if (!edge[i].empty()){
				if (find_cycle(i) == true){
					cout << "LoveLive!" << "\n";
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1){
			p.clear();
			e.clear();
			for (int i = 0; i < 500002 * 2 + 100002 * 2; i++){
				if (!edge[i].empty())
					edge[i].clear();
			}
			continue;
		}

		for (int j = 0; j < M * 2 + N * 2; j++){
			if (use[j] == false){
				longest_path(j);
			}
		}
		ll ans = -1;
		for (int j = 0; j < M * 2 + N * 2; j++){
			//printf("j:%d dp:%lld\n", j, dp[j]);
			if (dp[j] > ans)
				ans = dp[j];
		}
		cout << ans << "\n";
		p.clear();
		e.clear();
		for (int i = 0; i < 500002 * 2 + 100002 * 2; i++){
			if (!edge[i].empty())
				edge[i].clear();
		}
	}
	return 0;
}