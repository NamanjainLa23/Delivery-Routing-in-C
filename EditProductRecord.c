// This programm will help retaillers to add product or edit details of exixting product

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	
	FILE *fp, *fp1 , *fp2, *fp3, *fp4;
	typedef struct product{
		int ItemCode;
		char ItemName[20];
		int Quantity;
		int Price;
	}PRODUCT;
	PRODUCT p1;
	
	int found, code;
	int choice;
	printf("1. Append a record\n");
	printf("2. Read a record\n");
	printf("3. Edit a record\n");
	printf("4. Delete a record\n");
	printf("5. Exit");
	
	scanf("%d", &choice);
	
	switch(choice){
		case 1:
			fp = fopen("ProductData.dat","a+");
			if(fp==NULL){
				printf("\n FIle opening error");
				return 0;
			}
			printf("\nEnter Item Code   ");
			scanf("%d", &p1.ItemCode);
			
			printf("\nEnter Item Name   ");
			scanf("%s", p1.ItemName);
			
			printf("\nEnter Quantity   ");
			scanf("%d", &p1.Quantity);
			
			printf("\nEnter Item Price   ");
			scanf("%d", &p1.Price);
			
			fprintf(fp, "%d %s %d %d \n", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
			
			fclose(fp);
			printf("\n Record added successfully");
			break;
			
		case 2:
			found=0;
			fp = fopen("ProductData.dat","r");
			if(fp==NULL){
				printf("\n FIle opening error");
				return 0;
			}
			printf("Enter ItemCodde for item you want to search");
			scanf("%d", &code);
			fscanf(fp, "%d %s %d %d", &p1.ItemCode, p1.ItemName, &p1.Quantity, &p1.Price);
			if(p1.ItemCode==-1){
				break;
			}
			if(p1.ItemCode==code){
				found = 1;
				printf("\nThe details of Product is\n");
				printf("ItemCode =  %d    ItemName = %s    QuantityAvailable = %d    Price = %d", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
				break;
			}
			
			if(found==0){
				printf("Record not found for Itemcode %d", code);
			}
			fclose(fp);
			break;
			
		case 3:
			fp = fopen("ProductData.dat","r");
			if(fp==NULL){
				printf("\n FIle opening error");
				return 0;
			}
			
			fp1 = fopen("temp.txt","w");
			if(fp1==NULL){
				printf("\n FIle opening error");
				return 0;
			}
		
			printf("enter code for item you want to edit\n");
			scanf("%d", &code);
			
			fscanf(fp, "%d", &p1.ItemCode);
			if(p1.ItemCode==-1){
				break;
			}
			if(p1.ItemCode==code){
				found=1;
				fscanf("%s","%d","%d", p1.ItemName, p1.Quantity, p1.Price);
				printf("derails of exixting record are", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
					
				printf("\nEnter modified name of item");
				scanf("%s", p1.ItemName);
					
				printf("/nEnter modified quantity");
				scanf("%d", p1.Quantity);
					
				printf("\nEnter modified price");
				scanf("%d", p1.Price);
					
				// writing modified records to temporary file
					
				fprintf(fp1,"%d %s %d %d");
		   }
		   else{
		   	    //copy non matching records to temporary file
		   	    fscanf(fp, "%s %d %d", p1.ItemName, &p1.Quantity, &p1.Price);
		   	    fprintf(fp1, "%d %s %d %d", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
			   }
		   
		   fprintf(fp1, "%d", -1);
		   fclose(fp);
		   fclose(fp1);
		
	       if(found==0){
			  printf("The record for item code %d was not found in file", code);
		    }
		    
			else{
			  fp=fopen("ProductData.Dat","w");
			  if(fp==NULL){
				printf("file opening error");
				return 0;
			  }
			  fp1=fopen("temp.txt","r");
		   	  if(fp1==NULL){
				printf("file opening error");
				return 0;
			  }
			
			//copy contents of temporary file to actual file
			  while(1){
				fscanf(fp1,"%d", &p1.ItemCode);
				if(p1.ItemCode==-1){
					break;
				}
			    fscanf(fp1, "%s %d %d", p1.ItemName, &p1.Quantity, &p1.Price);
				fprintf(fp, "%d %s %d %d", p1.ItemCode, p1.ItemName, p1.Quantity, p1.Price);
		      }
	    	}
		    fclose(fp);
		    fclose(fp1);
		    printf("record updated");
		    return 0;
		    break;
		 
   }
return 0;
}
			
		
