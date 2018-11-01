#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;

// int min(int a, int b) {
    // return a < b ? a : b;
// }

struct minimax_heap {

    int K[1 << 20];
    int size = 0;

    int parent(int v) {
        int r = v % 4;
        return (r == 3 or r == 0) ? v / 2 : v / 2 - 1;
    }

    int left_son(int v) {
        return v & 1 ? 2*v + 1 : 2*v;
    }

    int right_son(int v) {
        return v & 1 ? 2*v + 3 : 2*v + 2;
    }

    bool is_leaf(int v) {
        return left_son(v) > size;
    }

    int mirror_leaf(int v) {
        if(v & 1) {
            return v + 1 <= size ? v + 1 : parent(v + 1);
        } else {
            return v - 1;
        }
    }

    int bad_leaf_order(int u, int v) {
        if(v & 1) swap(u, v);
        return K[u] > K[v];
    }

    void push_up(int v) {
        int par = parent(v);
        if(!par) return;
        if( ( (v & 1) == 1 and K[v] < K[par]) or 
            ( (v & 1) == 0 and K[v] > K[par]) ) {
            swap(K[v], K[par]);
            push_up(par);
        }
    }

    int push_down(int v) {
        if(is_leaf(v)) return v;
        
        int lson = left_son(v);
        int rson = right_son(v);
        if(rson > size) rson = lson;

        if(v & 1) {
            int better_son = lson;
            if(K[rson] < K[lson]) better_son = rson;
            if(K[v] > K[better_son]) {
                swap(K[v], K[better_son]);
                return push_down(better_son);
            } else {
                return v;
            }
        } else {
            int better_son = lson;
            if(K[rson] > K[lson]) better_son = lson;
            if(K[v] < K[better_son]) {
                swap(K[v], K[better_son]);
                return push_down(better_son);
            } else {
                return v;
            }
        }
    }
    
    void push(int x) {
        int v = ++size;
        K[v] = x;
        if(size == 1) return;
        int leaf = mirror_leaf(v);
        if(bad_leaf_order(v, leaf)) {
            swap(K[v], K[leaf]);
            v = leaf;
        }
        push_up(v);
    }

    void pop(int v) {
        swap(K[size--], K[v]);
        if(size == 1) return;
        v = push_down(v);
        if(is_leaf(v)) {
            int leaf = mirror_leaf(v);
            if(bad_leaf_order(v, leaf)) {
                swap(K[v], K[leaf]);
                push_up(leaf);
            }
        }
    }

    void pop_min() {
        pop(1);
    }

    void pop_max() {
        pop(std::min(size, 2));
    }

    int min() {
        return K[1];
    }

    int max() {
        return K[std::min(size, 2)];
    }
};

int main() {
    minimax_heap minimax;

    minimax.push(5);
    minimax.push(1);
    minimax.push(3);
    minimax.push(7);
    minimax.push(4);
    minimax.push(2);
    minimax.push(6);

    printf("%d\n", minimax.min());
    printf("%d\n", minimax.max());

    minimax.pop_min();
    minimax.pop_max();

    printf("%d\n", minimax.min());
    printf("%d\n", minimax.max());

    minimax.pop_min();
    minimax.pop_max();

    printf("%d\n", minimax.min());
    printf("%d\n", minimax.max());

    minimax.pop_min();
    minimax.pop_max();

    printf("%d\n", minimax.min());
    printf("%d\n", minimax.max());
}