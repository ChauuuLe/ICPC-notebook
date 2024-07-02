struct io {
    template<class T> inline static T next() {
        T n; std::cin >> n;
        return n;
    }
};
 
struct node {
    node() : max(INT_MIN), min(INT_MAX) {}
    int begin, end, mid, min, max; 
};
 
template<int size> struct segment_tree {
    node tree[size << 2];
 
    void init_tree(int index, int left, int right, int values[]) {
        node& now = tree[index];
        now.begin = left, now.end = right;
        now.mid = (now.begin + now.end) >> 1;
        if (now.begin != now.end) {
            init_tree(L(index), now.begin, now.mid, values);
            init_tree(R(index), now.mid + 1, now.end, values);
            now.max = max(now.max, max(tree[L(index)].max, tree[R(index)].max));
            now.min = min(now.min, min(tree[L(index)].min, tree[R(index)].min));
        } else
            now.min = now.max = values[now.begin];
    }
 
    state update(int index, int at, int value, int values[]) {
        node& now = tree[index];
        if (now.begin == at && now.end == at) {
            now.max = now.min = value;
            values[at] = value;
            return state(value, value);
        }
        if (now.begin > at || now.end < at)
            return state(now.max, now.min);
        state s1 = update(L(index), at, value, values);
        state s2 = update(R(index), at, value, values);
        now.max = max(s1.first, s2.first);
        now.min = min(s1.second, s2.second);
        return state(now.max, now.min);
    }
 
    state query(int index, int left, int right) {
        node& now = tree[index];
        if (now.begin >= left && now.end <= right)
            return state(now.max, now.min);
        if (now.begin > right || now.end < left)
            return state(INT_MIN, INT_MAX);
        state result(INT_MIN, INT_MAX);
        state s1 = query(L(index), left, right);
        state s2 = query(R(index), left, right);
        result.first = max(result.first, max(s1.first, s2.first));
        result.second = min(result.second, min(s1.second, s2.second));
        return result;
    }
};
 
segment_tree<MAXN> tree[MAXN];
int values[MAXN][MAXN];
