#include <iostream>
#include <string.h>
#include <algorithm>
#define ll long long int
using namespace std;

ll p[1000002], f[1000002];
ll cnt = 0;

void merge(int left, int mid, int right){
	for (int i = mid + 1; i <= right; i++){
		int a = lower_bound(p + left, p + mid + 1, p[i] - f[i]) - p;
		int b = upper_bound(p + left, p + mid + 1, p[i] + f[i]) - p;
		if (a < b)
			cnt += (b - a);
		//printf("i:%d left:%d mid:%d right:%d p[i] - f[i]:%d p[i] + f[i]:%d p[left]:%d p[mid]:%d a:%d b:%d\n", i, left, mid, right, p[i] - f[i], p[i] + f[i], p[left], p[mid], a, b);
	}
	ll length1 = mid - left + 1;
	ll tmp1[length1 + 2];
	ll tmp1f[length1 + 2];
	memcpy(tmp1, p + left, sizeof(ll) * length1);
	memcpy(tmp1f, f + left, sizeof(ll) * length1);
	ll length2 = right - mid;
	ll tmp2[length2 + 2];
	ll tmp2f[length2 + 1];
	memcpy(tmp2, p + mid + 1, sizeof(ll) * length2);
	memcpy(tmp2f, f + mid + 1, sizeof(ll) * length2);
	ll index1 = 0, index2 = 0, index3 = left;
	while (index1 < length1 && index2 < length2){
		if (tmp1[index1] <= tmp2[index2]){
			p[index3] = tmp1[index1];
			f[index3] = tmp1f[index1];
			index1++;
			index3++;
		}
		else{
			p[index3] = tmp2[index2];
			f[index3] = tmp2f[index2];
			index2++;
			index3++;
		}
	}
	while (length1 > index1){
		p[index3] = tmp1[index1];
		f[index3] = tmp1f[index1];
		index1++;
		index3++;
	}
	while (length2 > index2){
		p[index3] = tmp2[index2];
		f[index3] = tmp2f[index2];
		index2++;
		index3++;
	}
}

void merge_sort(int left, int right){
	if (right <= left)
		return;
	int mid = left + (right - left) / 2;
	merge_sort(left, mid);
	merge_sort(mid + 1, right);
	merge(left, mid, right);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	for (int i = 0; i < n; i++)
		cin >> f[i];
	merge_sort(0, n - 1);
	//for (int i = 0; i < n; i++)
	//	printf("%d ", p[i]);
	cout << cnt;
}