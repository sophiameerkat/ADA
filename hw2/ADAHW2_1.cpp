#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#define ll long long int
using namespace std;

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada

/*******************************************************************************
 * Example usage:
 * const int kN = 2000000;
 * int leadership[kN], team_value[kN];
 * int main() {
 *   int n = ada::Init(); // Get N
 *   for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
 *   for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
 * }
 ******************************************************************************/

const int kN = 2000000;
ll leadership[kN], team_value[kN];
ll dp[kN + 5];
ll dpsum[kN + 5];
ll sum[kN + 5];
ll mo = 1000000007;

void cal(int n){
    dp[n - 1] = 1;
    dpsum[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--){
        if (leadership[i] < team_value[i + 1])
            dp[i] = dp[i + 1];
        else {
            ll tmp = leadership[i] + sum[i];
            //printf("tmp:%d\n", tmp);
            int index = upper_bound(sum + i + 1, sum + n, tmp) - sum;
            index -= 1;
            //printf("index:%d\n", index);
            dp[i] = (dpsum[i + 1] % mo  - dpsum[index + 2] % mo + mo) % mo;
            if (index == n - 1)
               dp[i] += 1;
            dp[i] %= mo;
        }
        dpsum[i] = (dpsum[i + 1] % mo + dp[i] % mo) % mo;
        //printf("i:%d dp:%lld dpsum:%lld\n", i, dp[i], dpsum[i]);
    }
}

int main(){
    int n = ada::Init();
    for (int i = 0; i < n; i++)
        leadership[i] = ada::GetLeadership();
    for (int i = 0; i < n; i++)
        team_value[i] = ada::GetTeamValue();
    /*for (int i = 0; i < n; i++)
        printf("%d ", leadership[i]);
    for (int i = 0; i < n; i++)
        printf("%d ", team_value[i]);*/
    sum[0] = team_value[0];
    for (int i = 1; i < n; i++)
        sum[i] = sum[i - 1] + team_value[i];
    /*for (int i = 0; i < n; i++)
        printf("%d ", sum[i]);*/
    cal(n);
    printf("%lld\n", dp[0]);
    return 0;
}