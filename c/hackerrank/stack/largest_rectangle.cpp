#include <bits/stdc++.h>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string);

class Building {
    public:
      int lborder;
      int rborder;
      int height;
      int index;
      Building(int lborder, int rborder, int height, int index){
            this->lborder = lborder;
            this->rborder = rborder;
            this->height = height;
            this->index = index;
      }
      long int getArea() {
          cout << this->height * (rborder - lborder) << '\n';
          return this->height * (rborder - lborder);
      }
};

// Complete the largestRectangle function below.
long largestRectangle(vector<int> h) {
    long int maxArea = 0;
    stack<Building> buf;
    Building *prevBuilding = new Building(0, -1, h[0], 0);
    buf.push(*prevBuilding);
    for(int i = 1; i < h.size(); ++i){
        Building *current = new Building(-1, -1, h[i], i);
        if(current->height > buf.top().height){
            current->lborder = i;
            buf.push(*current);
        } else {
            while(!buf.empty() && current->height <= buf.top().height){
                buf.top().rborder = i;
                maxArea = max(maxArea, buf.top().getArea());
                buf.pop();
            }
            if(buf.empty()){
                current->lborder = 0;
            } else {
                current->lborder = buf.top().index + 1;
            }
            buf.push(*current);
        }
        prevBuilding = current;
    }
    while(!buf.empty()){
        buf.top().rborder = h.size();
        maxArea = max(maxArea, buf.top().getArea());
        buf.pop();
    }
    return maxArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split_string(h_temp_temp);

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

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
