#include <stdlib.h>
#include "list.h"


list *createElement(int data) {
	list *element = (list*)malloc(sizeof(list));
	element->Next = NULL;
	element->data = data;
	return element;
}

void destroyElement(list *element) {
	free(element);
}

void Add(list *listHead, int data) {
	list *iter = listHead;

	while (iter->Next != NULL) {
		iter = iter->Next;
	}

	list *newElement = createElement(data);
	iter->Next = newElement;

	return;
}

void DestroyList(list *listHead) {
	list *iter = listHead->Next;
	list *prevEl = NULL;

	while (iter != NULL) {
		prevEl = iter->Next;
		destroyElement(iter);
		iter = prevEl;
	}
	free(listHead);
}
