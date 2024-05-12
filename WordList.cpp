#pragma once
#include "WordList.h"
#include "Node.h"
#include <string>
#include <algorithm>
#include <vector>


WordList::WordList() {
    head = nullptr;
    InitializeList();
}

void WordList::InitializeList(){
   for(int i = 0 ; i < 26; i++){
       char name = 'A' + i;
       Node *newNode = new Node;
       newNode->word = string(1,name);
       newNode->next = nullptr;
       charIndexes[i] = newNode;
       if (head == nullptr) {
           head = newNode;
       } else {
           Node *temp = head;
           while (temp->next != nullptr) {
               temp = temp->next;
           }
           temp->next = newNode;
       }
   }
}

Node* WordList::FindWord(const std::string &word) {
    char firstWord = word[0];
    int i;
    for(i = 0; i < 26; i++){
        if(firstWord == std::tolower(charIndexes[i]->word[0])){
            break;
        }
    }

    Node* current = charIndexes[i];
    while(current != nullptr){
        if(current->word == word){
            return current; // Word found
        }
        current = current->next;
    }

    return nullptr; // Word not found
}

bool CompareNodesTop(Node* a, Node* b) {
    return a->HowMany() > b->HowMany();
}

bool CompareNodesLeast(Node* a, Node* b){
    return !CompareNodesTop(a, b);
}

void WordList::top10(std::vector<Node*>& top) const{

    Node* walk = this->head;

    while(walk != nullptr){

        if(top.size() < 10){ // If less than 10 words, simply add it to the list
            top.push_back(walk);

        }
        else{

            top.push_back(walk);
            std::sort(top.begin(), top.end(), CompareNodesTop);
            top.pop_back();

        }
        walk = walk->next;
    }
}

void WordList::least10(std::vector<Node*>& top){

    Node* walk = this->head->next;
    int counter = 0;

    while(walk != nullptr && counter < 10){

        if(walk->HowMany() == 1)
            counter++;

        if(top.size() < 10){ // If less than 10 words, simply add it to the list

            top.push_back(walk);
            std::sort(top.begin(), top.end(), CompareNodesLeast);

        }
        else if(walk->HowMany() != 0){

            top.push_back(walk);
            std::sort(top.begin(), top.end(), CompareNodesLeast);
            top.pop_back();

        }

        walk = walk->next;
    }

}





void WordList::AddWord(const std::string &word, const string& filename) {
    char firstWord = word[0];
    int i;
    for(i = 0; i < 26; i++){
        if(firstWord == std::tolower(charIndexes[i]->word[0])){
            break;
        }
    }

    Node* current = charIndexes[i];
    while(current != nullptr){
        if(current->word == word){
            current->Push(filename);
            return; // Word already exists in the list, so we just return
        }
        current = current->next;
    }

    // If we reach here, it means the word does not exist in the list, so we add it
    Node* newnode = findinsert(charIndexes[i],charIndexes[i+1], word);
    newnode->Push(filename);

}

Node * WordList::findinsert(Node* start, Node* end, const string& value){
    Node* Walk = start->next; // Start from the node after the marker
    Node* prev = start;
    if(start == end){

        Node* newnode = new Node(value);
        newnode->next = Walk;
        prev->next = newnode;
        return newnode;


    }

    while (Walk != end){

        if(Walk->word <= prev->word){
            break;
        }
        prev = Walk;
        Walk = Walk->next;
    }

    Node* newnode = new Node(value);
    newnode->next = Walk;
    prev->next = newnode;
    return newnode;


}

WordList::~WordList() {
    clear();
}



void WordList::clear() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int WordList::size() const {
    int size = 0;
    for (Node *temp = head; temp != nullptr; temp = temp->next) {
        ++size;
    }
    return size;
}

bool WordList::empty() const {
    return head == nullptr;
}



