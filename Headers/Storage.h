#ifndef Storage_H
#define Storage_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "Product.h"

static size_t storageArraySize;
typedef struct Storages
{
    Product product;
    int Quantity;
    double SalePrice;
    unsigned int ID;
} Storage;
typedef struct slinkedList
{
    Storage currentStorage;
    struct slinkedList * previous;
    struct slinkedList * next;
} StorageArray;

Storage StorageInfo(ProductArray * prodArr, unsigned int productId)
{
    Storage new_Storage;
// Storage info input probably read from file
    printf("Enter Quantity, Price and ID int the following order\n");
    int quant;
    double price;
    int id;
    scanf("%d %lf %d",&quant,&price,&id);
    new_Storage.product = searchProductByID(prodArr,productId);
    new_Storage.Quantity = quant;
    new_Storage.SalePrice = price;
    new_Storage.ID = id;
    //end input
    return new_Storage;
}
unsigned int searchStorageByProductID(StorageArray * storArr,unsigned int productId)
{
    for(int i = 0; i<storageArraySize; i++)
    {
        if(storArr->currentStorage.product.ID == productId)
            return storArr->currentStorage.ID;
    }
}
Storage returnStorageByProductID(StorageArray * storArr,unsigned int productId)
{
    for(int i = 0; i<storageArraySize; i++)
    {
        if(storArr->currentStorage.product.ID == productId)
            return storArr->currentStorage;
    }
}
void viewStorages(StorageArray * storArr)
{
    for(int i=0; i<storageArraySize; i++)
    {
        printf("Product name: %s Quantity: %d Sale price: %.02f ID: %u\n",
               storArr->currentStorage.product.Name,
               storArr->currentStorage.Quantity,
               storArr->currentStorage.SalePrice,
               storArr->currentStorage.ID);
               storArr = storArr->previous;
    }
}

StorageArray * newStorage(StorageArray * node, Storage storage)
{

    storageArraySize++;
    StorageArray * newNode = NULL;
    newNode = (StorageArray *) malloc(sizeof(StorageArray));
    if(newNode!=NULL){
    node -> next = newNode;
    newNode -> previous = node;
    newNode -> currentStorage = storage;
    newNode -> next = NULL;
    }
    else newNode = newStorage(node,storage);
    return newNode;
}
StorageArray * deleteStorage(StorageArray * storArr,Storage storage)
{
    StorageArray * lastf = storArr;
    for(int i=0; i<firmArraySize; i++)
    {
        if(storArr->currentStorage.ID == storage.ID)
        {
            StorageArray * storagenext = storArr->next;
            StorageArray * storageprev = storArr->previous;
            storageprev->next = storArr->next;
            storagenext->previous = storArr->previous;
            free(storArr);
            break;
        }
        storArr = storArr->previous;
    }
    storArr = lastf;
}
StorageArray * sellProductFromStorage(StorageArray * storArr, int id, int quant)
{
    StorageArray * lastf = storArr;
    for(int i=0; i<firmArraySize; i++)
    {
        if(storArr->currentStorage.ID == id)
        {
            storArr->currentStorage.Quantity -= quant;
            break;
        }
        storArr = storArr->previous;
    }
    storArr = lastf;
    return storArr;
}
StorageArray * addProductQuantity(StorageArray * storArr, int id, int quant)
{
    StorageArray * lastf = storArr;
    for(int i=0; i<firmArraySize; i++)
    {
        if(storArr->currentStorage.ID == id)
        {
            storArr->currentStorage.Quantity += quant;
            break;
        }
        storArr = storArr->previous;
    }
    storArr = lastf;
    return storArr;
}
#endif

