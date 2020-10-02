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
const int N = 1000010;
class Point {
public:
	lli x, y;
	Point() {x = 0ll;	y = 0ll;}
	Point(lli xx, lli yy) {x = xx;	y = yy;}

	// NEED const
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}

	lli operator * (const Point &b) const {
		return (x * b.y - y * b.x);
	}

	bool operator < (const Point &b) const {
		return x < b.x || (x == b.x && y < b.y);
	}
};

vector<Point> points;

lli dist(Point u, Point v) {
	return ((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}

lli cross(Point u, Point v, Point o) {
	return (u - o) * (v - o);
}

class convex_hull {
public:
	vector<Point> up;
	vector<Point> down;

	convex_hull() {    }

	convex_hull(vector<Point> all) {
		up = all;
		down = all;
		build();
	}

	void reserve(int i) {up.reserve(i); down.reserve(i);}
	void clear() {up.clear(); down.clear();}
	convex_hull operator + (const convex_hull &b) const {
		convex_hull c;
		c.up.resize(up.size() + b.up.size());
		merge(up.begin(), up.end(), b.up.begin(), b.up.end(), c.up.begin());
		c.down.resize(down.size() + b.down.size());
		merge(down.begin(), down.end(), b.down.begin(), b.down.end(), c.down.begin());
		c.build();
		return c;
	}

	void build() {
		{
			int n = up.size();
			int m = 0;
			for (int i = 0; i < n; ++i) {
				while (m > 1 && cross(up[i], up[m - 1], up[m - 2]) <= 0) {
					--m;
				}
				up[m++] = up[i];
			}
			up.resize(m);
		}
		{
			int n = down.size();
			int m = 0;
			for (int i = 0; i < n; ++i) {
				while (m > 1 && cross(down[i], down[m - 1], down[m - 2]) >= 0) {
					--m;
				}
				down[m++] = down[i];
			}
			down.resize(m);
		}
	}

	lli solve() {
		vector<Point> hull = up;
		for (int i = down.size() - 2; ~i; --i) {
			hull.push_back(down[i]);
		}
		reverse(hull.begin(), hull.end());
		int n = hull.size() - 1;
		lli ans = 0ll;
		for (int i = 0, j = 1; i < n; ++i) {
			while (dist(hull[i], hull[j + 1]) > dist(hull[i], hull[j])) {
				j = (j + 1) % n;
			}
			ans = max(ans, dist(hull[i], hull[j]));
			ans = max(ans, dist(hull[i + 1], hull[j + 1]));
		}
		return ans;
	}
};

// SEGMENT TREE with SINGLE ELEMENT MODIFICATION
// HAS A CONVEX HULL IN EVERY NODE
class SegmentTree {
public:
	vector<convex_hull> segTree;
	int n;

	SegmentTree(vector<Point>& arr) {
		segTree.resize(2 * N + 4, convex_hull());
		n = arr.size();
		for (int i = 0; i < arr.size(); i++)
			// leaves
			segTree[i + n] = convex_hull({arr[i]});
		build();
	}

	void build() {  // build the tree
		for (int i = n - 1; i > 0; --i)
			segTree[i] = segTree[i << 1] + segTree[i << 1 | 1];
	}

	convex_hull query(int l, int r) {  //interval [l, r)
		r++;					//to make interval [l,r]
		convex_hull res;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = res + segTree[l++];
			if (r & 1) res = res + segTree[--r];
		}
		return res;
	}
};


int main() {
	fio;
	int n;
	cin >> n;

	points.clear();	points.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}

	SegmentTree tree(points);
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;	r--;
		convex_hull x = tree.query(l, r);
		cout << x.solve() << "\n";
	}

}