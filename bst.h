#include<iostream>
#include<vector>
#include<string>
#include <sstream>

// using namespace std;

class BST{
    public:
        BST();
        BST(int val);
        ~BST();
        BST* insertKey(BST* root, int newKey);
        bool hasKey(BST* root, int searchKey);
        void inorder(BST* root, std::vector<int>& ordered);
        int getHeight(BST* root);
        int getDepth(BST* root, int key);
    private:
        BST* left;
        BST* right;
        int data;       
        int searchKey; 
};

BST::BST(){
    data = 0;
    left = nullptr;
    right = nullptr;
}

BST::BST(int val)
{
    data = val;
    left = nullptr;
    right = nullptr;
}

BST* BST::insertKey(BST* root, int newKey)
{
    if (root == nullptr) {
		return new BST(newKey);
	}

	if (newKey > root->data) {
		root->right = insertKey(root->right, newKey);
	}
	else if (newKey < root->data){
		root->left = insertKey(root->left, newKey);
	}

	return root;
}


void BST::inorder(BST* root, std::vector<int>& ordered)
{
	if (root == nullptr) {
		return;
	}
	inorder(root->left, ordered);
    ordered.push_back(root -> data);
	inorder(root->right, ordered);
}

bool BST::hasKey(BST* root, int searchKey)
{
    while (root != nullptr) {
        if (root->data == searchKey)
            return true;
        if (root->data < searchKey)
        {
            root = root->right;
        }
        else 
        {
            root = root->left;
        } 
    }
    return false;
}

int BST::getDepth(BST* root, int key)
{
    int count = 0;
    while (root != nullptr) {
        if (root->data == key)
            break;
        if (root->data < key)
            {root = root->right;
            count += 1;}
        else 
            {root = root->left;
            count += 1;} 
    }
    return count;
}

int BST::getHeight(BST* root) {
    if (root == NULL) 
        return 0;
    else {
        int left_height = getHeight(root->left);
        int right_height = getHeight(root->right);
        return std::max(left_height, right_height) + 1;
}
}

BST::~BST(){
    delete right;
    delete left;
}
