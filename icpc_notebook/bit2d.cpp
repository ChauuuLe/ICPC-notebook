int BIT[N][M];
void add(int u, int v, int x){
    for(int i = u; i <= n; i += i&(-i)){
        for(int j = v; j <= m; j += j&(-j))BIT[i][j]+=x;
    }
}

int query(int u, int v){
    int sum = 0;
    for(int i = u; i > 0; i -= i&(-i)){
        for(int j = v; j > 0; j -= j&(-j))sum += BIT[i][j];
    }
    return sum;
}
void rectAdd(int a, int b, int u, int v, int x){
    add(a, b, x);
    add(u+1, v+1, x);
    add(u+1, b, -x);
    add(a, v+1, -x);
}
int BIT[4][N][M]; // {D[i][j]; i*D[i][j]; j*D[i][j]; i*j*D[i][j]}

void add(int u, int v, int x){
    for(int i = u; i <= n; i += i&(-i)){
        for(int j = v; j <= m; j += j&(-j)){
            BIT[0][i][j] += x;
            BIT[1][i][j] += u * x;
            BIT[2][i][j] += v * x;
            BIT[3][i][j] += u * v * x;
        }
    }
}

void rectAdd(int a, int b, int u, int v, int x){
    add(a, b, x);
    add(a, v + 1, -x);
    add(u + 1, b, -x);
    add(u + 1, v + 1, x);
}
// ben bit 2d
vector<int> pos[N];
vector<int> BIT[N];

void fakeAdd(int u, int v, int x){
    for(u; u <= n; u += u&(-u)){
        pos[u].push_back(v);
    }
}

void fakeQuery(int u, int v){
    for(u; u <= n; u += u&(-u)){
        pos[u].push_back(v);
    }
}
void compress(){
    for(int i = 1; i <= n; i++){
        pos[i].push_back(0);
        sort(pos[i].begin(), pos[i].end());
        pos[i].erase(unique(pos[i].begin(), pos[i].end()), pos[i].end());
        BIT[i].assign(pos[i].size(), 0);
    }
}
void add(int u, int v, int x){
    for(int i = u; i <= n; i += i&(-i)){
        for(int j = lower_bound(pos[i].begin(), pos[i].end(), v) - pos[i].begin(); j < BIT[i].size(); j += j&(-j)){
            BIT[i][j] += x;
        }
    }
}

void query(int u, int v){
    int sum = 0;
    for(int i = u; i > 0; i -= i&(-i)){
        for(int j = lower_bound(pos[i].begin(), pos[i].end(), v) - pos[i].begin(); j > 0; j -= j&(-j)){
            sum += BIT[i][j];
        }
    }
    return sum;
}
