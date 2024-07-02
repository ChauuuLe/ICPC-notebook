using namespace std;
 
#define pb push_back
#define mp make_pair
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
 
#define forn(i,n) for (int i=0; i<int(n); ++i)
#define fornd(i,n) for (int i=int(n)-1; i>=0; --i)
#define xrange(i,a,b) for (int i=int(a); i<int(b); ++i)
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
 
const int INF = (int) 1e9;
const long long INF64 = (long long) 1e18;
const long double eps = 1e-9;
const long double pi = 3.14159265358979323846;
 
const int mod = 7340033;
const ll root = 5;
const ll root_1 = 4404020;
const ll root_pw = 1<<20;
 
int rev_element[7340033];
 
ll getmod(ll a, ll tmod){
    return ((a%tmod)+tmod)%tmod;
}
 
void fft (vector<ll> & a, bool invert) {
    int n = (int) a.size();
 
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
 
    for (int len=2; len<=n; len<<=1) {
        ll wlen = invert ? root_1 : root;
        for (int i=len; i<root_pw; i<<=1)
            wlen = ll (wlen * 1ll * wlen % mod);
        for (int i=0; i<n; i+=len) {
            ll w = 1;
            for (int j=0; j<len/2; ++j) {
                ll u = a[i+j],  v = ll (a[i+j+len/2] * 1ll * w % mod);
                a[i+j] = getmod(u+v,mod);
                a[i+j+len/2] = getmod(u-v,mod);
                w = ll (w * 1ll * wlen % mod);
            }
        }
    }
    if (invert) {
        ll nrev = rev_element[n];
        for (int i=0; i<n; ++i)
            a[i] = int (a[i] * 1ll * nrev % mod);
    }
}
 
void precalc(){
    rev_element[1] = 1;
    for (int i=2; i<mod; i++)
        rev_element[i] = (mod - (mod/i) * rev_element[mod%i] % mod) % mod;
}
 
 
void multiply (const vector<ll> & a, const vector<ll> & b, vector<ll> & res) {
    vector <ll> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);
    fft (fa, false),  fft (fb, false);
    forn(i,n)
        fa[i] *= fb[i];
    fft (fa, true);
    res.resize (n);
    forn(i,n)
        res[i] = fa[i] % mod;
}
 
int MN = 29;
int MK = 1001;
vector <vector <ll> > dp(MN+2,vector <ll> (MK,0));
vector <ll> d;
 
void init(){
    int m;
    for (int i=0; i<=MN; i++){
        dp[i][0] = 1;
        multiply(dp[i],dp[i],d);
        d.resize(MK);
        multiply(d,d,dp[i+1]);
        dp[i+1].insert(dp[i+1].begin(),0);
        dp[i+1].resize(MK);
    }
}
