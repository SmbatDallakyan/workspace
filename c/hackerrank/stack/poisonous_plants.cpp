#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p) {
    int days = 0;
    list<list<int>> ls;
    list <list<int>>::iterator it;
    list<int> *currentSt = new list<int>();
    currentSt->push_back(p[0]);
    for(int i = 1; i < p.size(); ++i){
        if(p[i] > currentSt->back()) {
          ls.push_back(*currentSt);
          currentSt = new list<int>();
        }
        currentSt->push_back(p[i]);
    }
    if(!currentSt->empty()){
          ls.push_back(*currentSt);
    }
    while(ls.size() > 1){
        ++days;
        it = ls.begin();
        ++it;
        while(it != ls.end()){
          it->pop_front();
          ++it;
        }
        it = ls.begin();
        advance(it, 1);
        while(it != ls.end()){
          if(it->empty()){
              ls.erase(it++);
          } else if(it->front() <= prev(it)->back()){
            prev(it)->splice(prev(it)->end(), *it);
            ls.erase(it++);
          } else {
              ++it;
          }
        }
    }
    return days;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
