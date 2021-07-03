#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "linkedlist.h"

#define RELEASED 0
#define LOCKED 1
// This code compiled with 9.3.0
/*
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
 
*/
sem_t products1Lock;
sem_t products2Lock;
sem_t favoriesListLock;


int price;
char product_type[30] = "";
int products1Count;
int products2Count;
int products1Status = RELEASED;
int products2Status = RELEASED;
int favoriesListStatus = RELEASED;


Node *favoriesList = NULL;
Node *products1 = NULL;
Node *products2 = NULL;


int lock(){
    while(1){
        // It will return -1, if two product lists are empty
        if(products1Count == 0 && products2Count == 0){
            return -1;
        }
	// if products1 is not null and products1 and favoriesList are not in use 
        if(favoriesListStatus == RELEASED && products1Status == RELEASED && products1Count != 0){
            sem_wait(&products1Lock);
            sem_wait(&favoriesListLock);
            favoriesListStatus = LOCKED;
            products1Status = LOCKED;
            return 1;
        }
	// if products2 is not null and products2 and favoriesList are not in use 
        if(favoriesListStatus == RELEASED && products2Status == RELEASED && products2Count != 0){
            sem_wait(&products2Lock);
            sem_wait(&favoriesListLock);
            favoriesListStatus = LOCKED;
            products2Status = LOCKED;
            return 2;
        }
    }
}

// It releases the products and favoriesList 
void release(int listNum){
    if(listNum == 1){
        sem_post(&products1Lock);
        sem_post(&favoriesListLock);
        favoriesListStatus = RELEASED;
        products1Status = RELEASED;
    }
    if(listNum == 2){
        sem_post(&products2Lock);
        sem_post(&favoriesListLock);
        favoriesListStatus = RELEASED;
        products2Status = RELEASED;
    }
}


void * allOperations(void *id) {
    int threadID = *((int *)id);

  
    if(threadID == 2){  // type 2 thread 

        printf("Type%d thread is performing \n",threadID);
        srand(time(NULL)); 
        int random = rand() % 3;
        Product * product=(Product*)malloc(sizeof(Product));
        if(random==0){

            int favListSize=getCount(&favoriesList);
            int num = rand() % favListSize;

            sem_wait(&favoriesListLock);
            favoriesListStatus = LOCKED;
            product = increasingProductPrice(&favoriesList,num);
            
            printf("Product price increased in favoriesList : %s , %d \n", product->product_name, product->price);
            sem_post(&favoriesListLock);
            favoriesListStatus = RELEASED;
        }

        else if(random==1){
            sem_wait(&products1Lock);
            products1Status = LOCKED;
            int products1Size=getCount(&products1);
            if(products1Size > 0){
              int num = rand() % products1Size;
              product = increasingProductPrice(&products1,num);
              printf("Product price increased in products1 : %s , %d \n", product->product_name, product->price);
            }
            sem_post(&products1Lock);
            products1Status = RELEASED;
        }
        else{
            sem_wait(&products2Lock);
            products2Status = LOCKED;
            int products2Size=getCount(&products2);
            if(products2Size > 0){
              int num = rand() % products2Size;
              product = increasingProductPrice(&products2,num);
              printf("Product price increased in products2 : %s , %d \n", product->product_name, product->price);
            }
            sem_post(&products2Lock);
            products2Status = RELEASED;
        }
    }
    
    else if(threadID == 3){// type 3 thread 

        printf("Type%d thread is performing\n",threadID);
        sem_wait(&favoriesListLock);
        favoriesListStatus = LOCKED;
        listByPrice(&favoriesList,price);
        sem_post(&favoriesListLock);
        favoriesListStatus = RELEASED;
    }
 
    else{// type 1 thread 
         while (products1Count != 0 || products2Count != 0){
            int listNum = lock();
            if(listNum != -1){

                printf("type1(%d) thread is performing \n", threadID);

                int cutTime = 2;
                int numofproduct=0;

                if(listNum == 1 && products1Count != 0){
                     Product *temp = (Product*)malloc(sizeof(Product));
                    for (int i = 0; i < cutTime; ++i) {
                        temp = deleteByProductType(&products1,product_type);
                        if(temp != NULL){
        		         insert(&favoriesList,temp, sizeof(Product));
			         numofproduct++;	
			}
                        products1Count--;
                   }
                }
                if(listNum == 2 && products2Count != 0){
                    Product *temp = (Product*)malloc(sizeof(Product));
                    for (int i = 0; i < cutTime; ++i) {
                        temp = deleteByProductType(&products2,product_type);
                        if(temp != NULL){
                          	insert(&favoriesList,temp, sizeof(Product));
				numofproduct++;	
			}
                        products2Count--;
                    }
                }
                
                printf("%d products is cut from Products%d and pasted to favories\n", numofproduct,listNum);

                release(listNum);
            }
            sleep(1);
        }
    }
    return 0;
}

