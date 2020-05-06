#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define ll long long int
#define INF 1e18

ll n, m, s, e;
ll distan[200002], dangerous[200002];
bool use[200002], use1[200002];
vector< pair<ll, ll> > p[200002];
vector< pair<ll, ll> > p1[200002];

void cal_dan(){
	for (ll i = 0; i < n; i++){
		dangerous[i] = INF;
		use[i] = false;
	}
	dangerous[s] = 0;
	priority_queue< pair <ll, ll>, vector< pair <ll, ll> >, greater <pair <ll, ll> > >Q;
	Q.push(make_pair(0, s));

	while (!Q.empty()){
		ll current = Q.top().second;
		Q.pop();
		if (use[current] == true)
			continue;
		use[current] = true;
		for (ll i = 0; i < p[current].size(); i++){
			ll point = p[current][i].first;
			ll dang = p[current][i].second;
			dangerous[point] = min(dangerous[point], max(dang, dangerous[current]));
			Q.push(make_pair(dangerous[point], point));
		}
	}
}

void cal_dist(){
	for (ll i = 0; i < n; i++){
		distan[i] = INF;
		use1[i] = false;
	}
	distan[s] = 0;
	priority_queue< pair <ll, ll>, vector< pair <ll, ll> >, greater <pair <ll, ll> > >Q1;
	Q1.push(make_pair(0, s));

	while (!Q1.empty()){
		ll current = Q1.top().second;
		Q1.pop();
		if (use1[current] == true)
			continue;
		use1[current] = true;
		for (ll i = 0; i < p1[current].size(); i++){
			ll point = p1[current][i].first;
			ll dist = p1[current][i].second;
			if (distan[current] != INF && p[current][i].second <= dangerous[e] && distan[point] > distan[current] + dist){
				distan[point] = distan[current] + dist;
				Q1.push(make_pair(distan[point], point));
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> s >> e;
	for (ll i = 0; i < m; i++){
		ll x, y, d, l;
		cin >> x >> y >> d >> l;
		p[x].push_back(make_pair(y, l));
		p1[x].push_back(make_pair(y, d));
		p[y].push_back(make_pair(x, l));
		p1[y].push_back(make_pair(x, d));
	}
	cal_dan();
	cal_dist();
	cout << distan[e] << " " << dangerous[e];
	return 0;
}