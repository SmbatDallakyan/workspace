#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Trie {
    public:
        map<char, Trie*> child;
        bool isCompleateWord = false;
        int wordCount = 0;
};

void addWord(string str, Trie *trie){
    for(int i = 0; i < str.size(); ++i){
        ++trie->wordCount;
        if(trie->child.find(str[i]) == trie->child.end()){
            trie->child[str[i]]=new Trie();
        }
        trie = trie->child[str[i]];
    }
    ++trie->wordCount;
    trie->isCompleateWord = true;
}

Trie* findNode(string str, Trie* trie){
    for(int i = 0; i < str.size(); ++i){
        if(trie->child.find(str[i]) == trie->child.end()){
            return nullptr;
        }
        trie = trie->child[str[i]];
    }
    return trie;
}

vector<int> contacts(vector<vector<string>> queries) {
  vector<int> result;
  Trie *trie = new Trie();
  Trie *currentTrie;
  for (int i = 0; i < queries.size(); ++i) {
    if (queries[i][0] == "add") {
      addWord(queries[i][1], trie);
    } else if (queries[i][0] == "find") {
      currentTrie = findNode(queries[i][1], trie);
      if (currentTrie == nullptr) {
        result.push_back(0);
      } else {
        result.push_back(currentTrie->wordCount);
      }
    }
  }

  return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
