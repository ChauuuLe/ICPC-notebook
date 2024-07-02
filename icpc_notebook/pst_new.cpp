struct vl {
	int x, y;
	bool operator < (const vl& oth) const {
		if (x != oth.x) return x > oth.x;
		return y < oth.y;
	}
};
int n, q;
int a[maxN];
vl b[maxN];
struct PersistentSegmentTree {
	static const int maxNodes = maxN * (logN + 4);
	int n, p = 0;
	vector<int> lc, rc;
	vector<int> st;
	vector<int> ver;
	PersistentSegmentTree(int n) : n(n), lc(maxNodes), rc(maxNodes), st(maxNodes) {}
	PersistentSegmentTree() {}
	int leaf(int v) {
		st[++p] = v;
		return p;
	}
	int parent(int l, int r) {
		p++;
		lc[p] = l;
		rc[p] = r;
		st[p] = st[l] + st[r];
		return p;
	}
	int build(int l, int r) {
		if (l == r) return leaf(0);
		int mid = (l + r) / 2;
		return parent(build(l, mid), build(mid + 1, r));
	}
	int update(int i, int v, int id, int l, int r) {
		if (i < l || r < i) return id;
		if (l == r) return leaf(st[id] + v);
		int mid = (l + r) / 2;
		return parent(update(i, v, lc[id], l, mid), update(i, v, rc[id], mid + 1, r));
	}
	int get(int L, int R, int id, int l, int r) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) return st[id];
		int mid = (l + r) / 2;
		int lv = get(L, R, lc[id], l, mid);
		int rv = get(L, R, rc[id], mid + 1, r);
		return lv + rv;
	}
	void build() {
		ver.push_back(build(1, n));
	}
	void update(int i, int v) {
		ver.push_back(update(i, v, ver.back(), 1, n));
	}
	int get(int L, int R, int k) {
		return get(L, R, ver[k], 1, n);
	}
} pst;
