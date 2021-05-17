//#include<iostream>
//#include <vector>
//#include <set>
//
//using namespace std;
//class Solution {
//public:
//    int flipgame(vector<int>& fronts, vector<int>& backs) {
//        std::set <int> s;
//        int n = fronts.size();
//        int ret = INT_MAX;
//        for (int i = 0; i < n; i++) {
//            if (fronts[i] == backs[i])s.insert(fronts[i]);
//        }
//        for (int i = 0; i < n; i++) {
//            if (s.count(fronts[i]) == 0) ret = min(ret, fronts[i]);
//        }
//        for (int i = 0; i < n; i++) {
//            if (s.count(backs[i]) == 0) ret = min(ret, backs[i]);
//        }
//        return ret == INT_MAX ? 0 : ret;
//    }
//};
//
//int main() {
//    vector<int> v1 = { 1,2,4,4,7 };
//    vector<int> v2 = { 1,3,4,1,3 };
//    Solution ob;
//    cout << (ob.flipgame(v1, v2));
//
//    return 0;
//}