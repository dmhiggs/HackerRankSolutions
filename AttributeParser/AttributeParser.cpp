#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef struct Tag {
    Tag *prev;
    string name;
    vector<Tag> nestedTags;
    map<string,string> attributes;
}Tag;

vector<string> tokenize(string s, char c) {
    vector<string> tokens;
    int start = 0;
    int end = 0;
    while (end != 1) {
        int pos = s.find(c);
        if (pos == s.npos) {
            pos = s.size();
            end = 1;
        }

        if (s.substr(start,pos-start) != "=") tokens.emplace(tokens.begin(), s.substr(start,pos-start));
        if (end != 1) s = s.substr(pos+1);
    }
    return tokens;
}

void getAttributePairs(vector<string> tokens, struct Tag *t) {
    string name, value;
    int size = tokens.size();

    for (int i = 0; i + 1 < size; i += 2) {
        name = tokens.at(i+1);
        tokens.at(i).pop_back();
        value = tokens.at(i).substr(1);
        t->attributes[name]=value;
    }
}

void printTag(struct Tag t) {
    cout << t.name << endl;
    for (auto& x: t.attributes) {
        cout << x.first << ": " << x.second << '\n';
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string str;
    vector<Tag> tags;
    Tag *current;
    int n, q;
    cin >> n >> q;
    getline(cin, str);

    for (int i = 0; i < n; i++) {
        getline(cin, str);

        if (str.at(1) == '/') {
            //end tag
            current = current->prev;
            continue;
        }

        str = str.substr(1, str.size()-2); //cut off < >
        vector<string> s = tokenize(str, ' ');

        Tag *t = new Tag;
        t->name = s.back();
        s.pop_back();
        getAttributePairs(s, t);

        if (current == nullptr) {
            tags.push_back(*t);
            current = &tags.back();
        }
        else {
            current->nestedTags.push_back(*t);
            current->nestedTags.back().prev = current;
            current = &current->nestedTags.back();
        }
        // printTag(*current);
    }

    for (int i = 0; i < q; i++) {
        string result = "Not Found!";
        getline(cin, str);

        vector<string> s = tokenize(str, '~');
        str = s.at(0); //the attribute name

        int found = 1;
        vector<Tag>* level = &tags;
        s = tokenize(s.at(1), '.'); //the tags
        while (s.size() > 0 && found == 1) {
            found = 0;
            for (int j = 0; j < level->size() && found != 1; j++) {
                if (level->at(j).name == s.back()) {
                    //match
                    found = 1;
                    current = &level->at(j);
                    level = &level->at(j).nestedTags;
                }
            }
            s.pop_back();
        }
        if (found == 1 && current->attributes.count(str) > 0) {
            result = current->attributes[str];
        }
        cout << result << endl;
    }
    return 0;
}
