//Data Structures
//1.Trie
//2.Set(RBT)

//Comparison
//1.Adding time
//2.Removing time
//3.Searching time

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

const int CHARACTERS_SIZE = 52;

class TrieNode {
public:
    bool is_end_of_word;
    TrieNode* children[CHARACTERS_SIZE];
    std::string examples = "";

    TrieNode() {
        is_end_of_word = false;
        for (int i = 0; i < CHARACTERS_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
// private:
//     TrieNode* root;

public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void Add(const std::string& word, const std::string& example) {        
        TrieNode* current = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int index;
            if (std::isupper(ch)) {
                index = ch - 'A';
            } else if (std::islower(ch)) {
                index = ch - 'a' + 26;
            }

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->is_end_of_word = true;

        if (example != "") {
            current->examples = example;            
        }
    }

    // time is the priority
    void Remove_t(const std::string& word) {
        TrieNode* current = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int index;
            if (std::isupper(ch)) {
                index = ch - 'A';
            } else if (std::islower(ch)) {
                index = ch - 'a' + 26;
            }

            if (current->children[index] == nullptr) {
                return;
            }
            current = current->children[index];
        }
        current->is_end_of_word = false; 
        current->examples = "";     
    }

    // memory is the priority
    // Returns true if root has no children, else false
    bool isEmpty(TrieNode* root) {
        for (int i = 0; i < CHARACTERS_SIZE; i++)
            if (root->children[i] != nullptr) {
                return false;
            }  
        return true;
    }
    
    // Recursive function to delete a word from given Trie
    TrieNode* Remove_m(TrieNode* root, std::string word, int depth = 0) {
        if (root == nullptr) {
            return nullptr;
        }

        if (depth == word.size()) {
            if (root->is_end_of_word) {
                root->is_end_of_word = false;
            }
            if (isEmpty(root)) {
                delete (root);
                root = nullptr;
            }
            return root;
        }
    
        char ch = word[depth];
        int index = 0;
        if (std::isupper(ch)) {
            index = ch - 'A';
        } else if (std::islower(ch)) {
            index = ch - 'a' + 26;
        }
        root->children[index] = Remove_m(root->children[index], word, depth + 1);
    
        if (isEmpty(root) && root->is_end_of_word == false) {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    bool CheckWordExistence (const std::string& word) const {
        TrieNode* current = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int index;
            if (std::isupper(ch)) {
                index = ch - 'A';
            } else if (std::islower(ch)) {
                index = ch - 'a' + 26;
            }

            current = current->children[index];
            if (current == nullptr) {                
                return false;
            }
        }
        if (current->is_end_of_word) {
            return true;
        } else {
            return false;
        }
    }

    TrieNode* SearchVocabularyPos(const std::string& word) const {
        TrieNode* current = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int index;
            if (std::isupper(ch)) {
                index = ch - 'A';
            } else if (std::islower(ch)) {
                index = ch - 'a' + 26;
            }

            current = current->children[index];
            if (current == nullptr) {                
                return nullptr;
            }
        }
        if (current->is_end_of_word) {
            return current;
        } else { 
            return nullptr;
        }
    }

    std::string& SearchVocabulary(const std::string& word) const {
        TrieNode* pos = SearchVocabularyPos(word);

        return pos->examples;    
    }

//     // function to check if current node is leaf node or not
//     bool isLeafNode(struct TrieNode* root)
//     {
//         for (int i = 0; i < CHARACTERS_SIZE; i++) {
//             if (root->children[i] != nullptr) {
//                 return false;
//             }
//         }
//         return true;
//     }

//     // function to display the content of Trie
//     void display(TrieNode* root, char str[], int level)
//     {
//         // If node is leaf node, it indicates end
//         // of string, so a null character is added
//         // and string is displayed
//         if (isLeafNode(root))
//         {
//             str[level] = '\0';
//             std::cout << str << std::endl;
//         }
    
//         int i;
//         for (i = 0; i < CHARACTERS_SIZE; i++)
//         {
//             // if NON NULL child is found
//             // add parent key to str and
//             // call the display function recursively
//             // for child node
//             if (root->children[i])
//             {
//                 str[level] = i + 'a';
//                 display(root->children[i], str, level + 1);
//             }
//         }
//     }
};

void AddService_trie(Trie& trie) {
    std::cout << "------------------------------------" << std::endl;

    bool want_to_stop = false;
    std::string want_to_stop_input = "";

    while (!want_to_stop) {
        std::string target;
        std::cout << "What vocabulary do you want to add?" << std::endl;
        std::cin >> target;

        if (trie.CheckWordExistence(target) == true) {
            std::cout << "Word already exists!!!" << std::endl;
            break;
        }

        //Allow to add one example now.
        std::cout << "Please type the example here..." << std::endl;
        std::string example = "";
        std::cin.get();
        std::getline(std::cin, example);

        // auto start = std::chrono::high_resolution_clock::now();
        trie.Add(target, example);
        // auto stop = std::chrono::high_resolution_clock::now();

        // auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        // std::cout << "Add(Trie): " << durationSearch.count() << "ns" << std::endl;   

        while (true) {
            std::cout << "Do you want to continue adding?(y/n)" << std::endl;
            std::cin >> want_to_stop_input;
            if (want_to_stop_input == "n") {
                want_to_stop = true;
                break;
            } else if (want_to_stop_input == "y") {
                break;
            }
        }
    }

    std::cout << "------------------------------------" << std::endl;

    return;
}
 
//fast but the memory will not be reduced
void RemoveService_trie(Trie& trie) {
    std::cout << "------------------------------------" << std::endl;

    bool want_to_stop = false;
    std::string want_to_stop_input = "";

    while (!want_to_stop) {
        std::string target;
        std::cout << "What vocabulary do you want to remove?" << std::endl;
        std::cin >> target;

        if (trie.CheckWordExistence(target) == false) {
            std::cout << "Word doesn't exist!!!" << std::endl;
            break;
        } else {
            // auto start = std::chrono::high_resolution_clock::now();

            trie.Remove_t(target);

            // auto stop = std::chrono::high_resolution_clock::now();

            // auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            // std::cout << "Remove(Trie): " << durationSearch.count() << "ns" << std::endl;     
        }

        while (true) {
            std::cout << "Do you want to continue removing?(y/n)" << std::endl;
            std::cin >> want_to_stop_input;
            if (want_to_stop_input == "n") {
                want_to_stop = true;
                break;
            } else if (want_to_stop_input == "y") {
                break;
            }
        }
    }

    std::cout << "------------------------------------" << std::endl;

    return;
}

void SearchService_trie(const Trie& trie) {
    std::cout << "------------------------------------" << std::endl;

    std::string target;
    std::cout << "What vocabulary do you want to search?" << std::endl;
    std::cin >> target;

    if (trie.CheckWordExistence(target) == false) {
        std::cout << "No match!" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        return;
    }

    // auto start = std::chrono::high_resolution_clock::now();

    std::string& examples = trie.SearchVocabulary(target);
    
    // auto stop = std::chrono::high_resolution_clock::now();

    // auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // std::cout << "Search(Trie): " << durationSearch.count() << "ns" << std::endl;   

    std::cout << "Vocabulary: " << target << std::endl; 
    if (examples == "") {
        std::cout << "No examples available." << std::endl;
    } else {
        std::cout << "Example: " << std::endl; 
        std::cout << examples << std::endl;
    }
    
    std::cout << "------------------------------------" << std::endl;
 
    return;
}

// Function to read a vocabulary file and build a Trie
void BuildTrieFromVocabularyFile(const std::string& filename, Trie& trie) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    std::string word = "";
    std::string example = "";
    while (std::getline(inputFile, word)) {
        // Skip empty or malformed lines
        if(word == "") {
            continue;
        }

        // Insert the vocabulary into the Trie
        trie.Add(word, example);
    }

