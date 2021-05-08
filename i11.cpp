#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

struct node {
public:
    int size;      // количество занятых ключей
    int key[3];
    node *first;   // *first <= key[0];
    node *second;  // key[0] <= *second < key[1];
    node *third;   // key[1] <= *third < key[2];
    node *fourth;  // kye[2] <= *fourth.
    node *parent; //Указатель на родителя нужен для того, потому что адрес корня может меняться при удалении

    bool find(int k) { // Этот метод возвращает true, если ключ k находится в вершине, иначе false.
        for (int i = 0; i < size; ++i)
            if (key[i] == k) return true;
        return false;
    }

    void swap(int &x, int &y) {
        int r = x;
        x = y;
        y = r;
    }

    void sort2(int &x, int &y) {
        if (x > y) swap(x, y);
    }

    void sort3(int &x, int &y, int &z) {
        if (x > y) swap(x, y);
        if (x > z) swap(x, z);
        if (y > z) swap(y, z);
    }

    void sort() { // Ключи в вершинах должны быть отсортированы
        if (size == 1) return;
        if (size == 2) sort2(key[0], key[1]);
        if (size == 3) sort3(key[0], key[1], key[2]);
    }

    void insert_to_node(int k) {  // Вставляем ключ k в вершину (не в дерево)
        key[size] = k;
        size++;
        sort();
    }

    void remove_from_node(int k) { // Удаляем ключ k из вершины (не из дерева)
        if (size >= 1 && key[0] == k) {
            key[0] = key[1];
            key[1] = key[2];
            size--;
        } else if (size == 2 && key[1] == k) {
            key[1] = key[2];
            size--;
        }
    }

    void become_node2(int k, node *first_, node *second_) {  // Преобразовать в 2-вершину.
        key[0] = k;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
    }

    bool is_leaf() { // Является ли узел листом; проверка используется при вставке и удалении.
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }

public:
    // Создавать всегда будем вершину только с одним ключом
    node(int k) : size(1), key{k, 0, 0}, first(nullptr), second(nullptr),
                  third(nullptr), fourth(nullptr), parent(nullptr) {}

    node(int k, node *first_, node *second_, node *third_, node *fourth_, node *parent_) :
            size(1), key{k, 0, 0}, first(first_), second(second_),
            third(third_), fourth(fourth_), parent(parent_) {}

    friend node *split(node *item); // Метод для разделение вершины при переполнении;
    friend node *insert(node *p, int k); // Вставка в дерево;
    friend node *search(node *p, int k); // Поиск в дереве;
    friend node *search_min(node *p); // Поиск минимального элемента в поддереве;
    friend node *merge(node *leaf); // Слияние используется при удалении;
    friend node *redistribute(node *leaf); // Перераспределение также используется при удалении;
    friend node *
    fix(node *leaf); // Используется после удаления для возвращения свойств дереву (использует merge или redistribute)
    friend node *remove(node *p, int k); // Собственно, из названия понятно;
};

node *
insert(node *p, int k) { // вставка ключа k в дерево с корнем p; всегда возвращаем корень дерева, т.к. он может меняться
    if (!p) return new node(k); // если дерево пусто, то создаем первую 2-3-вершину (корень)

    if (p->is_leaf()) p->insert_to_node(k);
    else if (k <= p->key[0]) insert(p->first, k);
    else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) insert(p->second, k);
    else insert(p->third, k);

    return split(p);
}

node *split(node *item) {
    if (item->size < 3) return item;

    node *x = new node(item->key[0], item->first, item->second, nullptr, nullptr,
                       item->parent); // Создаем две новые вершины,
    node *y = new node(item->key[2], item->third, item->fourth, nullptr, nullptr,
                       item->parent);  // которые имеют такого же родителя, как и разделяющийся элемент.
    if (x->first) x->first->parent = x;    // Правильно устанавливаем "родителя" "сыновей".
    if (x->second) x->second->parent = x;   // После разделения, "родителем" "сыновей" является "дедушка",
    if (y->first) y->first->parent = y;    // Поэтому нужно правильно установить указатели.
    if (y->second) y->second->parent = y;

    if (item->parent) {
        item->parent->insert_to_node(item->key[1]);

        if (item->parent->first == item) item->parent->first = nullptr;
        else if (item->parent->second == item) item->parent->second = nullptr;
        else if (item->parent->third == item) item->parent->third = nullptr;

        // Дальше происходит своеобразная сортировка ключей при разделении.
        if (item->parent->first == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        } else if (item->parent->second == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        } else {
            item->parent->fourth = y;
            item->parent->third = x;
        }

        node *tmp = item->parent;
        delete item;
        return tmp;
    } else {
        x->parent = item;   // Так как в эту ветку попадает только корень,
        y->parent = item;   // то мы "родителем" новых вершин делаем разделяющийся элемент.
        item->become_node2(item->key[1], x, y);
        return item;
    }
}

