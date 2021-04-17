#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
struct node {
    node *right;
    node *left;
    node *parent;
    int key;
    bool color;//1 red, 0 black

};


bool const BLACK = 0;
bool const RED = 1;


class myTree {
public:
    node *root;

    struct node *grandparent(struct node *n) {
        if ((n != nullptr) && (n->parent != nullptr))
            return n->parent->parent;
        else
            return nullptr;
    }

    struct node *uncle(struct node *n) {
        struct node *g = grandparent(n);
        if (g == nullptr)
            return nullptr;
        if (n->parent == g->left)
            return g->right;
        else
            return g->left;
    }

    struct node *sibling(struct node *n) {
        if (n == n->parent->left)
            return n->parent->right;
        else
            return n->parent->left;
    }

    void rotate_left(struct node *n) {
        struct node *pivot = n->right;
        if (root == n)
            root = pivot;
        pivot->parent = n->parent;
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }

        n->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = n;

        n->parent = pivot;
        pivot->left = n;
    }

    void rotate_right(struct node *n) {
        struct node *pivot = n->left;
        if (root == n)
            root = pivot;
        pivot->parent = n->parent;
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }

        n->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = n;

        n->parent = pivot;
        pivot->right = n;
    }

    void append(int element) {
        node *prev_node = nullptr;
        node *cur_node = root;
        if (root != nullptr)
            while (cur_node != nullptr) {
                node *left_node = cur_node->left;
                node *right_node = cur_node->right;
                prev_node = cur_node;
                if (element <= cur_node->key)
                    cur_node = left_node;
                else
                    cur_node = right_node;
            }

        cur_node = new node;
        cur_node->key = element;
        cur_node->right = nullptr;
        cur_node->left = nullptr;
        cur_node->parent = prev_node;
        cur_node->color = RED;
        if (prev_node != nullptr)
            if (cur_node->parent->key >= element) {
                cur_node->parent->left = cur_node;
            } else {
                cur_node->parent->right = cur_node;
            }
        insert_case1(cur_node);

    }

    void insert_case1(struct node *n) {
        if (n->parent == nullptr) {
            n->color = BLACK;
            root = n;
        } else
            insert_case2(n);
    }

    void insert_case2(struct node *n) {
        if (n->parent->color == BLACK)
            return;
        else
            insert_case3(n);
    }

    void insert_case3(struct node *n) {
        struct node *u = uncle(n), *g;
        if ((u != nullptr) && (u->color == RED)) {
            n->parent->color = BLACK;
            u->color = BLACK;
            g = grandparent(n);
            g->color = RED;
            insert_case1(g);
        } else {
            insert_case4(n);
        }
    }

    void insert_case4(struct node *n) {
        struct node *g = grandparent(n);
        if ((n == n->parent->right) && (n->parent == g->left)) {
            rotate_left(n->parent);
            n = n->left;
        } else if ((n == n->parent->left) && (n->parent == g->right)) {
            rotate_right(n->parent);
            n = n->right;
        }
        insert_case5(n);
    }

    void insert_case5(struct node *n) {
        struct node *g = grandparent(n);

        n->parent->color = BLACK;
        g->color = RED;
        if ((n == n->parent->left) && (n->parent == g->left)) {
            rotate_right(g);
        } else {
            rotate_left(g);
        }
    }

    node *find(int element) {
        node *cur_node = root;
        if (root == nullptr)
            return (nullptr);
        while (cur_node != nullptr) {
            node *left_node = cur_node->left;
            node *right_node = cur_node->right;
            if (cur_node != root && cur_node->parent == nullptr)
                free(cur_node);
            if (element < cur_node->key)
                cur_node = left_node;
            else if (element > cur_node->key)
                cur_node = right_node;
            else if (element == cur_node->key) {
                return (cur_node);
            }
        }
//        cout<<"no"<<endl;
        return (nullptr);
    }

    void myDelete(int element) {
        node *cur_node = find(element);
        node *left_node = cur_node;
        while (left_node->left != nullptr) {
            left_node = left_node->left;

        }

        node *del_node = left_node;
        if (left_node != cur_node)
            copy_nodes(cur_node, left_node);

        if (root == NULL) {
            free(del_node);
            return;
        } else if (del_node != nullptr)
            delete_one_child(del_node);
    }

    void copy_nodes(node *cur, node *left) {
        left->left = cur->left;
        left->right = cur->right;
        left->color = cur->color;

        if (cur->parent == nullptr) {
            root = left;
            left->parent = nullptr;
        } else {
            if (cur == cur->parent->left) {
                cur->parent->left = left;
            } else {
                cur->parent->right = left;
            }
            left->parent = cur->parent;
        }
    }

    void replace_node(node *n, node *child) {
        if (n->parent == nullptr) {
            root = child;
            if (child != nullptr)
                child->parent = nullptr;
        } else {
            if (n == n->parent->left) {
                n->parent->left = child;
            } else {
                n->parent->right = child;
            }
            if (child != nullptr)
                child->parent = n->parent;

        }
    }

    bool is_leaf(struct node *n) {
        return (n->left == nullptr && n->right == nullptr);
    }

    void delete_one_child(struct node *n) {

        struct node *child;
        if (n->left == nullptr)
            child = n->right;
        else if (n->right == nullptr) {
            child = n->left;
        }

        replace_node(n, child);
        if (n->color == BLACK) {
            if (child != nullptr && child->color == RED)
                child->color = BLACK;
            else if (child != nullptr)
                delete_case1(child);
        }

        free(n);
    }

    void delete_case1(struct node *n) {
        if (n->parent != nullptr)
            delete_case2(n);
    }

    void delete_case2(struct node *n) {
        struct node *s = sibling(n);

        if (s != nullptr && s->color == RED) {
            n->parent->color = RED;
            s->color = BLACK;
            if (n == n->parent->left)
                rotate_left(n->parent);
            else
                rotate_right(n->parent);
        }
        delete_case3(n);
    }

    void delete_case3(struct node *n) {
        struct node *s = sibling(n);

        if (s != nullptr && (n->parent->color == BLACK) &&
            (s->color == BLACK) &&
            (s->left->color == BLACK) &&
            (s->right->color == BLACK)) {
            s->color = RED;
            delete_case1(n->parent);
        } else
            delete_case4(n);
    }

    void delete_case4(struct node *n) {
        struct node *s = sibling(n);

        if ((n->parent->color == RED) &&
            (s->color == BLACK) &&
            (s->left->color == BLACK) &&
            (s->right->color == BLACK)) {
            s->color = RED;
            n->parent->color = BLACK;
        } else
            delete_case5(n);
    }

    void delete_case5(struct node *n) {
        struct node *s = sibling(n);

        if (s != nullptr && s->color == BLACK) {
            if ((n == n->parent->left) &&
                (s->right->color == BLACK) &&
                (s->left->color == RED)) {
                s->color = RED;
                s->left->color = BLACK;
                rotate_right(s);
            } else if ((n == n->parent->right) &&
                       (s->left->color == BLACK) &&
                       (s->right->color == RED)) {
                s->color = RED;
                s->right->color = BLACK;
                rotate_left(s);
            }
        }
        delete_case6(n);
    }

    void delete_case6(struct node *n) {
        struct node *s = sibling(n);
        if (s != nullptr) {
            s->color = n->parent->color;
            n->parent->color = BLACK;

            if (n == n->parent->left) {
                s->right->color = BLACK;
                rotate_left(n->parent);
            } else {
                s->left->color = BLACK;
                rotate_right(n->parent);
            }
        }
    }
};


