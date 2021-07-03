#include<stdlib.h>
#include "product.h"
#include<stdio.h>
struct node{
    Product  *data;
    struct node *next;
}; typedef struct node Node;

Node* createNode(Product *value, size_t data_size);
void insert(Node** head_ref, Product *new_data, size_t data_size);
void  printList(Node **start);
Product* deleteByProductType(Node **start,char product_type[30]);
void listByPrice(Node **start,int price);
int getCount(Node **start);
Product* increasingProductPrice(Node **start, int size);
int checkProductType(Node **start, char product_type[30]);
