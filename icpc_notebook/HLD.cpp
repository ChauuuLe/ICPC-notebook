void pre_dfs(int u, int p) {
	par[u] = p;
	if (u != p) depth[u] = depth[p] + 1;
	sz[u] = 1;
	for (int& i : adj[u]) {
		int v = e[i].u ^ e[i].v ^ u;
		if (v == p) continue;
		pre_dfs(v, u);
		sz[u] += sz[v];
	}
}
void hld(int u, int p, int is_heavy, int lastEdge) {
	if (!is_heavy) head[u] = u;
	else head[u] = head[p];
	treePos[u] = ++ti;
	edgePos[lastEdge] = ti;
	int maxsz = 0, heavy = -1, heavyEdge;
	for (int& i : adj[u]) {
		int v = e[i].u ^ e[i].v ^ u;
		if (v == p || sz[v] <= maxsz) continue;
		maxsz = sz[v], heavy = v, heavyEdge = i;
	}
	if (heavy != -1) hld(heavy, u, 1, heavyEdge);
	for (int& i : adj[u]) {
		int v = e[i].u ^ e[i].v ^ u;
		if (v == p || v == heavy) continue;
		hld(v, u, 0, i);
	}
}
int query(int u, int v) {
	int res = 0;
	for (; head[u] != head[v]; v = par[head[v]]) {
		if (depth[head[u]] > depth[head[v]]) swap(u, v);
		res = max(res, st.get(treePos[head[v]], treePos[v]));
	}
	if (depth[u] > depth[v]) swap(u, v);
	res = max(res, st.get(treePos[u] + 1, treePos[v]));
	return res;
}
