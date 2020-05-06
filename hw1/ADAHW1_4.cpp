#include <iostream>
#include <stdbool.h>
#include <string.h>
using namespace std;

char s1[2005], s2[2005];
int storage[2005][2005];

int dp(char s1[], char s2[], int pos1, int pos2, int length, int storage[][2005]){
	if (pos1 == length || pos2 == length)
		return 0;
	if (storage[pos1][pos2] != -2)
		return storage[pos1][pos2];
	if (s1[pos1] != s2[pos2]){
		storage[pos1][pos2] = dp(s1, s2, pos1 + 1, pos2 + 1, length, storage);
		return dp(s1, s2, pos1 + 1, pos2 + 1, length, storage);
	}
	storage[pos1][pos2] = 1 + (min(dp(s1, s2, pos1 + 1, pos2 + 1, length, storage), min(dp(s1, s2, pos1 + 1, pos2, length, storage), dp(s1, s2, pos1, pos2 + 1, length, storage))));
	return 1 + (min(dp(s1, s2, pos1 + 1, pos2 + 1, length, storage), min(dp(s1, s2, pos1 + 1, pos2, length, storage), dp(s1, s2, pos1, pos2 + 1, length, storage))));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s1 >> s2;
	int length1 = strlen(s1);
	int length2 = strlen(s2);
	int length = max(length1, length2);
	bool flag = true;
	for (int i = 0; i < 2005; i++){
		for (int j = 0; j < 2005; j++)
			storage[i][j] = -2;
	}
	for (int i = 0; i < length1 - 1; i++){
		if (s1[i] != s1[i + 1]){
			flag = false;
			break;
		}
	}
	if (s1[0] != s2[0])
		flag = false;
	if (flag == true){
		for (int i = 0; i < length2 - 1; i++){
			if (s2[i] != s2[i + 1]){
			    flag = false;
			    break;
			}
		}
	}
	if (flag == true)
		cout << min(length1, length2) << "\n";
	else{
		int ans = dp(s1, s2, 0, 0, length, storage);
	    cout << ans << "\n";
	}
	return 0;
}