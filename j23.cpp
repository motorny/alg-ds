#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
//Реализуйте хеш­таблицу элементами которой являются ASCII­Z строки. В качестве метода
//разрешения коллизий выберете двойное хеширование.
struct mydata {
    int hash1;
    int hash2;
    int count;
};


class hashTable {
public:
    map<string, mydata> table;
    int hash1[ 10000007];
    int hash2[9999937];

    int getHash1(string element) {
        long long  ans = 0;
        for (auto sign :element) {
            ans = (ans + int(sign)* 999983) % 10000007;
        }
        return ans;
    };

    int getHash2(string element) {
        long long  ans = 0;
        for (auto sign :element) {
            ans = (ans + int(sign) * 100003) % 9999937;
        }
        return ans;
    };

    pair<int, int> getHash(string element) {
        long long  ans1 = 0;
        long long  ans2 = 0;
        for (auto sign :element) {
            ans1 = (ans1 + int(sign) * 999983) % 10000007;
            ans2 = (ans2 + int(sign) * 100003) % 9999937;
        }
        pair<int, int> ans;
        ans.first = ans1;
        ans.second = ans2;
//        <ans1,ans2>
        return ans;
    };

    void insert(string element) {
        auto hash = getHash(element);
//        table[element].hash1 = hash.first;
//        table[element].hash2 = hash.second;
//        table[element].count++;
        hash1[hash.first]++;
        hash2[hash.second]++;
    }

    bool search(string element) {
        auto hash = getHash1(element);
        if (hash1[hash] > 0) {
            int kol = hash1[hash];
            hash = getHash2(element);
            if (hash2[hash] == kol)
                return true;
        }
        return false;
    }

    void remove(string element) {
        auto hash = getHash(element);
        if (hash1[hash.first] != 0) {
            hash1[hash.first]--;
            hash2[hash.second]--;
        }
    }
};

hashTable myTable;

void stressTest(int col) {
    for (int i = 0; i < col; i++) {

    }
}
string convert_to_strring(char *s){
    int len= strlen(s);
    string ans;
    for (int i=0;i<len;i++)
        ans+=s[i];
    return ans;
}
int main() {
//    char ch = getchar();
//    char str[MAX_STR_SIZE];
//    string element;
//    char ch;
//    while (cin >> ch) {
////        scanf("%s", element);
//        if (cin >> element)
    char ch = getchar();
    char str[256*256];
    while ( ch != EOF ){
        scanf("%s", str);
        string element= convert_to_strring(str);
        cerr<<element<<endl;
            switch (ch) {
                case 'a':
                    // add
                    myTable.insert(element);
                    cerr << "append sucsessfull" << endl;
                    break;
                case 'r':
                    // remove
                    myTable.remove(element);
                    cerr << "delete sucsessfull" << endl;
                    break;
                case 'f':
                    if (myTable.search(element))
                        cout << "yes" << endl;
                    else
                        cout << "no" << endl;
                    break;
                default:
                    return 0;
            }

        ch = getchar();
        if ( ch == '\r' )
            ch = getchar();
        if ( ch == '\n' )
            ch = getchar();
    }

    return 0;
}