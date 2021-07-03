#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include "product.h"


Product* createProduct(char product_name[30], char  product_type [30], int price){
    Product *newProduct = malloc(sizeof(Product));
    strcpy(newProduct->product_name,product_name);
    strcpy(newProduct-> product_type, product_type);
    newProduct->price = price;
    return newProduct;
}
 

// printing products
void printProduct(Product* p){
    printf("Product Name: %s\t", p->product_name);
    printf("Product Type: %s\t", p-> product_type);
    printf("Price: %d\n", p->price);
}
