#include <bits/stdc++.h>
#include "lru_cache.h"

using namespace std;

void test1_cache(int n, size_t size) {
    lru_cache cache(size);
    for (int i = 0; i < n; i++) {
        cache.insert(make_pair(i, i));
    }
    lru_cache::iterator it = cache.begin();
    while (it != cache.end()) {
        //cout << **it << endl;
        it++;
    }
    //cout << **it << endl;
    //cout << "_________________________________" << endl;
}

void test2_cache(int n, int size) {
    lru_cache cache((size_t) size);
    for (int i = 0; i < n; i++) {
        cache.insert(make_pair(i, i));
    }
    for (int i = 0; i < n; i++) {
        lru_cache::iterator p = cache.find(i);
        if ((i >= n - size) && (*p).second != i) cout << "WA" << endl;
        if ((i < n - size) && (*p) != *cache.end()) cout << "WA" << endl;
    }
    //cout << "_________________________________" << endl;
}

vector<pair<int, int>> save_test;

void print_test() {
    for (auto j: save_test) {
        printf("%d %d\n", j.first, j.second);
    }
    printf("___________________________\n");
}

bool _test3_cache(int n) {
    lru_cache cache((size_t) n + 1);
    map<int, int> right;
    save_test.clear();
    srand((unsigned)time(0));
    for (int i = 0; i < n; i++) {
        int key = rand() % (n + 2);
        cache.insert(make_pair(key, key));
        right[key] = key;
        save_test.push_back(make_pair(key, key));
    }
    lru_cache::iterator it = cache.begin();
    auto it_right = right.begin();
    bool ok = true;
    while (it != cache.end()) {
        if ((*it).second != (*it_right).second) {
            ok = false;
        }
        it++;
        it_right++;
    }
    if ((*it).second != (*it_right).second) {
        ok = false;
    }
    return ok;
}

void test3_cache(int n, int s) {
    for (int i = 0; i < n; i++) {
        if (!_test3_cache(s)) {
            printf("WA\n");
            print_test();
        }
    }
}

void test4_cache() {
    lru_cache cache(10);
    vector<pair<int, int>> k = {{6, 6}, {4, 4}, {8, 8}, {3, 3}, {5, 5}, {9, 9}, {1, 1}, {2, 2}};
    for (auto i: k) {
        cache.insert(i);
    }
    cache.erase(cache.find(6));
    //cache.erase(cache.find(9));
}

//void debug(int n) {
//    lru_cache cache((size_t) n + 2);
//    for (int i = 0; i < n; i++) {
//        int x = 0, y = 0;
//        scanf("%d %d", &x, &y);
//        cache.insert(make_pair(x, y));
//    }
//}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    test1_cache(10000, 20);
    test2_cache(10000, 100);
    test3_cache(1000, 100);
    test4_cache();
    return 0;
}