#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;
int N, M, Q;
vector <int> orip[200005];
vector <int> p[200005];
ll mod = 1000000007;
int a = 2939999, b = 37;
bool visit[200005];

int hashfunction(int point){
	return (a * point + b) % mod;
}

vector<int> unionn(vector<int> &p1, vector<int> &p2){
	vector<int> newp;
	int ind1 = 0, ind2 = 0, ind = 0;
	while (ind1 < p1.size() && ind2 < p2.size() && ind <= 500){
		if (p1[ind1] < p2[ind2]){
			newp.push_back(p1[ind1]);
			ind1++;
			ind++;
		}
		else if (p1[ind1] == p2[ind2]){
			newp.push_back(p1[ind1]);
			ind1++;
			ind2++;
			ind++;
		}
		else if (p2[ind2] < p1[ind1]){
			newp.push_back(p2[ind2]);
			ind2++;
			ind++;
		}
	}
	if (ind1 < p1.size() && ind <= 500){
		for (int i = ind1; i < p1.size(); ++i){
			ind++;
			newp.push_back(p1[i]);
		}
	}
	else if (ind2 < p2.size() && ind <= 500){
		for (int i = ind2; i < p2.size(); ++i){
			ind++;
			newp.push_back(p2[i]);
		}
	}
	return newp;
}

void dfs(int point){
	if (visit[point] == true)
		return;
	visit[point] = true;
	for (int i = 0; i < orip[point].size(); ++i){
		dfs(orip[point][i]);
		p[point] = unionn(p[point], p[orip[point][i]]);
	}
}

vector<int> intersect(vector<int> &p1, vector<int> &p2){
	vector<int> newp;
	int ind1 = 0, ind2 = 0, ind = 0;
	while (ind1 < p1.size() && ind2 < p2.size()){
		if (p1[ind1] < p2[ind2])
			ind1++;
		else if (p1[ind1] == p2[ind2] && ind <= 500){
			newp.push_back(p1[ind1]);
			ind1++;
			ind2++;
			ind++;
		}
		else if (p2[ind2] < p1[ind1])
			ind2++;
	}
	return newp;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> Q;
	for (int i = 1; i <= N; ++i)
		visit[i] = false;
	for (int i = 1; i <= N; ++i)
		p[i].push_back(hashfunction(i));
	for (int i = 0; i < M; ++i){
		int u, v;
		cin >> u >> v;
		orip[u].push_back(v);
		p[u].push_back(hashfunction(v));
	}
	for (int i = 1; i <= N; ++i)
		sort(p[i].begin(), p[i].end());
	for (int i = 1; i <= N; ++i)
		dfs(i);
	for (int i = 0; i < Q; ++i){
		int q1, q2;
		cin >> q1 >> q2;
		vector<int> inter = intersect(p[q1], p[q2]);
		vector<int> uni = unionn(p[q1], p[q2]);
		double ans = (double)inter.size() / uni.size();
		cout << ans << "\n";
 	}
	return 0;
}