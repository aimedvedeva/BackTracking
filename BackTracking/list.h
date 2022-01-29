#pragma once

typedef struct tag_list {
	struct tag_list *Next;
	int data;
}list;

void DestroyList(list *listHead);
void Add(list *listHead, int data);