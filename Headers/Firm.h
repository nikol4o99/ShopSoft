#ifndef FIRM_H
#define FIRM_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define CharStr_Max1 20
#define CharStr_Max2 30

static size_t firmArraySize;

typedef struct Firms
{
    char Address[CharStr_Max2];
    char Name[CharStr_Max1];
    char Mol[CharStr_Max1];
    unsigned int EIK;
} Firm;
typedef struct linkedList
{
    int currPlace;
    Firm currentFirm;
    struct linkedList * previous;
    struct linkedList * next;
} firmArray;

Firm firmInfo()
{
    Firm new_firm;
// firm info input
    int eik;
    char add[30],name[20],mol[20];
    printf("Enter EIK, Name, Address and Mol in the following order\n");
    scanf("%d%s%s%s",&eik,name,add,mol);
    //printf("%d%s%s%s\n",eik,name,add,mol);
    new_firm.EIK = eik;
    strcpy(new_firm.Address, add);
    strcpy(new_firm.Name, name);
    strcpy(new_firm.Mol, mol);
    //end input
    return new_firm;
}
Firm searchFirmByEIK(firmArray * firmArr, unsigned int eik)
{
    for(int i = 0; i < firmArraySize; i++)
    {
        if(firmArr->currentFirm.EIK == eik)
        {
            return firmArr->currentFirm;
        }
        firmArr = firmArr -> previous;
    }
//    return NULL;
}
void viewFirms(firmArray * firmArr)
{
    for(int i=0; i<firmArraySize; i++)
    {
        printf("EIK: %u Name: %s Address: %s MOL: %s\n",
               firmArr->currentFirm.EIK,
               firmArr->currentFirm.Name,
               firmArr->currentFirm.Address,
               firmArr->currentFirm.Mol);
               firmArr = firmArr -> previous;
    }
}
firmArray * newFirm(firmArray * node, Firm firm)
{
    firmArraySize++;
    firmArray * newNode = NULL;
    newNode = (firmArray *) malloc(sizeof(firmArray));
    if(newNode!=NULL){
    node -> next = newNode;
    newNode -> previous = node;
    newNode -> currPlace = (node -> currPlace) + 1;
    newNode -> currentFirm = firm;
    newNode -> next = NULL;
    }
    else newNode = newFirm(node,firm);
    return newNode;
}
firmArray * deleteFirm(firmArray * firmArr,unsigned int eik)
{
    firmArray * lastf = firmArr;

    for(int i=0; i<firmArraySize; i++)
    {
        if(firmArr->currentFirm.EIK == eik)
        {

            firmArray * firmprev = firmArr->previous;
            firmArray * firmnext = firmArr->next;
            firmprev->next = firmArr->next;
            firmnext->previous = firmArr->previous;
            printf("Here!");
            free(firmArr);
            firmArraySize--;
            break;
        }
        firmArr = firmArr->previous;
    }
    firmArr = lastf;

    return firmArr;
}
firmArray * updateFirm(firmArray * firmArr,int eik)
{
    firmArray * lastf = firmArr;
    for(int i=0; i<firmArraySize; i++)
    {
        if(firmArr->currentFirm.EIK == eik)
        {
            printf("Enter firm's new name, address and mol\n");
            scanf("%s %s %s",firmArr->currentFirm.Name,
                  firmArr->currentFirm.Address,
                  firmArr->currentFirm.Mol);
            break;
        }
        firmArr = firmArr->previous;
    }
    firmArr = lastf;
    return firmArr;
}
#endif
