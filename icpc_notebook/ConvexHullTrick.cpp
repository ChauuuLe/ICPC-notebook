struct Line {
	mutable int k, m, p;
	bool operator < (const Line& oth) const {
		if (oth.k == INF && oth.m == INF) return p < oth.p;
		return k < oth.k;
	}
};

struct ConvexHull : multiset<Line> {
	int divi(int x, int y) {
		return x / y - ((x ^ y) < 0 && x % y);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = divi(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(int k, int m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	int query(int x) {
		assert(!empty());
		auto l = *lower_bound({INF, INF, x});
		return l.k * x + l.m;
	}
};
