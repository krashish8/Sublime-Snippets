#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; //zero based
// p.order_of_key(x); // number of elements strictly less than x
// *p.find_by_order(x); // value at index x
// multiset: less -> less_equal
