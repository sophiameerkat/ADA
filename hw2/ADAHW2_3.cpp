#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;
#define INF -10000000000

typedef struct attribute{
	int a;
	int b;
	int e;
}Attribute;

int number, round;
Attribute p[105];
ll dp[2][10001][105];
ll tmp = 0, ans = -1000000000;

int cmp(Attribute p1, Attribute p2){
	if (p2.a * p1.b - p1.a * p2.b > 0)
		return 1;
	else if (p2.a * p1.b - p1.a * p2.b == 0){
		if (p1.b > p2.b)
			return 1;
		else
			return 0;
	}
	return 0;
}

void dpcal(){
	for (int i = 0; i <= 1; i++){
		for (int j = 0; j <= tmp; j++){
			for (int k = 0; k <= round; k++){
				if (i == 0 && k == 0 && j == 0)
					dp[i][j][k] = 0;
				else
					dp[i][j][k] = INF;
			}
		}
	}
	for (int i = 1; i <= number; i++){
		for (int j = 0; j <= tmp; j++){
			for (int k = 0; k <= round; k++){
				if (j - p[i].b < 0 || k - 1 < 0)
					dp[i % 2][j][k] = dp[(i - 1) % 2][j][k];
				else
					dp[i % 2][j][k] = max(dp[(i - 1) % 2][j][k], dp[(i - 1) % 2][j - p[i].b][k - 1] + (j - p[i].b) * p[i].a);
			}
		}
	}
	for (int j = 0; j <= tmp; j++){
		if (dp[number % 2][j][round] > ans)
			ans = dp[number % 2][j][round];
	}
	cout << ans;
}

int main(){ 
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> number >> round;
	for (int i = 1; i <= number; i++){
		cin >> p[i].a >> p[i].b;
		tmp += p[i].b;
	}
	//cout << tmp;
	sort(p + 1, p + number + 1, cmp);
	//for (int i = 1; i <= number; i++)
	//	cout << p[i].a << " " << p[i].b << '\n';
	p[1].e = 0;
	dpcal();
	return 0;
}