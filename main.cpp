#include <iostream>
#include <string>
#include <fstream>
#include "WordList.h"
#include "Node.h"
#include <vector>
#include <chrono>
#include <dirent.h>
#include <algorithm>


using namespace std;

std::string getAlphaWord(std::ifstream& file) {
    std::string word = "";
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(ch)) {
            word += ch;
        } else if (!word.empty()) {
            // Skip leading non-alphabetic characters
            if (std::isalpha(word[0])) {
                return word;
            } else {
                word = "";
            }
        }
    }
    // Skip leading non-alphabetic characters
    if (!word.empty() && std::isalpha(word[0])) {
        return word;
    }
    return "";
}


void AddWord(const string& Word, WordList& dictionary, const string& filename){

    dictionary.AddWord(Word, filename);

}

int main() {

    WordList dictionary;

    vector<Node*> least10;
    vector<Node*> most10;
    cout << "Please wait program is running..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::string path = "./AllDocs"; // The path to the directory with the text files
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            // Check if the file is a .txt file
            if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
                std::ifstream file(path + "/" + filename);
                if (!file) {
                    std::cerr << "Could not open file " << filename << "\n";
                    continue;
                }

                string content;
                while (!(content = getAlphaWord(file)).empty()) {
                    for (auto & c: content) c = std::tolower(c);
                    AddWord(content, dictionary, filename);
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Could not open directory " << path << "\n";
        return EXIT_FAILURE;
    }

    if(dictionary.size() <= 26){
        cout << "Could not find any files";
        return 0;

    }



    dictionary.top10(most10);
    dictionary.least10(least10);
    auto end = std::chrono::high_resolution_clock::now();
    chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    cout << endl << "Index creation time: " << duration.count() << " seconds." << endl;

    char choice;
    while(choice != '4'){

        cout << "\nSimple Document Retrieval System\n";
        cout << "1. Enter a single keyword to list the document(s)(file names)\n";
        cout << "2. Print the top 10 words that appeared most frequently\n";
        cout << "3. Print the top 10 words that appeared least frequently\n";
        cout << "4. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case '1': {
                string word;
                cout << "Enter word you want to find:";
                cin >> word;
                cout << endl;
                Node *theWord = dictionary.FindWord(word);

                if(theWord != nullptr)
                    theWord->PrintInfo();
                else
                    cout << "The word you entered couldn't be found" << endl;

                break;
            }
            case '2': {

                cout << "Top 10 words that appeared most frequently: " << endl;
                cout << endl;
                for(int i = 0 ; i < 10 ; i++){
                    cout << most10[i]->word <<": "<< most10[i]->HowMany()  << " times" << endl;
                }
                break;
            }
            case '3':

                cout << "Top 10 words that appeared least frequently: " << endl;
                cout << endl;
                for(int i = 0 ; i < 10 ; i++){
                    cout << least10[i]->word <<": "<< least10[i]->HowMany()  << " times" << endl;
                }
                break;
            case '4':
                dictionary.clear();
                break;
            default:

                cout << "Enter Valid Choice." << endl;
                break;
        }
    }

    return 0;
}