    inputFile.close();
}

void RemoveTrieDemo(const std::string& filename, Trie& trie) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    std::string word = "";
    std::string example = "";
    while (std::getline(inputFile, word)) {
        // Skip empty or malformed lines
        if(word == "") {
            continue;
        }
        std::getline(inputFile, example);
        // std::cout << word << std::endl;

//        trie.Remove_t(word);
        trie.Remove_m(trie.root, word, 0);
    }

    // for (int i = 0; i < CHARACTERS_SIZE; i++) {
    //     if (trie.root->children[i] != nullptr) {
    //         delete trie.root->children[i];
    //         trie.root->children[i] = nullptr;
    //     } 
    // }
    
    // if (trie.isEmpty(trie.root)) {
    //     std::cout << "SUCCESSFULLY REMOVED THE VOCABULARY FROM THE TRIE!!" << std::endl;
    // }

    inputFile.close();
}

void SearchTrieDemo(const std::string& filename, Trie& trie) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    std::string word = "";
    std::string example = "";
    while (std::getline(inputFile, word)) {
        // Skip empty or malformed lines
        if(word == "") {
            continue;
        }
        trie.SearchVocabularyPos(word);
    //     if (trie.SearchVocabularyPos(word)) {
    //         std::cout << word << "serrched!!" << std::endl;
    //     }
    }

    inputFile.close();
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class SetElement {
public: 
    std::string vocabulary = "";
    std::string examples = "";

    // Overloading the equality operator
    bool operator==(const SetElement& other) const {
        return vocabulary == other.vocabulary;
    }
    bool operator>(const SetElement& other) const {
        return vocabulary > other.vocabulary;
    }  
    bool operator<(const SetElement& other) const {
        return vocabulary < other.vocabulary;
    }      
};

