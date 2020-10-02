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

// SEGMENT TREE with RANGE UPDATES and SINGLE ELEMENT ACCESS
// WORKS only when order of modification of single element doesn't affect the result
class SegmentTree {
public:
	vlli segTree;
	int n;
	bool pushed;
	SegmentTree(vlli& arr) {
		segTree.resize(2 * N, 0);	n = arr.size();
		pushed = true;
		for (int i = 0; i < arr.size(); i++) 	segTree[i + n] = arr[i];
		build();
	}

	void build() {  // build the tree
		for (int i = n - 1; i > 0; --i) segTree[i] = segTree[i << 1] + segTree[i << 1 | 1];
	}

	// range update
	void modify(int l, int r, int value) {
		pushed = false;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) segTree[l++] += value;
			if (r & 1) segTree[--r] += value;
		}
	}

	void push() {
		pushed = true;
		for (int i = 1; i < n; ++i) {
			segTree[i << 1] += segTree[i];
			segTree[i << 1 | 1] += segTree[i];
			segTree[i] = 0;
		}
	}
	lli query(int p) {
		if (!pushed) {
			push();
		}
		lli res = 0;
		for (p += n; p > 0; p >>= 1) res += segTree[p];
		return res;
	}
};

int main() {
	// NO need to call push, already handled
	fio;
	int n;
	cin >> n;
	vlli arr(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	SegmentTree tree(arr);
	for (int i = 0; i < n; i++) {
		cout << tree.query(i);
	}
	return 0;
}
