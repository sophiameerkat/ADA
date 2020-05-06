#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
char arr[128][128];
bool e[128][128];
typedef struct info{
	int cnt;
	int index;
}Info;
Info p[128];
int s[128], s1[128];
int counter = 1;
typedef struct info1{
	int R;
	int C;
	int degree;
}Info1;
bool in[128];
vector <int> Q, Qmax, Col[128];

bool cmp(Info a, Info b){
	return a.cnt > b.cnt;
}

bool inter(int &po, int &k){
	for (int i = 0; i < Col[k].size(); ++i){
		if (e[po][Col[k][i]] == 1)
			return true;
	}
	return false;
}

void colorsort(vector <Info1> &pp){
	int maxnum = 1;
	int kmin = (int)Qmax.size() - (int)Q.size() + 1;
	if (kmin <= 0)
		kmin = 1;
	int j = 0;
	Col[1].clear();
	Col[2].clear();
	for (int i = 0; i < pp.size(); ++i){
		int po = pp[i].R;
		int k = 1;
		while (inter(po, k) == true)
			k++;
		if (k > maxnum){
			maxnum = k;
			Col[maxnum+1].clear();
		}
		Col[k].push_back(po);
		if (k < kmin){
			pp[j].R = pp[i].R;
			j++;
		}
	}
	if (j>0)
		pp[j-1].C = 0;
	if (kmin < 1)
		kmin = 1;
	for (int k = kmin; k <= maxnum; ++k){
		for (int i = 0; i < Col[k].size(); ++i){
			pp[j].R = Col[k][i];
			pp[j].C = k;
			j++;
		}
	}
}

vector <Info1> calintersect(int &poi, vector <Info1> &pp){
	vector <Info1> newp;
	for (int i = 0; i < pp.size(); ++i){
		if (e[poi][pp[i].R] == 1){
			Info1 tmp;
			tmp.R = pp[i].R;
			tmp.C = 0;
			tmp.degree = 0;
			newp.push_back(tmp);
		}
	}
	return newp;
}

void caldegree(vector <Info1> &newp){
	for (int i = 0; i < newp.size(); ++i){
		for (int j = 0; j < newp.size(); ++j){
			if (e[newp[i].R][newp[j].R] == 1)
				newp[i].degree++;
		}
	}
}

bool cmp1(Info1 a, Info1 b){
	return a.degree > b.degree;
}

void MCD(int l, vector <Info1> &pp){
	s[l] += (s[l-1] - s1[l]);
	s1[l] = s[l-1];
	while (!pp.empty()){
		int ind = pp.size() - 1;
		int poi = pp[ind].R;
		int co = pp[ind].C;
		pp.pop_back();
		if (Q.size() + co > Qmax.size()){
			Q.push_back(poi);
			vector <Info1> n = calintersect(poi, pp);
			if (!n.empty()){
				if (s[l] * 1.0 / counter < 0.025){
					caldegree(n);
					sort(n.begin(), n.end(), cmp1);
				}
				colorsort(n);
				s[l]++;
				counter++;
				MCD(l+1, n);
			}
			else if (Q.size() > Qmax.size())
				Qmax = Q;
			Q.pop_back();
		}
		else
			return;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	vector <Info1> point;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			cin >> arr[i][j];
			e[i][j] = 0;
		}
	}
	for (int i = 0; i < N; ++i){
		p[i].index = i;
		p[i].cnt = 0;
	}
	for (int i = 1; i <= N; ++i){
		s[i] = 0;
		s1[i] = 1;
	}
	for (int i = 0; i < N; ++i){
		for (int j = i + 1; j < N; ++j){
			if ((arr[i][i] - '0') + (arr[i][j] - '0') + (arr[j][i] - '0') + (arr[j][j] - '0') == 4){
				e[i][j] = 1;
				e[j][i] = 1;
			}
		}
	}
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			if (e[i][j] == 1)
				p[i].cnt++;
		}
	}
	sort(p, p+N, cmp);
	for (int i = 0; i < N; ++i){
		if (p[i].cnt != 0){
			Info1 tmp;
			tmp.R = p[i].index;
			tmp.C = 0;
			tmp.degree = p[i].cnt;
			point.push_back(tmp);
		}
	}
	colorsort(point);
	MCD(1, point);
	sort(Qmax.begin(), Qmax.end());
	for (int i = 0; i < Qmax.size(); ++i)
		cout << Qmax[i] + 1 << " ";
	for (int i = 0; i < N; ++i)
		in[i] = false;
	for (int i = 0; i < Qmax.size(); ++i)
		in[Qmax[i]] = true;
	for (int i = 0; i < N; ++i){
		if (in[i] == false)
			cout << i + 1 << " ";
	}
	return 0;
}