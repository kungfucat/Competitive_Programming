#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(c)	c.begin(), c.end()
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define trace(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {cout << "\n";}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << " : " << a << " | "; err(++it, args...);}

typedef long long int lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<lli, lli> > vplli;
typedef vector<lli> vlli;
typedef vector<vlli> vvlli;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define PI 3.141592653589793
#define mod (lli)(1000*1000*1000+7)

template<typename T> T gcd(T a, T b) { if (a == 0) return b; return gcd(b % a, a); }
template<typename T> T pow(T a, T b, lli m) {T ans = 1; while (b > 0) { if (b % 2 == 1) ans = ((ans % m) * (a % m)) % m; b /= 2; a = ((a % m) * (a % m)) % m; } return ans % m; }


lli add(lli a, lli b) {a += b; if (a >= mod)	a -= mod; return a;}

lli add(lli a, lli b, lli c) {return add(add(a, b), c);}

lli sub(lli a, lli b) {a -= b; if (a < 0)a += mod; return a;}

lli mult(lli a, lli b) {return (((a % mod) * (b % mod)) % mod);}

lli mult(lli a, lli b, lli c) {return mult(mult(a, b), c);}

lli power(lli a, lli b) {lli v = pow(a, b, mod); return v;}

lli inv(lli a) {
	a %= mod;
	if (a < 0) a += mod;
	lli b = mod, u = 0, v = 1;
	while (a) {
		lli t = b / a;
		b -= t * a; swap(a, b);
		u -= t * v; swap(u, v);
	}
	// assert(b == 1);
	if (u < 0) u += mod;
	return u;
}

int main() {
	fio;
	auto lambda = [](auto x, auto y) {return x + y;};

}