//Functions related to 1D geometry objects like points, lines, segments and vectors
const double EPS = 0.0000001;
const double pi = acos(-1.0);
const double INF = 100000000;
struct point{
	double x, y;
	point() {}
	point(double x, double y): x(x), y(y) {}
	bool operator < (point other) const{
		if(fabs(x-other.x) > EPS)
			return x < other.x;
		return y < other.y;
	}
	bool operator == (point other) const{
		return (fabs(x-other.x) < EPS) && (fabs(y-other.y) < EPS);
	}
};
struct line{
	double a, b, c;
	//ax + by + c = 0
	line() {}
	line(double a, double b, double c): a(a), b(b), c(c) {}
};

struct vec{
	double x, y;
	vec() {}
	vec(double x, double y): x(x), y(y) {} 
};
//point operations
double dist(point a, point b){ return hypot(a.x-b.x, a.y-b.y); }
double rad(double deg){ return (deg*pi)/180.0; }
double deg(double rad){ return (rad*180.0)/pi; }
point rotate(point p, double theta){
	double radian = rad(theta);
	return point(p.x*cos(radian)-p.y*sin(radian), p.x*sin(radian)+p.y*cos(radian));
}
//line operations
line createline(point p1, point p2){
	line l;
	if(fabs(p1.x-p2.x) < EPS) l = {1.0, 0.0, -p1.x};
	else l = {-(double)(p1.y-p2.y)/(p1.x-p2.x), 1.0, -(double)(l.a*p1.x)-p1.y};
	return l;
}
bool parallel(line l1, line l2){ return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
bool same(line l1, line l2){ return parallel(l1, l2) && (fabs(l1.c-l2.c) < EPS); }

point intersect(line l1, line l2){
	point p = {INF, INF};
	if(parallel(l1, l2)) return p;
	p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
	if(fabs(l1.b) < EPS)p.y = -(l1.a*p.x + l1.c);
	else p.y = -(l2.a*p.x + l2.c);
	return p;
}
//vector operations
vec createvec(point a, point b){return vec(b.x-a.x, b.y-a.y);}

vec scale(vec v, double s){return vec(v.x*s, v.y*s);}
point translate(point p, vec v){return point(p.x+v.x, p.y+v.y);}
double dot_product(vec a, vec b){return a.x*b.x + a.y*b.y;}
double cross_product(vec a, vec b){return a.x+b.y - a.y*b.x;}
double vec_sq(vec v){return v.x*v.x + v.y*v.y;}
double linedist(point p, point a, point b){
	vec ap = createvec(a, p);vec ab = createvec(a, b);
	double u = dot_product(ap, ab) / vec_sq(ab);
	point c = translate(a, scale(ab, u));return dist(p, c);
}
double segmentdist(point p, point a, point b){
	vec ap = createvec(a, p); vec ab = createvec(a, b);
	double u = dot_product(ap, ab) / vec_sq(ab);
	if(u < 0.0) return dist(p, a);
	if(u > 1.0) return dist(p, b);
	return linedist(p, a, b);
}
double angle(point a, point o, point b){
	vec oa = createvec(o, a); vec ob = createvec(o, b);
	return acos(dot_product(oa, ob) / sqrt(vec_sq(oa) * vec_sq(ob)));
}
bool ccw(point p, point q, point r){
	vec pq = createvec(p, q); vec pr = createvec(p, r);
	return cross_product(pq, pr) > -EPS;
}
bool collinear(point p, point q, point r){
	vec pq = createvec(p, q);
	vec pr = createvec(p, r);
	return fabs(cross_product(pq, pr)) < EPS;
}
bool segintersect(point a, point b, point c, point d){
	bool one, two;
	one = (ccw(a, b, c) * ccw(a, b, d)) < EPS;
	two = (ccw(c, d, a) * ccw(c, d, b)) < EPS;
	return one && two;
}
void solve(int x1, int y1, int x2, int y2, double theta, double x){
	point p(x1, y1);point r(x2, y2);point q(x1, y2);point s(x2, y1);
	//euclidean distance between two points
	double distance = dist(p, r);
	//convert degree to radian and vice versa
	double radian = rad(theta);
	double degree = deg(theta);
	//rotate a point with center at (0, 0)
	point rotated = rotate(p, theta);
	//create a line from two points
	line l1 = createline(p, r);
	line l2 = createline(q, s);
	//find point of intersection of two lines
	point intersection = intersect(l1, l2);
	//check if two lines are parallel
	bool isparallel = parallel(l1, l2);
	//check if two lines are the same
	bool issame = same(l1, l2);
	//create a vector(segment) from two points
	vec a = createvec(p, r);
	vec b = createvec(q, s);
	//scale a vector by a factor of x
	vec scaled = scale(a, x);
	//translate a point by a vector
	point translated = translate(p, a);
	//find the dot product of two vectors
	double dot = dot_product(a, b);
	//find the cross product of two vectors
	double cross = cross_product(a, b);
	//find the square of the vector
	double squared = vec_sq(a);
	//find the distance from a point to a line
	double linedistance = linedist(p, q, r);
	//find the distance from a point to a segment
	double segmentdistance = segmentdistance(p, q, r);
	//find the angle aob of three points in radian
	double angl = angle(p, q, r);
	//counter-clockwise test
	bool isccw = ccw(p, q, r);
	//check if three points are collinear
	bool issameline = collinear(p, q, r);
	//check if two segments intersect
	bool isintersect = segintersect(p, q, r, s);
}
