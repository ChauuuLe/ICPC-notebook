struct Dinic_lowerbound {
	struct edge {
		int v, rev;
		int cap, flow;
		int dem;
	};
	int S, T;
	vector<int> depth, ptr;
	vector<vector<edge>> adj;
	Dinic_lowerbound(int n) : S(n + 1), T(n + 2), depth(n + 5), ptr(n + 5), adj(n + 5) {}
	Dinic_lowerbound() {}
	void addEdge(int u, int v, int cap, int dem) {
		adj[u].push_back({v, (int)adj[v].size(), cap, 0, dem});
		adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0, 0});
	}
	bool bfs() {
		fill(depth.begin(), depth.end(), 0);
		queue<int> q;
		depth[S] = 1;
		q.push(S);
		while (!q.empty() && !depth[T]) {
			int u = q.front(); q.pop();
			for (edge& e : adj[u]) {
				if (depth[e.v] || e.cap - e.flow < 1) continue;
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
			flowOut += q;
			flowIn -= q;
			e.flow += q;
			adj[e.v][e.rev].flow -= q;
			if (flowIn == 0) break;
		}
		return flowOut;
	}
	int calc() {
		int maxFlow = 0;
		while (bfs()) {
			fill(ptr.begin(), ptr.end(), 0);
			maxFlow += dfs(S, INF);
		}
		return maxFlow;
	}
	int calc_with_lowerbound() {
		int n = S - 1;
		int s = n + 3;
		int t = n + 4;
		int sumDem = 0;
		vector<int> in(n + 3), out(n + 3);
		for (int u = 1; u <= n + 2; u++)
		for (edge& e : adj[u]) {
			sumDem += e.dem;
			out[u] += e.dem;
			in[e.v] += e.dem;
			e.cap -= e.dem;
		}
		for (int u = 1; u <= n; u++) {
			addEdge(s, u, in[u], 0);
			addEdge(u, t, out[u], 0);
		}
		addEdge(T, S, INF, 0);

		swap(s, S); swap(t, T);
		if (calc() != sumDem) return -1;
		swap(s, S); swap(t, T);

		for (int u = 1; u <= n + 2; u++)
		for (edge& e : adj[u]) {
			e.cap += e.dem;
			e.flow += e.dem;
		}
		for (int u = 1; u <= n; u++) {
			adj[u].pop_back();
			adj[u].pop_back();
		}
		adj[S].pop_back(); adj[T].pop_back();

		return calc() + sumDem;
	}
};