node *search(node *p, int k) { // Поиск ключа k в 2-3 дереве с корнем p.
    if (!p) return nullptr;

    if (p->find(k)) return p;
    else if (k < p->key[0]) return search(p->first, k);
    else if ((p->size == 2) && (k < p->key[1]) || (p->size == 1)) return search(p->second, k);
    else if (p->size == 2) return search(p->third, k);
}

node *search_min(node *p) { // Поиск узла с минимальным элементов в 2-3-дереве с корнем p.
    if (!p) return p;
    if (!(p->first)) return p;
    else return search_min(p->first);
}

node *remove(node *p, int k) { // Удаление ключа k в 2-3-дереве с корнем p.
    node *item = search(p, k); // Ищем узел, где находится ключ k

    if (!item) return p;

    node *min = nullptr;
    if (item->key[0] == k) min = search_min(item->second); // Ищем эквивалентный ключ
    else min = search_min(item->third);

    if (min) { // Меняем ключи местами
        int &z = (k == item->key[0] ? item->key[0] : item->key[1]);
        item->swap(z, min->key[0]);
        item = min; // Перемещаем указатель на лист, т.к. min - всегда лист
    }

    item->remove_from_node(k); // И удаляем требуемый ключ из листа
    return fix(item); // Вызываем функцию для восстановления свойств дерева.
}

node *fix(node *leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) { // Случай 0, когда удаляем единственный ключ в дереве
        delete leaf;
        return nullptr;
    }
    if (leaf->size != 0) { // Случай 1, когда вершина, в которой удалили ключ, имела два ключа
        if (leaf->parent) return fix(leaf->parent);
        else return leaf;
    }

    node *parent = leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
        leaf = redistribute(leaf); // Случай 2, когда достаточно перераспределить ключи в дереве
    else if (parent->size == 2 && parent->third->size == 2) leaf = redistribute(leaf); // Аналогично
    else
        leaf = merge(
                leaf); // Случай 3, когда нужно произвести склеивание и пройтись вверх по дереву как минимум на еще одну вершину

    return fix(leaf);
}

node *redistribute(node *leaf) {
    node *parent = leaf->parent;
    node *first = parent->first;
    node *second = parent->second;
    node *third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = nullptr;
            parent->first->insert_to_node(parent->key[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != nullptr) parent->first->first = leaf->first;
            else if (leaf->second != nullptr) parent->first->first = leaf->second;

            if (parent->first->first != nullptr) parent->first->first->parent = parent->first;

            parent->remove_from_node(parent->key[0]);
            delete first;
        } else if (second == leaf) {
            first->insert_to_node(parent->key[0]);
            parent->remove_from_node(parent->key[0]);
            if (leaf->first != nullptr) first->third = leaf->first;
            else if (leaf->second != nullptr) first->third = leaf->second;

            if (first->third != nullptr) first->third->parent = first;

            parent->second = parent->third;
            parent->third = nullptr;

            delete second;
        } else if (third == leaf) {
            second->insert_to_node(parent->key[1]);
            parent->third = nullptr;
            parent->remove_from_node(parent->key[1]);
            if (leaf->first != nullptr) second->third = leaf->first;
            else if (leaf->second != nullptr) second->third = leaf->second;

            if (second->third != nullptr) second->third->parent = second;

            delete third;
        }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first != nullptr) {
                leaf->second = leaf->first;
                leaf->first = nullptr;
            }

            leaf->insert_to_node(parent->key[1]);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                second->remove_from_node(second->key[1]);
                leaf->first = second->third;
                second->third = nullptr;
                if (leaf->first != nullptr) leaf->first->parent = leaf;
            } else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != nullptr) leaf->first->parent = leaf;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        } else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->first == nullptr) {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                second->insert_to_node(parent->key[1]);
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            } else if (first->size == 2) {
                if (leaf->second == nullptr) {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }
                second->insert_to_node(parent->key[0]);
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        } else if (first == leaf) {
            if (leaf->first == nullptr) {
                leaf->first = leaf->second;
                leaf->second = nullptr;
            }
            first->insert_to_node(parent->key[0]);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                second->remove_from_node(second->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
            } else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
        }
    } else if (parent->size == 1) {
        leaf->insert_to_node(parent->key[0]);

        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            second->remove_from_node(second->key[0]);

            if (leaf->first == nullptr) leaf->first = leaf->second;

            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = nullptr;
            if (leaf->second != nullptr) leaf->second->parent = leaf;
        } else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            first->remove_from_node(first->key[1]);

            if (leaf->second == nullptr) leaf->second = leaf->first;

            leaf->first = first->third;
            first->third = nullptr;
            if (leaf->first != nullptr) leaf->first->parent = leaf;
        }
    }
    return parent;
}

