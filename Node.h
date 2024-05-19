#pragma once
#include "TxtNode.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class Node
{
public:
    string word;
    TxtNode* occurrences;
    Node* next;

    Node():next(nullptr), occurrences(nullptr){}
    Node(const string &na) :next(nullptr), word(na), occurrences(nullptr) {}

    void Push(string filename){

        if(occurrences == nullptr){
            TxtNode* nexttxt = new TxtNode(filename);
            occurrences = nexttxt;
            return;
        }
        TxtNode* walk=occurrences;
        while (walk != nullptr){
            if(walk->filenname == filename){
                return;
            }
            walk= walk->next;
        }
        TxtNode* nexttxt = new TxtNode(filename);
        nexttxt->next = occurrences;
        occurrences = nexttxt;
    }

    int HowMany(){
        if(occurrences == nullptr)
            return 0;

        TxtNode* walk = occurrences;
        int counter = 0;

        while(walk != nullptr){
            counter++;
            walk = walk->next;
        }
        return counter;
    }


    void PrintInfo(){
        cout << "The Word '" << this->word << "' Occurs in " << HowMany() << " files which are:" << endl;
        TxtNode* node = this->occurrences;
        while (node != nullptr){
            cout << node->filenname << endl;
            node = node->next;
        }
        cout << "These files are the word '" << this->word << "' occurred." << endl;
    }

};
