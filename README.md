# Operating-Systems-Assignment-4

CENG 322- Operating Systems
 Homework #4
In this homework, you are expexted to solve synchronization problem between
threads that are responsible from different tasks. You will create 2 types of
linked lists that are related with shopping products and favories. (It can be
thought as Trendyol, we have product lists which contains several varying types
products, and user favorite list which includes some of the products that
belongs to products list) You should implement a multi-threaded program
(whose tasks are given below) that operates on linked lists.. Your program
requires 3 types of threads:
1. Cut and pasting thread
2. Price increasing thread
3. Product offering thread
In your program you will have 2 types of linked lists which are products (which
contain all the products) and favories(which are the favories of the user).
Type ‘1’ thread should use both of the linked lists (one of the products list and
favories list) at the same time. Without having both of the lists, it can not
perform its task. It should cut any 2 products from products list with given
product_type, paste it to the favories list.
Type ‘2’ thread increases the product_price %20 in one of the lists (products or
favories lists). The price of the product to be increased can be decided
randomly among the products in the list.
Type ‘3’ thread offers products which can be bought in the favories lists for the
user-specified money/budget.(You can print all the products which are less
than given budget)
You should create 2 lists (products1 and products2) for the products lists, also 1
list for favories list.
You should have 2 threads in type ‘1 thread’, and 1 thread for type ‘2’ and type
‘3’ thread.
Your program can initialize the products lists with random products(at least 10
product for each). Favories list is initiallty empty. Please use the data structure
for product specified below:
Struct product{
int product_name; // (phone, tshirt, coke etc.)
char product_type[30]; //(electronicDevice, clothing, market etc.)
int price; // (can be integer between 1-1000)
 }
Your program should get the product_type which will be cut from
products_list, and budget that is used to product offering(for thread type ‘3’)
from the user. When work with the lists is finished, print the contents of the
lists to the console, or offered product that can be bought with the given
budget. At the end of your program, products1 and products2 lists should be
empty.
You should prevent any possible deadlocks in this homework. Therefore make
sure that you follow synchronization methologies like semaphore and mutex.
Example code output is given below:
Current products lists are:
Products1:
product_name: iphoneX, product_type: electronicDevice, price: 1000
product_name: shoes, product_type: clothing, price: 550
product_name: powerbank, product_type: electronicDevice, price: 100
product_name: detergent, product_type: market, price: 20
product_name: coke, product_type: market, price:5
product_name: tshirt, product_type: clothing, price: 70
%%%%%%%%%%
 Products2:
product_name: jean, product_type: clothing, price: 220
product_name: dress, product_type: clothing, price: 300
product_name: hairDrier, product_type: electronicDevice, price: 300
product_name: blender, product_type: electronicDevice, price: 500
product_name: coffee, product_type: market, price: 75
 product_name: tea, product_type: market, price: 30
 %%%%%%%%%%
 Favories:
 %%%%%%%%%%
 Please enter your favorite product_type (in lower case):
 Product_type: market
 %%%%%%%%%%%
 Please enter your budget for shopping:
 Budget: 150
 %%%%%%%%%%%%
 Type 1 thread is perfoming.
 Type 1 thread is performing.
 2 products is cut from Products1 and pasted to favories.
 Type 3 thread is performing.
 2 products is cut from Products2 and pasted to favories.
 Type 2 thread is performing.
 Product price increased in products1: powerbank, 120
 You can buy products which are less than your budget: detergent, tshirt 
