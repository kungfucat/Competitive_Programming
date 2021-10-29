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
const int N = 200010;

class GH {
public:
	// linB=linkOfB
	lli vers, linB, sum;
};

class Node {
public:
	lli data;
	Node *left, *right;
	Node() {
		data = 0ll;	left = right = NULL;
	}
};

Node* version[N];
lli latestVersion, n, q;

// Basic Build function to build version 0 of segmentTree B
void build(Node* n, lli low, lli high, lli B[]) {
	if (low == high) {
		n->data = B[low];
		return;
	}

	lli mid = (low + high) / 2;
	n->left = new Node();
	n->right = new Node();

	build(n->left, low, mid, B);
	build(n->right, mid + 1, high, B);
	n->data = n->left->data + n->right->data;
}

// Upgrades node from prev to curr,
// when updating IDX with VAL
// At most logN new nodes
// root will always get one upgraded child, 
// saved that in versions array for storing different versions of B
// old versions needed when querying mapped component for array A to array B
void upgrade(Node* prev, Node* curr, lli low, lli high, lli idx, lli val) {
	if (idx > high || idx < low || low > high)
		return;

	if (low == high) {
		curr->data = val;
		return;
	}

	lli mid = (low + high) / 2;
	if (idx <= mid) {
		// Only update the left child with a new node
		curr->right = prev->right;
		curr->left = new Node();
		upgrade(prev->left, curr->left, low, mid, idx, val);
	}
	else {
		// Only update right child with a new node
		curr->left = prev->left;
		curr->right = new Node();
		upgrade(prev->right, curr->right, mid + 1, high, idx, val);
	}
	// recorrect parent
	curr->data = curr->left->data + curr->right->data;
}

// Simple sum query from l to r on a particular version of segmenttree of B
lli query(Node* n, lli low, lli high, lli l, lli r) {
	if (l > high || r < low || low > high)
		return 0;
	if (l <= low && high <= r) {
		return n->data;
	}

	lli mid = (low + high) / 2;
	lli p1 = query(n->left, low, mid, l, r);
	lli p2 = query(n->right, mid + 1, high, l, r);
	return p1 + p2;
}

// builds a segment tree, in the form
// of an array with version =-1, meaning no version mapping for each index as of the beginning
// vers gets the version number of the persistent segment trees of B, which queried to lazily propogate
void buildTree(GH* segTree, lli idx, lli arr[], lli si, lli ei) {
	if (si == ei) {
		segTree[idx].sum = arr[si];
		// No link to B, no version needed of B
		segTree[idx].linB = -1;
		segTree[idx].vers = -1;
		return;
	}

	lli mid = (si + ei) / 2;
	buildTree(segTree, 2 * idx + 1, arr, si, mid);
	buildTree(segTree, 2 * idx + 2, arr, mid + 1, ei);
	segTree[idx].sum = segTree[2 * idx + 1].sum + segTree[2 * idx + 2].sum;
	segTree[idx].linB = -1;
	segTree[idx].vers = -1;
}

