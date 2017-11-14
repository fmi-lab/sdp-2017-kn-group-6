TreeNode<char>* parseExpression(const std::string& s) {
	std::stack<TreeNode<char>* > symbol;

	for (char ch: s)
	{
		if (ch != ')'){
			TreeNode<char> * temp = new TreeNode<char>(ch);
			symbol.push(temp);
		}
		else {
			std::vector<TreeNode<char>* > generate;
			while (symbol.top()->data != '(') {
				generate.push_back(symbol.top());
				symbol.pop();
			}
			symbol.pop();
			TreeNode<char>* newExpr = new TreeNode<char>(generate[1]->data, generate[2], generate[0]);
			symbol.push(newExpr);
		}
		
	}
	return symbol.top();
}
