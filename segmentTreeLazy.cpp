#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
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

vi segTree;
vi lazy;
vi arr;

void build(int stIdx, int lo, int hi) {
	if (lo == hi) {
		segTree[stIdx] = arr[lo];
		return;
	}

	int left = 2 * stIdx, right = left + 1, mid = (lo + hi) / 2;
	build(left, lo, mid);
	build(right, mid + 1, hi);

	int m = min(segTree[left], segTree[right]);
	segTree[stIdx] = m;
}

void update(int node, int beg, int end, int l, int r, int delta) {
	if (lazy[node] != 0) {
		segTree[node] = segTree[node] + lazy[node];
		if (beg != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}

	if (l > end || r < beg)	return;
	if (beg >= l && end <= r) {
		segTree[node] = segTree[node] + delta;
		if (beg != end) {
			lazy[node * 2] += delta;
			lazy[node * 2 + 1] += delta;
		}
		return;
	}
	int mid = (beg + end) / 2, left = node * 2, right = node * 2 + 1;
	update(left, beg, mid, l, r, delta);
	update(right, mid + 1, end, l, r, delta);
	int m = min(segTree[left], segTree[right]);
	segTree[node] = m;
}

int query(int node, int beg, int end, int l, int r) {
	if (l > end || r < beg)	return 1e9;
	if (lazy[node] != 0) {
		segTree[node] = segTree[node] + lazy[node];
		if (beg != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}

	if (beg >= l && end <= r) {
		return segTree[node];
	}

	int mid = (beg + end) / 2;
	int query1 = query(node * 2, beg, mid, l, r);
	int query2 = query(node * 2 + 1, mid + 1, end, l, r);
	return min(query2, query1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// update(1,0,n-1,fromRange, toRange, delta);
	// query(1,0,n-1,fromRange,toRange);
}