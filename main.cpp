#include <bits/stdc++.h>
#include "lru_cache.h"

using namespace std;


//void test1() { //delete private before using
//    lru_cache cache(10);
//    map<int, int> ans;
//    set<int> keys;
//    const int N = 100;
//    int a = 0, b = 0;
//    srand(time(0));
//    for (int i = 0; i < N; i++) {
//        a = rand() % 1000000;
//        b = rand() % 1000000;
//        keys.insert(a);
//        cache.set.insert(make_pair(a, b));
//        ans.insert(make_pair(a, b));
//    }
//    for (int i: keys) {
//        int right, my;
//        if (ans.count(i)) {
//            right = ans[i];
//        } else {
//            right = (*ans.end()).second;
//        }
//        my = *(*cache.set.find(i)).mapped;
//        if (my != right) {
//            cout << "WA!!!\n";
//        }
//    }
//}
//
//void testtest() {
//    lru_cache cache(10);
//    cache.set.insert(make_pair(1, 1));
//    cache.set.insert(make_pair(5, 5));
//    cache.set.insert(make_pair(2, 2));
//    cache.set.insert(make_pair(4, 4));
//    cache.set.insert(make_pair(3, 3));
//    cout << *((*cache.set.find(0)).mapped) << endl;
//}

int main() {
    lru_cache cache(2);
    cache.insert(make_pair(10, 10));
    cache.insert(make_pair(20, 20));
    cache.insert(make_pair(0, 0));
    cache.insert(make_pair(100, 100));
    cout << **cache.end();
    return 0;
}