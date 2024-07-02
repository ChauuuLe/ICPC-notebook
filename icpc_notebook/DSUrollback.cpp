int par[maxN];
int up[maxN];
int dist[maxN];
int cnt;
vector<pair<int*, int>> changes;
void rickroll(int id) {
	while (id < changes.size()) {
		*changes.back().first = changes.back().second;
		changes.pop_back();
	}
}
int Find(int u) {
	int res = par[u] >= 0 ? Find(par[u]) : u;
	if (res == u) up[u] = dist[u] = 0;
	else dist[u] = up[u] ^ dist[par[u]];
	return res;
}
void Unite(int u, int v) {
	int x = Find(u), y = Find(v);
	if (x == y) {
		if (dist[u] == dist[v]) {
			changes.push_back({&cnt, cnt});
			cnt++;
		}
		return;
	}
	if (par[x] > par[y]) swap(x, y);
	changes.push_back({&par[x], par[x]});
	changes.push_back({&par[y], par[y]});
	par[x] += par[y];
	par[y] = x;
	up[y] = dist[u] ^ dist[v] ^ 1;
}
