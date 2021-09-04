#include "DoubleLinkedList.h"

void DLL::put(StockItem* item, int value) {
	ListNode* newNode = createNewNode(item, value);
	ListNode* last = head;

	if (head == NULL) {
		head = tail = newNode;
		return;
	}

	while (last != nullptr && last->item->getName() != item->getName()) {
		last = last->next;
	}

	if (last != nullptr) {
		last->value = value;
		delete newNode;
		newNode = nullptr;
		return;
	}

	newNode->prev = tail;
	tail->next = newNode;
	tail = newNode;
}

ListNode* DLL::createNewNode(StockItem* item, int value) {
	ListNode* newNode = new ListNode;
	newNode->item = item;
	newNode->value = value;
	newNode->next = newNode->prev = nullptr;
	return newNode;
}

int DLL::get(StockItem* item) {
	ListNode* headRef = head;

	while ((headRef != nullptr) && (headRef->item->getName() != item->getName())) {
		headRef = headRef->next;
	}

	return (headRef != nullptr) ? headRef->value : 0;
}

void DLL::remove(StockItem* item) {
	if (item == nullptr)
		return;

	ListNode* current = head;

	while (current != nullptr && current->item->getName() != item->getName()) {
		current = current->next;
	}

	if (current == nullptr)
		return;

	// If node to be deleted is head node
	if (head == current) {
		head = current->next;
	}

	// Change next only if node to be deleted is NOT the last node
	if (current->next != NULL) {
		current->next->prev = current->prev;
	}

	// Change prev only if node to be deleted is NOT the head node
	if (current->prev != NULL) {
		current->prev->next = current->next;
	}

	delete current;
}

int DLL::getSize() {
	ListNode* p = head;
	int n = 0;
	while (p != nullptr) {
		p = p->next;
		n++;
	}
	return n;
}

