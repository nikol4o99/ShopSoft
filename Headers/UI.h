#ifndef UI_H
#define UI_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "Firm.h"
#include "Product.h"
#include "Storage.h"
#include "Sold.h"
#include "DataLoader.h"
#include "DataSaver.h"

int firmOrProduct()
{
    printf("For firm enter F\nFor product enter P\n");
    char choice;
    scanf(" %c",&choice);
    if(choice == 'F') return 1;
    if(choice == 'P') return 2;
}
int storageFirmOrProduct()
{
    printf("For firm enter F\nFor product enter P\nFor storage enter S\n");
    char choice;
    scanf(" %c",&choice);
    if(choice == 'F') return 1;
    if(choice == 'P') return 2;
    if(choice == 'S') return 3;
}

void commandUI(firmArray * firmsArr, ProductArray * ProductsArr, StorageArray * StoragesArr, SaleArray * SalesArr)
{
    int command;
    printf("Choose action via typing in the command code!\n"
           "1. Create a new Firm\n"
           "2. Create a new Product\n"
           "3. New Sale\n"
           "4. Add product Quantity\n"
           "5. Update \(an existing Firm, Product\)\n"
           "6. Delete \(an existing Firm, Product\)\n"
           "7. Display\n"
           "8. Show Sales\n"
           "9. Exit\n");
    scanf("%d",&command);
    system("cls");
    unsigned int prID,id,k;
    int qtity;
    switch (command)
    {
        case 1:
            firmsArr = newFirm(firmsArr,firmInfo());
            break;
        case 2:
            ProductsArr = newProduct(ProductsArr,productInfo());
            StoragesArr = newStorage(StoragesArr,StorageInfo(ProductsArr,ProductsArr->currentProduct.ID));
            break;
        case 3:
            SalesArr = newSale(SalesArr,SaleInfo(ProductsArr,firmsArr));
            StoragesArr = sellProductFromStorage(StoragesArr,searchStorageByProductID(StoragesArr,SalesArr->currentSale.product.ID),SalesArr->currentSale.Quantity);
            break;
        case 4:
            printf("Enter product ID and Quantity\n");
            scanf("%d %d",&prID,&qtity);
            StoragesArr = addProductQuantity(StoragesArr,searchStorageByProductID(StoragesArr,prID),qtity);
            break;
        case 5:
            k = firmOrProduct();
            switch (k)
            {
                case 1:
                    viewFirms(firmsArr);
                    printf("Enter firm EIK:\n");
                    scanf("%d",&id);
                    firmsArr = updateFirm(firmsArr,id);
                    break;
                case 2:
                    viewProducts(ProductsArr);
                    printf("Enter product ID:\n");
                    scanf("%d",&id);
                    ProductsArr = updateProduct(ProductsArr,id);
                    break;
            }
            break;
        case 6:
            k = firmOrProduct();
            switch (k)
            {
                case 1:
                    viewFirms(firmsArr);
                    printf("Enter firm EIK:\n");
                    scanf("%d",&id);
                    firmsArr = deleteFirm(firmsArr,id);
                    break;
                case 2:
                    viewProducts(ProductsArr);
                    printf("Enter product ID:\n");
                    scanf("%d",&id);
                    ProductsArr = deleteProduct(ProductsArr,id);
                    StoragesArr = deleteStorage(StoragesArr,returnStorageByProductID(StoragesArr,id));
                    break;
            }
            break;
        case 7:
            k = storageFirmOrProduct();
            switch (k)
            {
                case 1:
                    viewFirms(firmsArr);
                    break;
                case 2:
                    viewProducts(ProductsArr);
                    break;
                case 3:
                    viewStorages(StoragesArr);
                    break;
            }
            break;
        case 8:
            viewSales(SalesArr);
            break;
        case 9:
            memoryDump(firmsArr,ProductsArr,StoragesArr,SalesArr);
            exit(EXIT_SUCCESS);
    }

    if(command!=9)updateDB(firmsArr,ProductsArr,StoragesArr,SalesArr);
    system("pause");
    system("cls");
    commandUI(firmsArr,ProductsArr,StoragesArr,SalesArr);
}

void marketStart()
{
    ProductArray * productArray = NULL;
    productArray = (ProductArray *) malloc(sizeof(ProductArray));
    if(productArray != NULL)
        productArray  = productLoad(productArray);

    firmArray * FirmArray = NULL;
    FirmArray = (firmArray *) malloc(sizeof(firmArray));
    if(FirmArray != NULL)
        FirmArray  = firmLoad(FirmArray);

    StorageArray * storageArray = NULL;
    storageArray = (StorageArray *) malloc(sizeof(StorageArray));
    if(storageArray != NULL)
        storageArray  = storageLoad(storageArray,productArray);

    SaleArray * saleArray = NULL;
    saleArray = (SaleArray *) malloc(sizeof(SaleArray));
    if(saleArray != NULL)
        saleArray  = saleLoad(saleArray,productArray,FirmArray);
        viewFirms(FirmArray);
        viewProducts(productArray);
        viewSales(saleArray);
        viewStorages(storageArray);
    commandUI(FirmArray,productArray,storageArray,saleArray);
}

#endif // UI_H
