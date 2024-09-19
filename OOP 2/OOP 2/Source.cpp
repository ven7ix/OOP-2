#include <iostream>
#include <queue>

class node {
	int _info;
	node* _left;
	node* _right;
	node* _parent;

public:
	node(int data) : _info(data), _left(nullptr), _right(nullptr), _parent(nullptr) {}
	
	node* treeAdd(node* v, int data) {
		if (!v) {
			node* v = new node(data);
			return v;
		}
		if (data > v->_info) {
			v->_right = treeAdd(v->_right, data);
			v->_right->_parent = v;
		}
		else {
			v->_left = treeAdd(v->_left, data);
			v->_left->_parent = v;
		}
		return v;
	}

private:
	void printWidth(node* v) {
		std::queue <node*> queue;
		if (!v) return;
		queue.push(v);
		while (!queue.empty()) {
			node* current = queue.front();
			queue.pop();
			std::cout << current->_info << " ";
			if (current->_left) queue.push(current->_left);
			if (current->_right) queue.push(current->_right);
		}

	}

	void printDepth(node* v) {
		if (!v) return;
		std::cout << v->_info << " ";
		printDepth(v->_left);
		printDepth(v->_right);
	}

public:
	void printTree(node* v, bool choice) {
		if (choice) printWidth(v);
		else printDepth(v);
		std::cout << "\n";
	}

private:
	void treeDelete(node* &v) {
		if (!v) return;
		treeDelete(v->_left);
		treeDelete(v->_right);
		delete(v);
		v = nullptr;
	}

public:
	void treeDeleteNode(node* &v, int elementData) {
		std::queue <node*> queue;
		if (!v) return;
		queue.push(v);
		while (!queue.empty()) {
			node* current = queue.front();
			queue.pop();
			//удаление
			if (current->_info == elementData) {
				if (!current->_parent) {
					treeDelete(v);
				}
				else {
					if (current->_parent->_left && current->_parent->_left->_info == elementData) {
						current->_parent->_left = nullptr;
					}
					else {
						current->_parent->_right = nullptr;
					}
					treeDelete(current);
				}
				return;
			}
			//конец удаления
			if (current->_left) queue.push(current->_left);
			if (current->_right) queue.push(current->_right);
		}
	}

	node* treeFind(node* v, int elementData) { 
		//if (!v) return nullptr;
		//if (v->_info == elementData) {
		//	/*while (v) {
		//		std::cout << v->_info << " ";
		//		v = v->_parent;
		//	}*/
		//}
		//treeFind(v->_left, elementData);
		//treeFind(v->_right, elementData);
		std::queue <node*> queue;
		if (!v) return nullptr;
		queue.push(v);
		while (!queue.empty()) {
			node* current = queue.front();
			queue.pop();
			//поиск элемента
			if (current->_info == elementData) return current;
			//конец поиска
			if (current->_left) queue.push(current->_left);
			if (current->_right) queue.push(current->_right);
		}
		return nullptr;
	}
};

int main() {
	const int n = 5;
	int treeElements[n] = { 4,8,2,9,-12 };

	node* v = new node(10);
	for (int i = 0; i < n; i++) v = v->treeAdd(v, treeElements[i]);

	v->printTree(v, true);
}