#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

int N, flag = 0;
ll a[200002], s[7], rnum[8] = {0}, t = 0;

void rang(){
	for (int i = 0; i < N; i++){
		if (a[i] <= s[0])
			rnum[0]++;//用s1可以解決
		else if (a[i] > s[0] && a[i] <= s[1])
			rnum[1]++;//用s2可以解決
		else if (a[i] > s[1] && a[i] <= s[2])
			rnum[2]++;//用s3可以解決or用s1+s2可以解決
		else if (a[i] > s[2] && a[i] <= s[3])
			rnum[3]++;//用s1+s2可以解決or用s3可以解決
		else if (a[i] > s[3] && a[i] <= s[4])
			rnum[4]++;//用s1+s3可以解決
		else if (a[i] > s[4] && a[i] <= s[5])
			rnum[5]++;//用s2+s3可以解決
		else if (a[i] > s[5] && a[i] <= s[6])
			rnum[6]++;//用s1+s2+s3可以解決
		else if (a[i] > s[6])
			rnum[7]++;//都不能解決
	}
	//for (int i = 0; i <= 7; i++)
	//	printf("%lld ", rnum[i]);
}

void cal(){
	if (rnum[7] != 0){
		cout << "-1";
		return;
	}
	t += rnum[6];
	if (rnum[5] > 0){
		//cout << "5:" << '\n';
		//cout << rnum[5] << '\n';
		t += rnum[5];
		rnum[0] -= min(rnum[0], rnum[5]);
	}
	if (rnum[4] > 0){
		//cout << "4:" << '\n';
		//cout << rnum[4] << '\n';
		t += rnum[4];
		if (rnum[4] <= rnum[1]){
			rnum[1] -= rnum[4];
			rnum[4] = 0;
		}
		else {
			rnum[4] -= rnum[1];
			rnum[1] = 0;
			if (rnum[0] > 0)
				rnum[0] -= min(rnum[0], rnum[4]);
		}
	}
	if (flag == 0) {
		if (rnum[3] > 0){
			//cout << "3:" << '\n';
			//cout << rnum[3] << '\n';
			t += rnum[3];
			if (rnum[3] <= rnum[2]){
				rnum[2] -= rnum[3];
				rnum[3] = 0;
			}
			else {
				rnum[3] -= rnum[2];
				rnum[2] = 0;
				if (rnum[1] > 0){
					if (rnum[3] <= rnum[1]){
						rnum[1] -= rnum[3];
						rnum[3] = 0;
					}
					else {
						rnum[3] -= rnum[1];
						rnum[1] = 0;
						if (rnum[0] > 0)
							rnum[0] -= min(rnum[0], rnum[3]);
					}
				}
				else if (rnum[0] > 0){
					if (rnum[3] <= rnum[0]){
						rnum[0] -= rnum[3];
						rnum[3] = 0;
					}
					else {
						rnum[3] -= rnum[0];
						rnum[0] = 0;
					}
				}
			}
		}
		while (rnum[2] > 0 && rnum[1] > 0 && rnum[0] > 0){
			rnum[0]--;
			rnum[1]--;
			rnum[2]--;
			t++;
		}
		if (rnum[1] > 0 && rnum[2] > 0){
			while (rnum[1] > 0 && rnum[2] > 0){
				rnum[1]--;
				rnum[2]--;
				t++;
			}
			if (rnum[2] > 0)
				t += rnum[2] / 2 + rnum[2] % 2;
			if (rnum[1] > 0)
				t += rnum[1] / 2 + rnum[1] % 2;
		}
		else if (rnum[0] > 0 && rnum[2] > 0){
			while (rnum[0] > 0 && rnum[2] > 0){
				rnum[0] -= 2;
				rnum[2]--;
				t++;
			}
			if (rnum[2] > 0)
				t += rnum[2] / 2 + rnum[2] % 2;
			if (rnum[0] > 0){
				t += rnum[0] / 3;
				if (rnum[0] % 3 != 0)
					t++;
			}
		}
		else if (rnum[0] > 0 && rnum[1] > 0){
			 t += rnum[1] / 2;
			 rnum[0] -= rnum[1] / 2;
			 rnum[1] -= 2 * (rnum[1] / 2);
			 if (rnum[0] > 0 && rnum[1] > 0){
			 	rnum[0] -= 2;
			 	t++;
			 	if (rnum[0] > 0){
			 		t += rnum[0] / 3;
			 		if (rnum[0] % 3 != 0)
			 			t++;
			 	}
			 }
			 else if (rnum[1] > 0)
			 	t++;
			 else if (rnum[0] > 0){
			 	t += rnum[0] / 3;
			 	if (rnum[0] % 3 != 0)
			 		t++;
			 }
		}
		else if (rnum[2] > 0)
			t += rnum[2] / 2 + rnum[2] % 2;
		else if (rnum[1] > 0)
			t += rnum[1] / 2 + rnum[1] % 2;
		else if (rnum[0] > 0){
			t += rnum[0] / 3;
			if (rnum[0] % 3 != 0)
				t++;
		}
	}
	else if (flag == 1){
		while (rnum[3] > 0 && rnum[1] > 0 && rnum[0] > 0){
			rnum[3]--;
			rnum[1]--;
			rnum[0]--;
			t++;
		}
		if (rnum[3] > 0 && rnum[1] > 0){
			while (rnum[1] > 0 && rnum[3] > 0){
				rnum[1]--;
				rnum[3]--;
				t++;
			}
		}
		else if (rnum[3] > 0 && rnum[0] > 0){
			while (rnum[0] > 0 && rnum[3] > 0){
				rnum[0] -= 2;
				rnum[3]--;
				t++;
			}
		}
		if (rnum[3] > 0){
			t += rnum[3];
			if (rnum[3] >= rnum[2]){
				rnum[3] -= rnum[2];
				rnum[2] = 0;
			}
			else {
				rnum[2] -= rnum[3];
				rnum[3] = 0;
			}
		}
		if (rnum[2] > 0){
			while (rnum[2] > 0 && rnum[1] > 0 && rnum[0] > 0){
				rnum[2]--;
				rnum[1]--;
				rnum[0]--;
				t++;
			}
			if (rnum[1] > 0 && rnum[2] > 0){
				while (rnum[1] > 0 && rnum[2] > 0){
					rnum[1]--;
					rnum[2]--;
					t++;
				}
			}
			else if (rnum[0] > 0 && rnum[2] > 0){
				while (rnum[0] > 0 && rnum[2] > 0){
					rnum[0] -= 2;
					rnum[2]--;
					t++;
				}
			}
			if (rnum[2] > 0)
				t += rnum[2] / 2 + rnum[2] % 2;
		}
		if (rnum[0] > 0 && rnum[1] > 0){
			 t += rnum[1] / 2;
			 rnum[0] -= rnum[1] / 2;
			 rnum[1] -= 2 * (rnum[1] / 2);
			 if (rnum[0] > 0 && rnum[1] > 0){
			 	rnum[0] -= 2;
			 	t++;
			 	if (rnum[0] > 0){
			 		t += rnum[0] / 3;
			 		if (rnum[0] % 3 != 0)
			 			t++;
			 	}
			 }
			 else if (rnum[1] > 0)
			 	t++;
			 else if (rnum[0] > 0){
			 	t += rnum[0] / 3;
			 	if (rnum[0] % 3 != 0)
			 		t++;
			 }
		}
		else if (rnum[1] > 0)
			t += rnum[1] / 2 + rnum[1] % 2;
		else if (rnum[0] > 0){
			t += rnum[0] / 3;
			if (rnum[0] % 3 != 0)
				t++;
		}
	}
	cout << t;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < 3; i++)
		cin >> s[i];
	sort(s, s + 3);
	s[3] = s[0] + s[1];
	s[4] = s[0] + s[2];
	s[5] = s[1] + s[2];
	s[6] = s[0] + s[1] + s[2];
	if (s[3] < s[2]){
		flag = 1;
		int tmp = s[2];
		s[2] = s[3];
		s[3] = tmp;
	}
	for (int i = 0; i < N; i++)
		cin >> a[i];
	rang();
	cal();
	return 0;
}