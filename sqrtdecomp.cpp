#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb emplace_back
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

// CALCULATES the number of elements <=k in a given range
// along with range increments/decrements of elements
class SQRTDECOMP {
public:
	vi arr;
	int BLOCK_SIZE, n;
	vvi blocks;
	vi lazy;

	SQRTDECOMP(vi& t, int bs) {
		arr = t;
		BLOCK_SIZE = bs;
		n = arr.size();
		blocks.clear();
		blocks.resize(n / BLOCK_SIZE + 2, vi());
		lazy.clear();
		lazy.resize(n / BLOCK_SIZE + 2, 0);
		setUp();
	}

	int size() {	return n;}

	int blockbeg(int id) {
		return id * BLOCK_SIZE;
	}
	int blockend(int id) {
		return min(n, (id + 1) * BLOCK_SIZE);
	}

	void setUp() {
		int blk = -1;
		for (int i = 0; i < n; i++) {
			if (i % BLOCK_SIZE == 0) {
				blk++;
			}
			blocks[blk].pb(arr[i]);
		}
		for (int i = 0; i < blocks.size(); i++) {
			sort(all(blocks[i]));
		}
	}

	void update(int from, int to, int delta) {
		if (from > to)	return;

		vi haha;
		for (int i = from; i <= to; ) {
			if (i % BLOCK_SIZE == 0 && i + BLOCK_SIZE - 1 <= to) {
				// if the whole block starting at i belongs to [l; r]
				vi& mst = blocks[i / BLOCK_SIZE];
				lazy[i / BLOCK_SIZE] += delta;
				i += BLOCK_SIZE;
			}
			else {
				if (i == from) {
					haha.pb(i / BLOCK_SIZE);
				}
				if (i == to && from / BLOCK_SIZE != to / BLOCK_SIZE) {
					haha.pb(i / BLOCK_SIZE);
				}
				arr[i] += delta;
				++i;
			}
		}

		if (haha.size() == 0)	return;
		for (int blkId : haha) {
			blocks[blkId].clear();
			int bg = blockbeg(blkId), en = blockend(blkId);
			for (int i = bg; i < en; i++) {
				blocks[blkId].pb(arr[i]);
			}
			sort(all(blocks[blkId]));
		}
	}

	int find(vi& a, lli k) {
		if (a.size() == 0)	return 0;
		if (a[0] > k)	return 0;
		if (a.back() <= k)	return a.size();
		int beg = 0, end = a.size() - 2;
		int val = 0;
		while (beg <= end) {
			int mid = (beg + end) / 2;
			lli value = a[mid];
			if (value <= k) {
				val = mid;
				beg = mid + 1;
			} else {
				end = mid - 1;
			}
		}
		return val + 1;
	}

	int query(int from, int to, lli k) {
		if (from > to)	return 0;
		int ans = 0;
		for (int i = from; i <= to; ) {
			if (i % BLOCK_SIZE == 0 && i + BLOCK_SIZE - 1 <= to) {
				// if the whole block starting at i belongs to [l; r]
				ans += find(blocks[i / BLOCK_SIZE], k - lazy[i/BLOCK_SIZE]);
				i += BLOCK_SIZE;
			}
			else {
				if (arr[i] <= k)	ans++;
				++i;
			}
		}
		return ans;
	}

	void clear() {
		blocks.clear();
		lazy.clear();
		arr.clear();
	}
};

int main(){
	int n;
	cin>>n;
	vi arr(n);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	SQRTDECOMP sqr(arr, 500);
}