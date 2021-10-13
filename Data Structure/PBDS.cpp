//Data structure for query operation in O(logn) time

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef
tree<
	int, //data type
	null_type,
	less<int>, //comparator
	rb_tree_tag,
	tree_order_statistics_node_update>
ordered_set;

void solve(vector<int> a, int k){
	//declare the pbds
	ordered_set t;
	
	//insert element to pbds
	for(int i = 0; i < a.size(); i++){
		t.insert(a[i]);
	}
	
	//kth element based on comparator, indexing starts from 0
	int kth = *t.find_by_order(k);
	
	//find the number of elements smaller than k in the set
	int cnt = t.order_of_key(k);
}
