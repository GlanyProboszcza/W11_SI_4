#include <iostream>
#include <vector>

struct Node {
	int value{-1};
	Node* left{nullptr};
	Node* right{nullptr};
};

void addNode(Node& root, int value) {
	if (root.value == -1) {
		root.value = value;
	}
	else if (root.value > value) {
			if(root.left == nullptr)
				root.left = new Node;
			addNode(*root.left, value);
	}
	else {
		if (root.right == nullptr)
			root.right = new Node;
		addNode(*root.right, value);
	}
}

Node* findNode(Node* node, int x) {
	if (node->value == x) {
		return node;
	}
	else {
		if (x < node->value && node->left != nullptr) {
			return findNode(node->left, x);
		}
		else if (x > node->value && node->right != nullptr) {
			return findNode(node->right, x);
		}
		else
			return nullptr;
	}
};

void print(Node* root) {
	if (root->left != nullptr)
		print(root->left);
	std::cout << root->value << "\t";
	if (root->right != nullptr)
		print(root->right);

}

void print2(Node* root, int x) {
	if (root->left != nullptr)
		print2(root->left,x+1);
	for (int i = 0; i < x; i++) {
		std::cout << "\t";
	}
	std::cout << root->value << "\n";
	if (root->right != nullptr)
		print2(root->right, x+1);
}

void sortToTree(Node& root, std::vector <int> sorted, int low, int high) {
	
	if (low <= high) {
		int median;
		median = (low + high) / 2;
		addNode(root, sorted[median]);
		sortToTree(root, sorted, low, median - 1);
		sortToTree(root, sorted, median + 1, high);
	}
}

int main()
{
	//std::vector <int> unsorted{ 11,2,23,14,95,66,7,88,97 };
	std::vector <int> sorted{ 1,2,3,4,5,6,7,8,9 };
	Node root;
	sortToTree(root, sorted, 0, sorted.size() - 1);

	/*for (auto a : sorted) {
		addNode(root, a);
		std::cout << "\n";
	}*/
	print2(&root,0);
}
