#include <fstream>

#include <iostream>

#include <vector>



using namespace std;



namespace BSTree {



	enum order{direct, symmetric, back};

	template <class T>

	struct Node {

		T data;

		Node<T> *left;

		Node<T> *right;

		Node<T> *parent;

	};

	template <class T>

	class Tree {

		private:

			Node<T>* root;

			auto insert(Node<T>*& root,Node<T>*& parent,T value) -> Node<T>*;

			auto insert(Node<T>*& root,Node<T>*& parent,Node<T>*& value) -> Node<T>*;

			auto show(Node<T>* root,T stage) const -> void;

			auto show(Node<T>* root,std::ostream& os,T stage) const -> void;

			auto delete_tree(Node<T> *&node) -> void;

			auto direct_bypass(Node<T>* root,std::vector<T>& numbers_array) const -> void;

			auto direct_bypass(Node<T>* root, std::ofstream &fout) const -> void;

			auto symmetric_bypass(Node<T>* root,std::vector<T>& numbers_array) const -> void;

			auto back_bypass(Node<T>* root,std::vector<T>& numbers_array) const -> void;

			auto delete_node(Node<T> *&root,T value) -> bool;

		public:

			Tree();

			Tree(std::initializer_list<T> list);

			Tree(const Tree<T>& tree);

			auto exists(T value) ->bool;

			auto insert(T value) -> bool;

			auto delete_node(T value) -> bool;

			auto save_to_file(const std::string& path) -> bool;

			auto load_from_file(const std::string& path)-> bool;

			auto version_bypass(order) const -> void;

			template <class T2>

			auto friend operator<<(std::ostream& os,const Tree<T2>& tr) -> std::ostream&;

			auto operator=(const Tree<T>&) -> Tree<T>&;

