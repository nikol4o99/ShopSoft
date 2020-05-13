#ifndef DATALOAD_H
#define DATALOAD_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Firm.h"
#include "Product.h"
#include "Storage.h"
#include "Sold.h"


firmArray * firmLoad(firmArray * firmsLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Firms.txt";
    fp = fopen(path,"r+");
    firmArray * first = firmsLoaded;
    size_t fileSize;
    fscanf(fp,"%d\n",&fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        //firmArraySize++;
        int eik;
        char name[20],address[30],mol[20];
        // firmArray * newNode = NULL;
        fscanf(fp,"%d %s %s %s",&eik,name,address,mol);
        Firm _newFirm;
        _newFirm.EIK = (int)eik;
        strcpy(_newFirm.Name, name);
        strcpy(_newFirm.Address, address);
        strcpy(_newFirm.Mol, mol);
        firmsLoaded = newFirm(firmsLoaded,_newFirm);

    }
    fclose(fp);
    return firmsLoaded;
}
ProductArray * productLoad(ProductArray * productsLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Products.txt";
    fp = fopen(path,"r+");
    ProductArray * first = productsLoaded;
    size_t fileSize;
    fscanf(fp,"%d\n",&fileSize);
//printf("%d",fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        char name[20],description[50];
        int id;
        double price;
        Product _newProduct;
        fscanf(fp,"%s %s %lf %d\n",name,description,&price,&id);
        _newProduct.ID = id;
        _newProduct.Price = price;
        strcpy(_newProduct.Name,name);
        strcpy(_newProduct.Description,description);
        productsLoaded = newProduct(productsLoaded,_newProduct);

    }
    fclose(fp);
    return productsLoaded;
}
StorageArray * storageLoad(StorageArray * StoragesLoaded,ProductArray * prodArr)
{
    FILE * fp;
    char path[] = "./Headers/Data/Storages.txt";
    fp = fopen(path,"r+");
    StorageArray * first = StoragesLoaded;
    size_t fileSize;
    fscanf(fp,"%d\n",&fileSize);

    for(int i = 0 ; i < fileSize ; i++)
    {
        unsigned int productId;
        int quant;
        double price;
        unsigned int id;
        Storage _newStorage;


        fscanf(fp,"%d %lf %u %u\n",&quant,&price,&id,&productId);
        _newStorage.ID = id;
        _newStorage.Quantity = quant;
        _newStorage.SalePrice = price;
        _newStorage.product = searchProductByID(prodArr,productId);
        StoragesLoaded = newStorage(StoragesLoaded,_newStorage);
    }
    fclose(fp);
    return StoragesLoaded;
}
SaleArray * saleLoad(SaleArray * SalesLoaded,ProductArray * prodArr,firmArray * firmArr)
{
    FILE * fp;
    char path[] = "./Headers/Data/Sales.txt";
    fp = fopen(path,"r+");
    SaleArray * first = SalesLoaded;
    size_t fileSize;
    fscanf(fp,"%d\n",&fileSize);

    for(int i = 0 ; i < fileSize ; i++)
    {
        unsigned int productId;
        int quant;
        unsigned int eik;
        double price;
        Sale _newSale;

        fscanf(fp,"%d %d %lf %d",&productId,&quant,&price,&eik);
        _newSale.firm = searchFirmByEIK(firmArr,eik);
        _newSale.product = searchProductByID(prodArr,productId);
        _newSale.Quantity = quant;
        _newSale.SalePrice = price;
        SalesLoaded = newSale(SalesLoaded,_newSale);
    }
    fclose(fp);
    return SalesLoaded;
}

#endif
