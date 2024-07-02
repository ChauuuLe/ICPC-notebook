struct PersistentSegmentTree {
	static const int maxNodes = maxN * (logN + 4) * 3;
	int n, p = 0;
	vector<int> lc, rc;
	vector<int> st;
	vector<int> lazy1, lazy2;
	vector<int> ver;
	PersistentSegmentTree(int n) : n(n), lc(maxNodes), rc(maxNodes), st(maxNodes), lazy1(maxNodes), lazy2(maxNodes) {}
	PersistentSegmentTree() {}
	int leaf(int v) {
		st[++p] = v;
		return p;
	}
	int parent(int l, int r) {
		p++;
		if (p >= maxNodes) {cout << "br0"; exit(0);}
		lc[p] = l;
		rc[p] = r;
		st[p] = st[l] + st[r];
		return p;
	}
	void change(int v1, int v2, int id, int l, int r) {
		st[id] += v1 * (r - l + 1);
		lazy1[id] += v1;
		st[id] += v2 * (l + r) * (r - l + 1) / 2;
		lazy2[id] += v2;
	}
	int lazykid(int v1, int v2, int id, int l, int r) {
		p++;
		if (p >= maxNodes) {cout << "br0"; exit(0);}
		lc[p] = lc[id];
		rc[p] = rc[id];
		st[p] = st[id];
		lazy1[p] = lazy1[id];
		lazy2[p] = lazy2[id];
		change(v1, v2, p, l, r);
		return p;
	}
	void down(int id, int l, int r) {
		if (lazy1[id] == 0 && lazy2[id] == 0) return;
		int mid = (l + r) / 2;
		lc[id] = lazykid(lazy1[id], lazy2[id], lc[id], l, mid);
		rc[id] = lazykid(lazy1[id], lazy2[id], rc[id], mid + 1, r);
		lazy1[id] = 0;
		lazy2[id] = 0;
	}
	int build(int l, int r) {
		if (l == r) return leaf(0);
		int mid = (l + r) / 2;
		return parent(build(l, mid), build(mid + 1, r));
	}
	int update(int L, int R, int v1, int v2, int id, int l, int r) {
		if (R < l || r < L) return id;
		if (L <= l && r <= R) return lazykid(v1, v2, id, l, r);
		down(id, l, r);
		int mid = (l + r) / 2;
		return parent(update(L, R, v1, v2, lc[id], l, mid), update(L, R, v1, v2, rc[id], mid + 1, r));
	}
	int get(int L, int R, int id, int l, int r) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) return st[id];
		down(id, l, r);
		int mid = (l + r) / 2;
		int lv = get(L, R, lc[id], l, mid);
		int rv = get(L, R, rc[id], mid + 1, r);
		return lv + rv;
	}
	void build() {
		ver.push_back(build(1, n));
	}
	void update(int L, int R, int v1, int v2) {
		ver.push_back(update(L, R, v1, v2, ver.back(), 1, n));
	}
	int get(int L, int R, int k) {
		return get(L, R, ver[k], 1, n);
	}
} pst;
