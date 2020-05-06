#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

int n;
ll arr[500002];
ll cnt;
ll max_arr[500002 * 3];
ll min_arr[500002 * 3];
ll cou[500002 * 3] = {0};

void merge(int left, int mid, int right){
	//printf("left:%d mid:%d right:%d\n", left, mid, right);
	max_arr[mid] = arr[mid];
	for (int i = mid - 1; i >= left; i--){
		if (arr[i] > max_arr[i + 1])
			max_arr[i] = arr[i];
		else
			max_arr[i] = max_arr[i + 1];
	}
	max_arr[mid + 1] = arr[mid + 1];
	for (int i = mid + 2; i <= right; i++){
		if (arr[i] > max_arr[i - 1])
			max_arr[i] = arr[i];
		else
			max_arr[i] = max_arr[i - 1];
	}
	min_arr[mid] = arr[mid];
	for (int i = mid - 1; i >= left; i--){
		if (arr[i] < min_arr[i + 1])
			min_arr[i] = arr[i];
		else
			min_arr[i] = min_arr[i + 1];
	}
	min_arr[mid + 1] = arr[mid + 1];
	for (int i = mid + 2; i <= right; i++){
		if (arr[i] < min_arr[i - 1])
			min_arr[i] = arr[i];
		else
			min_arr[i] = min_arr[i - 1];
	}
	//for (int i = left; i <= right; i++)
		//printf("max:%lld min:%lld\n", max_arr[i], min_arr[i]);
	for (int i = mid; i >= left; i--){//左大左小
		int index4 = max_arr[i] - min_arr[i];
		if (max_arr[i + index4] < max_arr[i] && min_arr[i + index4] > min_arr[i] && i + index4 > mid && i + index4 <= right)
			cnt++;
	}
	for (int i = mid + 1; i <= right; i++){//右大右小
		int index5 = max_arr[i] - min_arr[i];
		if (max_arr[i - index5] < max_arr[i] && min_arr[i - index5] > min_arr[i] && i - index5 <= mid && i - index5 >= left)
			cnt++;
	}
	for (int i = mid; i >= left; i--)
		cou[i + max_arr[i] + n] = 0;
	int index = mid + 1;
	int index1 = mid + 1;
	for (int i = mid; i >= left; i--){//左大右小
		while (max_arr[i] > max_arr[index] && index <= right){
			cou[index + min_arr[index] + n]++;
			//printf("i:%d index:%lld cou:%lld\n", i, index + min_arr[index] + n, cou[index + min_arr[index] + n]);
			index++;
		}
		while (min_arr[i] < min_arr[index1] && index1 <= right && index1 < index){
			cou[index1 + min_arr[index1] + n]--;
			//printf("i:%d index1:%lld cou:%lld\n", i, index1 + min_arr[index1] + n, cou[index1 + min_arr[index1] + n]);
			index1++;
		}
		//printf("cou:%lld\n", cou[i + max_arr[i] + n]);
		cnt += cou[i + max_arr[i] + n];
	}
	for (int i = mid + 1; i <= right; i++)
		cou[max_arr[i] - i + n] = 0;
	int index2 = mid;
	int index3 = mid;
	for (int i = mid + 1; i <= right; i++){//左小右大
		while (max_arr[i] > max_arr[index2] && index2 >= left){
			cou[min_arr[index2] - index2 + n]++;
			//printf("i:%d index2:%lld cou:%lld\n", i, min_arr[index2] - index2 + n, cou[min_arr[index2] - index2 + n]);
			index2--;
		}
		while (min_arr[i] < min_arr[index3] && index3 >= left && index3 > index2){
			cou[min_arr[index3] - index3 + n]--;
			//printf("i:%d index3:%lld cou:%lld\n", i, min_arr[index3] - index3 + n, cou[min_arr[index3] - index3 + n]);
			index3--;
		}
		//printf("cou:%lld\n", cou[max_arr[i] - i + n]);
		cnt += cou[max_arr[i] - i + n];
	}
	return;
}

void compute(int left, int right){
	if (left == right)
		return;
	int mid = left + (right - left) / 2;
	compute(left, mid);
	compute(mid + 1, right);
	merge(left, mid, right);
	return;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	cnt = n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	compute(0, n - 1);
	cout << cnt << "\n";
	return 0;
}