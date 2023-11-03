#include <iostream>
#include <set>
using namespace std;

int main() {
    int N;
    string str;
    cin >> N;
    set<string> s;

    for (int n = 1; n <= N; n++) {
        cin >> str;
        if (s.find(str) != s.end()) continue;
        s.insert(str);
        cout << n << endl;
    }
}