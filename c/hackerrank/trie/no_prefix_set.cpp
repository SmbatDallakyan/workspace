#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Trie {
    public:
        map<char, Trie*> child;
        bool isCompleateWord = false;
};

bool addWord(string str, Trie *trie){
    bool isGoodSet;
    for(int i = 0; i < str.size(); ++i){
        if(trie->isCompleateWord){
            return false;
        }
        if(trie->child.find(str[i]) == trie->child.end()){
            trie->child[str[i]]=new Trie();
        }
        trie = trie->child[str[i]];
    }
    isGoodSet = trie->child.empty() && !trie->isCompleateWord;
    trie->isCompleateWord = true;
    return isGoodSet;
}

int main() {
    int n;
    string str;
    Trie *trie = new Trie();
    bool isGood;
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>str;
        isGood = addWord(str, trie);
        if(!isGood){
            cout<<"BAD SET\n"<<str<<"\n";
            return 0;
        }
    }
    cout << "GOOD SET\n";

    return 0;
}
