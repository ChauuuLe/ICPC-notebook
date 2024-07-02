const int K = 269;
const int MOD1 = 1e9 + 7, MOD2 = 998244353;
int pw1[maxLen], pw2[maxLen];
void init_pw() {
	for (int i = 0; i < maxLen; i++) {
		pw1[i] = i ? pw1[i - 1] * K % MOD1 : 1;
		pw2[i] = i ? pw2[i - 1] * K % MOD2 : 1;
	}
}
struct Hash {
	int x, y;
	bool operator == (const Hash& oth) const {
		return x == oth.x && y == oth.y;
	}
};
struct Roll : vector<Hash> {
	string s;
	Roll(const string& s) : s(s) {
		assign(s.size(), {0, 0});
		for (int i = 1; i < s.size(); i++) {
			at(i).x = (at(i - 1).x * K + s[i]) % MOD1;
			at(i).y = (at(i - 1).y * K + s[i]) % MOD2;
		}
	}
	Roll() {}
	Hash get(int l, int r) {
		Hash res;
		res.x = (at(r).x - at(l - 1).x * pw1[r - l + 1] + MOD1 * MOD1) % MOD1;
		res.y = (at(r).y - at(l - 1).y * pw2[r - l + 1] + MOD2 * MOD2) % MOD2;
		return res;
	}
	int lcp(int i, int j) {
		int l = 0, r = size() - max(i, j);
		while (l < r) {
			int mid = (r - l) / 2 + l + 1;
			if (get(i, i + mid - 1) == get(j, j + mid - 1)) l = mid;
			else r = mid - 1;
		}
		return l;
	}
	bool cmp(int i, int j) {
		int l = lcp(i, j);
		if (i + l - 1 == size() - 1) return 1;
		if (j + l - 1 == size() - 1) return 0;
		return s[i + l] < s[j + l];
	}
};const int K = 269;
const int MOD1 = 1e9 + 7, MOD2 = 998244353;
int pw1[maxLen], pw2[maxLen];
void init_pw() {
	for (int i = 0; i < maxLen; i++) {
		pw1[i] = i ? pw1[i - 1] * K % MOD1 : 1;
		pw2[i] = i ? pw2[i - 1] * K % MOD2 : 1;
	}
}
struct Hash {
	int x, y;
	bool operator == (const Hash& oth) const {
		return x == oth.x && y == oth.y;
	}
};
struct Roll : vector<Hash> {
	string s;
	Roll(const string& s) : s(s) {
		assign(s.size(), {0, 0});
		for (int i = 1; i < s.size(); i++) {
			at(i).x = (at(i - 1).x * K + s[i]) % MOD1;
			at(i).y = (at(i - 1).y * K + s[i]) % MOD2;
		}
	}
	Roll() {}
	Hash get(int l, int r) {
		Hash res;
		res.x = (at(r).x - at(l - 1).x * pw1[r - l + 1] + MOD1 * MOD1) % MOD1;
		res.y = (at(r).y - at(l - 1).y * pw2[r - l + 1] + MOD2 * MOD2) % MOD2;
		return res;
	}
	int lcp(int i, int j) {
		int l = 0, r = size() - max(i, j);
		while (l < r) {
			int mid = (r - l) / 2 + l + 1;
			if (get(i, i + mid - 1) == get(j, j + mid - 1)) l = mid;
			else r = mid - 1;
		}
		return l;
	}
	bool cmp(int i, int j) {
		int l = lcp(i, j);
		if (i + l - 1 == size() - 1) return 1;
		if (j + l - 1 == size() - 1) return 0;
		return s[i + l] < s[j + l];
	}
};
