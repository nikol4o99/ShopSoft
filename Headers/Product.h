#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>


#define CharStr_Max1 20
#define CharStr_Max3 50

static size_t productArraySize;

typedef struct Products
{
    char Name[CharStr_Max1];
    char Description[CharStr_Max3];
    double Price;
    unsigned int ID;
} Product;
typedef struct plinkedList
{
    Product currentProduct;
    struct plinkedList * previous;
    struct plinkedList * next;
} ProductArray;

Product productInfo()
{
    Product new_product;
// product info input probably read from file
    char name[20],description[50];
    unsigned long long int id;
    double price;
    printf("Enter Name, Description, Price and ID in the following order\n");
    scanf("%s%s%lf%d",name,description,&price,&id);
    //printf("%d%s%s%s\n",eik,name,add,mol);
    new_product.ID = id;
    strcpy(new_product.Description, description);
    strcpy(new_product.Name, name);
    new_product.Price = price;
    //end input
    return new_product;
}
Product searchProductByID(ProductArray * prodArr,unsigned int id)
{
    for(int j=0; j<productArraySize; j++)
    {
        if(prodArr->currentProduct.ID == id)
        {
            return prodArr->currentProduct;
        }
        prodArr = prodArr->previous;
    }
//        return NULL;
}
ProductArray * newProduct(ProductArray * node,Product product)
{

    ProductArray * newNode = NULL;
    newNode = (ProductArray *) malloc(sizeof(ProductArray));
    if(newNode!=NULL)
    {
    node -> next = newNode;
    newNode -> previous = node;
    newNode -> currentProduct = product;
    newNode -> next = NULL;
    productArraySize++;
    }
    else newNode = newProduct(node,product);
    return newNode;
}
void viewProducts(ProductArray * prodArr)
{
    for(int i=0; i<productArraySize; i++)
    {
        printf("Name: %s Descr: %s Price: %.02f ID: %u\n",
               prodArr->currentProduct.Name,
               prodArr->currentProduct.Description,
               prodArr->currentProduct.Price,
               prodArr->currentProduct.ID);
        prodArr = prodArr -> previous;
    }
}
ProductArray *deleteProduct(ProductArray * prodArr,int id)
{
    ProductArray * lastf = prodArr;
    for(int i=0; i<productArraySize; i++)
    {
        if(prodArr->currentProduct.ID == id)
        {
            ProductArray * prodnext = prodArr->next;
            ProductArray * prodprev = prodArr->previous;
            prodprev->next = prodArr->next;
            prodnext->previous = prodArr->previous;
            free(prodArr);
            productArraySize--;
            break;
        }
        prodArr = prodArr->previous;
    }
    prodArr = lastf;
    return prodArr;
}
ProductArray * updateProduct(ProductArray * prodArr,int id)
{
    ProductArray * lastf = prodArr;
    for(int i=0; i<productArraySize; i++)
    {
        if(prodArr->currentProduct.ID == id)
        {
            printf("Enter product's new name, description and price\n");
            scanf("%s %s %lf",
                  prodArr->currentProduct.Name,
                  prodArr->currentProduct.Description,
                  &prodArr->currentProduct.Price);
            break;
        }
        prodArr = prodArr->previous;
    }
    prodArr = lastf;
    return prodArr;
}
#endif
