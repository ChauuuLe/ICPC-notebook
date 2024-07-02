void dfs(int u) {
	tin[u] = low[u] = ++cnt;
	st.push_back(u);
	for (int v : a[u]) {
		if (tin[v]) low[u] = min(low[u], tin[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	}
	if (tin[u] == low[u]) {
		scc++;
		while (1) {
			int v = st.back();
			st.pop_back();
			tin[v] = low[v] = INF;
			root[v] = scc;
			sz[scc]++;
			if (v == u) break;
		}
	}
}
