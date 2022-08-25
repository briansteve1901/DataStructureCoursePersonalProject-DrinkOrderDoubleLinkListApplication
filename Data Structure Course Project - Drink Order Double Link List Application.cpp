#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct DrinkOrder{
	int orderNumber;
	char name[100];
	int quantity;
	char request[100];
	DrinkOrder*next;
	DrinkOrder*prev;
}*head=NULL,*tail=NULL;

DrinkOrder*createOrder(int orderNumber,char *name,int quantity,char *request){
	DrinkOrder*newOrder=(DrinkOrder*)malloc(sizeof(DrinkOrder));
    
	newOrder->orderNumber=orderNumber;
    strcpy(newOrder->name,name);
    newOrder->quantity=quantity;
    strcpy(newOrder->request,request);
    
    newOrder->next = newOrder->prev = NULL;
    return newOrder;
}

void pushTail(DrinkOrder*newOrder){
	if(head==NULL){
		head=tail=newOrder;
	}	
	else{
		tail->next=newOrder;
		newOrder->prev=tail;
		tail=newOrder;
	}
}

void pushHead(DrinkOrder*newOrder){
	if(head==NULL){
		head=tail=newOrder;
	}	
	else{
		head->prev=newOrder;
		newOrder->next=head;
		head=newOrder;
	}
}

void pushMid(DrinkOrder*newOrder){
	if(head==NULL){
		head=tail=newOrder;
	}
	else if(head->orderNumber>=newOrder->orderNumber){
		pushHead(newOrder);
	}
	else if(tail->orderNumber<=newOrder->orderNumber){
		pushTail(newOrder);
	}
	else{
		DrinkOrder*curr=head;
		while(curr!=NULL){
			curr=curr->next;
			if(curr->orderNumber>=newOrder->orderNumber){
				newOrder->prev=curr->prev;
				newOrder->next=curr;
				curr->prev->next=newOrder;
				curr->prev=newOrder;
				break;
			}
		}
	}
}

DrinkOrder*pophead(){
	DrinkOrder* deleted;
	if(head==NULL){
		deleted=NULL;
	}
	else if(head==tail){
		deleted=head;
		head=tail=NULL;
	}
	else{
	    DrinkOrder*toBeDeleted=head;
		deleted=head;
		head=head->next;
		head->prev=NULL;
	}
	return deleted;
}

DrinkOrder*poptail(){
	DrinkOrder*deleted;
	if(head==NULL){
		deleted=NULL;
	}
	else if(head==tail){
		deleted=head;
		head=tail=NULL;
	}
	else{
	    DrinkOrder*toBeDeleted=tail;
		deleted=tail;
		tail=tail->prev;	
		tail->next=NULL;
	}
	return deleted;
}

DrinkOrder*popMid(int orderNumber){
	DrinkOrder*deleted;
	if(head==NULL){
		deleted=NULL;
	}
	else if(orderNumber==head->orderNumber){
		deleted=pophead();
	}
	else if(orderNumber==tail->orderNumber){
		deleted=poptail();
	}
    else{
	    DrinkOrder*curr=head;
	    while(curr!=NULL){
	    	if(curr->orderNumber==orderNumber){
	    		deleted=curr;
				curr->prev->next=curr->next;
	    		curr->next->prev=curr->prev;
	    		curr->next=NULL;
	    		curr->prev=NULL;
	    		break;
			}
			curr=curr->next;
		}
		if(curr==NULL){
			deleted=curr=NULL;
		printf("Not found!\n");
		}
    }
    return deleted;
}

void print(){
	DrinkOrder*curr=head;
	if(curr==NULL){
		printf("No order!\n");
		return;
	}
	while(curr!=NULL){
		printf("Order Number: %d\n",curr->orderNumber);
		printf("Drink Name: %s\n",curr->name);
		printf("Quantity: %d\n",curr->quantity);
		printf("Request: %s\n\n",curr->request);
		curr=curr->next;
	}
}

int main(){ 
    int orderNumber,quantity;
    char name[100];
    char request[100];
    int choose;
    do{
    	printf("1. Add Drink Order\n");
    	printf("2. View Order\n");
    	printf("3. Delete Order\n");
    	printf("4. Exit\n");
    	
    	printf("Choose >> ");
    	scanf("%d",&choose);
    	getchar();
    	
    	if(choose==1){
    		printf("Input order number: ");
    		scanf("%d", &orderNumber); getchar();
    		
    		printf("Input drink name: ");
    		scanf("%[^\n]", name); getchar();
    		
    		printf("Input quantity: ");
    		scanf("%d", &quantity); getchar();
    		
    		printf("Input request: ");
    		scanf("%[^\n]", &request); getchar();
		
		    pushMid(createOrder(orderNumber,name,quantity,request));
		    printf("Add new order success!\n");
		}   
		
		else if(choose==2){
			print();
		}
    	else if(choose==3){
			printf("Input order number:\n");
			scanf("%d",&orderNumber);
			getchar();
			DrinkOrder*deleted=popMid(orderNumber);
			if (deleted==NULL){
				printf("Order number invalid!\n");
			}
			if (deleted!=NULL){
			printf("Delete %s success!\n",deleted->name);
		    free(deleted);
		    }
		}	
	}while(choose!=4);
	return 0;
}
