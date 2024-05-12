#pragma once
#include <string>
#include <iostream>
#include "Node.h"
using namespace std;
class TxtNode{
public:
    string filenname;
    TxtNode* next;
    TxtNode():next(nullptr){}
    TxtNode(string filename):filenname(filename),next(nullptr){}
};