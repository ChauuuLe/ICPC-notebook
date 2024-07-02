void dfs(int u, int p) {
	tin[u] = low[u] = ++now;
	if (u != p) parts[u]++;
	for (int v : a[u]) {
		if (v == p) continue;
		if (tin[v]) low[u] = min(low[u], tin[v]);
		else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > tin[u]) bridge++;
			if (low[v] >= tin[u]) parts[u]++; // part >= 2 -> articuno++
		}
	}
}
void dfs(int u,int p){
	check[u]=root.size();
	if(u!=p)h[u]=h[p]+1;
	sz[u]=1;
	for(int v:a[u]){
		if(v==p)continue;
		if(!check[v]){
			dfs(v,u);
			sz[u]+=sz[v];
			dp[u]+=dp[v];
		}
		else{
			if(h[u]<h[v])dp[u]--;
			else dp[u]++;
		}
	}
	if(u!=p&&dp[u]==0)bridge.push_back(u);
}
