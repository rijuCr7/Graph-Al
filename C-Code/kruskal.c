#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{
	int v1;
	int v2;
	int wt;
}edges;
void shiftDown(edges *arr,int start,int end){
	int parent,child;
	parent=start;
	while((2*parent)+1<=end){//while atleast 1 left child exists
		child=(2*parent)+1;//assign child to left child
		//checking whether the right child weight is greater than left child
		if(child<end && arr[child].wt<arr[child+1].wt){
			child=child+1;//make child the right child
		}
		//if child's weight is bigger than parent's weight
		if(arr[child].wt>arr[parent].wt){
			//swap child and parent
			edges temp=arr[child];
			arr[child]=arr[parent];
			arr[parent]=temp;
			parent=child;//make child the new parent
		}
		else{
			return;
		}
	}
}
void heapify(edges *arr,int count){
	int start,i;
	start=(int)floor((count-2)/2);//start from the least(lowest) parenr
	while(start>=0){
		shiftDown(arr,start,count-1);//trickle down the element if it violates the heap property
		start--;//move down the heap to get successive parents
	}
}
void heapSort(edges *arr,int count){
	int end;
	heapify(arr,count);//make a min heap of the array
	end=count-1;//decrease the count by 1
	while(end>=0){//while the entire array hasn't been sorted
		edges c=arr[0];//extract the minimum in O(1) time
		arr[0]=arr[end];//move the top to the end for deletion and repeat heapify
		arr[end]=c;
		end--;
		shiftDown(arr,0,end);//continue trickling
	}
} 				
void findUnion(int *p,edges e){
	int i=e.v1;//storiing the first vertex
	int j=e.v2;//storing the second vertex
	//checking component of i
	while(p[i]>-1){
		i=p[i];
	}
	//checking component of j
	while(p[j]>-1){
		j=p[j];
	}
	//if they do not belong to the same component then merge them and include that edge
	if(i!=j){
		p[j]=i;
		printf("%d %d %d\n",e.v1,e.v2,e.wt);
	}
}
void findKrus(edges *edgs,int size,int vertex){
	int *p;//component array
	p=malloc(vertex*sizeof(int));//allocating component array of size the number of vertices
	edges e;//variable for  holding edges
	int i;
	for(i=0;i<vertex;i++){
		p[i]=-1;//initially all components are -1
	}
	for(i=0;i<size;i++){
		e=edgs[i];//pick up an edge from the edge array
		findUnion(p,e);//find the union of  the vertices in the edge
	}
}
int main(){
	FILE *fp;
	fp=fopen("kruskal.txt","r");
	if(fp==NULL){
		printf("Unable to open File!!");
		return 0;
	}
	int vertex,edge;
	fscanf(fp,"%d",&vertex);
	fscanf(fp,"%d",&edge);
	edges *edgs;
	edgs=malloc((2*edge)*sizeof(edges));
	int i=0,x,y,z;
	while(3==fscanf(fp,"%d,%d,%d",&x,&y,&z)){
		edgs[i].v1=x;
		edgs[i].v2=y;
		edgs[i].wt=z;
		i++;
	}
	heapSort(edgs,(2*edge));
	printf("==============================\n");
	printf("The minimum spanning tree is:\n");
	printf("==============================\n");
	findKrus(edgs,(2*edge),vertex);
	printf("==============================\n");
	return 0;
}
	
	
