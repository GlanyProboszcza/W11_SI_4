#include <iostream>
#include <vector>
#include <string>

struct Node {
	int value{NULL};
	Node* left{nullptr};
	Node* right{nullptr};
};

void addNode(Node& root, int value) {
	if (root.value == NULL) {
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

Node* findNode(Node& node, int x) {
	if (node.value == x) {
		return &node;
	}
	else {
		if (x < node.value && node.left != nullptr) {
			return findNode(*node.left, x);
		}
		else if (x > node.value && node.right != nullptr) {
			return findNode(*node.right, x);
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

Node* findParent(Node& node, int value) {

	if (node.left != nullptr && node.left->value == value || node.right != nullptr && node.right->value == value)
	{
		return &node;
	}
	else if ( (node.left != nullptr || node.right != nullptr) && node.value != NULL && node.value != value)
	{
		Node* temp;
		if (value < node.value) {
			temp = findParent(*node.left, value);
		}
		else {
			temp = findParent(*node.right, value);
		}
		if (temp == nullptr || (temp->right->value == value || temp->left->value == value))
			return temp;
	}
	return nullptr;
}

Node& minimumOfTheTree(Node& node) {
	if (node.left != nullptr) {
		minimumOfTheTree(*node.left);
	}
	else
		return node;
}

Node& next(Node& node, Node& root) {

	if (node.right != nullptr) {
		return minimumOfTheTree(node);
	}
	else {
		Node* helper;
		helper = findParent(root, node.value);
		while (helper != nullptr && node.value == helper->right->value) {
			node = *helper;
			helper = findParent(root, helper->value);
		}
	}
}

struct Node* removeNode(struct Node& root, int key)
{
	if (root.value == NULL)
		return &root;
	if (key < root.value)
		root.left = removeNode(*root.left, key);
	else if (key > root.value)
		root.right = removeNode(*root.right, key);
	else {
		if (root.left == NULL && root.right == NULL)
			return NULL;
		else if (root.left == NULL) {
			struct Node* temp = root.right;
			free(&root);
			return temp;
		}
		else if (root.right == NULL) {
			struct Node* temp = root.left;
			free(&root);
			return temp;
		}
		struct Node* temp = &minimumOfTheTree(*root.right);
		root.value = temp->value;
		root.right = removeNode(*root.right, temp->value);
	}
	return &root;
}

int main()
{
	//std::vector <int> unsorted{ 11,2,23,14,95,66,7,88,97 };
	std::vector <int> sorted{ 1,2,3,4,5,6,7,8,9 };
	Node root;
	sortToTree(root, sorted, 0, sorted.size() - 1);
	std::cout << "Print tree: " << std::endl;
	print2(&root,0);

	std::cout << std::endl;
	std::cout << "Find parent of 5: " << ((findParent(root, 5) != nullptr) ? std::to_string(findParent(root, 5)->value) : "Parent not found") << std::endl;
	std::cout << "Find parent of 3: " << ((findParent(root, 3) != nullptr) ? std::to_string(findParent(root, 3)->value) : "Parent not found") << std::endl;
	std::cout << "Find node of 8: " << findNode(root, 8)->value << std::endl;
	std::cout << "Find node of 18: " << ( (findNode(root, 18) != nullptr) ? std::to_string(findNode(root, 18)->value) : "Node not found" )<< std::endl;

	removeNode(root, 5);
	std::cout << "Print tree after remove 9: " << std::endl;
	print2(&root, 0);
}
