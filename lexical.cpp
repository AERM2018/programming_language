#include <iostream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <array>
#include <map>
#include <vector>
#include <vector>
using namespace std;

ifstream readFile();
void generateTokens(ifstream file);
vector<string> split(string text, string del);
vector<string> findSpecialChars(string text);

string reservedWords[5] = {"int","do","for","while","double"};

int main(){
        generateTokens(readFile());

}

ifstream readFile(){
        string filename;
        cout << "File's name to be compiled: \n";
        cin >> filename;
        ifstream file(filename.c_str());
        return file;
}

void generateTokens(ifstream file){
        string line;
        map<string,string> tokens;
        while(getline(file,line)){
                auto words = split(line," ");
                for(const auto &word:words){
                        if( find(begin(reservedWords), end(reservedWords),word) == end(reservedWords) ){
                            auto specialChars = findSpecialChars( word );
                            for(const auto a : specialChars){
                                cout << "special--- " << a << endl;
                            }
                                // return;
                        }
                                tokens.insert({"reserved_word",word});
                        // switch (word)
                        // {
                        // default:
                        //     break;
                        // }
                }
        }
        for(auto& iter: tokens){
                cout << "< "<< iter.first << ", " << iter.second << " >"<< endl;
        }
        file.close();
}

vector<string> split(string text, string del){
        vector<string> words;
        text.append(" ");
        size_t delPos;
        while((delPos = text.find(del)) != string::npos){
                words.push_back(text.substr(0,delPos));
                text.erase(0,delPos + del.length());
        }
        return words;
}

vector<string> findSpecialChars(string text){
    vector<string> wordStruct;
    int pos = 0;
        while(size_of(text) > 0){
            switch (text[pos])
            {
                case "=":
                    wordStruct.push_back(text[pos]);
                    text.erase(pos,1);
                case ";":
                    wordStruct.push_back(text[pos]);
                    text.erase(pos,1);
            default:
                break;
            }
            pos++;
        }
        return wordStruct;
}