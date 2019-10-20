#include <bits/stdc++.h>

using namespace std;

// Line Sweep: Closest Pair of Points
#define px second
#define py first
typedef pair<long long, long long> pairll;
pairll pnts [MAX];
int compare(pairll a, pairll b)
{ 
        return a.px<b.px; 
}
double closest_pair(pairll pnts[],int n)
{
        sort(pnts,pnts+n,compare);
        double best=INF;
        set<pairll> box;
        box.insert(pnts[0]);
        int left = 0;
        for (int i=1;i<n;++i)
        {
            while (left<i && pnts[i].px-pnts[left].px > best)
                box.erase(pnts[left++]);
            for(typeof(box.begin()) it=box.lower_bound(make_pair(pnts[i].py-best, pnts[i].px-best));it!=box.end() && pnts[i].py+best>=it->py;it++)
                best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0)+pow(pnts[i].px - it->px, 2.0)));
            box.insert(pnts[i]);
        }
        return best;
}

// Line Sweep: Union of Rectangles (Area)
#define MAX 1000
struct event 
{
    int ind; // Index of rectangle in rects
    bool type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int ind, int type) : ind(ind), type(type) {};
};
struct point 
{
    int x, y;
};
point rects [MAX][12]; // Each rectangle consists of 2 points: [0] = lower-left ; [1] = upper-right
bool compare_x(event a, event b) { return rects[a.ind][a.type].x<rects[b.ind][b.type].x; }
bool compare_y(event a, event b) { return rects[a.ind][a.type].y<rects[b.ind][b.type].y; }
int union_area(event events_v[],event events_h[],int n,int e)
{
       //n is the number of rectangles, e=2*n , e is the number of points (each rectangle has two points as described in declaration of rects)
        bool in_set[MAX]={0};int area=0;
        sort(events_v, events_v+e, compare_x);  //Pre-sort of vertical edges
        sort(events_h, events_h+e, compare_y); // Pre-sort set of horizontal edges
        in_set[events_v[0].ind] = 1;
        for (int i=1;i<e;++i) 
        { // Vertical sweep line
                event c = events_v[i];
                int cnt = 0; // Counter to indicate how many rectangles are currently overlapping
                // Delta_x: Distance between current sweep line and previous sweep line
                int delta_x = rects[c.ind][c.type].x - rects[events_v[i-1].ind][events_v[i-1].type].x;
                int begin_y;
                if (delta_x==0){
                        in_set[c.ind] = (c.type==0);
                        continue;
                }
                for (int j=0;j<e;++j)
                        if (in_set[events_h[j].ind]==1)                 //Horizontal sweep line for active rectangle
                        {
                                if (events_h[j].type==0)                //If it is a bottom edge of rectangle
                                {
                                        if (cnt==0) begin_y = rects[events_h[j].ind][0].y; // Block starts
                                        ++cnt;                          //incrementing number of overlapping rectangles
                                }
                                else                                    //If it is a top edge
                                {
                                        --cnt;                          //the rectangle is no more overlapping, so remove it
                                        if (cnt==0)                     //Block ends
                                        {
                                                int delta_y = (rects[events_h[j].ind][13].y-begin_y);//length of the vertical sweep line cut by rectangles
                                                area+=delta_x * delta_y;
                                        }
                                }
                        }
                in_set[c.ind] = (c.type==0);//If it is a left edge, the rectangle is in the active set else not
        }
    return area;
}

// Line Sweep: Closest Pairs
// Sort by x then y
// BST / Set of Line Sweep, push pt[0]
// set h = the closest distance we got now
// for 1 to n - 1, erase pt that has distance x and y > than h, insert pts that has distance x and y <= than h and update h //ubound lowbound set
// return h

// Line Sweep: Intersection
// Sort by x then y
// BST / Set of Line Sweep
// if start point of edge, push to set, else, erase to set, also check wether the delta y is on the 0 to i - 1 of the set or not for point i ? ret++ //ubound lowbound set
// return ret

// Line Sweep: Union Area of Rectangles
// Sort by x then y
// BST / Set of Line Sweep
// if start point of edge, push to set, else, erase to set, each event do line sweep horizontally (rotate 90) to count the length of delta y
// return area
