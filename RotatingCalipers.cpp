#define P(p) const point &p
#define L(p0, p1) P(p0), P(p1)
#define C(p0, r) P(p0), double r
#define PP(pp) pair<point,point> &pp
typedef complex<double> point;
double dot(P(a), P(b)) { return real(conj(a) * b); }
double cross(P(a), P(b)) { return imag(conj(a) * b); }
point rotate(P(p), double radians = pi / 2,
             P(about) = point(0,0)) {
  return (p - about) * exp(point(0, radians)) + about; }
point reflect(P(p), L(about1, about2)) {
  point z = p - about1, w = about2 - about1;
  return conj(z / w) * w + about1; }
point proj(P(u), P(v)) { return dot(u, v) / dot(u, u) * u; }
point normalize(P(p), double k = 1.0) {
  return abs(p) == 0 ? point(0,0) : p / abs(p) * k; }
double ccw(P(a), P(b), P(c)) { return cross(b - a, c - b); }
bool collinear(P(a), P(b), P(c)) {
  return abs(ccw(a, b, c)) < EPS; }
double angle(P(a), P(b), P(c)) {
  return acos(dot(b - a, c - b) / abs(b - a) / abs(c - b)); }
double signed_angle(P(a), P(b), P(c)) {
  return asin(cross(b - a, c - b) / abs(b - a) / abs(c - b)); }
double angle(P(p)) { return atan2(imag(p), real(p)); }
point perp(P(p)) { return point(-imag(p), real(p)); }
double progress(P(p), L(a, b)) {
  if (abs(real(a) - real(b)) < EPS)
    return (imag(p) - imag(a)) / (imag(b) - imag(a));
  else return (real(p) - real(a)) / (real(b) - real(a)); }
// vim: cc=60 ts=2 sts=2 sw=2:

bool collinear(L(a, b), L(p, q)) {
  return abs(ccw(a, b, p)) < EPS && abs(ccw(a, b, q)) < EPS; }
bool parallel(L(a, b), L(p, q)) {
  return abs(cross(b - a, q - p)) < EPS; }
point closest_point(L(a, b), P(c), bool segment = false) {
  if (segment) {
    if (dot(b - a, c - b) > 0) return b;
    if (dot(a - b, c - a) > 0) return a;
  }
  double t = dot(c - a, b - a) / norm(b - a);
  return a + t * (b - a); }
double line_segment_distance(L(a,b), L(c,d)) {
  double x = INFINITY;
  if (abs(a - b) < EPS && abs(c - d) < EPS) x = abs(a - c);
  else if (abs(a - b) < EPS)
    x = abs(a - closest_point(c, d, a, true));
  else if (abs(c - d) < EPS)
    x = abs(c - closest_point(a, b, c, true));
  else if ((ccw(a, b, c) < 0) != (ccw(a, b, d) < 0) &&
       (ccw(c, d, a) < 0) != (ccw(c, d, b) < 0)) x = 0;
  else {
    x = min(x, abs(a - closest_point(c,d, a, true)));
    x = min(x, abs(b - closest_point(c,d, b, true)));
    x = min(x, abs(c - closest_point(a,b, c, true)));
    x = min(x, abs(d - closest_point(a,b, d, true)));
  }
  return x; }
bool intersect(L(a,b), L(p,q), point &res,
    bool lseg=false, bool rseg=false) {
  // NOTE: check parallel/collinear before
  point r = b - a, s = q - p;
  double c = cross(r, s),
         t = cross(p - a, s) / c, u = cross(p - a, r) / c;
  if (lseg && (t < 0-EPS || t > 1+EPS)) return false;
  if (rseg && (u < 0-EPS || u > 1+EPS)) return false;
  res = a + t * r; return true; }
// vim: cc=60 ts=2 sts=2 sw=2:

struct caliper {
  ii pt;
  double angle;
  caliper(ii _pt, double _angle) : pt(_pt), angle(_angle) { }
  double angle_to(ii pt2) {
    double x = angle - atan2(pt2.second - pt.second,
                             pt2.first - pt.first);
    while (x >= pi) x -= 2*pi;
    while (x <= -pi) x += 2*pi;
    return x; }
  void rotate(double by) {
    angle -= by;
    while (angle < 0) angle += 2*pi; }
  void move_to(ii pt2) { pt = pt2; }
  double dist(const caliper &other) {
    point a(pt.first,pt.second),
       b = a + exp(point(0,angle)) * 10.0,
       c(other.pt.first, other.pt.second);
    return abs(c - closest_point(a, b, c)); } };
// int h = convex_hull(pts);
// double mx = 0;
// if (h > 1) {
//     int a = 0,
//         b = 0;
//     rep(i,0,h) {
//         if (hull[i].first < hull[a].first)
//             a = i;
//         if (hull[i].first > hull[b].first)
//             b = i; }
//     caliper A(hull[a], pi/2), B(hull[b], 3*pi/2);
//     double done = 0;
//     while (true) {
//         mx = max(mx, abs(point(hull[a].first,hull[a].second)
//                     - point(hull[b].first,hull[b].second)));
//         double tha = A.angle_to(hull[(a+1)%h]),
//                 thb = B.angle_to(hull[(b+1)%h]);
//         if (tha <= thb) {
//             A.rotate(tha);
//             B.rotate(tha);
//             a = (a+1) % h;
//             A.move_to(hull[a]);
//         } else {
//             A.rotate(thb);
//             B.rotate(thb);
//             b = (b+1) % h;
//             B.move_to(hull[b]); }
//         done += min(tha, thb);
//         if (done > pi) {
//             break;
//         } } }
// vim: cc=60 ts=2 sts=2 sw=2:

//Below is Rotating Calipers Monochain's Algorithm - Wikipedia

///* All indices starts from 1.		  
//   dir(p,q,r) returns +ve number if p-q-r segments are clockwise,
//     -ve number if they are anti clockwise and 0 if collinear.
//     it can be defined as (q.y-p.y)(r.x-p.x) - (q.x-p.x)(r.y-p.y)
//*/     
//GetAllAntiPodalPairs(p[1..n])
//  //Obtain upper and lower parts of polygon
//  p’ = Sort p lexicographically (i.e. first by x then by y)
//  U, L = create new stacks of points
//  for k = 1 to n
//    while U.size > 1 and dir(U[U.size-1], U[U.size], p’[k]) <= 0
//      U.pop()
//    while L.size > 1 and dir(L(L.size-1], L[L.size], p’[k]) >= 0
//      L.pop()
//    U.append(p’[k])
//    L.append(p’[k])
//	
//  //Now we have U and L, apply rotating calipers
//  i = 1
//  j = L.size
//  while i < U.size or j > 1
//    yield U[i], L[j]
//	
//    //if i or j made it all the way through
//    //advance other size
//    if i = U.size
//      j = j - 1
//    else if j = 1
//      i = i + 1
//    else if (U[i+1].y - U[i].y) * (L[j].x - L[j-1].x)
//         > (U[i+1].x - U[i].x) * (L[j].y - L[j-1].y)
//      i = i + 1
//    else
//      j = j - 1
