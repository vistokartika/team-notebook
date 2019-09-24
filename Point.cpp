#include <iostream>
#include <math.h>
using namespace std;

const long double EPS = 0.0000000001;
const long double pi = acos(-1.0);

long double rad(long double deg){
	return (deg*180/pi);
}

long double deg(long double rad){
	return (rad*pi/180);
}

//integer points
struct point_i{
	int x, y;
	point_i(){
		x = y = 0;
	}
	point(int _x, int _y){
		x = _x;
		y = _y;
	}
	bool operator <(point_i other) const{
		if(x < other.x)
			return true;
		else if(x > other.x)
			return false;
		return y < other.y;
	}
	bool operator ==(point_i other) const{
		return (x == other.x && y == other.y);
	}
};

long double dist(point_i a, point_i b){
	return hypot(a.x-b.x, a.y-b.y);
}

//decimal points
struct point{
	long double x, y;
	point(){
		x = y = 0.0;
	}
	point(double _x, double _y){
		x = _x;
		y = _y;
	}
	bool operator <(point other) const{
		if(fabs(x-other.x) > EPS)
			return x < other.x;
		return y < other.y;
	}
	bool operator ==(point other) const{
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS);
	}
};

long double dist(point a, point b){
	return hypot(a.x-b.x, a.y-b.y);
}

point rotate(point a, long double theta){
	long double x = a.x * cos(rad(theta)) - a.y * sin(rad(theta));
	long double y = a.x * sin(rad(theta)) + a.y * cos(rad(theta));
	point ans;
	ans.x = x;
	ans.y = y;
	return ans;
}
