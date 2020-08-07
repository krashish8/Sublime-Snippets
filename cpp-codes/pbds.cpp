#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// ------------MOVE ABOVE TWO LINE TO TOP---------------
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; //zero based
// p.order_of_key(x); // number of elements strictly less than x (index of x)
// *p.find_by_order(x); // value at index x
// multiset: less -> less_equal --------BETTER, DON'T USE THIS
// If using pairs, use ->first and not .first
