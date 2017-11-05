template<class T>
bool BTree<T>::isLeaf(const TreeNode<T>*& elem) const {
	return elem->left == nullptr && elem->right == nullptr;
}

template<class T>
void BTree<T>::findLeaves(TreeNode<T>*& _root, std::vector<T>& container) {
	if(_root){
		if (isLeaf(_root))
		{
			container.push_back(_root->data);
			return;
		}

		findLeaves(_root->left, container);

		findLeaves(_root->right, container);
	}
}
template<class T>
bool findTrace(TreeNode<T>*&_root, std::string& trace,const T& x) {
	if (!_root) return false;
	if (_root->data == x) {
		return true;
	}
	if (!findTrace(_root->left, trace.push_back('L'), x)) {
		trace.pop_back();
		if (!findTrace(_root->right, trace.push_back('R'), x)) {
			trace.pop_back();
			return false;
		}
	}
	return true;
}
template<class T>
std::vector<T> BTree<T>::findLeavesBFS(TreeNode<T>*& _root) {
	std::queue<TreeNode<T> *> q;
	std::vector<T> leaves;
	if (_root == nullptr) return leaves;
	q.push(_root);
	TreeNode<T> *temp;
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		if (isLeaf(temp))
		{
			leaves.push_back(temp->data);
		}
		else
		{
			if(temp->left)
				q.push(temp->left);
			if(temp->right)
				q.push(temp->right);
		}
	}
	return leaves;
}
template<class T>
std::vector<T> BTree<T>::listLeaves() {
	std::vector<T> result;
	findLeaves(root, result);
	return result;
}
