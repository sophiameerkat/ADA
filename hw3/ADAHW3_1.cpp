#include <iostream>
#include <vector>
#define ll long long int
using namespace std;
vector< pair<ll, ll> >p[(1<<18) + 5];
ll indegree[(1<<18) + 5];
ll or_indegree[(1<<18) + 5];
vector<ll> use;
bool query[(1<<18) + 5];
ll ans = 0;

ll change_route(ll oriplug_point, ll plug_point){
	//printf("point:%lld parent:%lld indegree:%lld\n", plug_point, p[plug_point][0].first, indegree[plug_point]);
	use.push_back(p[plug_point][0].first);
	ans += p[plug_point][0].second;
	if (p[plug_point][0].first == 0)
		return plug_point;
	indegree[p[plug_point][0].first]--;
	if (indegree[p[plug_point][0].first] != 0){
		if (query[oriplug_point] == false)
			p[plug_point][0].second = 1;
		return p[plug_point][0].first;
	}
	if (or_indegree[p[plug_point][0].first] > 1){
		change_route(oriplug_point, p[plug_point][0].first);
		if (query[oriplug_point] == false)
			p[plug_point][0].second = 1;
	}
	else {
		ll tmp = change_route(oriplug_point, p[plug_point][0].first);
		if (p[p[plug_point][0].first][0].first != 0)
			p[plug_point][0].second = p[p[plug_point][0].first][0].second + 1;
		p[plug_point][0].first = tmp;
	}
	if (or_indegree[plug_point] > 1)
		return plug_point;
	return p[plug_point][0].first;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll N;
	cin >> N;
	for (ll i = 1; i <= N; i++){
		or_indegree[i] = 0;
		indegree[i] = 0;
	}
	for (ll i = 1; i <= N; i++){
		ll point;
		cin >> point;
		p[i].push_back(make_pair(point, 1));
		or_indegree[point]++;
		indegree[point]++;
	}
	for (ll i = 1; i <= N; i++)
		query[i] = false;
	ll Q;
	cin >> Q;
	for (ll i = 0; i < Q; i++){
		ll num;
		cin >> num;
		for (ll j = 1; j <= num; j++){
			ll plug_point;
			cin >> plug_point;
			change_route(plug_point, plug_point);
			query[plug_point] = true;
		}
		cout << ans << "\n";
		ans = 0;
		//for (ll j = 1; j <= N; j++)
			//printf("j:%lld parent:%lld weight:%lld\n", j, p[j][0].first, p[j][0].second);
		for (ll j = 0; j < use.size(); j++)
			indegree[use[j]] = or_indegree[use[j]];
		use.clear();
	}
	return 0;
}