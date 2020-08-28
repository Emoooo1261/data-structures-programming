#include <iostream>
#include <fstream>
#include "DList.hpp"

using namespace std;

void swapNodes(DListElement<int>* left, DListElement<int>* right) { //Function that swaps two nodes, left and right are next to each other
	DListElement<int>* tempNext = right->next; //Save the right->next node
	DListElement<int>* tempPrev = left->prev;  //And the left->prev node
	left->next = right->next;
	right->next = left;
	right->prev = left->prev;
	left->prev = right;
	if (tempNext) { //If it's the end of the list the last node is NULL and cannot point back to the previous node 
		tempNext->prev = left;
	}
	if (tempPrev) { //If it's the beginning of the list the left node of the first one is NULL and cannot point back to it
		tempPrev->next = right;
	}
}

void sortCocktailStyle(DList<int>& dl) {
	dl.iterStart();
	DListElement<int>* curr = dl.iterNext();

	bool sorted = true;
	int size = dl.length();
	if (size < 2) { //If there is only 1 node, or less, there is no need to sort
		return;
	}

	do {
		sorted = true; //Bool variable that starts as true and if it doesn't get changed after a whole 
						//traversal of the list, then the list is sorted

		while(curr->next) { //Traverse the list all the way to the right
			if (curr->data > curr->next->data) { //Check if left node's data is > right node's data
				swapNodes(curr, curr->next); //Swap them if true
				sorted = false; //And the list will need another whole traversal without swapping for it to be sorted
			}
			else {
				curr = curr->next; //Else go to the right node
			}
		}
		if (sorted) { //If the list was traversed and no nodes were swapped then it is sorted
			break;
		}
		sorted = true; //Reset the bool, so if the reversed traverse doesn't change anything, the list is sorted

		while(curr->prev) { //Now the traverse starts on the right and goes to left, basically doing the same thing
			if (curr->prev->data > curr->data) { //Check if left node's data is > right node's data
				swapNodes(curr->prev, curr); //Swap them if true
				sorted = false; //The list wasn't sorted
			}
			else {
				curr = curr->prev; //Else go to the left node
			}
		}
	} while (!sorted);

	dl.setStart(); //Methods that I added to the DList.hpp that fix the "start" and "end" pointers
	dl.setEnd(); //Because after swapping the start and end still point to the same nodes
}

int main() {
	
	ifstream inLinkedListFileStream("LList.txt");

	if (!inLinkedListFileStream.is_open()) {
		throw std::runtime_error("Couldn't open file!");
	}

	DList<int> listElements;
	int temp;
	while (inLinkedListFileStream >> temp) {
		listElements.insertToEnd(temp);
	}
	inLinkedListFileStream.close();

	listElements.print();
	sortCocktailStyle(listElements);
	listElements.print();

	return 0;
}