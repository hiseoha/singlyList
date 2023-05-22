#include <stdio.h>
#include <malloc.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct ListNode{
	element data;
	struct ListNode *link;
} ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	return;
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value; 
	p->link = pre->link; 
	pre->link = p; 
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; 
	free(removed);
}

int list_len(ListNode* head) {
	int length = 0;
	ListNode* current = head;

	while (current != NULL) {
		length++;
		current = current->link;
	}

	return length;
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

int main(void)
{
	ListNode* head = NULL;
	ListNode* pre = NULL;

	int choice, num, pos, len, count;


	while (1) {
		printf("Menu\n");
		printf("(1) Insert\n");
		printf("(2) Delete\n");
		printf("(3) Print\n");
		printf("(0) Exit\n");
		printf("Enter the menu: ");
		scanf_s("%d", &choice);

		if (choice == 1) {
			printf("Enter the number and position: ");
			scanf_s("%d %d", &num, &pos);
			len = list_len(head);
			count = 0;
			if (pos != 0 && len == 0) {
				printf("List is empty. Insert at position 0.\n");
				pos = 0;
			}
			else if (pos > len) {
				printf("The last index is %d. Insert at the end of the list.\n", len - 1);
				pos = len;
			}
			if (pos == 0)
				head = insert_first(head, num);
			else {
				pre = head;
				for (int i = 0; i < pos - 1; i++) {
					pre = pre->link;
					count++;
				}
				head = insert(head, pre, num);
				count++;
			}
			printf("\nMove along the link: %d\n", count);
		}
		else if (choice == 2) {
			if (head == NULL) {
				printf("List is empty.\n");
			}
			else {
				count = 0;
				len = list_len(head);
				printf("Enter the position to delete: ");
				scanf_s("%d", &pos);
				if (pos < 0 || pos >= len) {
					printf("Invalid position.\n");
				}
				else if (pos == 0)
					head = delete_first(head);
				else {
					pre = head;
					for (int i = 0; i < pos - 1; i++) {
						pre = pre->link;
						count++;
					}
					head = delete(head, pre);
					count++;
				}
				printf("\nMove along the link: %d\n", count);
			}
		}
		else if (choice == 3) {
			print_list(head);
		}
		else if (choice == 0) {
			printf("Exit the program.\n");
			break;
		}
		else {
			printf("Invalid Menu. Please select again.\n\n");
		}
	}
	return 0;
}
