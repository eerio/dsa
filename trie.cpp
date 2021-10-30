#include<string>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

class TrieNode {
  public:
    TrieNode *parent;
    map<char, TrieNode *> children;

    void insert(string word) {
      TrieNode *node = this;

      cout << "insert word: " << word << endl;
      for (char c: word) {
        cout << "insert letter: " << c << ' ' << endl;
        node = node->children[c];
      }

      // node->children.insert(pair<char, TrieNode *>('\0', new TrieNode));
      node->children['\0'];
    }

    TrieNode *get_subtree(string word) {
      TrieNode *node = this;

      for (char c: word) {
        if (!node->children.count(c)) return NULL;
        node = node->children[c];
      }

      return node;
    }

    string get_word() {
      TrieNode *node = this;
      vector<char> v;
      
      v.push_back(node->key);

      while (node = node->parent) {
        v.push_back(node->key);
      }

      string str (v.begin(), v.end());
      return str;
    }
};


int main() {
  TrieNode sjp;

  sjp.insert_iter("sponiewierac");
  sjp.insert_iter("sponiewierany");
  sjp.insert_iter("spokojny");


  TrieNode *with_prefix = sjp.get_subtree("spo");
  for (auto word : with_prefix->get_children()) {
    cout << word->get_word() << endl;
  }

  with_prefix = sjp.get_subtree("sponie");
  for (auto word : with_prefix->get_children()) {
    cout << word->get_word() << endl;
  }

  return 0;
}

