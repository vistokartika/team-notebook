//Functions related to 2D geometry objects like circles, triangles and polygons
 //Requires: 1D.cpp
 const double EPS = 0.0000001;
const double pi = acos(-1.0);
const double INF = 100000000;
//circle operations
int insidecircle(point p, point c, double r){
	double dx = p.x-c.x;
	double dy = p.y-c.y;
	double dist = dx*dx + dy*dy;
	double rsq = r*r;
	if(dist < rsq) return 0; //inside
	else if(dist == rsq) return 1; //border
	else return 2; //outside
}
//triangle operations
double areatriangle(double ab, double bc, double ca){
	double s = (ab+bc+ca)/2; return sqrt(s*(s-ab)*(s-bc)*(s-ca));
}
double incircleradius(double ab, double bc, double ca){
	return areatriangle(ab, bc, ca) / (0.5 * (ab + bc + ca));
}
pair<point, double> incircle(point p1, point p2, point p3){
	pair<point, double> ans = {{INF, INF}, INF};
	double r = incircleradius(dist(p1, p2), dist(p2, p3), dist(p3, p1));
	if(fabs(r) < EPS) return ans;
	line l1, l2;
	double ratio = dist(p1, p2) / dist(p1, p3);
	point p = translate(p2, scale(createvec(p2, p3), ratio/(1+ratio)));
	l1 = createline(p1, p); ratio = dist(p2, p1) / dist(p2, p3);
	p = translate(p1, scale(createvec(p1, p3), ratio/(1+ratio)));
	l2 = createline(p2, p); point center = intersect(l1, l2);
	ans.first = center; ans.second = r; return ans;
}
double circumcircleradius(double ab, double bc, double ca){
	return (ab*bc*ca)/(4.0 * areatriangle(ab, bc, ca));
}
//polygon operations
double shoelace(vector<point> p){
	double area = 0.0; int sz = p.size(); int j = sz - 1;
	for(int i = 0; i < sz; i++){
		area += (p[j].x + p[i].x) * (p[j].y - p[i].y); j = i;
	}
	return abs(area/2.0);
}
bool isconvex(vector<point> p){
	int sz = p.size();
	if(sz <= 3) return false;
	bool firstturn = ccw(p[0], p[1], p[2]);
	for(int i = 1; i < sz-1; i++){
		if(i + 2 == sz)
			if(ccw(p[i], p[i+1], p[1]) != firstturn)
				return false;
		else
			if(ccw(p[i], p[i+1], p[i+2]) != firstturn)
				return false;		
	} return true;
}
bool inpolygon(point pt, vector<point> p){
	int sz = p.size(); if(sz <= 3) return false;
	double sum = 0;
	for(int i = 0; i < sz-1; i++){
		if(pt == p[i]) return true;
		if(ccw(pt, p[i], p[i+1])) sum += angle(p[i], pt, p[i+1]);
		else sum -= angle(p[i], pt, p[i+1]);
	}
	if(fabs(sum) < pi){ double area;
		for(int i = 0; i < sz-1; i++){
			area = areatriangle(dist(pt, p[i]), dist(p[i], p[i+1]), dist(p[i+1], pt));
			if(area == 0){
				if(pt.x >= p[i].x && pt.x <= p[i+1].x){
					if(pt.y >= p[i].y && pt.y <= p[i+1].y)
						return true;
					else if(pt.y >= p[i+1].y && pt.y <= p[i].y)
						return true;
				}
				else if(pt.x >= p[i+1].x && pt.x <= p[i].x){
					if(pt.y >= p[i].y && pt.y <= p[i+1].y) return true;
					else if(pt.y >= p[i+1].y && pt.y <= p[i].y) return true;	
				}
			}
		}
		return false;
	}
	return true;
}
void solve(vector<point> p, point pt, point c, double r, double ab, double bc, double ca){
	//check if a point is inside a circle
	bool circleinside = insidecircle(pt, c, r);
	//find the area of a triangle given three side lengths
	double trianglearea = areatriangle(ab, bc, ca);
	//find the incircle radius given three side lengths
	double radiusincircle = incircleradius(ab, bc, ca);
	//find the center and radius of incircle given three points
	pair<point, double> incirclepts = incircle(p[0], p[1], p[2]);
	//find the circumcircle radius given three side lengths
	double radiuscircumcircle = circumcircleradius(ab, bc, ca);
	//find the area of a polygon
	double areapolygon = shoelace(p);
	//check if a polygon is convex
	bool convex = isconvex(p);
	//check if a point is inside a polygon
	bool isinside = inpolygon(pt, p);
}
