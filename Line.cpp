/*
Requires:
-Point.cpp
*/

#include <iostream>
#include <math.h>
using namespace std;

const long double EPS = 0.0000000001;

struct line{
	long double a, b, c;
	//ax + by = c
};

line create(point a, point b){
	line l;
	if(fabs(a.x - b.x) < EPS){
		l = {1.0, 0.0, -a.x};
	}
	else{
		l = {-(a.y-b.y)/(a.x-b.x), 1.0, -(l.a*a.x)-b.y};
	}
	return l;
}

bool parallel(line a, line b){
	return (fabs(a.a-b.a) < EPS && fabs(a.b-b.b) < EPS);
}

bool same(line a, line b){
	return (parallel(a, b) && fabs(a.c-b.c) < EPS);
}

bool intersect(line a, line b, point &ans){
	if(parallel(a, b)){
		return false;
	}
	ans.x = (b.b*a.c - a.b*b.c)/(b.a*a.b - a.a*b.b);
	if(fabs(a.b) > EPS){
		ans.y = -(a.a*ans.x + a.c);
	}
	else{
		ans.y = -(b.a*ans.x + b.c);
	}
	return true;
}
