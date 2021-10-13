//Finding the center and radius of the smallest circle that encloses a set of points
//Requires: 1D.cpp

const double EPS = 0.0000001;
point arr[1005];

pair<point, double> smallestcircle(int n){
	double X, Y, d, e, p;
	double xi, yi, xj, yj;
	X = Y = 0;
	for(int i = 0; i < n; i++){
		X += arr[i].x;
		Y += arr[i].y;
	}
	X /= n;
	Y /= n;
	p = 0.1;
	for(int i = 0; i < 30000; i++){
		int f = 0;
		xi = X-arr[0].x;
		yi = Y-arr[0].y;
		d = xi*xi + yi*yi;
		for(int j = 1; j < n; j++){
			xj = X-arr[j].x;
			yj = Y-arr[j].y;
			e = xj*xj + yj*yj;
			if(d < e){
				d = e;
				f = j;
			}
			X += (arr[f].x - X)*p;
			Y += (arr[f].y - Y)*p;
			p *= 0.999;
		}
	}
	return {{X, Y}, sqrt(d)};
}

void solve(int n){
	pair<point, double> ans = smallestcircle(n);
}
