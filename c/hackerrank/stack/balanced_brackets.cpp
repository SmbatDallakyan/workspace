#include <bits/stdc++.h>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s) {
  stack<char> scopes;
  for (int i = 0; i < s.length(); ++i) {
    switch (s[i]) {
    case '[':
    case '{':
    case '(':
      scopes.push(s[i]);
      break;
    case ']':
      if (scopes.empty() || scopes.top() != '[') {
        return "NO";
      } else {
        scopes.pop();
      }
      break;
    case '}':
      if (scopes.empty() || scopes.top() != '{') {
        return "NO";
      } else {
        scopes.pop();
      }
      break;
    case ')':
      if (scopes.empty() || scopes.top() != '(') {
        return "NO";
      } else {
        scopes.pop();
      }
      break;
    }
  }
  if(!scopes.empty()){
    return "NO";
  }
  return "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);
        cout << result << "\n";

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
