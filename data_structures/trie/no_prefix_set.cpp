/**
 * Given N strings. Each string contains only lowercase letters from a-j (both inclusive).
 * The set of N strings is said to be GOOD SET if no string is prefix of another string else,
 * it is BAD SET. (If two strings are identical, they are considered prefixes of each other.)
 * For example, aab, abcde, aabcd is BAD SET because aab is prefix of aabcd.
 *
 * Print GOOD SET if it satisfies the problem requirement.
 * Else, print BAD SET and the first string for which the condition fails.
 *
 * https://www.hackerrank.com/challenges/no-prefix-set/problem
**/


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
    cin>>n;
    for(int i = 0; i < n; ++i){
        bool isGood;
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
