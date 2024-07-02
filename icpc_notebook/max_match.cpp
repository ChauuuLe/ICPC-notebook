bool dfs (int u) {
	if (vis[u]) return 0;
	vis[u] = 1;
	for (int v : adj[u]) {
		if (ass[v]==0 || dfs (ass[v])) {
			ass[v] = u;
			return 1;
		}
	}
	return 0;
}
signed main () {
	random_shuffle (p + 1,p + 1 + n);
	for (int i=1;i<=n;i++) {
		memset (vis , 0 , sizeof (vis));
		match += dfs (p[i]);
	}
	cout<<match<<'\n';
	for (int i=1;i<=m;i++) {
		cout<<ass[i]<<" ";
	}
}