myTree tree;
myTree test_tree;

void stress_text(int n = 10000) {
    for (int i = 0; i < n; i++) {
        int col = rand() % 20;
        vector<int> test_elements;
        for (int j = 0; j < col; j++) {
            int x = rand() % 10000;
            test_tree.append(x);
            test_elements.push_back(x);
        }
        for (int k = 0; k < col; k++) {
            cout << test_elements[k] << " ";
        }
        cout << endl;
        for (int j = 0; j < col; j++) {
//            cout<<j<<endl;
            test_tree.myDelete(test_elements[j]);
            if (test_tree.find(test_elements[j]) != nullptr) {
                cout << i << " error " << test_elements[j] << " after " << j << " in " << endl;
                for (int k = 0; k < col; k++) {
                    cout << test_elements[k] << " ";
                }
                cout << endl;
                for (int k = 0; k < col; k++) {
                    cout << k << "    ";
                }
                cout << endl;
            }
        }
        cout << i << endl;
    }
}

int main() {
    int element;

//    stress_text(100);
//    tree.append(2);
//    tree.append(4);
//    tree.append(5);
//    tree.append(7);
//    tree.append(2);
//    tree.append(8);
//    tree.myDelete(2);
//    tree.myDelete(4);
//    tree.myDelete(5);
//    cerr << tree.find(5) << endl;
//    cerr<<tree.find(4);//=sefm error

    //    tree.myDelete(2);
//    tree.myDelete(4);

    double dt = 100;
    double t_start;
    char command = getchar();
    while (command != EOF) {

        cin >> element;
        if (command == 'a') {
            tree.append(element);
            cerr << "append sucsessfull" << endl;
        }
        if (command == 'f') {
            node *ans = tree.find(element);
            if (ans != nullptr)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        }
        if (command == 'r') {
            tree.myDelete(element);
            cerr << "delete sucsessfull" << endl;
        }
        command = getchar();
        if (command == '\r')
            command = getchar();
        else if (command == '\n')
            command = getchar();
    }
    return 0;
}
