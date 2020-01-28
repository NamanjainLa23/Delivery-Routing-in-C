// Display the contents of file on the console that contains details of products available with the webstore

#include <stdio.h> 
#include <stdlib.h> 
  
int main(){  
   typedef struct product{
		int ItemCode;
		char ItemName[20];
		int Quantity;
		int Price;
	}; 
    FILE *fp; 
    struct product input;
	int i; 
       
    fp=fopen("ProductData.dat","r");        // opening the file in reading mode
    if(fp == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit(1); 
    } 
    printf("details of products availabe are\n");
    while(1){
       fread(&input, sizeof(input), 1, fp);
	   if(feof(fp)) 
	       break;
	                                    // reading the contents of the file in binary mode 
        printf("itemcode = %d    itemName  =  %s    quantity = %d      price = %d\n", input.ItemCode, input.ItemName, input.Quantity, input.Price);   // printing the contents of file to console
    }
    fclose(fp);   // closing the file after writing it's contents to console 
  
    return 0; 
}   

