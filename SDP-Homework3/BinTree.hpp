#ifndef BIN_TREE_HPP
#define BIN_TREE_HPP

#include <iostream>

using namespace std;

template
<typename T>
struct node
{
	T data;
	node<T> *left, *right;
};

template <typename T>
class BinTree {
private:
	node<T> *root;
	void deleteBinTree(node<T> * &) const;
	void copy(node<T> * &, node<T> * const &) const;
	void copyBinTree(BinTree<T> const &);
	void printFromNode(const node<T> *) const;
	void createBinTree(node<T> * &) const;

public:
	BinTree();
	~BinTree();
	BinTree(BinTree<T> const &);
	BinTree& operator=(BinTree<T> const &);
	BinTree<T> leftBinTree() const;
	BinTree<T> rightBinTree() const;
	T getRootData() const;
	node<T>* getRootPtr();
	bool empty() const;
	void print() const;
	void create();
	void createWithData(T, BinTree<T>, BinTree<T>);
	void createWithRoot(node<T>*);
};

// Конструктор по подразбиране
template <typename T>
BinTree<T>::BinTree() {
	root = NULL;
}
// Деструктор
template <typename T>
BinTree<T>::~BinTree() {
	deleteBinTree(root);
}
// Конструктор за копиране
template <typename T>
BinTree<T>::BinTree(BinTree<T> const &tree) {
	copyBinTree(tree);
}
// operator =
template <typename T>
BinTree<T>& BinTree<T>::operator=(BinTree<T> const &tree) {
	if (this != &tree) {
		deleteBinTree(root);
		copyBinTree(tree);
	}
	return *this;
}
// Изтриване на двоично дърво от определен връх
template <typename T>
void BinTree<T>::deleteBinTree(node<T>* &treeRoot) const {
	if (!treeRoot) {
		return;
	}
	deleteBinTree(treeRoot->left);
	deleteBinTree(treeRoot->right);
	delete treeRoot;
	treeRoot = NULL;
}
// Копиране на двоично дърво
template <typename T>
void BinTree<T>::copyBinTree(BinTree<T> const &tree) {
	copy(root, tree.root);
}
// Копиране на дърво от даден връх
template <typename T>
void BinTree<T>::copy(node<T> * &dest, node<T>* const &src) const {
	dest = NULL;
	if (src) {
		dest = new node<T>;
		dest->data = src->data;
		copy(dest->left, src->left);
		copy(dest->right, src->right);
	}
}
template <typename T>
bool BinTree<T>::empty() const {
	return root == NULL;
}
template <typename T>
T BinTree<T>::getRootData() const {
	return root->data;
}
template <typename T>
node<T>* BinTree<T>::getRootPtr() {
	return root;
}
// Копиране на лявото поддърво
template <typename T>
BinTree<T> BinTree<T>::leftBinTree() const {
	BinTree<T> copiedTree;
	copy(copiedTree.root, root->left);
	return copiedTree;
}
// Копиране на дясното поддърво
template <typename T>
BinTree<T> BinTree<T>::rightBinTree() const {
	BinTree<T> copiedTree;
	copy(copiedTree.root, root->right);
	return copiedTree;
}
template <typename T>
void BinTree<T>::printFromNode(const node<T> *treeNode) const {
	if (!treeNode) {
		return;
	}
	printFromNode(treeNode->left);
	cout << treeNode->data << " ";
	printFromNode(treeNode->right);
}
template <typename T>
void BinTree<T>::print() const {
	printFromNode(root);
}
// Създаване на двоично дърво по корен и две поддървета
template <typename T>
void BinTree<T>::createWithData(T x, BinTree<T> left, BinTree<T> right) {
	root = new node<T>;
	root->data = x;
	copy(root->left, left.root);
	copy(root->right, right.root);
}
template <typename T>
void BinTree<T>::createBinTree(node<T>* &treeNode) const {
	T x; char c;
	cout << "root: ";
	cin >> x;
	treeNode = new node<T>;
	treeNode->data = x;
	treeNode->left = NULL;
	treeNode->right = NULL;
	cout << "left BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') {
		createBinTree(treeNode->left);
	}
	cout << "right BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') {
		createBinTree(treeNode->right);
	}
}
template <typename T>
void BinTree<T>::create() {
	createBinTree(root);
}
template <typename T>
void BinTree<T>::createWithRoot(node<T>* root) {
	this->root = root;
}

#endif // !BIN_TREE_HPP
