#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void shiftDown(int *arr,int start,int end){
	int parent,child;
	parent=start;
	while(((2*parent)+1)<=end){
		child=(2*parent)+1;
		if((child<end)&&(arr[child]>arr[child+1])){
			child=child+1;
		}
		if(arr[child]<arr[parent]){
			int c=arr[child];
			arr[child]=arr[parent];
			arr[parent]=c;
		}
		else{
			return;
		}
	}
}
void heapify(int *arr,int count){
	int start,i;
	start=(int)floor((count-2)/2);
	while(start>=0){
		shiftDown(arr,start,count-1);
		start--;
	}
}
void heapSort(int *arr,int count){
	int end;
	heapify(arr,count);
	end=count-1;
	while(end>=0){
		int c=arr[0];
		arr[0]=arr[end];
		arr[end]=c;
		end--;
		shiftDown(arr,0,end);
	}
}
int main(){
	int *arr;
	arr=malloc(5*sizeof(int));
	int i;
	printf("Enter the array\n");
	for(i=0;i<5;i++){
		scanf("%d",&arr[i]);
	}
	printf("\n");
	printf("After Sorting\n");
	heapify(arr,5);
	printf("=============\n");
	for(i=0;i<5;i++){
		printf("%d\t",arr[i]);
	}
}
	
		
	