void AddService_set(std::set<SetElement>& set) {
    std::cout << "------------------------------------" << std::endl;

    bool want_to_stop = false;
    std::string want_to_stop_input = "";

    while (!want_to_stop) {
        SetElement target;
        std::cout << "What vocabulary do you want to add?" << std::endl;
        std::cin >> target.vocabulary;

        if (set.find(target) != set.end()) {
            std::cout << "Word already exists!!!" << std::endl;
            break;
        }

        //Allow to add one example now.
        std::cout << "Please type the example here..." << std::endl;
        std::cin.get();
        std::getline(std::cin, target.examples);

        // auto start = std::chrono::high_resolution_clock::now();
        set.insert(target);
        // auto stop = std::chrono::high_resolution_clock::now();

        // auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        // std::cout << "Add(Set): " << durationSearch.count() << "ns" << std::endl;       

        while (true) {
            std::cout << "Do you want to continue adding?(y/n)" << std::endl;
            std::cin >> want_to_stop_input;
            if (want_to_stop_input == "n") {
                want_to_stop = true;
                break;
            } else if (want_to_stop_input == "y") {
                break;
            }
        }
    }

    std::cout << "------------------------------------" << std::endl;

    return;
}

//fast but the memory will not be reduced
void RemoveService_set(std::set<SetElement>& set) {
    std::cout << "------------------------------------" << std::endl;

    bool want_to_stop = false;
    std::string want_to_stop_input = "";

    while (!want_to_stop) {
        SetElement target;
        std::cout << "What vocabulary do you want to remove?" << std::endl;
        std::cin >> target.vocabulary;

        if (set.find(target) == set.end()) {
            std::cout << "Word doesn't exist!!!" << std::endl;
            break;
        } else {
            // auto start = std::chrono::high_resolution_clock::now();

            set.erase(set.find(target));

            // auto stop = std::chrono::high_resolution_clock::now();

            // auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            // std::cout << "Remove(Set): " << durationSearch.count() << "ns" << std::endl;              
        }

        while (true) {
            std::cout << "Do you want to continue removing?(y/n)" << std::endl;
            std::cin >> want_to_stop_input;
            if (want_to_stop_input == "n") {
                want_to_stop = true;
                break;
            } else if (want_to_stop_input == "y") {
                break;
            }
        }
    }

    std::cout << "------------------------------------" << std::endl;

    return;
}

