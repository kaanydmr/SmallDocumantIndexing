#pragma once
#include "Node.h"
#include "WordList.h"
#include <string>
#include <algorithm>

class WordList{
private:
    Node* head;
    Node* charIndexes[26];
public:
    WordList();
    ~WordList();

    void InitializeList();
    Node * findinsert(Node* start, Node* end, const string& value);
    Node* FindWord(const std::string &word);

    void AddWord(const string &word, const string& filename);

    void top10(vector<Node *> &top)const;

    void least10(vector<Node *> &top);

    int size() const;
    bool empty() const;
    void clear();

};