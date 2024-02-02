#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

std::string getFirstWord(const std::string& line) {
    size_t pos = line.find_first_not_of(" \t");
    if (pos == std::string::npos) return "";

    size_t end = line.find_first_of(" \t", pos);
    return line.substr(pos, end - pos);
}

static std::unordered_map<std::string, std::string> dictionary() {
    //unordered map to return a dictionary of words and the class type : noun, verb or pronoun
    std::unordered_map<std::string, std::string> dict;
    dict["cat"] = "noun";
    dict["dog"] = "noun";
    dict["house"] = "noun";
    dict["car"] = "noun";
    dict["job"] = "noun";
    dict["food"] = "noun";
    dict["school"] = "noun";
    dict["man"] = "noun";
    dict["woman"] = "noun";
    dict["child"] = "noun";
    dict["run"] = "verb";
    dict["work"] = "verb";
    dict["jump"] = "verb";
    dict["read"] = "verb";
    dict["stop"] = "verb";
    dict["bring"] = "verb";
    dict["sleep"] = "verb";
    dict["give"] = "verb";
    dict["turn"] = "verb";
    dict["listen"] = "verb";
    dict["hide"] = "verb";
    dict["you"] = "pronoun";
    dict["he"] = "pronoun";
    dict["she"] = "pronoun";
    dict["it"] = "pronoun";
    dict["we"] = "pronoun";
    dict["they"] = "pronoun";
    dict["me"] = "pronoun";
    dict["him"] = "pronoun";
    dict["her"] = "pronoun";
    return dict;
}

std::string matchString(std::string entry) {
    //one string var to be a temp string (keys) to add chars
    //one string var to return the category type of a word(word) 
    std::string word;
    std::string keys;
    //vector to hold matched words fromd dictionary
    std::vector<std::string> words;
    //for loop cycles through the entire first word entry from user
    for (int i = 0; i <= entry.size(); i++) {
        //checks for spaces
        if (!isspace(entry[i])) {
            keys = keys + entry[i];
        }
        else {
            keys = "";
        }
        for (auto x : dictionary()) {
            if (keys == x.first) {
                word = "\n Word: " + x.first + " " + "Category: " + x.second + "\n";
                words.push_back(word);
                //std::cout<<word;
                break;
                keys = "";
            }
            else
                word = "\n Category: external\n";
        }
    }


    for (int i = 0; i < words.size(); i++) {
        std::cout << words[i];
    }

    return word;
}

static int count(std::string str, char countChar) {
    int count = 0;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == countChar) {
            count++;
        }
    }

    return count;
}

static std::string formatString(std::string str) {
    
    

    // Removes consecutive spaces

    bool lastCharSpace = false;

    for (size_t i = 0; i < str.length(); i++)
    {
        if (std::isspace(str[i]) && !lastCharSpace)
        {
            lastCharSpace = true;
        }
        else if (std::isspace(str[i]) && lastCharSpace)
        {
            str.erase(str.begin() + i);
            i--;
        }
        else {
            lastCharSpace = false;
        }
    }

    
    /*

    base case: pdLoc == -1; return str
    1. find pound symbol - store position in pdLoc
    2. count " and ' behind it
    3. if both are even, return str.substr(0, pdLoc)
    4. if either is odd, move start up to pdLoc
    */

    int start = 0;

    while (true) {

        int pdLoc = str.find('#', start);

        if (pdLoc == std::string::npos) {
            return str;
        }
        std::string beforePd = str.substr(0, pdLoc);

        if (count(beforePd, '\'') % 2 == 0 && count(beforePd, '"') % 2 == 0) {
            return str.substr(0, pdLoc);
        }

        start = pdLoc + 1;
    }
}

int main() {
    std::vector<std::string> answer;
    std::string line, partialLine;
    bool continueLine = false;
    while (true) {
        std::cout << (continueLine ? ">>> " : "ALPHA $ ");
        std::getline(std::cin, line);

        line = formatString(line);

        if (continueLine) {
            partialLine += line;
        }
        else {
            partialLine = line;
        }

        if (!partialLine.empty() && partialLine.size() >= 2 && partialLine.back() == '\\') {
            partialLine.erase(partialLine.size() - 1); // Remove the "\n"
            continueLine = true;
            continue; // Skip the rest of the loop
        }

        continueLine = false;

        std::string firstWord = getFirstWord(partialLine);

        if (firstWord == "exit") {
            break;
        }
        std::string wordClass = matchString(line);
        std::cout << firstWord << ": " << wordClass << std::endl;
    }

}