			~Tree();

	};



template <class T>

Tree<T>::Tree(): root(nullptr) {};

template <class T>

Tree<T>::Tree(std::initializer_list<T> list) {

	root = nullptr;

	for(auto i : list)

		insert(root, root, i);

}

template <class T>

Tree<T>::Tree(const Tree<T>& tree) {

	root = nullptr;

	vector<int> numbers_array;

	direct_bypass(tree.root, numbers_array);

	for(int i = 0; i < numbers_array.size(); i++)

		insert(numbers_array[i]);

}

template <class T>

auto Tree<T>::show(Node<T>* root, ostream& os, T stage) const -> void {

	if (root->left != nullptr)

		show(root->left, os, stage + 1);

	if (root != this->root) {

		os.width(stage * 4);

		os << "--";

	}

	os << "(" << root->data << ")" << endl;

	if (root->right != nullptr)

		show(root->right, os, stage + 1);

}



template <class T>

auto Tree<T>::exists(T value) -> bool {

	if(!root) {

		cout << "tree is empty" << endl;

		return false;

	} else if(root) {

		Node<T>*current = root;

		while(current != nullptr) {

			if(value < current->data) {

				current = current->right;

			} else if(value > current->data) {

				current = current->left;

			} else if(current->data == value) {

				break;

			}

		}

		if(current == nullptr){

			cout << "item not found" << endl;

			return false;

		}else{

			cout << "item found" << endl;

			return true;

		}

	}

}

template <class T>

auto Tree<T>::insert(Node<T>*& root, Node<T>*& parent, T value) -> Node<T>* {

	if (root == nullptr) {

		root = new Node<T> {value, nullptr, nullptr, nullptr};

		if(root != this->root)

			root->parent = parent;

	} else {

		if (root->data < value) {

			root->left = insert(root->left, root, value);

		} else if (root->data > value) {

			root->right = insert(root->right, root, value);

		} else if(root -> data == value) {

			cout<<"tree is have this node"<<endl;

			return root;

		}

	}

	return root;

}

template <class T>

auto Tree<T>::insert(Node<T>*& root,Node<T>*& parent,Node<T>*& value) -> Node<T>* {

	if (root == nullptr) {

		root = value;

		if(root != this->root)

			root->parent = parent;

	} else {

		if (root->data < value->data) {

			root->left = insert(root->left, root, value);

		} else if (root->data > value->data) {

			root->right = insert(root->right, root, value);

		}

	}

	return root;

}



template <class T>

auto Tree<T>::insert(T value) -> bool {

	insert(root, root, value);

}



template <class T>

auto Tree<T>::direct_bypass(Node<T>* root, vector<T>& numbers_array) const -> void {

	if (root != nullptr) {

		numbers_array.push_back(root->data);

		direct_bypass(root->right, numbers_array);

		direct_bypass(root->left, numbers_array);

	}

}

template <class T>

auto Tree<T>::direct_bypass(Node<T>* root, ofstream &fout) const -> void {

	if (root != nullptr) {

		fout << root->data << " ";

		direct_bypass(root->right, fout);

		direct_bypass(root->left, fout);

	}

}

template <class T>

auto Tree<T>::symmetric_bypass(Node<T>* root, vector<T>& numbers_array) const -> void {

	if (root != nullptr) {

		symmetric_bypass(root->right, numbers_array);

		numbers_array.push_back(root->data);

		symmetric_bypass(root->left, numbers_array);

	}

	return;

}

template <class T>

auto Tree<T>::back_bypass(Node<T>* root, vector<T>& numbers_array) const -> void {

	if (root != nullptr) {

		back_bypass(root->left, numbers_array);

		back_bypass(root->right, numbers_array);

		numbers_array.push_back(root->data);

	}

}

template <class T>

auto Tree<T>::version_bypass(order ch) const -> void {

	vector<T> numbers_array;

	switch (ch) {

		case direct:

			direct_bypass(root, numbers_array);

			break;

		case symmetric:

			symmetric_bypass(root, numbers_array);

			break;

		case back:

			back_bypass(root, numbers_array);

			break;

	}

	for(int i = 0; i < numbers_array.size(); i++)

		cout << numbers_array[i] << " ";

}

template <class T>

auto Tree<T>::delete_tree(Node<T>*&node) -> void {

	if(node != nullptr) {

		delete_tree(node->left);

		delete_tree(node->right);

		delete node;

		node = nullptr;

	}

}

template <class T>

auto Tree<T>::delete_node(Node<T>*&root, T value) ->bool {

	if(!root) {

		cout << "tree is empty" << endl;

		return false;

	} else if(root) {

		Node<T>* current = root;

		while(current != nullptr) {

			if(value < current->data) {

				current = current->right;

			} else if(value > current->data) {

				current = current->left;

			} else if(current->data == value)

				break;

		}

		if(current == nullptr) {

			cout << "item not found" << endl;

			return false;

		}

		Node<T>* left = nullptr;

		Node<T>* right = nullptr;

		if(current == root) {

			root = current->right;

			insert(root, root, current->left);

			delete current;

			cout << "deleted successfully" << endl;

			return true;

		} else {

			if(current->right != nullptr && current->left == nullptr) {

				if(current == current->parent->left)

					current->parent->left = nullptr;

				else

					current->parent->right = nullptr;

				right = current->right;

				insert(root, root, right);

			} else if(current->left != nullptr && current->right == nullptr) {

				if(current == current->parent->left)

					current->parent->left = nullptr;

				else

					current->parent->right = nullptr;

				left = current->left;

				insert(root, root, left);

			} else if(current->right != nullptr && current->left != nullptr) {

				left = current->left;

				right = current->right;

				if(current == current->parent->left)

					current->parent->left = nullptr;

				else

					current->parent->right = nullptr;

				insert(root, root, left);

				insert(root, root, right);

			} else {

				if(current == current->parent->left)

					current->parent->left = nullptr;

				if(current == current->parent->right)

					current->parent->right = nullptr;

			}

			delete current;

			cout<<"deleted successfully"<<endl;

			return true;

		}

	}

}

template <class T>

auto Tree<T>::save_to_file(const std::string& path) -> bool {

	ofstream fout(path.c_str());

	if(!fout.is_open() || root == nullptr) {

		cout << "ERROR:file cant open or tree is empty" << endl;

		return false;

	}

	direct_bypass(root, fout);

	return true;



}

template <class T>

auto Tree<T>::load_from_file(const std::string& path)-> bool {

	ifstream fin(path.c_str());

	if (!fin.is_open()) {

		cout << "file cant open";

		return false;

	}

	if(root) {

		delete_tree(root);

	}

	int value;

	while(fin >> value) {

		insert(value);

	}

	return true;

}

	template <class T2>

	auto operator<<(std::ostream& os, const Tree<T2>& tr) -> std::ostream& {

		if(tr.root) {

			tr.show(tr.root, os, 1);

			return os;

		} else{

			os << "tree is empty" << endl;

			return os;

		}

	}

template <class T>

auto Tree<T>::operator=(const Tree<T>& tree) -> Tree<T>& {

	if(root != nullptr)

		delete_tree(root);

	vector<int> numbers_array;

	direct_bypass(tree.root, numbers_array);

	for(int i = 0; i < numbers_array.size(); i++)

		insert(numbers_array[i]);



}

template <class T>

auto Tree<T>::delete_node(T value) -> bool {

	delete_node(root, value);

}

template <class T>

Tree<T>::~Tree() {

	delete_tree(root);

}

}
