// program that accepts a string user input of words to be found in the synopsis of the top 50 anime from myanimelist.net
// returns the names of the anime where all the valid words were found
// The TOP 50 data was selected on 20/08/2025 1:02 PM EST

#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

/*
Class to store objects that will be continuously used across the program.
Also has 2 methods -- map_printer() and get_filename() that are used to:
1. print the map of all the words and indexes from all the files
2. convert the indexes of the files containing the query words into the filenames of the files

object list
Words_Indexxed::words_indexes
Words_Indexxed::filenames
Words_Indexxed::intersections_result
Words_Indexxed::stopwords
*/ 
class Words_Indexxed {
public:
    inline static std::unordered_map<std::string, std::unordered_set<int>> words_indexes = 
    {};

    inline static std::set<int> intersections_result = {};

    inline static std::vector<std::string> filenames = {};

    // list of common english words that carry littlie meaning and can be skipped
    inline static std::set<std::string> stopwords = {
    "a","about","above","after","again","against","all","am","an","and","any","are","aren’t",
    "as","at","be","because","been","before","being","below","between","both","but","by",
    "can’t","cannot","could","couldn’t","did","didn’t","do","does","doesn’t","doing","don’t",
    "down","during","each","few","for","from","further","had","hadn’t","has","hasn’t","have",
    "haven’t","having","he","he’d","he’ll","he’s","her","here","here’s","hers","herself","him",
    "himself","his","how","how’s","i","i’d","i’ll","i’m","i’ve","if","in","into","is","isn’t","it",
    "it’s","its","itself","let’s","me","more","most","mustn’t","my","myself","no","nor","not","of",
    "off","on","once","only","or","other","ought","our","ours","ourselves","out","over","own",
    "same","shan’t","she","she’d","she’ll","she’s","should","shouldn’t","so","some","such",
    "than","that","that’s","the","their","theirs","them","themselves","then","there","there’s",
    "these","they","they’d","they’ll","they’re","they’ve","this","those","through","to","too",
    "under","until","up","very","was","wasn’t","we","we’d","we’ll","we’re","we’ve","were",
    "weren’t","what","what’s","when","when’s","where","where’s","which","while","who",
    "who’s","whom","why","why’s","with","won’t","would","wouldn’t","you","you’d","you’ll",
    "you’re","you’ve","your","yours","yourself","yourselves"
    };

    static void map_printer(){
        for (auto &k : words_indexes){
        std::cout << k.first << "[";
        bool first = true;
        for (int id : k.second){
            if (!first) std::cout << ",";
            std::cout << id;
            first = false;
        }
        std::cout << "] ";
        }   
    }

    static void get_filename(){
        if (intersections_result.size() > 0){
            std::cout << "Word(s) were found in the following anime:" << std::endl;
            for (auto &k : intersections_result) std::cout << filenames[k-1] << std::endl;
        }
        else std::cout << "No match with query words was found.";
    }
};

// Porter Stemmer -> reduces words to their root forms
// Example: "running" -> "run"
// Useful because different variants of the same word can be treated as the same
std::string porter_stem(std::string& word){
    if (word.size() <= 2) return word;

    std::string w = word;
    
    // remove plurals -- ssses > ss; ies > i; remove last s
    if (w.size() > 4 && w.substr(w.length()-4) == "sss") w = w.substr(0, w.size()-2);
    else if (w.size() > 3 && w.substr(w.size()-3) == "ies") w = w.substr(0, w.size()-2);
    else if (w.size() > 2 && w.back() == 's' && w[w.size()-2] != 's') w.pop_back();

    // remove past tense "ed" and gerund "ing"
    if (w.size() > 3 && w.substr(w.size()-3) == "ing") w = w.substr(0, w.size()-3);
    else if (w.size() > 2 && w.substr(w.size()-2) == "ed") w = w.substr(0, w.size()-2);

    // turn y to i
    if (!w.empty() && w.back() == 'y') w.back() = 'i';

    return w;
}

