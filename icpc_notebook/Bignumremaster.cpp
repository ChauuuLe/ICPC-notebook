const int BASE = 1e7, LBASE = 7;
void fix(big& a) {
	a.push_back(0);
	for (int i = 0; i < a.size() - 1; i++) {
		a[i + 1] += a[i] / BASE;
		a[i] %= BASE;
		if (a[i] < 0) a[i] += BASE, a[i + 1]--;
	}
	while (a.size() >= 2 && a.back() == 0) a.pop_back();
}
big operator + (big a, const big& b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) a[i] += b[i];
	fix(a); return a;
}
big operator - (big a, const big& b) {
	for (int i = 0; i < b.size(); i++) a[i] -= b[i];
	fix(a); return a;
}
big operator * (const big& a, const big& b) {
	big c(a.size() + b.size());
	for (int i = 0; i < a.size(); i++)
	for (int j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
	fix(c); return c;
}
big operator / (const big& a, int x) {
	big res;
	int r = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		r = r * BASE + a[i];
		res.push_back(r / x);
		r %= x;
	}
	reverse(res.begin(), res.end());
	fix(res); return res;
}
int operator % (const big& a, int x) {
	int r = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		r = r * BASE + a[i];
		r %= x;
	}
	return r;
}
bool operator < (const big& a, const big& b) {
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = a.size() - 1; i >= 0; i--)
	if (a[i] != b[i]) return a[i] < b[i];
	return 0;
}
big stringToBig(const string& s) {
	big a(s.size() / LBASE + 1);
	for (int i = 0; i < s.size(); i++) {
		int x = (s.size() - i - 1) / LBASE;
		a[x] = a[x] * 10 + s[i] - '0';
	}
	fix(a); return a;
}
void Print(const big& a) {
	cout << a.back();
	for (int i = (int) a.size() - 2; i >= 0; i--)
		cout << setw(LBASE) << setfill('0') << a[i];
}