node *merge(node *leaf) {
    node *parent = leaf->parent;

    if (parent->first == leaf) {
        parent->second->insert_to_node(parent->key[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != nullptr) parent->second->first = leaf->first;
        else if (leaf->second != nullptr) parent->second->first = leaf->second;

        if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

        parent->remove_from_node(parent->key[0]);
        delete parent->first;
        parent->first = nullptr;
    } else if (parent->second == leaf) {
        parent->first->insert_to_node(parent->key[0]);

        if (leaf->first != nullptr) parent->first->third = leaf->first;
        else if (leaf->second != nullptr) parent->first->third = leaf->second;

        if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

        parent->remove_from_node(parent->key[0]);
        delete parent->second;
        parent->second = nullptr;
    }

    if (parent->parent == nullptr) {
        node *tmp = nullptr;
        if (parent->first != nullptr) tmp = parent->first;
        else tmp = parent->second;
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}

node *tree;
node *test_tree;

void stress_text(int n = 10000) {
    for (int i = 0; i < n; i++) {
        int col = rand() % 20;
        vector<int> test_elements;
        for (int j = 0; j < col; j++) {
            int x = rand() % 10000;
            test_tree=insert(test_tree, x);
            test_elements.push_back(x);
        }
        for (int k = 0; k < col; k++) {
            cout << test_elements[k] << " ";
        }
        cout << endl;
        for (int j = 0; j < col; j++) {
//            cout<<j<<endl;
            test_tree=remove(test_tree,test_elements[j]);
            if (search(test_tree, test_elements[j]) != nullptr) {
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
//            assert(test_tree== nullptr);
        }
        assert(test_tree== nullptr);
        cout << i << endl;
    }
    cerr<<"stress test complite"<<endl;
}
void showbfs(node* root){

    for (int i=0; i<root->size;i++){
        cout<<root->key[i]<<" ";
    }
    cout<<endl;
    if (root->size==1 && root->first != nullptr){
        showbfs(root->first);
        showbfs(root->second);
    }else if (root->size==2 && root->first!= nullptr){
        showbfs(root->first);
        showbfs(root->second);
        showbfs(root->third);
    }
}
bool isEven(int value){return value&1;}
int main() {
    int element;
    int a;
    cout<<isEven(112);
//    stress_text(1000000);
//    tree=insert(tree, 1);
//    tree=insert(tree, 2);
//    tree=insert(tree, 3);
//    tree=insert(tree, 4);
//    tree=insert(tree, 5);
//    showbfs( tree );
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
            tree=insert(tree, element);
            cerr << "append sucsessfull" << endl;
        }
        if (command == 'f') {
            node *ans = search(tree, element);
            if (ans != nullptr)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        }
        if (command == 'r') {
            tree=remove(tree, element);
            cerr << "delete sucsessfull" << endl;
        }
        if (command == 's') {
            showbfs(tree);
            cerr << "show sucsessfull" << endl;
        }
        command = getchar();
        if (command == '\r')
            command = getchar();
        else if (command == '\n')
            command = getchar();
    }
    return 0;
}
