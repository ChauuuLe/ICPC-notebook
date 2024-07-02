void add_poly (vector<ll> &a, vector<ll> &b) {
	for (int i = 0; i < (int) a.size(); i++) {
		a[i] = add (a[i], b[i]);
	}
}
void nhan (vector<ll> &a , ll chim) {
	vector<ll> tmp (k + 2, 0);
	for (int i=0;i<=k;i++) {
		tmp[i + 1] = a[i];
	}
	for (int i=0;i<=k + 1;i++) {
		tmp[i] = sub (tmp[i], 1ll * chim * a[i] % mod);
	}
	a = tmp;
}
void init () {
	dt.resize (k + 2);
	for (int i=1;i<=k + 1;i++) {
		p[i] = add (p[i - 1], cdt (i, k));
	}
	
	for (int i=0;i<=k + 1;i++) {
		vector<ll> tmp (k + 2, 0);
		tmp[0] = p[i];
		ll dak = 1;
		for (int j=0;j<=k + 1;j++) {
			if (j==i) continue;
			nhan (tmp, j);
			dak = 1ll *  dak * cdt ( sub (i, j), mod - 2) % mod;
		}
		for (ll &j : tmp) {
			j = 1ll * j * dak % mod;
			
		}
		add_poly (dt, tmp);
	}
	
}
