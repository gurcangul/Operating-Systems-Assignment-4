#include <string.h>
#include "linkedlist.h"
#include<stdio.h>
Node* createNode(Product *value, size_t data_size){
    Node *newNode = malloc(sizeof(Node));
    newNode->data  = malloc(data_size);
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insert(Node** list, Product *new_data, size_t data_size){
    Node* new_node = createNode(new_data, data_size);
    if(*list==NULL){
        *list = new_node;
        return; 
    }
    else{
        Node *nextNode = (*list);
        while (nextNode->next != NULL){
            nextNode = nextNode->next;
        }
        nextNode->next = new_node;
    }
}

void printList(Node **start){
    if(*start == NULL){
        printf("List is empty\n" );
    }
    Node* node = *start;
    while (node != NULL&&node->data != NULL){
        printProduct(node->data);
        node = node->next;
    }
}
int getCount(Node **start){// It return count of nodes in the linkelist
    Node *node = *start;
    int count=0;
    while (node!=NULL){
        count++;
        node=node->next;

    }
    return count;
}

Product* increasingProductPrice(Node **start, int size){
    Node *node = *start;
    int counter = 0;
    if(node == NULL){
      printf("There is not found any product!\n");
    }
    else if (node->data == NULL)
    {
      printf(" List is empty\n");
    }

    while (counter < size){
        counter++;
        node=node->next;
    }
    node->data->price += (node->data->price * 20) / 100;
    return node->data;
}
Product* deleteByProductType(Node **start, char product_type[30]){
    Node* node = *start;
    Node* prev = NULL;
    if(node == NULL)
      return NULL;
    while (strcmp(node->data->product_type,product_type) != 0){
        if(node->next==NULL){
            return NULL;
        }else{
            prev = node;
            node = node->next;
        }
    }
    if(node == *start){
        *start = node->next;
    }
    else
        prev->next = node->next;

    return node->data;
}

void listByPrice(Node **start,int price){
    Node* node = *start;

    if(node == NULL){
      printf("There is not found any product!\n");
    }
    printf("You can buy products which are less than your budget:  ");
    while (node != NULL){
        if(price >= node->data->price)
            printf("%s , ",node->data->product_name );

        node = node->next;
    }
    printf("\n");
}

int checkProductType(Node **start, char product_type[30]){
  Node* node = *start;
  Node* prev = NULL;

  while (node != NULL){
      if(strcmp(node->data->product_type, product_type) == 0){
          return 1;
      }
      else{
          prev = node;
          node = node->next;
      }
  }
  return 0;

}

