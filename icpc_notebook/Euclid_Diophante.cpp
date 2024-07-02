struct vl{
	long x,y;
};
long t;
long a,b,c,d;
long gcd(long a,long b){
	return b?gcd(b,a%b):a;
}
vl extended_euclid(long a,long b){
	long m=a,xm=1;
	long n=b,xn=0;
	while(n){
		long q=m/n;
		long r=m-q*n,xr=xm-q*xn;
		m=n,xm=xn;
		n=r,xn=xr;
	}
	// if m < 0 ?? (d = -1)
	return {xm,(m-a*xm)/b};
}
