//  Maisa Ahmad
// This project will implement a spell checker by using quadratic probing. Spellcheck with cases for removing characters, adding characters and swapping.

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void Spellcheck(const string &dictionary_filename, const string &document_filename){
    HashTable<string> hash_check;//hash table to store words from dictionary
    
    ifstream dictionary (dictionary_filename);//read dictionary for words
    string word;
    
    while (dictionary >>word){
        hash_check.Insert(word);//load into hash table so accessing is easier
    }
    dictionary.close();
    
    ifstream document(document_filename);
    string check_;
    while (document>>check_){
        for(int i=0; i<check_.size(); i++){
            check_[i] = tolower(check_[i]);//make all characters lowercase
            if(ispunct(check_[0])){
                check_ = check_.substr(1);//removes if first is punctuation
            }
            if(ispunct(check_[check_.size()-1])){//for last remove punctuation
                check_.pop_back();
                if(ispunct(check_[check_.size()-1])){//incase of two punctuations in last
                    check_.pop_back();
                }
            }
        }
        
        
        bool found = hash_check.Contains(check_);
        //case a - adding one character in each possible position
        if(found == false){
            string hold = check_;//to hold incorrect spelling
            for (int i=0; i<check_.size(); i++){
                for(size_t j='a'; j<='z'; j++){
                    check_.insert(i, 1, j);//insert j at location i, size of 1
                    if (hash_check.Contains(check_)){//check dictionary for existance
                        cout<< hold << " -> " << check_ << " (case a)"<<endl;
                    }
                    check_ = hold;//check original string
                }
            }
            
            //case b - removing one character from the word
            for (int i=0; i<check_.size(); i++){
                check_.erase(i, 1);//remove character i and check dictionary for its existance
                if (hash_check.Contains(check_)){
                    cout<< hold << " -> " << check_ << " (case b)"<<endl;
                }
                check_ = hold;
            }
            
            //case c - swapping adjacent characters in the word
            for (int i=0; i<check_.size(); i++){
                swap(check_[i], check_[i+1]);//swap letter with the one next to it
                if (hash_check.Contains(check_)){//check dictionary for existance
                    cout<< hold << " -> " << check_ << " (case c)"<<endl;
                }
                swap(check_[i], check_[i+1]);//swap back
            }
        }
    }
}


// Sample main for program spell_check
int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
        return 0;
    }
    
    const string document_filename(argv[1]);
    const string dictionary_filename(argv[2]);
    
    cout << "Input document filename is " << document_filename << endl;
    cout << "Input dictionary filename is " << dictionary_filename << endl;
    
    // Call functions implementing the assignment requirements.
    Spellcheck(dictionary_filename, document_filename);
    

    return 0;
}
