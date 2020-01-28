// This program will create a database in c that will store the details of user choices and their addresses

#include <stdio.h>   
#include <stdlib.h> 
#include <string.h> 
  
int main(){
	FILE *fp;
	typedef struct person{
		char ItemName[10];
		int Quantity;
		char address[30];
	}PERSON;
	PERSON p1;
	
	fp = fopen("Customerdata.dat","w");
	if(fp == NULL){
		printf("file opening error");
		return 0;
	}
	printf("Enter item Name   ");
	scanf("%s", &p1.ItemName);
	
	if(strcmp(p1.ItemName , "exit") != 0 || strcmp(p1.ItemName , "exit\n") != 0){
		printf("Enter Quantity   ");
		scanf("%d", &p1.Quantity);
		
		printf("Enter your address   ");
		scanf("%s", p1.address);
		
		fprintf(fp, "%s %d %s\n", p1.ItemName, p1.Quantity, p1.address);
		fflush(stdin);
		
		printf("\n\nEnter item name ");
    	scanf("%s", p1.ItemName);
		
	}
	fclose(fp);
	return 0;
	
}