// qs & qe : Array A's L and R
// idx= of segment tree of A
// si & ei=start and end index of node idx's segment in Segment tree
// A & B are indices of array B which we need to map L and R to
void update_query(GH* segTree, lli qs, lli qe, lli idx, lli si, lli ei, lli A, lli B) {

	lli mid = (si + ei) / 2;
	if (qs <= si && qe >= ei) {
		// complete segment inside the query ranges
		// will need to query this version when will lazily update the sum
		segTree[idx].vers = latestVersion;
		// X+i-L
		segTree[idx].linB = A + si - qs;

		if (segTree[idx].linB != -1) {
			lli sz = ei - si + 1;
			// query the vers version of B, which idx needed
			segTree[idx].sum = query(version[segTree[idx].vers], 0, n - 1, segTree[idx].linB, segTree[idx].linB + sz - 1);

			// tell the children, if exist to switch to the latest version
			if (2 * idx + 1 < 4 * n + 1) {
				segTree[2 * idx + 1].vers = segTree[idx].vers;
				segTree[2 * idx + 1].linB = segTree[idx].linB;
			}
			if (2 * idx + 2 < 4 * n + 1) {
				segTree[2 * idx + 2].vers = segTree[idx].vers;
				segTree[2 * idx + 2].linB = segTree[idx].linB + mid + 1 - si;
			}
			// Not dependent on any versions now
			segTree[idx].linB = -1;
			segTree[idx].vers = -1;
		}
		return;
	}

	// same as above
	if (segTree[idx].linB != -1) {
		lli sz = ei - si + 1;
		segTree[idx].sum = query(version[segTree[idx].vers], 0, n - 1, segTree[idx].linB, segTree[idx].linB + sz - 1);

		if (2 * idx + 1 < 4 * n + 1) {
			segTree[2 * idx + 1].vers = segTree[idx].vers;
			segTree[2 * idx + 1].linB = segTree[idx].linB;
		}
		if (2 * idx + 2 < 4 * n + 1) {
			segTree[2 * idx + 2].vers = segTree[idx].vers;
			segTree[2 * idx + 2].linB = segTree[idx].linB + mid + 1 - si;
		}
		segTree[idx].linB = -1;
		segTree[idx].vers = -1;
	}

	// Out of range
	if (qs > ei || qe < si)	return;
	update_query(segTree, qs, qe, 2 * idx + 1, si, mid, A, B);
	update_query(segTree, qs, qe, 2 * idx + 2, mid + 1, ei, A, B);
	segTree[idx].sum = segTree[2 * idx + 1].sum + segTree[2 * idx + 2].sum;
}

lli sum_query(GH* segTree, lli qs, lli qe, lli idx, lli si, lli ei) {
	lli mid = (si + ei) / 2;
	if (segTree[idx].linB != -1) {
		lli sz = ei - si + 1;
		// query the vers version of segment tree B for segment tree index idx
		segTree[idx].sum = query(version[segTree[idx].vers], 0, n - 1, segTree[idx].linB, segTree[idx].linB + sz - 1);


		if (2 * idx + 1 < 4 * n + 1) {
			segTree[2 * idx + 1].vers = segTree[idx].vers;
			segTree[2 * idx + 1].linB = segTree[idx].linB;
		}
		if (2 * idx + 2 < 4 * n + 1) {
			segTree[2 * idx + 2].vers = segTree[idx].vers;
			// start of index mapping of right child will always be different
			segTree[2 * idx + 2].linB = segTree[idx].linB + mid + 1 - si;
		}

		segTree[idx].linB = -1;
		segTree[idx].vers = -1;
	}
	if (qs > ei || qe < si)	return 0;
	if (qs <= si && qe >= ei)	return segTree[idx].sum;
	lli a = sum_query(segTree, qs, qe, 2 * idx + 1, si, mid);
	lli b = sum_query(segTree, qs, qe, 2 * idx + 2, mid + 1, ei);
	return a + b;
}

int main() {
	fio;
	cin >> n >> q;
	latestVersion = 0;
	lli A[n], B[n];
	for (int i = 0; i < n; i++)	{
		cin >> A[i];
	}
	for (int i = 0; i < n; i++)	{
		cin >> B[i];
	}

	GH* segTree = new GH[4 * n + 1];
	// build Segtree for array A
	buildTree(segTree, 0, A, 0, n - 1);
	Node* root = new Node();
	// A simple segment tree for B, at least for version 0
	build(root, 0, n - 1, B);
	// version 0
	version[0] = root;
	while (q--) {
		lli t;
		cin >> t;
		if (t == 1) {
			lli a, b;
			cin >> a >> b;
			a--;
			latestVersion++;
			Node* newRoot = new Node();
			upgrade(version[latestVersion - 1], newRoot, 0, n - 1, a, b);
			// Got a new version when did point update
			// will NEED old version for array A which mapped to some segment of B
			version[latestVersion] = newRoot;
			B[a] = b;
		}
		else if (t == 2) {
			lli l, r, X;
			cin >> l >> r >> X;
			l--;	r--;	X--;
			// Simple mapping to current version of B
			update_query(segTree, l, r, 0, 0, n - 1, X, X + r - l);
		} else {
			lli l, r;
			cin >> l >> r;
			l--;	r--;
			// Simple sum query and applying updates as needed
			cout << sum_query(segTree, l, r, 0, 0, n - 1) << "\n";
		}
	}
}