// -- > Less

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

// order_of_key(k) : returns number of elements strictly less than k
// find_by_order(k) : returns kth smallest element from the set indexing from 0

// -- > Greater

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,greater<int>, rb_tree_tag,tree_order_statistics_node_update>

// order_of_key(k) : returns number of elements greater or equal to k
// find_by_order(k) : returns kth biggest element from the set indexing from 0
