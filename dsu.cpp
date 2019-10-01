#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define max(x,y,z) max(x,max(y,z))
#define min(x,y,z) min(x,min(y,z))
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define trace1(x)                cout<<#x<<": "<<x<<endl
#define trace2(x, y)             cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define trace3(x, y, z)          cout<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define trace4(a, b, c, d)       cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl
#define trace5(a, b, c, d, e)    cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<endl
#define trace6(a, b, c, d, e, f) cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<" | "<<#f<<": "<<f<<endl

typedef long long int lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<lli, lli> > vii;
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

vi arr, sizes;
void setUpDSU(int n) {
	arr.resize(n + 1, 0);
	sizes.resize(n + 1, 0);
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = i;
		sizes[i] = 1;
	}
}

int getParent(int x) {
	while (arr[x] != x) {
		arr[x] = arr[arr[x]];
		x = arr[x];
	}
	return x;
}

bool isConnected(int a, int b) {
	return getParent(a) == getParent(b);
}

void unite(int a, int b) {
	int rt_a = getParent(a);
	int rt_b = getParent(b);

	// size of root a is larger, so combine b into as
	if (sizes[rt_a] > sizes[rt_b]) {
		arr[rt_b] = arr[rt_a];
		sizes[rt_a] += sizes[rt_b];
	} else {
		arr[rt_a] = arr[rt_b];
		sizes[rt_b] += sizes[rt_a];
	}
	// trace3(a,b,ans);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	setUpDSU(n);
	while (k--) {
		int x, y;
		cin >> x >> y;

		if (isConnected(x, y))	continue;
		else {
			unite(x, y);
		}
	}
}