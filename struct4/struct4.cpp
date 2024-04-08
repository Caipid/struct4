#include <iostream>
#include <locale>
#include <fstream>

using namespace std;

struct Btree // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	Btree* left;
	Btree* right;
	Btree(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(Btree* p)
{
	return p ? p->height : 0;
}

int bfactor(Btree* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(Btree* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

Btree* rotateright(Btree* p) // правый поворот вокруг p
{
	Btree* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Btree* rotateleft(Btree* q) // левый поворот вокруг q
{
	Btree* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

Btree* balance(Btree* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

Btree* insert(Btree* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new Btree(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

Btree* findmin(Btree* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left ? findmin(p->left) : p;
}

Btree* removemin(Btree* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

Btree* remove(Btree* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else // k == p->key
	{
		Btree* q = p->left;
		Btree* r = p->right;
		delete p;
		if (!r) return q;
		Btree* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void printTree(Btree* root) {
	cout << root->key << " "; //Выводим корень дерева
	//output << root->key << " ";
	if (root->left != NULL) { //Выводим левого потомка
		cout << root->left->key << " ";
	}
	else { //Если левого потомка нет
		cout << "- ";
	}
	if (root->right != NULL) { //Выводим правого потомка
		cout << root->right->key << " ";
	}
	else { //Если правого потомка нет
		cout << "- ";
	}
	cout << endl; //Переход на поддеревья
	if (root->left != NULL) { //Если левый потомок есть, рекурсивно выводим его
		printTree(root->left);
	}
	if (root->right != NULL) { //Если правый потомок есть, рекурсивно выводим его
		printTree(root->right);
	}
}

void writeTree(Btree* root, ofstream& infile) {
	infile << root->key << " ";
	if (root->left != NULL) { //Выводим левого потомка
		infile << root->left->key << " ";
	}
	else { //Если левого потомка нет
		infile << "- ";
	}
	if (root->right != NULL) { //Выводим правого потомка
		infile << root->right->key << " ";
	}
	else { //Если правого потомка нет
		infile << "- ";
	}
	infile << endl;
	if (root->left != NULL) {
		writeTree(root->left, infile);
	}
	if (root->right != NULL) { //Если правый потомок есть, рекурсивно выводим его
		writeTree(root->right, infile);
	}
}

Btree* otbor(Btree*& root1, Btree* root2, int key) {
	if (root1 != NULL) {
		if (root1->key > key) {
			root2 = insert(root2, root1->key);
		}
		if (root1->left != nullptr) {
			root2 = otbor(root1->left, root2, key);
		}
		if (root1->right != nullptr) {
			root2 = otbor(root1->right, root2, key);
		}
		return root2;
	}
}

Btree* delet(Btree * root, Btree * root2) {
	if (root != NULL && root2 != NULL) {
		root = remove(root, root2->key);// удаление ключа k из дерева 
		if (root2->left != nullptr) {
			root = delet(root, root2->left);
		}
		if (root2->right != nullptr) {
			root = delet(root, root2->right);
		}
		
	}
	return root;
}

int main(){
	ofstream infile("input.dat");
	ofstream outfile("output.dat");
	setlocale(LC_ALL, "ru");
	Btree* root = nullptr;
	Btree* root2 = nullptr;
	root = insert(root, 50);
	root = insert(root, 68);
	root = insert(root, 42);
	root = insert(root, 27);
	root = insert(root, 44);
	root = insert(root, 12);
	root = insert(root, 8);
	root = insert(root, 70);
	root = insert(root, 60);
	root = insert(root, 77);
	cout << "Введите число для отбора узлов:";
	infile << "Введите число для отбора узлов:";
	outfile << "Введите число для отбора узлов:";
	int key;
	cin >> key;
	infile << key << endl;
	outfile << key << endl;
	cout << "Исходное дерево:" << endl;
	infile << "Исходное дерево" << endl;
	outfile << "Исходное дерево:" << endl;
	printTree(root);
	writeTree(root, infile);
	writeTree(root, outfile);
	root2 = otbor(root, root2, key);
	if (root2 == NULL) {
		cout << "Все элементы первого дерева меньше, чем заданное число";
		outfile << "Все элементы первого дерева меньше, чем заданное число";
	}
	else {
		cout << "Второе дерево созданное из чисел больше заданного числа:" << endl;
		outfile << "Второе дерево созданное из чисел больше заданного числа:" << endl;
		writeTree(root2,outfile);
		printTree(root2);
		root = delet(root, root2);
		cout << "Элементы оставщиеся в первом дереве" << endl;
		outfile << "Элементы оставщиеся в первом дереве" << endl;
		writeTree(root,outfile);
		printTree(root);
	}
}