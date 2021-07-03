#include<stdlib.h>

struct product{
    char product_name[30];// (phone, tshirt, coke etc.)
    char product_type[30]; //(electronicDevice, clothing, market etc.)
    int price; // (can be integer between 1-1000)
 };typedef struct product Product;

Product* createProduct(char product_name[30], char product_type [30], int price);
void printProduct(Product* s);
