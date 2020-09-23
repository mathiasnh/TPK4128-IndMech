#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
	list_t list;

	list = malloc(sizeof(list));
	if (list) { //Check if malloc succeded
		list->length = 0;
	}
	printf("klarte list create\n");
	return list;
}

void list_delete(list_t list)
{
	struct node *temp_node = list->head;
	struct node *free_node;

	while(temp_node != NULL){
		free_node = temp_node;
		temp_node = free_node->next;
		free(free_node);
	}
	free(temp_node);

	free(list);
}

void list_insert(list_t list, int index, char *data)
{
	struct node *new_node = malloc(sizeof(new_node));
	new_node->data = data;
	new_node->length = sizeof(data);

	struct node *temp_node = list->head;

	for(int i = 0; i < index; i++){
		temp_node = temp_node->next;
	}

	new_node->prev = temp_node->prev;
	new_node->next = temp_node;
	temp_node->prev->next = new_node;
	temp_node->prev = new_node;

	list->length++;
}

void list_append(list_t list, char *data)
{
	struct node *node;

	node = malloc(sizeof(node));
	
	node->next = NULL;
	node->data = data;
	node->length = sizeof(data);

	if (list->length == 0){
		node->prev = NULL;
		list->head = node;
		list->tail = node;
	} else {
		if (list->length == 1){
			node->prev = list->head;
			list->head->next = node;
			list->tail = node;
		} else {
			node->prev = list->tail;
			list->tail->next = node;
			list->tail = node;
		}
		
	} 

	list->length++;

}

void list_print(list_t list)
{
	struct node *temp_node = list->head;

	while(temp_node != NULL){
		printf("%s ", temp_node->data);
		temp_node = temp_node->next;
	}
	printf("\n");
}

int list_get(list_t list, int index)
{
	struct node *temp_node = list->head;

	for(int i = 0; i < index; i++){
		temp_node = temp_node->next;
	}

	return temp_node->data;
}

int list_extract(list_t list, int index)
{
	struct node *temp_node = list->head;

	for(int i = 0; i < index; i++){
		temp_node = temp_node->next;
	}

	if(list->length == 1){
		list->head = NULL;
		list->tail = NULL;
	} else {
		if(temp_node->prev == NULL){
			
			list->head = temp_node->next;
			list->head->prev = NULL;
		} else {
			temp_node->prev->next = temp_node->next;
			temp_node->next->prev = temp_node->prev;

		}
	}

	list->length--;

	int ret = temp_node->data;

	free(temp_node);
	
	return ret;
}
