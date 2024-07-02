struct Dinic {
	static const bool SCALING = false;
	int lim;
	struct edge {
		int v, rev;
		int cap, flow;
	};
	int S, T;
	vector<int> depth, ptr;
	vector<vector<edge>> adj;
	Dinic(int n) : S(n + 1), T(n + 2), depth(n + 3), ptr(n + 3), adj(n + 3) {}
	Dinic() {}
	void addEdge(int u, int v, int cap, int undirected = 0) {
		adj[u].push_back({v, (int)adj[v].size(), cap, 0});
		adj[v].push_back({u, (int)adj[u].size() - 1, cap * undirected, 0});
	}
	bool bfs() {
		fill(depth.begin(), depth.end(), 0);
		queue<int> q;
		depth[S] = 1;
		q.push(S);
		while (!q.empty() && !depth[T]) {
			int u = q.front(); q.pop();
			for (edge& e : adj[u]) {
				if (depth[e.v] || e.cap - e.flow < lim) continue;
				depth[e.v] = depth[u] + 1;
				q.push(e.v);
			}
		}
		return depth[T];
	}
	int dfs(int u, int flowIn) {
		if (u == T) return flowIn;
		int flowOut = 0;
		for (; ptr[u] < adj[u].size(); ptr[u]++) {
			edge& e = adj[u][ptr[u]];
			if (depth[u] + 1 != depth[e.v] || e.cap - e.flow == 0) continue;
			int q = dfs(e.v, min(flowIn, e.cap - e.flow));
			flowIn -= q;
			flowOut += q;
			e.flow += q;
			adj[e.v][e.rev].flow -= q;
			if (flowIn == 0) break;
		}
		return flowOut;
	}
	int calc() {
		int maxFlow = 0;
		for (lim = SCALING ? (1 << 12) : 1; lim; lim >>= 3) {
			while (bfs()) {
				fill(ptr.begin(), ptr.end(), 0);
				maxFlow += dfs(S, INF);
			}
		}
		return maxFlow;
	}
};
