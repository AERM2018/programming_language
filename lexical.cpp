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
void generateTokensForLine(string text);
string getType(string part);

string reservedWords[] = {"int","string","do","for","while","double"};

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
        vector<string> tokens;
        while(getline(file,line)){
                auto words = split(line," ");
                for(const auto &word:words){
                        if( find(begin(reservedWords), end(reservedWords),word) == end(reservedWords) ){
                            generateTokensForLine( word );
                        }
                        tokens.push_back("< "+getType(word)+">");
                        // switch (word)
                        // {
                        // default:
                        //     break;
                        // }
                }
        }
        for(auto iter: tokens){
                cout << iter << endl;
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

void generateTokensForLine(string text){
        vector<string> tokens;
        int pos = 0;
        string strOrNum = "";
        while(pos < size(text)){
                 char letter = text[pos];
                 switch (letter)  
                 {
                     case '=':
                        if(text.substr(0,pos)!=""){
                             tokens.push_back("<id, "+text.substr(0,pos)+">");
                        }
                             tokens.push_back("<assignation, "+text.substr(pos,pos)+">");
                             text.erase(0,pos + 1);
                             pos = 0;
                             break;
                     case ';':
                     
                             tokens.push_back("<"+getType(text.substr(0,pos))+">");
                             tokens.push_back("<del, "+text.substr(pos,pos)+">");
                             text.erase(0,pos + 1);
                             pos = 0;
                             break;
                     default:
                        if(pos == size(text) - 1){
                                tokens.push_back("<"+getType(text)+">");
                        }
                        //  if(getType(letter)){
                        //         string str(1,letter);
                        //         strOrNum.append(str);
                        //         char nextChar = text[pos + 1];
                        //         if(!getType(nextChar)){
                        //                 tokens.insert({text.substr(0,pos),"number"});
                        //                 text.erase(0,pos + 1); 
                        //                 pos = 0;
                        //         }
                        //  }
                         break;
                 }
                pos++;
        }
        for(auto iter: tokens){
                 cout << iter << endl;
         }
}

string getType(string part){
        string partStr;
        string possibleNums[] = {"0","1","2","3","4","5","6","7","8","9","."};
        string booleans[] = {"true","false"};
        if(find(begin(reservedWords), end(reservedWords),part) != end(reservedWords)) return "reserved_word, " + part;
        if(find(begin(booleans), end(booleans),part) != end(booleans)) return "bool, " + part;
        for(int i=0;i<size(part);i++){
                partStr = part[i];
                if(find(begin(possibleNums), end(possibleNums),partStr) == end(possibleNums)) i = size(part);
                if(i == size(part) - 1) return "number, " + part;
        }
        if(part[0] == '"'){
                if(part[size(part) - 1] == '"') return "string, " + part;
                return "invalid, " + part;
        }
        return "id, "+part;
        return "invalid, " + part;
}