void SearchService_set(const std::set<SetElement>& set) {
    std::cout << "------------------------------------" << std::endl;

    SetElement target;
    std::cout << "What vocabulary do you want to search?" << std::endl;
    std::cin >> target.vocabulary;

    if (set.find(target) == set.end()) {
            std::cout << "No match!" << std::endl;
            return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string examples = (set.find(target))->examples;
    auto stop = std::chrono::high_resolution_clock::now();

    auto durationSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Search(Set): " << durationSearch.count() << "ns" << std::endl;   

    std::cout << "Vocabulary: " << target.vocabulary << std::endl; 
    if (examples == "") {
        std::cout << "No examples available." << std::endl;
    } else {
        std::cout << "Example: " << std::endl; 
        std::cout << examples << std::endl;
    }
    
    std::cout << "------------------------------------" << std::endl;
 
    return;
}

// Function to read a vocabulary file and build a Set
void BuildSetFromVocabularyFile(const std::string& filename, std::set<SetElement>& set) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    SetElement word;
    while (std::getline(inputFile, word.vocabulary)) {
        // Skip empty or malformed lines
        if(word.vocabulary == "") {
            continue;
        }
        // std::getline(inputFile, word.examples);
        // std::cout << word.vocabulary << word.examples << std::endl;

        // Insert the vocabulary into the Trie
        set.insert(word);
    }

    inputFile.close();
}

void RemoveSetDemo(const std::string& filename, std::set<SetElement>& set) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    SetElement word;
    while (std::getline(inputFile, word.vocabulary)) {
        // Skip empty or malformed lines
        if(word.vocabulary == "") {
            continue;
        }
        std::getline(inputFile, word.examples);
        // std::cout << word.vocabulary << std::endl;
        
        auto it = set.find(word);
        if (it != set.end()) {
            set.erase(it); 
        }           
    }

    // if (set.size() == 0) {
    //     std::cout << "SUCCESSFULLY REMOVED THE VOCABULARY FROM THE SET!!" << std::endl;
    // }

    inputFile.close();
}

