#include <cstdio>
#include <stack>
using namespace std;

const long long INF = 1LL << 60;

char max (char a, char b) {
    return a > b ? a : b;
}

char min (char a, char b) {
    return a < b ? a : b;
}

struct node {
    node *left;
    node *right;
    long long value;
    char balance;

    node(long long val) : left(NULL), right(NULL), value(val), balance(0) { }
};

class AVL {
    private:
        node *root;
        stack<node*> path;

        void get_path (long long val) {
            while (path.size()) {
                path.pop();
            }

            auto v = root;
            while (v) {
                path.push(v);
                if (val == v -> value) {
                    return;
                }
                else if (val > v -> value) {
                    v = v -> right;
                } else {
                    v = v -> left;
                }
            }
        }

        void rotate_left (node *v, node **parent_ptr) {
            auto u = v -> left;
            auto beta = u -> balance;
            auto gamma = max(0, beta) + 1 + v -> balance;

            v -> left = u -> right;
            u -> right = v;
            *parent_ptr = u;

            v -> balance = gamma - beta;
            u -> balance = max(beta, gamma) + 1;
        }

        void rotate_right (node *v, node **parent_ptr) {
            auto u = v -> right;
            auto beta = - u -> balance;
            auto alpha = max(0, beta) + 1 - v -> balance;

            v -> right = u -> left;
            u -> left = v;
            *parent_ptr = u;

            v -> balance = beta - alpha;
            u -> balance = -max(alpha, beta) - 1;
        }

    public:
        AVL() : root(NULL) { }

        void insert (long long val) {
            if (!root) {
                root = new node(val);
                return;
            }

            get_path(val);
            auto v = path.top();
            path.pop();
            if (val == v -> value) {
                return;
            }

            bool rotate = false;
            if(val > v -> value) {
                v -> right = new node(val);
                if (v -> balance++ > 1) {
                    rotate = true;
                }
            } else {
                v -> left = new node(val);
                if (v -> balance-- < -1) {
                    rotate = true;
                }
            }
            if (v -> balance == 0) {
                return;
            }

            if (!rotate) {
                while (path.size()) {
                    auto prev = v;
                    v = path.top();
                    path.pop();

                    if (v -> right and v -> right -> value == prev -> value) {
                        v -> balance++;
                    } else {
                        v -> balance--;
                    }

                    if (v -> balance == 0) {
                        return;
                    } else if (v -> balance < -1 or v -> balance > 1) {
                        rotate = true;
                        break;
                    }
                }
            }

            if (!rotate) {
                return;
            }

            node **parent_ptr = &root;
            if (path.size()) {
                auto parent = path.top();
                if (parent -> right and parent -> right -> value == v -> value) {
                    parent_ptr = &(parent -> right);
                } else {
                    parent_ptr = &(parent -> left);
                }
            }

            if (v -> balance > 1) {
                auto u = v -> right;
                if (u -> balance == -1) {
                    rotate_left(u, &(v -> right));
                }
                rotate_right(v, parent_ptr);
            } else {
                auto u = v -> left;
                if (u -> balance == 1) {
                    rotate_right(u, &(v -> left));
                }
                rotate_left(v, parent_ptr);
            }
        }

        bool remove (long long val) {
            get_path(val);
            if(path.empty() or path.top() -> value != val) {
                return false;
            }

            node **parent_ptr = &root;
            auto v = path.top();
            auto u = v -> left;

            bool leftson = true;
            if (u) {
                parent_ptr = &(v -> left);
                if (u -> right) {
                    leftson = false;
                }
                while (u -> right) {
                    path.push(u);
                    parent_ptr = &(u -> right);
                    u = u -> right;
                }
                swap(v -> value, u -> value);
                *parent_ptr = u -> left;
                delete(u);
            } else {
                path.pop();
                if (!path.empty()) {
                    auto parent = path.top();
                    if (parent -> left and parent -> left -> value == val) {
                        parent_ptr = &(parent -> left);
                    } else {
                        leftson = false;
                        parent_ptr = &(parent -> right);
                    }
                }
                *parent_ptr = v -> right;
                delete(v);
            }

            node* prev = NULL;
            while (path.size()) {
                v = path.top();
                path.pop();

                parent_ptr = &root;
                if (path.size()) {
                    auto parent = path.top();
                    if (parent -> right and parent -> right -> value == v -> value) {
                        parent_ptr = &(parent -> right);
                    } else {
                        parent_ptr = &(parent -> left);
                    }
                }

                if ((prev and v -> left and v -> left -> value == prev -> value) or (!prev and leftson)) {
                    v -> balance++;
                    if (v -> balance > 1) {
                        u = v -> right;
                        if (u -> balance >= 0) {
                            rotate_right(v, parent_ptr);
                            if (u -> balance == -1) {
                                break;
                            }
                        } else {
                            rotate_left(u, &(v -> right));
                            rotate_right(v, parent_ptr);
                        }
                    } else if (v -> balance == 1) {
                        break;
                    }
                } else {
                    v -> balance--;
                    if (v -> balance < -1) {
                        u = v -> left;
                        if (u -> balance <= 0) {
                            rotate_left(v, parent_ptr);
                            if (u -> balance == 1) {
                                break;
                            }
                        } else {
                            rotate_right(u, &(v -> left));
                            rotate_left(v, parent_ptr);
                        }
                    } else if (v -> balance == -1) {
                        break;
                    }
                }
                prev = *parent_ptr;
            }
            return true;
        }

        long long lower (long long val) {
            auto v = root;
            auto ans = -INF;
            while (v) {
                if (val == v -> value) {
                    return val;
                }
                if (val > v -> value) {
                    ans = max(ans, v -> value);
                    v = v -> right;
                } else {
                    v = v -> left;
                }
            }
            return ans;
        }

        long long upper (long long val) {
            auto v = root;
            auto ans = INF;
            while (v) {
                if (val == v -> value) {
                    return val;
                }
                if (val < v -> value) {
                    ans = min(ans, v -> value);
                    v = v -> left;
                } else {
                    v = v -> right;
                }
            }
            return ans;
        }

};

int main () {
    AVL bst;
    int n;
    scanf("%d", &n);
    while(n--) {
        char op;
        long long x;
        scanf("%*[ \n\t]%c %lld", &op, &x);
        if (op == 'I') {
            bst.insert(x);
        } else if (op == 'D') {
            if (bst.remove(x)) {
                puts("OK");
            } else {
                puts("BRAK");
            }
        } else if (op == 'U') {
            auto ans = bst.upper(x);
            if (ans < INF) {
                printf("%lld\n", ans);
            } else{
                puts("BRAK");
            }
        } else {
            auto ans = bst.lower(x);
            if (ans > -INF) {
                printf("%lld\n", ans);
            } else {
                puts("BRAK");
            }
        }
    }
}
