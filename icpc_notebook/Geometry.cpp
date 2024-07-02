const double EPS = 1e-7;
const double DFT = 6969.69;
bool equal(const double& a, const double& b) {
	return abs(a - b) < EPS;
}
struct point {
	int x, y;
	point operator + (const point& oth) const {
		return {x + oth.x, y + oth.y};
	}
	point operator - (const point& oth) const {
		return {x - oth.x, y - oth.y};
	}
	// Dot product
	int operator % (const point& oth) const {
		return x * oth.x + y * oth.y;
	}
	// Cross product
	int operator * (const point& oth) const {
		// Equal to 2 * area(aOb)
		// Postive if slope(a) < slope(b)
		// Negative if slope(a) > slope(b)
		// |x1 y1|
		// |x2 y2|
		return x * oth.y - oth.x * y;
	}
	int sqrlen() const {
		return x * x + y * y;
	}
	double len() const {
		return sqrt(sqrlen());
	}
};
using Polygon = vector<point>;
point vect(const point& a, const point& b) {
	return b - a;
}
double turn(const point& a, const point& b) {
	// angle aOb in radian
	return atan2(a * b, a % b);
}
bool collinear(const point& a, const point& b, const point& c) {
	return vect(a, b) * vect(b, c) == 0;
}
bool between(const point& a, const point& b, const point& c) {
	return collinear(a, b, c) && vect(a, b) % vect(b, c) >= 0;
}
// a -> b -> c = left turn?
bool leftTurn(const point& a, const point& b, const point& c) {
	return vect(a, b) * vect(b, c) > 0;
}
int polygonArea2(const vector<point>& p) {
	// Two times the area of a polygon with integral vertices
	// Positive if counterclockwise
	// Negative if clockwise
	int area2 = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		area2 += p[i] * p[j];
	}
	return area2;
}
bool inside_polygon(const point& a, const Polygon& p) {
	double angle = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if (between(p[i], a, p[j])) return 1;
		angle += turn(vect(a, p[i]), vect(a, p[j]));
	}
	return equal(abs(angle), 2 * PI);
}
struct segment {
	point a, b;
};
struct line {
	int a, b, c;
	line(const segment& l) {
		point n = vect(l.a, l.b);	
		n = {n.y, -n.x};
		a = n.x;
		b = n.y;
		c = -(a * l.a.x + b * l.a.y);
	}
};
point line_intersection(const line& l1, const line& l2) {
	// |a1 b1|
	// |a2 b2|
	double d = l1.a * l2.b - l2.a * l1.b;
	// |b1 c1|
	// |b2 c2|
	double dx = l1.b * l2.c - l2.b * l1.c;
	// |c1 a1|
	// |c2 a2|
	double dy = l1.c * l2.a - l2.c * l1.a;
	if (equal(d, 0)) {
		// Coincide
		if (equal(dx + dy, 0)) return {DFT, 1};
		// Nope
		return {DFT, 0};
	}
	return {dx / d, dy / d};
}
point intersection(const segment& l1, const segment& l2) {
	point p = line_intersection(line(l1), line(l2));
	if (p.x == DFT || !between(l1.a, p, l1.b) || !between(l2.a, p, l2.b))
		return {DFT};
	return p;
}
void convex_hull {
	cin >> n; point p0 = {INF, INF};
	for (int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
		if (p[i].y < p0.y || (p[i].y == p0.y && p[i].x < p0.x)) 
			id = i, p0 = p[i];
	}
	// Lowest + Leftmost point
	swap(p[id], p[0]);
	// Graham Scan
	sort(p + 1, p + n, [](const point& a, const point& b) {
		// Sort by slope
		// Same slope -> sort by len
		point u = a - p0;
		point v = b - p0;
		int t = u * v;
		return t > 0 || (t == 0 && u.sqrlen() < v.sqrlen());
	});
	// Find convex hull
	vector<point> q;
	for (int i = 0; i < n; i++) {
		// If right turn -> goodbye fellow	
		while (q.size() >= 2 && !leftTurn(q[q.size() - 2], q[q.size() - 1], p[i]))
			q.pop_back();
		q.push_back(p[i]);
	}
}
