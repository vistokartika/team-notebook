//Finding the starting point and period of a cycle in a given function

int f(int x){
	//function as described by the question
}

pair<int, int> findcycle(int x0){
	int tortoise = f(x0);
	int hare = f(f(x0));
	while(tortoise != hare){
		tortoise = f(tortoise);
		hare = f(f(hare));
	}

	int start = 0;
	hare = x0;
	while(tortoise != hare){
		tortoise = f(tortoise);
		hare = f(hare);
		start++;
	}

	int period = 1;
	hare = f(tortoise);
	while(tortoise != hare){
		hare = f(hare);
		period++;
	}
	return make_pair(start, period);
}

void solve(int x0){
	pair<int, int> cycle = findcycle(x0);
}
