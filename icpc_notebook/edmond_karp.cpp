void add_edge(int u, int v, int c) {
	a[u].push_back(v);
	a[v].push_back(u);
	cap[u][v] = c;
}
void inc_flow(int u, int v, int f) {
	flow[u][v] += f;
	flow[v][u] -= f;
	if (u == s) max_flow += f;
}
int residual(int u, int v) {
	return cap[u][v] - flow[u][v];
}
void bfs(int s, int t) {
	fill(par + 1, par + 1 + n, 0);
	queue<int> q;
	par[s] = s;
	q.push(s);
	while (!q.empty() && par[t] == 0) {
		int u = q.front(); q.pop();
		for (int& v : a[u]) {
			if (par[v] != 0 || residual(u, v) == 0) continue;
			par[v] = u;
			q.push(v);
		}
	}
}
bool find_augmenting_path() {
	bfs(s, t);
	return par[t] != 0;
}
void augment() {
	int minn = INF;
	for (int v = t; v != s; v = par[v])
		minimize(minn, residual(par[v], v));

	for (int v = t; v != s; v = par[v])
		inc_flow(par[v], v, minn);
}
signed main() {
	while (find_augmenting_path())
		augment();
	cout << max_flow;
}