int main(){
    time_t t;
    srand((unsigned) time(&t));
    
    // initialised semaphores 
    sem_init(&products1Lock, 0, 1);
    sem_init(&products2Lock, 0, 1);
    sem_init(&favoriesListLock, 0, 1);

    // products1 and products2 are filling with products 
    unsigned product_size = sizeof(Product);
    Product* temp = NULL;

    temp = createProduct("iphoneX","electronicDevice",1000);
    insert(&products1, temp, product_size);
    temp = createProduct("shoes","clothing",550);
    insert(&products1, temp, product_size);
    temp = createProduct("powerbank","electronicDevice",100);
    insert(&products1, temp, product_size);
    temp = createProduct("detergent","market",20);
    insert(&products1, temp, product_size);
    temp = createProduct("coke","market",5);
    insert(&products1, temp, product_size);
    temp = createProduct("tshirt","clothing",70);
    insert(&products1, temp, product_size);
    temp = createProduct("jean","clothing",220);
    insert(&products1, temp, product_size);
    temp = createProduct("dress","clothing",300);
    insert(&products1, temp, product_size);
    temp = createProduct("hairDrier","electronicDevice",300);
    insert(&products1, temp, product_size);
    temp = createProduct("blender","electronicDevice",500);
    insert(&products1, temp, product_size);
    temp = createProduct("coffee","market",75);
    insert(&products2, temp, product_size);
    temp = createProduct("tea","market",30);
    insert(&products2, temp, product_size);
    temp = createProduct("HJCRpha11","helmet",600);
    insert(&products2, temp, product_size);
    temp = createProduct("AraiChaserX","helmet",800);
    insert(&products2, temp, product_size);
    temp = createProduct("AraiRx7","helmet",750);
    insert(&products2, temp, product_size);
    temp = createProduct("ShoeiGtAir","helmet",700);
    insert(&products2, temp, product_size);
    temp = createProduct("ShoeiNxr","helmet",600);
    insert(&products2, temp, product_size);
    temp = createProduct("gloves","clothing",100);
    insert(&products2, temp, product_size);
    temp = createProduct("appleWatch3","electronicDevice",2000);
    insert(&products2, temp, product_size);
    temp = createProduct("airpods2","electronicDevice",1000);
    insert(&products2, temp, product_size);

    while (1){
        if(products1==NULL && products2==NULL)
            break;

        products1Count = 2;
        products2Count = 2;
        printf("products1:\n");
        printList(&products1);
        printf("products2:\n");
        printList(&products2);
        printf("favoriesList:\n");
        printList(&favoriesList);
        printf("Enter the product_type:\n");
        if (scanf(" %s", product_type) == 0) {
            printf("You entered NaN.\n");
           
           
        }
        while(1){
            int flag1 = checkProductType(&products1, product_type);
            int flag2 = checkProductType(&products2, product_type);
            if(flag1 == 1 || flag2 == 1)
              break;
            else{
              printf("There is no this product type\n");
              printf("Enter the product_type:\n");
              if (scanf(" %s", product_type) == 0) {
                  printf("You entered null\n");
            }
          }
        }
        printf("Enter the price:\n");
        if (scanf(" %d", &price) == 0) {
            printf("You entered null\n");
        }

        pthread_t tid[4];
        pthread_attr_t attr[4];

        int i=0;
        for(i=0; i<4; i++) { // created and initialized the threads 
            void *memory = malloc(sizeof(int));
            int* id = (int *) memory;
            *id = i;
            pthread_attr_init(&attr[i]);
            pthread_create(&tid[i], &attr[i], allOperations, id);

        }


        for(i=0; i<4; i++) {
            pthread_join(tid[i], NULL);
        }
    }

	//printing
    printf("products1:\n");
    printList(&products1);
    printf("products2:\n");
    printList(&products2);
    printf("favoriesList:\n");
    printList(&favoriesList);


}

