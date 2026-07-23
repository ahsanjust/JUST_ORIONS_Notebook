#include <ext/rope>
using namespace __gnu_cxx;
crope r;                // crope for char, rope<int> for ints
r.push_back('a');       // append
r.insert(0, "hello ");  // insert string
r.erase(0, 6);          // erase 6 chars from pos 0
r.substr(0, 5);         // extract substring [0,5)
char c = r[3];          // access O(log N)
cout << r << "\n";      // print whole rope
string s = "test";
crope r2(s.begin(), s.end());
