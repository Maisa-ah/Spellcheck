// Maisa Ahmad

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    cout << "TestFunctionForHashTables..." << endl;
    cout << "Words filename: " << words_filename << endl;
    cout << "Query filename: " << query_filename << endl;
    hash_table.MakeEmpty();
    //..Insert your own code
    string words_line;
    ifstream words_file(words_filename);//read file
    if (words_file.is_open()){
        cout << "\n" << "Inserting words into the Hash table..." <<endl;
        while (words_file >> words_line){
            hash_table.Insert(words_line);//insert each element into the hash table
        }
    }
    words_file.close();
    
    double collisions_ = hash_table.NumOfCollisions();//function returns collision count
    double elements_ = hash_table.NumOfElements();//returns num of elements
    double tb_size_ = hash_table.TableSize();//function returns size of hash table, array.size keeps track for changes
    double ld_factor = elements_/tb_size_; //load factor is elements/table size
    double avg_collisions_ = collisions_/elements_;//average collisions is collisions/elements
    
    cout << "Statistics for this Hash Table:" << endl;
    cout << "Collisions: " << collisions_ << endl;
    cout << "Number of items: " << elements_ <<endl;
    cout << "Size of hash table: " << tb_size_ <<endl;
    cout << "Load factor: " << ld_factor <<endl;
    cout << "Avg. number of collisions: " << avg_collisions_ <<endl;
    
    string query_line;
    ifstream query_file(query_filename);//read file
    if (query_file.is_open()){
        cout<< "\n" << "Beginning seaching for query words:" <<endl;
        while (query_file >> query_line){//as words being read
            if (hash_table.Contains(query_line)){//check if hash table contains it
                cout<< query_line << ": Found in " << hash_table.NumOfProbes() << " probes" << endl;//if contains
            }
            else{//otherwise word not found
                cout<< query_line << ": Not found in " << hash_table.NumOfProbes() << " probes" << endl;
            }
        }
    }
    query_file.close();
}



// Sample main for program create_and_test_hash
int
main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
        return 0;
    }
    
    const string words_filename(argv[1]);
    const string query_filename(argv[2]);
    const string param_flag(argv[3]);
     
    if (param_flag == "linear") {
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } else if (param_flag == "quadratic") {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    } else if (param_flag == "double") {
        HashTableDouble<string> double_probing_table;
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } else {
        cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}
