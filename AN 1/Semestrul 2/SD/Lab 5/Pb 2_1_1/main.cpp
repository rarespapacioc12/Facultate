// 100p - https://www.infoarena.ro/job_detail/3353358

#include <fstream>
#include <vector>

std::ifstream fin("trie.in");
std::ofstream fout("trie.out");

struct TrieNode {
    int word_count;
    int pass_count;
    std::vector<TrieNode*> children;

    TrieNode() : word_count(0), pass_count(0), children(std::vector<TrieNode*>(26, nullptr)) {}
};

class Trie{
private:
    TrieNode* root;

public:
    Trie() : root(new TrieNode()) {}

    void insert(const std::string& s){
        TrieNode* curr = root;
        for (char c : s) {
            int poz = c - 'a';
            if(curr->children[poz] == nullptr){
                curr->children[poz] = new TrieNode();
            }
            curr = curr->children[poz];
            curr->pass_count++;
        }
        curr->word_count++;
    }

    void erase(const std::string& s){
        TrieNode* curr = root;
        for(char c : s){
            int poz = c - 'a';
            curr = curr->children[poz];
            curr->pass_count--;
        }
        curr->word_count--;
    }

    int count(const std::string& s){
        TrieNode* curr = root;
        for(char c : s){
            int poz = c - 'a';
            if(curr->children[poz] == nullptr || curr->children[poz]->pass_count == 0){
                return 0;
            }
            curr = curr->children[poz];
        }
        return curr->word_count;
    }

    int longestPrefix(const std::string& s){
        TrieNode* curr = root;
        int max_len = 0;
        for (char c : s) {
            int poz = c - 'a';
            if(curr->children[poz] == nullptr || curr->children[poz]->pass_count == 0){
                break;
            }
            curr = curr->children[poz];
            max_len++;
        }
        return max_len;
    }
};

Trie trie;
int op;
std::string s;

int main(){
    while(fin >> op >> s){
        switch(op) {
            case 0:
                trie.insert(s);
                break;
            case 1:
                trie.erase(s);
                break;
            case 2:
                fout << trie.count(s) << '\n';
                break;
            case 3:
                fout << trie.longestPrefix(s) << '\n';
                break;
            default:
                break;
        }
    }
}