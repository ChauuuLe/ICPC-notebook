struct Trie {
	struct Node {
		int child[C];
		int par;
		int val;
		int link = 0;
		int nex[C];
		int ends = 0;
		int cnt = 0;
		Node(int par = -1, int val = -1) : par(par), val(val) {
			fill(child, child + C, 0);
			fill(nex, nex + C, 0);
		}
	};
	vector<Node> trie;
	Trie() {
		trie.reserve(maxLen);
		trie.push_back(Node());
	}
	void add(const string& s) {
		int v = 0;
		for (char c : s) {
			c -= 'A';
			if (!trie[v].child[c]) {
				trie[v].child[c] = trie.size();
				trie.push_back(Node(v, c));
			}
			v = trie[v].child[c];
		}
		trie[v].ends++;
	}
	void Ahchoo() {
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			int p = trie[u].link;
			trie[u].cnt = trie[p].cnt + trie[u].ends;
			for (int c = 0; c < C; c++) {
				if (trie[u].child[c]) {
					trie[trie[u].child[c]].link = trie[p].nex[c];
                    trie[u].nex[c] = trie[u].child[c];
					q.push(trie[u].child[c]);
				}
				else {
					trie[u].nex[c] = trie[p].nex[c];
				}
			}
		}
	}
} trie;
