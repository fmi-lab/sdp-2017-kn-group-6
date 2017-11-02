#include<iostream>
#include<functional>
#include<vector>
#include<queue>
template<typename T>
struct TreeNode {
	T data;
	std::vector<TreeNode<T>* > children;
};

template<typename T>
class Tree {
	TreeNode<T>* root;
	void copyTree(TreeNode<T>*&,TreeNode<T>*);
	void deleteTree(TreeNode<T>*&);
public:
	Tree(TreeNode<T>*);
	Tree();
	Tree(const Tree<T>&);
	~Tree();
	Tree& operator=(const Tree<T>&);
	void addHelper(TreeNode<T>*&, const T&);
	void add(const T&);
	void printHelper(TreeNode<T>*);
	void print() ;
	int heightHelper(TreeNode<T>*);
	int height() ;
	//std::vector<T> listLeaves();
	//std::string findTrace(const T&);
	//std::vector<T> level(int);
};
template<typename T>
Tree<T>::Tree(TreeNode<T>* _root) {
	root = _root;
}
template<typename T>
Tree<T>::Tree() :root(nullptr) {}

template<typename T>
Tree<T>::Tree(const Tree<T>& other) {
	copyTree(root, other.root);
}
template<typename T>
Tree<T>::~Tree() {
	deleteTree(root);
}
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
	if (this != &other) {
		deleteTree(root);
		copyTree(root, other.root);
	}
	return *this;
}
template<typename T>
void Tree<T>::copyTree(TreeNode<T>*& _root,TreeNode<T>* toCopy) {
	_root = nullptr;
	if (toCopy) {
		_root = new TreeNode<T>;
		_root->data = toCopy->data;

		for (int i = 0; i < toCopy->children.size(); i++) {
			_root->children.push_back(nullptr);
			copyTree(_root->children[i], toCopy->children[i]);
		}
	}
}
template<typename T>
void Tree<T>::deleteTree(TreeNode<T>*& _root) {
	if (_root) {
		for (int i = 0; i < _root->children.size(); i++) {
			deleteTree(_root->children[i]);
		}
		delete _root;
		_root = nullptr;
	}
}
template<typename T>
void Tree<T>::printHelper(TreeNode<T>*_root) {
	if (_root) {
		std::cout << _root->data << " ";
		for (TreeNode<T>* elem : _root->children) {
			printHelper(elem);
		}
	}
}
template<typename T>
void Tree<T>::print(){
	printHelper(root);
}
template<typename T>
int Tree<T>::heightHelper(TreeNode<T>* _root) {
	if (!_root) return 0;
	std::priority_queue<int, std::vector<int>, std::less<int>> maxHeight;
	for (TreeNode<T>* child : _root->children) {
		maxHeight.push(heightHelper(child));
	}
	if (maxHeight.empty()) return 1;
	return 1 + maxHeight.top();
}
template<typename T>
int Tree<T>::height(){
	return heightHelper(root);
}
template<typename T>
void Tree<T>::addHelper(TreeNode<T>*& _root, const T& elem) {
	if (!_root) {
		_root = new TreeNode<T>;
		_root->data = elem;
	}
	else {
		//и до тук с идеите
	}
}
template<typename T>
void Tree<T>::add(const T& elem) {
	addHelper(root, elem);
}
int main() {
	TreeNode<int>* root = new TreeNode<int>;
	root->data = 10;
	TreeNode<int>* tr1 = new TreeNode<int>;
	tr1->data = 2;
	root->children.push_back(tr1);
	TreeNode<int>* tr2 = new TreeNode<int>;
	tr2->data = 3;
	root->children.push_back(tr2);
	TreeNode<int>* tr3 = new TreeNode<int>;
	tr3->data = 4;
	root->children.push_back(tr3);
	TreeNode<int>* tr4 = new TreeNode<int>;
	tr4->data = 5;
	root->children[0]->children.push_back(tr4);
	Tree<int> t(root);
	t.print();
	std::cout << std::endl;
	std::cout<<t.height();
	std::cout << std::endl;
	Tree<int> t2(t);
	t2.print();
	int a;
	std::cin >> a;
	return 0;
}