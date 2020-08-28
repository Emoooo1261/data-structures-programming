#ifndef DLIST_HPP
#define DLIST_HPP

using namespace std;

template <typename T>
struct DListElement {
	T data;
	DListElement<T> *prev;
	DListElement<T> *next;
};

template <typename T>
class DList {
private:
	DListElement<T> *start;
	DListElement<T> *end;
	DListElement<T> *currentS;
	DListElement<T> *currentE;
	void deleteList();
	void copyList(DList<T> const &);
public:
	DList();
	DList(DList<T> const &);
	DList& operator= (DList<T> const &);
	~DList();
	void iterStart(DListElement<T> *elemPtr = NULL);
	DListElement<T>* iterNext();
	void iterEnd(DListElement<T> *elemPtr = NULL);
	DListElement<T>* iterPrev();
	void setStart();
	void setEnd();
	void insertToEnd(T const &);
	void deleteElem(DListElement<T>*, T &);
	void print();
	void print_reverse();
	int length(); //може да бъде const (разглеждаме дословно реализацията)
	void delElemtAtPos(int);
};
// Конструктор по подразбиране
template
<typename T>
DList<T>::DList() {
	start = NULL;
	end = NULL;
}
// Деструктор
template <typename T>
DList<T>::~DList() {
	deleteList();
}
// Конструктор за копиране
template <typename T>
DList<T>::DList(DList<T> const & list) {
	copyList(list);
}
// Оператор =
template <typename T>
DList<T>& DList<T>::operator=(DList<T> const & list) {
	if (this != &list) {
		deleteList();
		copyList(list);
	}
	return *this;
}
// Изтриване на списък
template <typename T>
void DList<T>::deleteList() {
	DListElement<T> *elemPtr;
	while (start) {
		elemPtr = start;
		start = start->next;
		delete elemPtr;
	}
	end = NULL;
}
// Копиране на елементите на списък
template <typename T>
void DList<T>::copyList(DList<T> const & list) {
	start = end = NULL;
	if (list.start) {
		DListElement<T> *elemPtr = list.start;
		while (elemPtr) {
			insertToEnd(elemPtr->data);
			elemPtr = elemPtr->next;
		}
	}
}
template <typename T>
void DList<T>::iterStart(DListElement<T> *elemPtr) {
	if (elemPtr) {
		currentS = elemPtr;
	}
	else {
		currentS = start;
	}
}
template <typename T>
DListElement<T>* DList<T>::iterNext() {
	DListElement<T> *temp = currentS;
	if (currentS) {
		currentS = currentS->next;
	}
	return temp;
}
template <typename T>
void DList<T>::iterEnd(DListElement<T> *elemPtr) {
	if (elemPtr) {
		currentE = elemPtr;
	}
	else {
		currentE = end;
	}
}
template <typename T>
DListElement<T>* DList<T>::iterPrev() {
	DListElement<T> *temp = currentE;
	if (currentE) {
		currentE = currentE->prev;
	}
	return temp;
}
template <typename T>
void DList<T>::insertToEnd(T const & x) {
	DListElement<T> *newElemPtr = new DListElement<T>;
	newElemPtr->data = x;
	newElemPtr->next = NULL;
	if (end) {
		end->next = newElemPtr;
	}
	else {
		start = newElemPtr;
	}
	newElemPtr->prev = end;
	end = newElemPtr;
}
template <typename T>
void DList<T>::deleteElem(DListElement<T> *delElemPtr, T & x) {
	x = delElemPtr->data;
	if (start == end) {
		start = NULL;
		end = NULL;
	}
	else if (delElemPtr == start) {
		start = start->next;
		start->prev = NULL;
	}
	else if (delElemPtr == end) {
		end = delElemPtr->prev;
		end->next = NULL;
	}
	else {
		delElemPtr->prev->next = delElemPtr->next;
		delElemPtr->next->prev = delElemPtr->prev;
	}
	delete delElemPtr;
}
template <typename T>
void DList<T>::print() {
	DListElement<T>* elemPtr = start;
	while (elemPtr) {
		cout << elemPtr->data << " ";
		elemPtr = elemPtr->next;
	}
	cout << endl;
}
template <typename T>
void DList<T>::print_reverse() {
	DListElement<T>* elemPtr = end;
	while (elemPtr) {
		cout << elemPtr->data << " ";
		elemPtr = elemPtr->prev;
	}
	cout << endl;
}
template <typename T>
int DList<T>::length() {
	int n = 0;
	DListElement<T>* elemPtr = start;
	while (elemPtr) {
		n++;
		elemPtr = elemPtr->next;
	}
	return n;
}
template <typename T>
void DList<T>::delElemtAtPos(int num) {
	if (length() < num) {
		return;
	}
	if (num == 0) {
		DListElement<T>* temp = start;
		start = start->next;
		start->prev = nullptr;
		currentS = start;
		temp->next = nullptr;
		delete temp;
		return;
	}
	if (num == length()) {
		DListElement<T>* temp = end;
		end = end->prev;
		end->next = nullptr;
		currentE = end;
		temp->prev = nullptr;
		delete temp;
		return;
	}
	DListElement<T>* curr = start;
	for (int i = 0; i < num; ++i) {
		curr = curr->next;
	}

	DListElement<T>* next = curr->next;
	curr->next = nullptr;
	DListElement<T>* prev = curr->prev;
	curr->prev = nullptr;
	prev->next = next;
	next->prev = prev;
	delete curr;


}
template <typename T>
void DList<T>::setStart() {
	while (start->prev) {
		start = start->prev;
	}
}
template <typename T>
void DList<T>::setEnd() {
	while (end->next) {
		end = end->next;
	}
}

#endif // !DLIST_HPP
