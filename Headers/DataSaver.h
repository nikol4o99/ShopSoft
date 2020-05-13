#ifndef DATASAVE_H
#define DATASAVE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Firm.h"
#include "Product.h"
#include "Sold.h"
#include "Storage.h"

firmArray * firmSave(firmArray * firmsLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Firms.txt";
    fp = fopen(path,"w+");
    int fileSize = firmArraySize;
    fprintf(fp,"%d\n",fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        fprintf(fp,"%d %s %s %s\n",
                firmsLoaded->currentFirm.EIK,
                firmsLoaded->currentFirm.Name,
                firmsLoaded->currentFirm.Address,
                firmsLoaded->currentFirm.Mol);
                firmsLoaded = firmsLoaded ->previous;
    }
    fclose(fp);
}
ProductArray * ProductSave(ProductArray * ProductsLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Products.txt";
    fp = fopen(path,"w+");
    int fileSize = productArraySize ;
    fprintf(fp,"%d\n",fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        fprintf(fp,"%s %s %.02f %u\n",
                ProductsLoaded->currentProduct.Name,
                ProductsLoaded->currentProduct.Description,
                ProductsLoaded->currentProduct.Price,
                ProductsLoaded->currentProduct.ID);
                ProductsLoaded = ProductsLoaded ->previous;
    }
    fclose(fp);
}
StorageArray * StorageSave(StorageArray * StoragesLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Storages.txt";
    fp = fopen(path,"w+");
    int fileSize = storageArraySize;
    fprintf(fp,"%d\n",fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        fprintf(fp,"%d %.02f %u %u\n",
                StoragesLoaded->currentStorage.Quantity,
                StoragesLoaded->currentStorage.SalePrice,
                StoragesLoaded->currentStorage.ID,
                StoragesLoaded->currentStorage.product.ID);
                StoragesLoaded = StoragesLoaded ->previous;
    }
    fclose(fp);
}
SaleArray * SaleSave(SaleArray * SalesLoaded)
{
    FILE * fp;
    char path[] = "./Headers/Data/Sales.txt";
    fp = fopen(path,"w+");
    int fileSize = soldSize ;

    fprintf(fp,"%d\n",fileSize);

    for(int i = 0 ; i < fileSize ; i++)
    {
        fprintf(fp,"%u %d %.02lf %u\n",
                SalesLoaded->currentSale.product.ID,
                SalesLoaded->currentSale.Quantity,
                SalesLoaded->currentSale.SalePrice,
                SalesLoaded ->currentSale.firm.EIK);

                SalesLoaded = SalesLoaded ->previous;
    }
    fclose(fp);
}
void updateDB(firmArray * firmsArr, ProductArray * ProductsArr, StorageArray * StoragesArr, SaleArray * SalesArr)
{
    firmSave(firmsArr);
    ProductSave(ProductsArr);
    StorageSave(StoragesArr);
    SaleSave(SalesArr);
}
void memoryDump(firmArray * firmsArr, ProductArray * ProductsArr, StorageArray * StoragesArr, SaleArray * SalesArr)//GC
{
    for(int i=0;i<firmArraySize;i++){
        firmsArr = firmsArr->previous;
        free(firmsArr->next);
    }
    for(int i=0;i<productArraySize;i++){
        ProductsArr = ProductsArr->previous;
        free(ProductsArr->next);
    }
    for(int i=0;i<storageArraySize;i++){
        StoragesArr = StoragesArr->previous;
        free(StoragesArr->next);
    }
    for(int i=0;i<soldSize;i++){
        SalesArr = SalesArr->previous;
        free(SalesArr->next);
    }
}
#endif

