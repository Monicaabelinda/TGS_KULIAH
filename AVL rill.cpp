#include<iostream>
#include<algorithm>
using namespace std;

struct node
{
	int data;
	struct node *right;
	struct node *left;
}*root;

class Avltree {
	public:
		int height(node *);
		int difference(node *);
		node *rr_rotation(node *);
		node *ll_rotation(node *);
		node *lr_rotation(node *);
		node *rl_rotation(node *);
		void tampilkan(node *, int);
		void inorder(node *);
		void preorder(node *);
		void postorder(node *);
		node* balance(node *);
		node* insert(node *, int);
		node* nilaiMax(node*);
		node* nilaiMin(node*);
		node* remove(node* x, int z);
		Avltree(){
		root = NULL;
	}
};

// menentukan height

int Avltree::height(node *temp)
{
	int a = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		a = max_height + 1;
	}
	return a;
}

// untuk Difference

int Avltree :: difference(node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int balance_factor = l_height - r_height;
	return balance_factor;
}

/*
* Right- Right Rotation
*/
node *Avltree :: rr_rotation(node *parent)
{
	node *temp;
	temp = parent->right;
	parent -> right = temp -> left;
	temp -> left = parent;
	return temp;
}
/*
* Left- Left Rotation
*/
node *Avltree :: ll_rotation(node *parent)
{
	node *temp;
	temp = parent -> left;
	parent -> left = temp -> right;
	temp -> right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
node *Avltree :: lr_rotation(node *parent)
{
	node *temp;
	temp = parent -> left;
	parent -> left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
* Right- Left Rotation
*/
node *Avltree :: rl_rotation(node *parent)
{
	node *temp;
	temp = parent -> right;
	parent -> right = ll_rotation(temp);
	return rr_rotation(parent);
}

// insert data

node *Avltree :: insert(node *root, int nilai)
{
	if (root == NULL)
	{
		root = new node;
		root -> data = nilai;
		root -> left = NULL;
		root -> right = NULL;
		return root;
	}
	else if (nilai < root -> data)
	{
		root -> left = insert(root -> left, nilai);
		root = balance(root);
	}
	else if (nilai >= root -> data)
	{
		root -> right = insert(root -> right, nilai);
		root = balance(root);
	}
	return root;
}

// balance tree

node *Avltree :: balance(node *temp){
	
	int ballance_factor = difference(temp);
	if (ballance_factor > 1)
	{	
		if (difference(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (ballance_factor < -1)
	{
		if (difference(temp -> right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

// tampilan avl tree

void Avltree::tampilkan(node *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		tampilkan(ptr -> right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr -> data;
		tampilkan(ptr -> left, level + 1);
	}
}

void Avltree :: preorder(node *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}

// PreOrder AVL Tree

node* Avltree :: nilaiMin(node* t) {
	if (t == NULL) return NULL;
	else if (t -> left == NULL) return t; 
	else return nilaiMin(t -> left);
}
node* Avltree :: nilaiMax(node* t) {
	if (t == NULL) return NULL;
	else if (t -> right == NULL) return t;
	else return nilaiMax(t -> right);
}

// InOrder AVl Tree

void Avltree :: inorder(node *tree)
{
	if (tree == NULL)
		return;
	inorder(tree -> left);
	cout << tree -> data << "  ";
	inorder(tree -> right);
}

//	PostOrder AVL Tree

void Avltree :: postorder(node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree -> left);
	postorder(tree -> right);
	cout << tree -> data << "  ";
}
node* Avltree :: remove(node* t, int x){
	node* temp;
	if (t == NULL) return NULL;
	else if (x < t->data) t->left = remove(t->left, x);
	else if (x >t->data) t->right = remove(t->right, x);

	else if (t -> left && t -> right) {
		temp = nilaiMin(t->right);
		t -> data = temp->data;
		t -> right = remove(t -> right, t -> data);
	}
	else {
		temp = t;
		if (t -> left == NULL) t = t -> right;
		else if (t -> right == NULL) t = t -> left;
		delete temp;
	}
	if (t == NULL) return t;
	t = balance(t);
}

int main()
{
	int pil, angka;
	Avltree avl;
	while (1)
	{
		cout << "\n-----------------------------" << endl;
		cout << "\tProgram AVL Tree" << endl;
		cout << "\n-----------------------------" << endl;
		cout << "1.Masukkan Data ke dalam Tree" << endl;
		cout << "2.Hapus data pada Tree" << endl;
		cout << "3.Tampilkan data AVL Tree" << endl;
		cout << "4.PreOrder Traversal" << endl;
		cout << "5.InOrder traversal" << endl;
		cout << "6.PostOrder traversal" << endl;
		cout << "7.Exit" << endl;
		cout << "Masukkan Pilihan anda : ";
		cin >> pil;
		switch (pil){
			case 1:
				cout << "Masukkan Nilai : ";
				cin >> angka;
				root = avl.insert(root, angka);
				break;
			case 2:
				cout << "Masukkan Nilai yang ingin dihapus : ";
				cin >> angka;
				root = avl.remove(root, angka);
				break;
			case 3:
				if (root == NULL)
				{
					cout << "Tree Masih Kosong !!" << endl;
					continue;
				}
				cout << "Balanced AVL Tree:" << endl;
				avl.tampilkan (root, 1);
				break;
			case 4:
				cout << "Preorder Traversal:" << endl;
				avl.preorder(root);
				cout << endl;
				break;
			case 5:
				cout << "Inorder Traversal:" << endl;
				avl.inorder(root);
				cout << endl;
				break;
			case 6:
				cout << "Postorder Traversal:" << endl;
				avl.postorder(root);
				cout << endl;
				break;
			case 7:
				cout << "Program Selesai !!" << endl;
				exit(1);
				break;
			default:
				cout << "Pilihan tidak tersedia" <<endl;
		}
	}
	return 0;
}
