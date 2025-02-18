#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

// Random word generator
std::string generateRandomWord(int length) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static const int alphabetSize = sizeof(alphabet) - 1;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::string word;
    std::uniform_int_distribution<> dis(0, alphabetSize - 1);

    for (int i = 0; i < length; ++i) {
        word += alphabet[dis(gen)];
    }

    return word;
}

// Example sentence generator
std::string generateExampleSentence(const std::string& word) {
    // Replace this with your own logic to generate example sentences
    return "This is an example sentence for the word '" + word + "'.";
}

// Generate vocabulary and example sentences
void generateVocabulary(const std::string& filename, int numWords) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "Failed to open output file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < numWords; ++i) {
        std::string word = generateRandomWord(8); // Adjust the word length as needed
        // std::string example = generateExampleSentence(word);

        outputFile << word << std::endl;
        // outputFile << example << std::endl;
    }

    outputFile.close();
    std::cout << "Vocabulary generation complete." << std::endl;
}

int main() {
    std::string filename = "vocabulary.txt";
    int numWords = 370105; // Adjust the number of words as needed

    generateVocabulary(filename, numWords);

    return 0;
}
