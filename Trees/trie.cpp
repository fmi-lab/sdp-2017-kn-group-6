#include <iostream>
#include <queue>
#include <cassert>
#include <list>
using namespace std;
struct Node {
	Node* parent;
	Node* children[26];
	bool end;
	int value;
	Node(Node* _parent = NULL, bool _end = false, int _value = -1) : parent(_parent), end(_end), value(_value) {
		for (int i = 0; i < 26; i++) children[i] = NULL;
	}
};
class Trie {
	Node*root;
	void copy(Node*&_root, Node*other, Node*parent) {
		_root = nullptr;
		if (other == nullptr) return;
		_root = new Node(parent, other->end, other->value);
		for (int i = 0; i < 26; i++) {
			if (other->children[i]) {
				_root->children[i] = new Node(_root, other->children[i]->end, other->children[i]->value);
				copy(_root->children[i], other->children[i], _root);
			}
			else _root->children[i] = nullptr;
		}
	}
	void printHelp(Node*_root, list<char>ls) {
		if (_root->end) {
			list<char>copy = ls;
			while (!copy.empty()) {
				cout << copy.front();
				copy.pop_front();
			}
			cout << endl;
		}
		for (int i = 0; i < 26; i++) {
			if (_root->children[i]) {
				ls.push_back((char)(i + 'a'));
				printHelp(_root->children[i], ls);
				ls.pop_back();
			}
		}
	}
public:
	void del(Node*&_root) {
		if (_root == nullptr) return;
		for (int i = 0; i < 26; i++)
		{
			if (_root->children[i])
				del(_root->children[i]);
		}
		delete _root;
		_root = nullptr;
	}
	Trie() {
		root = new Node();
	}
	Trie(const Trie&other) {
		copy(root, other.root, nullptr);
	}
	~Trie() {
		del(root);
	}
	Trie&operator=(const Trie&other) {
		if (this != &other) {
			del(root);
			copy(root, other.root, nullptr);
		}
		return *this;
	}
	Node*&getRoot() {
		return root;
	}
	bool member(const char* str) {
		if (root == NULL) return false;
		int i = 0, size = strlen(str), index = 0;
		Node*curr = root;
		while (i < size) {
			index = str[i] - 'a';
			if (curr->children[index] == NULL) return false;
			curr = curr->children[index];
			i++;
		}
		return curr->end;
	}
	int&operator[](const char* str) {
		int i = 0, size = strlen(str), index = 0;
		Node*curr = root;
		while (i < size) {
			index = str[i] - 'a';
			if (curr->children[index] == NULL) curr->children[index] = new Node(curr,false,-1);
			curr = curr->children[index];
			i++;
		}
		curr->end = true;
		return curr->value;
	}
	void print() {
		if (numberOfChildren(root)==0) cout << "There is nothig to print.\n";
		else {
			list<char>ls;
			printHelp(root, ls);
		}
	}
	Node*getEndOfWord(const char*str) {
		if (!member(str)) return NULL;
		int i = 0, size = strlen(str);
		Node*curr = root;
		for (int i = 0; i < size; i++) {
			curr = curr->children[str[i] - 'a'];
		}
		return curr;
	}
	int numberOfChildren(Node*p) {
		if (p == nullptr) return 0;
		int numberOfChildren = 0;
		for (int i = 0; i < 26; i++) {
			if (p->children[i]) numberOfChildren++;
		}
		return numberOfChildren;
	}
	int remove(const char* str)
	{
		if (!member(str)) { cout << "This word doesn't belong to the trie.\n"; return -1; }
		Node* curr = getEndOfWord(str);
		int result = curr->value;
		if (numberOfChildren(curr) > 0)
		{
			curr->end = false;
			curr->value = -1;
		}
		else {
			Node*fd;
			int i = strlen(str) - 1;
			do {
				fd = curr;
				curr = curr->parent;
				delete fd;
				curr->children[str[i] - 'a'] = NULL;
				i--;
			} while (curr->end == false && numberOfChildren(curr)==0 && curr!=root);
		}
		return result;
	}
};
int main() {
	Trie tree;
	tree["prejudice"] = 1;
	tree["cocoa"] = 2;
	tree["ocoa"] = 3;
	tree["coa"] = 4;
	tree["oa"] = 5;
	tree["a"] = 6;
	tree["co"] = 7;
	cout << "All words:\n";
	tree.print();
	tree.remove("co");
	cout << "Without co:\n";
	tree.print();
	cout<<tree.remove("coa")<<endl;
	cout << "Without coa:\n";
	tree.print();
	cout << tree.remove("ocoa") << endl;
	cout << "Without ocoa:\n";
	tree.print();
	cout << tree.remove("a") << endl;
	cout << "Without a:\n";
	tree.print();
	cout << tree.remove("oa") << endl;
	cout << "Without oa:\n";
	tree.print();
	cout << tree.remove("cocoa") << endl;
	cout << "Without cocoa:\n";
	tree.print();
	system("pause");
	return 0;
}