void tokenFromFiles(){
    std::filesystem::path folder = std::filesystem::current_path() / "files";
    int docID = 1;

    for (auto& entry : std::filesystem::directory_iterator(folder)){
        if (entry.is_regular_file()){
            std::string filepath = entry.path().string();
            std::ifstream file(filepath);
            Words_Indexxed::filenames.push_back(entry.path().stem().string());

            //tokenization (turns words into tokens)
            std::string word;
            char c;

            while (file.get(c)){
                if (c != ' ' && c != '\n' && c != '\t' && c != '.' && c != ',') {
                    c = std::tolower(static_cast<unsigned char>(c));
                    word += c;
                }
                else {
                    if (!word.empty()){
                        if (Words_Indexxed::stopwords.count(word) == 0){
                            std::string stemmed = porter_stem(word);
                            Words_Indexxed::words_indexes[stemmed].insert(docID);
                            word.clear();
                        }
                        else word.clear();
                    }   
                }       
            }
                if (!word.empty()) {
                    if (Words_Indexxed::stopwords.count(word) == 0){
                        std::string stemmed = porter_stem(word);
                        Words_Indexxed::words_indexes[stemmed].insert(docID);
                    }
                }
            file.close();
            docID++;
        }
    }
}

std::vector<std::string> stringtowords(std::string& input){
    std::string word;
    std::vector<std::string> words;
    for(char& c : input){
        if (c != ' ' && c != '\n' && c != '\t' && c != '.' && c != ','){
            c = std::tolower(static_cast<unsigned char>(c));
            word += c;
        }
        else{
            if (!word.empty()){
                if (Words_Indexxed::stopwords.count(word) == 0){
                    std::string stemmed = porter_stem(word);
                    words.push_back(stemmed);
                    word.clear();
                }
                else word.clear();
            }
        }
    }
    if (!word.empty()) {
        if (Words_Indexxed::stopwords.count(word) == 0){
            std::string stemmed = porter_stem(word);
            words.push_back(stemmed);
            word.clear();
        }
    }

    return words;
}

std::set<int> intersections(std::vector<std::set<int>>& intersection_list){
    int iterations = intersection_list.size();
    std::set<int> answer = intersection_list[0];

    for (int i = 1; i < iterations; i++){
        std::set<int> temp;
        std::set_intersection(answer.begin(), answer.end(),
                            intersection_list[i].begin(), intersection_list[i].end(),
                            std::inserter(temp, temp.begin()));
        answer = temp;
        }

    return answer;
}

void complex_query(std::string& multi_word_query){
    std::vector<std::string> words = stringtowords(multi_word_query);

    std::vector<std::set<int>> answer;
    std::set<int> temp_set;

    for (std::string &word : words){
        for (auto &k : Words_Indexxed::words_indexes){
            if (k.first == word){
                for (int id : k.second) temp_set.insert(id);
            }
        }
        answer.push_back(temp_set);
        temp_set.clear();
    }

    Words_Indexxed::intersections_result = intersections(answer);
}

int main(){
    /// Opens all files, adds valid words to dictionary of [word] -> [file index] where it was found
    tokenFromFiles();

    /// Method to print the map of all the words and indexes from all the files
    ///Words_Indexxed::map_printer();

    /// Complex Query (Accepts more than 1 word) ///

    // To accept user input from terminal
    // std::string multi_word_query;
    // std::cout << "This program takes a text and tries to find if it matches text in the synopsis of the TOP 50 anime from myanimelist.net. The result will match all of the words in the text, so if none of the synopsis match all of the words in the text, nothing will return." << std::endl;
    // std::cout << "Enter text to search: ";
    // std::getline(std::cin, multi_word_query);
    // complex_query(multi_word_query);


    // To add text inside program
    std::string multi_word_query = {"titans, eren"};
    complex_query(multi_word_query);

    /// Get filenames of the files with intersection ///
    Words_Indexxed::get_filename();
}