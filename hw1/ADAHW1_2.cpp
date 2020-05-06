#include <iostream>
#define ll long long int
using namespace std;

ll arr[5000002];

typedef struct info{
	ll max_sum;
	ll tot_sum;
	ll l_sum;
	ll r_sum;
}Info;

Info node[5000002 * 4];

Info get_value(Info l, Info r, int in){
	Info a;
	node[in].tot_sum = l.tot_sum + r.tot_sum;
	node[in].l_sum = l.tot_sum + r.l_sum;
	if (l.l_sum > node[in].l_sum)
	    node[in].l_sum = l.l_sum;
	node[in].r_sum = r.tot_sum + l.r_sum;
	if (r.r_sum > node[in].r_sum)
		node[in].r_sum = r.r_sum;
	node[in].max_sum = l.r_sum + r.l_sum;
	if (node[in].tot_sum > node[in].max_sum)
		node[in].max_sum = node[in].tot_sum;
	if (l.max_sum > node[in].max_sum)
		node[in].max_sum = l.max_sum;
	if (r.max_sum > node[in].max_sum)
		node[in].max_sum = r.max_sum;
	if (node[in].l_sum > node[in].max_sum)
		node[in].max_sum = node[in].l_sum;
	if (node[in].r_sum > node[in].max_sum)
		node[in].max_sum = node[in].r_sum;
	return node[in];
}

Info max_sub(ll arr[], int in, int left, int right){
	if (left == right){
		node[in].max_sum = arr[left];
		node[in].tot_sum = arr[left];
		node[in].l_sum = arr[left];
		node[in].r_sum = arr[left];
		return node[in];
	}
	int mid = left + (right - left) / 2;
	Info l = max_sub(arr, 2 * in, left, mid);
	Info r = max_sub(arr, 2 * in + 1, mid + 1, right);
    Info ans = get_value(node[2 * in], node[2 * in + 1], in);
	//printf("%d %d %lld %lld %lld %lld %lld\n", left, right, l.r_sum, r.l_sum, ans.l_sum, ans.r_sum, ans.max_sum);
	return ans;
}

Info change(ll arr[], int in, int p, int v, int left, int right){
	if (left == right){
		node[in].max_sum = v;
		node[in].tot_sum = v;
		node[in].l_sum = v;
		node[in].r_sum = v;
		return node[in];
	}
	int mid = left + (right - left) / 2;
	if (p <= mid)
		change(arr, 2 * in, p, v, left, mid);
	else
		change(arr, 2 * in + 1, p, v, mid + 1, right);
	Info ans = get_value(node[2 * in], node[2 * in + 1], in);
	return ans;
}

int main(){
	int n, q, p;
	ll v;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	ll ans = max_sub(arr, 1, 1, n).max_sum;
	if (ans < 0)
		ans = 0;
	cout << ans << "\n";
	for (int i = 0; i < q; i++){
		cin >> p >> v;
		arr[p] = v;
		ll ans = change(arr, 1, p, v, 1, n).max_sum;
		if (ans < 0)
			ans = 0;
	    cout << ans << "\n";
	}
	return 0;
}