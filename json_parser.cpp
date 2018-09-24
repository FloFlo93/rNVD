#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <fstream>
using namespace std;

vector<string> split(char delimiter, string str);
vector<vector<string>> parse_json(string json);
vector<string> removeWhitespaceEntries(vector<string> items);

vector<vector<string>> fromFile(string filename) {
    ifstream file(filename);
    string json = "";
    string str;
    while (getline(file, str))
    {
        json += str;
    }
    return parse_json(json);
}

vector<vector<string>> parse_json(string json) {

    vector<vector<string>> clusterSet;

    vector<string> clusters = split(',', json);

    for(string cluster : clusters) {
        vector<string> itemVal = split(':', cluster);
        string allValues = itemVal[1];
        allValues.erase (remove(allValues.begin(), allValues.end(), '\"'), allValues.end());
        allValues.erase (remove(allValues.begin(), allValues.end(), '}'), allValues.end());
        vector<string> items = split(' ', allValues);
        items = removeWhitespaceEntries(items);
        sort(items.begin(), items.end());
        clusterSet.push_back(items);
    }
    return clusterSet;
}

vector<string> removeWhitespaceEntries(vector<string> items) {
    vector<string> items_no_ws;
    for(unsigned int i=0; i<items.size(); i++) {
        if(items[i].find_first_not_of(' ') != std::string::npos)
        {
            items_no_ws.push_back(items[i]);
        }
    }
    return items_no_ws;
}

vector<string> split(char delimiter, string str) {
    vector<string> chunks;
    string token;
    size_t pos = 0;
    size_t prevPos = 0;
    while ((pos = str.find(delimiter, prevPos)) != string::npos) {
        token = str.substr(prevPos, pos-prevPos);
        chunks.push_back(token);
        prevPos = pos +1;
    }
    token = str.substr(prevPos, str.length());
    chunks.push_back(token);

    return chunks;
}
