#ifndef Sale_H
#define Sale_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "Product.h"
#include "Firm.h"

static size_t soldSize;
typedef struct Sales
{
    Product product;
    Firm firm;
    int Quantity;
    double SalePrice;
    unsigned int ID;
} Sale;
typedef struct tlinkedList
{
    Sale currentSale;
    struct tlinkedList * previous;
    struct tlinkedList * next;
} SaleArray;

Sale SaleInfo(ProductArray * prodArr,firmArray * firmArr)
{
    unsigned int productId;
    int quant;
    unsigned int eik;
    double price;
    Sale _newSale;
    printf("Enter Product ID, Quantity, Price and EIK in the following order\n");
    scanf("%d %d %lf %d",&productId,&quant,&price,&eik);
    _newSale.firm = searchFirmByEIK(firmArr,eik);
    _newSale.product = searchProductByID(prodArr,productId);
    _newSale.Quantity = quant;
    _newSale.SalePrice = price;
    return _newSale;
}
void viewSales(SaleArray * saleArr)
{
    double sum;
    for(int i=0;i<soldSize;i++){
        printf("Product: %s Price per piece: %.02f Quantity: %d Firm: %s Total price: %.02f\n",
               saleArr->currentSale.product.Name,
               saleArr->currentSale.SalePrice,
               saleArr->currentSale.Quantity,
               saleArr->currentSale.firm.Name,
               saleArr->currentSale.SalePrice * saleArr->currentSale.Quantity);
        sum+=saleArr->currentSale.SalePrice * saleArr->currentSale.Quantity;
               saleArr = saleArr->previous;
    }
    printf("Total Sales Today : %.02f\n",sum);
}
SaleArray * newSale(SaleArray * node,Sale sale)
{

    SaleArray * newNode = NULL;
    newNode = (SaleArray *) malloc(sizeof(SaleArray));
    if(newNode!=NULL){
    node -> next = newNode;
    newNode -> previous = node;
    newNode -> currentSale = sale;
    newNode -> next = NULL;
    soldSize++;
    }
    else newNode = newSale(node,sale);
    return newNode;
}

SaleArray * updateSale(SaleArray * saleArr,int id)
{
    SaleArray * lastf = saleArr;
    for(int i=0; i<soldSize; i++)
    {
        if(saleArr->currentSale.ID == id)
        {
            printf("Enter sale's new quantity and sell price\n");
            scanf("%d %lf",
                  saleArr->currentSale.Quantity,
                  saleArr->currentSale.SalePrice);
            break;
        }
        saleArr = saleArr->previous;
    }
    saleArr = lastf;
    return saleArr;
}
#endif

