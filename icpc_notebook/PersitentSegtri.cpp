struct segment {
	int l, r, p;
	bool operator < (const segment& oth) const {
		return l < oth.l;
	}
};
int n, m, k;
vector<segment> vec;
struct PersistentSegmentTree {
	static const int maxNodes = maxN * 19;
	struct Node {
		int v, lc, rc;
	};
	int n;
	vector<Node> st;
	vector<int> ver;
	PersistentSegmentTree(int n) {
		this->n = n;
		st.reserve(maxNodes);
	}
	PersistentSegmentTree() {}
	int create(Node a) {
		st.push_back(a);
		return st.size() - 1;
	}
	int build(int l, int r) {
		if (l == r) {
			return create({INF});
		}
		int mid = (l + r) / 2;
		int id = create({INF, build(l, mid), build(mid + 1, r)});
		return id;
	}
	int update(int i, int v, int oldId, int l, int r) {
		if (l == r) {
			return create({min(v, st[oldId].v)});
		}
		int mid = (l + r) / 2;
		int id = create(st[oldId]);
		if (i <= mid)
			st[id].lc = update(i, v, st[oldId].lc, l, mid);
		else
			st[id].rc = update(i, v, st[oldId].rc, mid + 1, r);
		st[id].v = max(st[st[id].lc].v, st[st[id].rc].v);
		return id;
	}
	int get(int L, int R, int id, int l, int r) {
		if (R < l || r < L) return -1;
		if (L <= l && r <= R) return st[id].v;
		int mid = (l + r) / 2;
		int lv = get(L, R, st[id].lc, l, mid);
		int rv = get(L, R, st[id].rc, mid + 1, r);
		return max(lv, rv);
	}
	void build() {
		ver.push_back(0);
		build(1, n);
	}
	void update(int i, int v) {
		ver.push_back(update(i, v, ver.back(), 1, n));
	}
	int get(int L, int R, int k) {
		return get(L, R, ver[k], 1, n);
	}
} pst;
