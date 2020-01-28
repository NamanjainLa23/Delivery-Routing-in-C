// This program will create a database in c that will store the details of the products available with the company webstore

#include <stdio.h>   
#include <stdlib.h> 
#include <string.h> 
  
int main(){
	FILE *fp;
	typedef struct product{
		int ItemCode;
		char ItemName[20];
		int Quantity;
		int Price;
	}PRODUCT;
	PRODUCT p1;
	
	fp = fopen("ProductData.dat","w");
	if(fp == NULL){
		printf("file opening error");
		return 0;
	}
	printf("Enter item code   ");
	scanf("%d", &p1.ItemCode);
	while(p1.ItemCode != -1){
		printf("Enter Item Name   ");
		scanf("%s", p1.ItemName);
		
		printf("Enter Item Quantity available   ");
		scanf("%d", &p1.Quantity);
		
		printf("Enter Item Price   ");
		scanf("%d", &p1.Price);
		
		fprintf(fp, "%d %s %d %d\n", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
		fflush(stdin);
		
		printf("\n\nEnter item code   ");
    	scanf("%d", &p1.ItemCode);
		
	}
	fclose(fp);
	return 0;
	
}
