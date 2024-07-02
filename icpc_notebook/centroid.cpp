void pre_dfs(int u, int p) {
	sz[u] = 1;
	for (int& v : adj[u]) {
		if (v == p || ban[v]) continue;
		pre_dfs(v, u);
		sz[u] += sz[v];
	}
}
int centos(int u, int p, int root) {
	for (int& v : adj[u]) {
		if (v == p || ban[v]) continue;
		if (sz[v] * 2 > sz[root])
			return centos(v, u, root);
	}
	return u;
}
void decompose(int u) {
	pre_dfs(u, u);
	ban[u = centos(u, u, u)] = 1;
	for (int& v : adj[u])
	if (!ban[v]) decompose(v);
}
