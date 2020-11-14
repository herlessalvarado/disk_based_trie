#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

class Trie {
public:
    Trie* letters[256];
    bool isLeaf = false;
    vector<pair<long,long> > data;
    
    Trie() {
        for(int i=0; i<256; i++){
            letters[i] = nullptr;
        }
    }
    
    void insert(string word, long begin, long end) {
        Trie* current = this;
        for(auto a : word){
            if(!current->letters[a]){
                current->letters[a] = new Trie();
            }
            current = current->letters[a];
        }
        current->isLeaf = true;
        current->data.push_back(make_pair(begin,end));
    }
    
    void search(string word) {
        vector<pair<int,int>> ans;
        Trie* current = this;
        for(auto a : word){
            if(!current->letters[a]) return;
            current = current->letters[a];
        }
        if(current->isLeaf){
          fstream file("index.txt",ios::in |ios::out );
          string data;
          for(auto a : current->data){
            file.seekg(a.first);
            getline(file,data);
            cout << data << '\n';
          }
          return;
        }else{
          return;
        }
    }
    
};

pair<string,string> getName(string s){
    int count = 0;
    for(int i=s.size()-1; i>=0; i--){
        if(s[i] == '/') break;
        count++;
    }
    return make_pair(s.substr(s.size()-count, s.size()), s.substr(0, s.size()-count));
}

int main(){
    Trie trie = Trie();
    ifstream file("index.txt");
    if (file.is_open()) {
        string line;
        long prev = 0;
        while (std::getline(file, line)) {
            pair<string,string> path = getName(line);
            string name = path.first.substr(0, path.first.size()-4);
            long begin = prev;
            long size = path.first.size();
            long end = (long)file.tellg() - size;
            prev = (long) file.tellg();
            trie.insert(name,begin,end);
        }
        file.close();
    }
    trie.search("uml 2 toolkit");
}