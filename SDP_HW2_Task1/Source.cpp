#include <iostream>

using namespace std;

struct ListNode {
	int data;
	ListNode* next;
};

void printNode(ListNode* start) {
	if (!start) {
		return;
	}
	ListNode* curr = start;

	while (curr) {
		cout << curr->data << ' ';
		curr = curr->next;
	}
	cout << endl;
}

bool containsCycle(ListNode* start) {
	if (!start) {
		return 0;
	}
	ListNode* slow = start; //two iterators pointing to the start
	ListNode* fast = start;

	while (fast->next) {
		if (fast->next->next == nullptr) {
			return false;
		}
		fast = fast->next->next; //the fast iterator goes to the next->next
		slow = slow->next; //and the slow iterator goes through the whole node 1 by 1
		if (fast == slow) { //if they meet there is a cycle
			return true;
		}
	}
	return false; //if the node has ended then there isn't a cycle
}


int main() {
	ListNode* empty = new ListNode();
	empty->data = 0;
	empty->next = nullptr;
	cout << containsCycle(empty) << ' '; //Empty node

	ListNode* start1 = new ListNode();
	start1->data = 1;
	ListNode* curr1 = start1;

	for (int i = 2; i < 5; ++i) {
		curr1->next = new ListNode();
		curr1 = curr1->next;
		curr1->data = i;
	}
	curr1->next = nullptr; 
	
//	printNode(start1);
	cout << containsCycle(start1) << ' '; //Not cycling node



	ListNode* start2 = new ListNode();
	start2->data = 1;
	ListNode* curr2 = start2;

	for (int i = 2; i < 5; ++i) {
		curr2->next = new ListNode();
		curr2 = curr2->next;
		curr2->data = i;
	}
	curr2->next = start2; 

	//printNode(start2);
	cout << containsCycle(start2) << ' '; //Cycle with the last node pointing to the first one



	ListNode* start3 = new ListNode();
	start3->data = 1;
	ListNode* curr3 = start3;

	ListNode* temp = new ListNode();

	for (int i = 2; i < 5; ++i) {
		curr3->next = new ListNode();
		curr3 = curr3->next;
		curr3->data = i;
		if (i == 3) {
			temp = curr3;
		}
	}
	curr3->next = temp; 

	//printNode(start3);
	cout << containsCycle(start3) << ' '; //Cycle with the last node pointing to the third one



	ListNode* start4 = new ListNode();
	start4->data = 1;
	ListNode* curr4 = start4;

	for (int i = 2; i < 512; ++i) {
		curr4->next = new ListNode();
		curr4 = curr4->next;
		curr4->data = i;
		if (i == 4) {
			temp = curr4;
		}
	}
	curr4->next = temp; 

	
	cout << containsCycle(start4) << endl; //Cycle with the last (511) node pointing to the fourth one
	//printNode(start4);
}