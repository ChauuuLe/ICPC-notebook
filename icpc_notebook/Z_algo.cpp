void Z() {
	s = ' ' + s;
	for (int i = 2, l, r = -1; i <= n; i++) {
		if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
		while (i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) z[i]++;
		if (r < i + z[i] - 1) {
			l = i;
			r = i + z[i] - 1;
		}
	}
}
