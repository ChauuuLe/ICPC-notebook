#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(time(NULL));
int ran(int l, int r) {
	return rng() % (r - l + 1) + l;
}
bool is_prime(int x) {
	for (int i = 2; i * i <= x; i++)
	if (x % i == 0) return 0;
	return 1;
}
const int maxLen = 2e5 + 69;
const int K = 317;
const int MS = 1;
int MODS[MS];
ll MM[MS];
using hsh = array<int, MS>;
hsh powK[maxLen];
hsh operator + (hsh h, int c) {
	for (int i = 0; i < MS; i++)
		h[i] = (1ll * h[i] * K + c) % MODS[i];
	return h;
}
void init_hsh() {
	const int MINN = 8e8, MAXX = 1e9;
	for (int i = 0; i < MS; i++) {
		MODS[i] = ran(MINN, MAXX);
		while (!is_prime(MODS[i])) MODS[i]++;
		MM[i] = 1ll * MODS[i] * MODS[i];
		powK[0][i] = 1;
	}
	for (int i = 1; i < maxLen; i++) powK[i] = powK[i - 1] + 0;
}
struct Hash {
	string s;
	vector<hsh> h;
	Hash(const string& s) {
		this->s = s;
		h.resize(s.size());
		for (int i = 1; i < s.size(); i++) h[i] = h[i - 1] + s[i];
	}
	Hash() {}
	hsh get(int l, int r) {
		hsh res;
		for (int i = 0; i < MS; i++)
		res[i] = (h[r][i] - 1ll * h[l - 1][i] * powK[r - l + 1][i] + MM[i]) % MODS[i];
		return res;
	}
	int lcp(int i, int j) {
		int l = 0, r = s.size() - max(i, j);
		while (l < r) {
			int mid = (r - l) / 2 + l + 1;
			if (get(i, i + mid - 1) == get(j, j + mid - 1)) l = mid;
			else r = mid - 1;
		}
		return l;
	}
	bool cmp(int i, int j) {
		int l = lcp(i, j);
		if (i + l - 1 == s.size() - 1) return 1;
		if (j + l - 1 == s.size() - 1) return 0;
		return s[i + l] < s[j + l];
	}
};

bool minimize(int& a, int b) {
	return a > b ? a = b, 1 : 0;
}

const int maxN = 2e5 + 69;
const int logN = 19;
struct vl {
	int x, y;
	bool operator < (const vl& oth) const {
		if (x != oth.x) return x < oth.x;
		return y < oth.y;
	}
};
int n;
string s;
Hash h;
int sa[maxN];
int lcp[maxN];
vl minn[maxN][logN];

set<int> se[maxN];

int x = 0, y = 1;
void Try(int a, int b) {
	// x / y vs a / b
	if (1ll * x * b < 1ll * a * y) x = a, y = b;
}
void build() {
	for (int i = 1; i < n; i++) minn[i][0] = {lcp[i], i};
	for (int j = 1; j < logN; j++)
	for (int i = 1; i + (1 << j) - 1 < n; i++)
		minn[i][j] = min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
}
vl get(int l, int r) {
	int j = 31 - __builtin_clz(r - l + 1);
	return min(minn[l][j], minn[r - (1 << j) + 1][j]);
}
int solve(int l, int r) {
	if (l == r) {
		se[l].insert(sa[l]);
		return l;
	}

	vl mid = get(l, r - 1);

	int left = solve(l, mid.y);
	int right = solve(mid.y + 1, r);

	if (se[left].size() > se[right].size()) swap(left, right);

	for (auto& u : se[left]) {
		auto it = se[right].lower_bound(u);
		if (it != se[right].end()) Try(mid.x, abs(u - *it));
		if (it != se[right].begin()) {
			it--;
			Try(mid.x, abs(u - *it));
		}
	}
	for (auto& u : se[left]) se[right].insert(u);

	return right;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init_hsh();
	cin >> s;
	n = s.size();
	s = ' ' + s;
	h = Hash(s);

	for (int i = 1; i <= n; i++) sa[i] = i;
	stable_sort(sa + 1, sa + 1 + n, [&] (int i, int j) {
		return h.cmp(i, j);
	});

	for (int i = 1; i < n; i++) lcp[i] = h.lcp(sa[i], sa[i + 1]);
	build();

	solve(1, n);

	int d = __gcd(x, y);
	x /= d;
	y /= d;
	x += y;
	cout << x << '/' << y;
}
