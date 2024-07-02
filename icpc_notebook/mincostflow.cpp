struct MinCostFlow {
	struct edge {
		int u, v, rev;
		int cap, flow;
		int cost;
	};
	int S, T;
	vector<int> dist, inq;
	vector<edge*> par;
	vector<vector<edge>> adj;
	MinCostFlow(int n) : S(n + 1), T(n + 2), dist(n + 3), inq(n + 3), par(n + 3), adj(n + 3) {}
	MinCostFlow() {}
	void addEdge(int u, int v, int cap, int cost) {
		adj[u].push_back({u, v, (int)adj[v].size(), cap, 0, cost});
		adj[v].push_back({v, u, (int)adj[u].size() - 1, 0, 0, -cost});
	}
	bool spfa() {
		fill(dist.begin(), dist.end(), INF);
		queue<int> q;
		dist[S] = 0;
		q.push(S);
		inq[S] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			inq[u] = 0;
			for (edge& e : adj[u]) {
				if (dist[u] + e.cost >= dist[e.v] || e.cap - e.flow == 0) continue;
				dist[e.v] = dist[u] + e.cost;
				par[e.v] = &e;
				if (!inq[e.v]) {
					q.push(e.v);
					inq[e.v] = 1;
				}
			}
		}
		return dist[T] != INF;
	}
	pair<int, int> calc() {
		int flow = 0, cost = 0;
		while (spfa()) {
			int f = INF;
			for (int u = T; u != S; u = par[u]->u)
				f = min(f, par[u]->cap - par[u]->flow);
			for (int u = T; u != S; u = par[u]->u) {
				par[u]->flow += f;
				adj[u][par[u]->rev].flow -= f;
			}
			flow += f;
			cost += f * dist[T];
		}
		return {flow, cost};
	}
};
