#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

void FilterVocobularyByLength(const std::string& filename) {
   std::ifstream inputFile(filename);
   std::ofstream outputFile("dictionary_inorder_long.txt");  // Create a new output file
   
   if (!inputFile) {
       std::cerr << "Failed to open input file: " << filename << std::endl;
       return;
   }

   std::string line;
   while (std::getline(inputFile, line)) {
       if (line.length() > 8) {
           outputFile << line << std::endl;  // Write the line to the output file 
       }  
   }

   inputFile.close();
   outputFile.close();
}

void randomizeVocabulary(const std::string& inputFile, const std::string& outputFile) {
   // Read the input file containing vocabulary in alphabetical order
   std::ifstream input(inputFile);
   if (!input) {
       std::cerr << "Failed to open input file: " << inputFile << std::endl;
       return;
   }

   std::vector<std::string> vocabulary;
   std::string word;
   while (std::getline(input, word)) {
       vocabulary.push_back(word);
   }
   input.close();

   // Randomize the order of the vocabulary words
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::shuffle(vocabulary.begin(), vocabulary.end(), std::default_random_engine(seed));

   // Create the output file
   std::ofstream output(outputFile);
   if (!output) {
       std::cerr << "Failed to create output file: " << outputFile << std::endl;
       return;
   }

   // Write the vocabulary words in random order
   for (const auto& word : vocabulary) {
       output << word << std::endl;
   }
   output.close();

   std::cout << "Vocabulary randomized and written to " << outputFile << std::endl;
}

int main() {
   std::string filename = "dictionary_inorder_all.txt";
   FilterVocobularyByLength(filename);

//    std::string inputFile = "dictionary_inorder_all.txt";
//    std::string outputFile = "dictionary_unordered_all.txt";
//    randomizeVocabulary(inputFile, outputFile);

   return 0;
}