void SearchSetDemo(const std::string& filename, std::set<SetElement>& set) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open vocabulary file: " << filename << std::endl;
        return;
    }

    SetElement word;
    while (std::getline(inputFile, word.vocabulary)) {
        // Skip empty or malformed lines
        if(word.vocabulary == "") {
            continue;
        }
        auto tem = set.find(word);
    }

    inputFile.close();
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void AddService(Trie& trie, std::set<SetElement>& set) {
    std::cout << "------------------------------------" << std::endl;

    bool want_to_stop = false;
    std::string want_to_stop_input = "";

    while (!want_to_stop) {
        SetElement target;
        std::cout << "What vocabulary do you want to add?" << std::endl;
        std::cin >> target.vocabulary;

        if (trie.CheckWordExistence(target.vocabulary) == true) {
            std::cout << "Word already exists!!!(trie)" << std::endl;
            break;
        }

        if (set.find(target) != set.end()) {
            std::cout << "Word already exists!!!(set)" << std::endl;
            break;
        }

        while (true) {
            //Allow to add one example now.
            std::cout << "Do you want to add examples?(y/n)" << std::endl;
            std::string answer;
            std::cin >> answer;
            if (answer == "y") {
                std::cout << "Please type the example here..." << std::endl;
                std::cin.get();
                std::getline(std::cin, target.examples);

                auto start1 = std::chrono::high_resolution_clock::now();
                trie.Add(target.vocabulary, target.examples);
                auto stop1 = std::chrono::high_resolution_clock::now();

                auto durationSearch1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
                std::cout << "Add:(trie) " << durationSearch1.count() << "ns" << std::endl;   

                auto start2 = std::chrono::high_resolution_clock::now();
                set.insert(target);
                auto stop2 = std::chrono::high_resolution_clock::now();

                auto durationSearch2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
                std::cout << "Add:(set) " << durationSearch2.count() << "ns" << std::endl; 

                break;
            } else if (answer == "n") {
                auto start1 = std::chrono::high_resolution_clock::now();
                trie.Add(target.vocabulary, target.examples);
                auto stop1 = std::chrono::high_resolution_clock::now();

                auto durationSearch1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
                std::cout << "Add:(trie) " << durationSearch1.count() << "ns" << std::endl;

                auto start2 = std::chrono::high_resolution_clock::now();
                set.insert(target);
                auto stop2 = std::chrono::high_resolution_clock::now();

                auto durationSearch2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
                std::cout << "Add(set): " << durationSearch2.count() << "ns" << std::endl;      

                break;
            }            
        }

        while (true) {
            std::cout << "Do you want to continue adding?(y/n)" << std::endl;
            std::cin >> want_to_stop_input;
            if (want_to_stop_input == "n") {
                want_to_stop = true;
                break;
            } else if (want_to_stop_input == "y") {
                break;
            }
        }
    }

    std::cout << "------------------------------------" << std::endl;

    return;   
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

int main() {
    Trie trie;
    std::set<SetElement> set;  

   // Read a vocabulary file and convert it to a trie
   auto start1 = std::chrono::high_resolution_clock::now();

   BuildTrieFromVocabularyFile("dictionary_inorder_short.txt", trie);

   auto stop1 = std::chrono::high_resolution_clock::now();

   // Read a vocabulary file and convert it to a set
   auto start2 = std::chrono::high_resolution_clock::now();

   BuildSetFromVocabularyFile("dictionary_inorder_short.txt", set);

   auto stop2 = std::chrono::high_resolution_clock::now();

   auto durationSearch1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
   std::cout << "BuildTrieFromVocabularyFile: " << durationSearch1.count() << "ms" << std::endl; 

   auto durationSearch2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
   std::cout << "BuildSetFromVocabularyFile: " << durationSearch2.count() << "ms" << std::endl;

   // Search the elements in a trie
   start1 = std::chrono::high_resolution_clock::now();

   SearchTrieDemo("dictionary_inorder_short.txt", trie);

   stop1 = std::chrono::high_resolution_clock::now();

   // Search the elements in a set
   start2 = std::chrono::high_resolution_clock::now();

   SearchSetDemo("dictionary_inorder_short.txt", set);

   stop2 = std::chrono::high_resolution_clock::now();

   durationSearch1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
   std::cout << "SearchTrieDemo: " << durationSearch1.count() << "ms" << std::endl; 
   
   durationSearch2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
   std::cout << "SearchSetDemo: " << durationSearch2.count() << "ms" << std::endl; 

   // Remove the elements in a trie
   start1 = std::chrono::high_resolution_clock::now();

   RemoveTrieDemo("dictionary_inorder_short.txt", trie);

   stop1 = std::chrono::high_resolution_clock::now();

       // for (int i = 0; i < CHARACTERS_SIZE; i++) {
       //     if (curr->children[i] != nullptr) {
       //         if (0 <= i && i <= 25) {
       //             std::cout << static_cast<char>(i + 97) << " ";
       //         } else {
       //             std::cout << static_cast<char>(i + 65) << " ";
       //         }
       //     }
       // } 

   // Remove the elements in a set
   start2 = std::chrono::high_resolution_clock::now();

   RemoveSetDemo("dictionary_inorder_short.txt", set);

   stop2 = std::chrono::high_resolution_clock::now();

   durationSearch1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
   std::cout << "RemoveTrieDemo: " << durationSearch1.count() << "ms" << std::endl; 

   durationSearch2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
   std::cout << "RemoveSetDemo: " << durationSearch2.count() << "ms" << std::endl; 

    trie.Add("love", "We're no stranges to love.");

   std::string choice = "";
   while (true) {
       std::cout << "What do you want to do?(0:Exit 1:Add 2:Remove 3:Search)" << std::endl;
       std::cin >> choice;

       if (choice == "0") {
           break;
       } else if (choice == "1") {
           // AddService(trie, set);
           AddService_trie(trie);
       } else if (choice == "2") {
           // RemoveService(trie, set) ;
           RemoveService_trie(trie);
       } else if (choice == "3") {
           // SearchService(trie, set);
           SearchService_trie(trie);
       }
   }
    return 0;
}



