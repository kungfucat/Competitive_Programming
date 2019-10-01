#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
typedef tree <lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update >ordered_set;

#define PI 3.141592653589793
#define mod (lli)(1000*1000*1000+7)

template<typename T> T gcd(T a, T b) { if (a == 0) return b; return gcd(b % a, a); }
template<typename T> T pow(T a, T b, lli m) {T ans = 1; while (b > 0) { if (b % 2 == 1) ans = ((ans % m) * (a % m)) % m; b /= 2; a = ((a % m) * (a % m)) % m; } return ans % m; }
const int N = 100010;

// SEGMENT TREE with SINGLE ELEMENT MODIFICATION
class SegmentTree {
public:
	vlli segTree;
	int n;

	SegmentTree(vlli& arr) {
		segTree.resize(2 * N, 0);	n = arr.size();
		for (int i = 0; i < arr.size(); i++) 	segTree[i + n] = arr[i];
		build();
	}

	void build() {  // build the tree
		for (int i = n - 1; i > 0; --i) segTree[i] = segTree[i << 1] + segTree[i << 1 | 1];
	}

	void modify(int p, lli value) {  // set value at position p
		for (segTree[p += n] = value; p > 1; p >>= 1) segTree[p >> 1] = segTree[p] + segTree[p ^ 1];
	}

	lli query(int l, int r) {  //interval [l, r)
		if (l > r)	return 0ll;
		lli res = 0ll;
		r++;					//to make interval [l,r]
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += segTree[l++];
			if (r & 1) res += segTree[--r];
		}
		return res;
	}
};

int main() {
	// build(), query(l,r) for [l,r], modify(pos, val)
	fio;
	int n;
	cin >> n;
	vlli arr(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	SegmentTree tree(arr);
	for (int i = 0; i < n; i++) {
		cout << tree.query(i, i);
	}
	return 0;
}
lli a1 = llabs(ele2 * k - ele1 * k);
lli a2 = llabs(ele2 * k - ele1);
lli a3 = llabs(ele2 - ele1 * k);
cur = min(cur, min(a1, min(a2, a3)));
if (cur == a1)	CASE = "41";
if (cur == a2)	CASE = "42";
if (cur == a3)	CASE = "43";