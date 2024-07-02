void dfs(int u) { 
	 // all deg even, ans size = E + 1
    while (!a[u].empty()) {
        edge& p = e[a[u].back()];
        a[u].pop_back();
        if (p.used) continue;
        p.used = 1;
        int v = p.u ^ p.v ^ u;
        dfs(v);
        ans.push_back(v);
    }
}
