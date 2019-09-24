#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Point{
	long double x, y;
	
	bool operator<(Point p){
		return x < p.x || (x == p.x && y < p.y);
	}
};

const long double EPS = 0.0000001;

long double cross_product(Point o, Point a, Point b){
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

vector<Point> convex_hull(vector<Point> A){
	int n = A.size(), k = 0;
	
	if(n <= 3){
		return A;
	}
	
	vector<Point> ans(2*n);
	
	sort(A.begin(), A.end());
	
	for(int i = 0; i < n; i++){
		while(k >= 2 && cross_product(ans[k-2], ans[k-1], A[i]) <= EPS){
			k--;
		}
		ans[k++] = A[i];
	}
	
	for(int i = n-1, t = k+1; i > 0; i--){
		while(k >= t && cross_product(ans[k-2], ans[k-1], A[i-1]) <= EPS){
			k--;
		}
		ans[k++] = A[i-1];
	}
	
	ans.resize(k-1);
	return ans;
}

int main(){
	
	int n, sz;
	long double x, y;
	vector<Point> points;
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> x >> y;
		points.push_back({x, y});
	}
	
	vector<Point> ans = convex_hull(points);
	sz = ans.size();
	
	for(int i = 0; i < sz; i++){
		cout << ans[i].x << ' ' << ans[i].y << endl;
	}
	
	return 0;
}
