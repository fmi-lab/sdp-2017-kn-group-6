#include<iostream>
#include<stack>
#include<vector>
#include<cassert>

template<class T>
struct TreeNode {
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode(T _data, TreeNode<T>* _left = nullptr, TreeNode<T>* _right = nullptr) :data(_data), left(_left), right(_right) {}
};

template<class T>
using predType = bool(*)(TreeNode<T>*&);

//Simple iterator from lections
template<class T>
struct Task {
	TreeNode<T>* node;
	bool toPrint;
	Task(TreeNode<T>* _node, bool _print) :node(_node), toPrint(_print) {}
};

template<class T>
class LRoRIterator {
	std::stack<Task<T>> elements;
	void windStack() {
		while (!elements.empty() && elements.top().toPrint == false) {
			Task<T> currentTask = elements.top();
			elements.pop();
			if (currentTask.node->right) {
				elements.push(Task<T>(currentTask.node->right, false));
			}
			elements.push(Task<T>(currentTask.node, true));
			if (currentTask.node->left) {
				elements.push(Task<T>(currentTask.node->left, false));
			}
		}
	}
public:
	LRoRIterator(TreeNode<T>* start) {
		if (start) {
			Task<T> firstState(start, false);
			elements.push(firstState);
			windStack();
		}
	}
	void operator ++(int) {
		if (!elements.empty()) {
			elements.pop();
			windStack();
		}
	}
	T operator * () {
		return elements.top().node->data;
	}
};

// Custom iterate class 1 - same as above
template<class T>
class LRoRIterate {
public:
	void operator () (std::stack <Task<T>>& container) {
		while (!container.empty() && container.top().toPrint == false) {
			Task<T> currentTask = container.top();
			container.pop();
			if (currentTask.node->right) {
				container.push(Task<T>(currentTask.node->right, false));
			}
			container.push(Task<T>(currentTask.node, true));
			if (currentTask.node->left) {
				container.push(Task<T>(currentTask.node->left, false));
			}
		}

	}
};

//Another custom iterate class
template<class T>
class RRoLIterate {
public:
	void operator () (std::stack <Task<T>>& container) {
		while (!container.empty() && container.top().toPrint == false) {
			Task<T> currentTask = container.top();
			container.pop();
			if (currentTask.node->left) {
				container.push(Task<T>(currentTask.node->left, false));
			}
			container.push(Task<T>(currentTask.node, true));
			if (currentTask.node->right) {
				container.push(Task<T>(currentTask.node->right, false));
			}
		}
	}
};

template<class T>
class BFSIterate {
public:
	void operator () (std::stack <Task<T>>& container) {
		while (!container.empty() && container.top().toPrint == false) {
			std::vector<Task<T>> level;
			while (!container.empty()) {
				level.push_back(container.top());
				container.pop();
			}
			for (Task<T> t : level) {
				if (t.node->right) container.push(Task<T>(t.node->right, false));
				if (t.node->left) container.push(Task<T>(t.node->left, false));
			}
			for (Task<T> t : level) {
				t.toPrint = true;
				container.push(t);
			}
		}
	}
};

template<class T>
class PredicateIterate {
	predType<T> predicate;
public:
	PredicateIterate(predType<T> pr) :predicate(pr) {}
	void operator () (std::stack <Task<T>>& container) {
		while (!container.empty() && container.top().toPrint == false) {
			Task<T> currentTask = container.top();
			container.pop();
			if (currentTask.node->right) container.push(Task<T>(currentTask.node->right, false));
			if (predicate(currentTask.node)) container.push(Task<T>(currentTask.node, true));
			if (currentTask.node->left) container.push(Task<T>(currentTask.node->left, false));
		}
	}
};

//Our custom iterator
template<class T, class iterate > // iterate defines the iterate class
class Iterator {
	std::stack<Task<T>> elements;
	iterate unwind;

	void windStack() {
		unwind(elements);
	}
public:


	Iterator(TreeNode<T>* start) {
		assert(start);
		Task<T> firstState(start, false);
		elements.push(firstState);
		windStack();
	}
	Iterator(TreeNode<T>* start, predType<T> pred):unwind(pred) {
		assert(start);
		Task<T> firstState(start, false);
		elements.push(firstState);
		windStack();
	}
	void operator ++(int) {
		assert(!elements.empty());
		elements.pop();
		windStack();
	}
	T operator * () {
		assert(!elements.empty());
		return elements.top().node->data;
	}
};



template<class T>
class BTree {
	TreeNode<T>* root;
public:
	BTree() :root(nullptr) {}
	void addBOT(const T&);
	void addHelp(TreeNode<T>*&, const T&);
	void printLRoR();
	void printHelp(TreeNode<T>*&);

	template<class iterate>
	Iterator<T, iterate> begin();
	template<class iterate>
	Iterator<T, iterate> begin(predType<T>);

};

template<class T>
void BTree<T>::addHelp(TreeNode<T>*& _root, const T & elem)
{
	if (_root) {
		if (elem <= _root->data) addHelp(_root->left, elem);
		else addHelp(_root->right, elem);
	}
	else {
		_root = new TreeNode<T>(elem);
	}
}

template<class T>
void BTree<T>::printLRoR()
{
	printHelp(root);
}

template<class T>
void BTree<T>::printHelp(TreeNode<T>*& _root)
{
	if (_root) {
		printHelp(_root->left);
		std::cout << _root->data;
		printHelp(_root->right);
	}
}

template<class T>
template<class iterate>
Iterator<T, iterate> BTree<T>::begin()
{
	return Iterator<T, iterate>(root);
}

template<class T>
template<class iterate>
Iterator<T, iterate> BTree<T>::begin(predType<T> pred)
{
	return Iterator<T, iterate>(root,pred);
}

template<class T>
void BTree<T>::addBOT(const T& elem) {
	addHelp(root, elem);
}

template<class T>
bool isOdd(TreeNode<T>*& elem)
{
	return elem->data % 2 != 0;
}

template<class T>
bool isLeaf(TreeNode<T>*& elem) {
	return (elem->left == nullptr) && (elem->right == nullptr);
}

int main() {
	BTree<int> tree;
	tree.addBOT(5);
	tree.addBOT(23);
	tree.addBOT(13);
	tree.addBOT(1);
	tree.addBOT(2);
	tree.addBOT(3);
	tree.printLRoR();
	std::cout << '\n';
	Iterator<int, PredicateIterate<int>> it = tree.begin<PredicateIterate<int>>(isOdd);
	std::cout << *it;
	it++;
	std::cout << '\n';
	std::cout << *it;
	it++;
	std::cout << '\n';
	std::cout << *it;
	it++;
	std::cout << '\n';
	std::cout << *it;
	it++;
	std::cout << '\n';
	std::cout << *it;
	//Assert will fail below
	/*it++;
	std::cout << '\n';
	std::cout << *it;*/
	int a;
	std::cin >> a;
	return 0;
}
