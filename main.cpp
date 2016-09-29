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

void test1_cache(int n, size_t size) {
    lru_cache cache(size);
    for (int i = 0; i < n; i++) {
        cache.insert(make_pair(i, 10 * i));
    }
    lru_cache::iterator it = cache.begin();
    while (it != cache.end()) {
        cout << **it << endl;
        it++;
    }
    cout << **it << endl;
    cout << "_________________________________" << endl;
}

void test2_cache(int n, int size) {
    lru_cache cache((size_t) size);
    for (int i = 0; i < n; i++) {
        cache.insert(make_pair(i, i));
    }
    for (int i = 0; i < n; i++) {
        lru_cache::iterator p = cache.find(i);
        if ((i >= n - size) && **p != i) cout << "WA" << endl;
        if ((i < n - size) && **p != **cache.end()) cout << "WA" << endl;
    }
    cout << "_________________________________" << endl;
}

int main() {
    test1_cache(10000, 10000 - 1);
    test2_cache(10000, 1000);
    return 0;
}