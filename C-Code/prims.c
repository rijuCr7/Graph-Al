#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node{
	int val;
	struct node *next;
};
typedef struct{
	int v1;
	int v2;
	int wt;
}edges;
struct tree{
	edges ed;
	struct tree *next;
};
struct tree *allocateEdge(edges e){
	struct tree *temp;
	temp=malloc(sizeof(struct tree));
	temp->ed=e;
	temp->next=NULL;
	return temp;
};
struct node *allocate(int item){
	struct node *temp;
	temp=malloc(sizeof(struct node));
	temp->val=item;
	temp->next=NULL;
	return temp;
}
void insertPrior(struct tree **start,edges e){
	if((*start)==NULL){
		(*start)=allocateEdge(e);
		return;
	}
	else{
		struct tree *p=*start;
		struct tree *q=NULL;
		if(((p!=NULL)&&(((p->ed).wt)<e.wt))){
			q=p;
			p=p->next;
		}
		if(q==NULL){
			struct tree *temp=allocateEdge(e);
			temp->next=(*start);
			(*start)=temp;
		}
		else{
			struct tree *temp=allocateEdge(e);
			temp->next=p;
			q->next=temp;
		}
	}
	return;
}
void insert(struct node **start,int item){	
	if(*start==NULL){		
		*start=allocate(item);				
	}
	else{
		struct node *p;
		for(p=*start;(p->next)!=NULL;p=p->next){
			;
		}
		p->next=allocate(item);
	}
	return;
}
int count(struct node *start){
	struct node *p=start;
	int c=0;
	while(p!=NULL){
		c=c+1;
		p=p->next;
	}
	return c;
}
int isPresant(struct node *start,int item){
	struct node *p=start;
	while(p!=NULL){
		if((p->val)==item){
			return 1;
		}
		p=p->next;
	}
}
void prims(edges *edgs,int vertices,int size,int start){
	struct tree *heap=NULL;
	struct node *b=NULL;
	int c=count(b);
	insert(&b,start);
	int n=vertices;
	int i=0,j=0;
	while(c!=n){
		struct node *p=b;
		while(p!=NULL){
			for(i=0;i<size;i++){
				if((edgs[i].v1)==(p->val)){
					if(!isPresant(b,edgs[i].v2)){
						insertPrior(&heap,edgs[i]);
					}
				}
			}
			p=p->next;
		}
		printf("\n");
		printf("%d %d %d\n",(heap->ed).v1,(heap->ed).v2,(heap->ed).wt);
		for(i=0;i<size;i++){
			if(((heap->ed).v1==edgs[i].v1)&&((heap->ed).v2)==edgs[i].v2){
				edgs[i].wt=999999;
			}
		}
		for(i=0;i<size;i++){
			if(((heap->ed).v2==edgs[i].v1)&&((heap->ed).v1)==edgs[i].v2){
				edgs[i].wt=999999;
			}
		}
		if(!isPresant(b,(heap->ed).v2)){
			insert(&b,(heap->ed).v2);
		}
		heap=NULL;
		c=count(b);
	}
	return;
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
	printf("Enter the starting vertex:\n");
	int start;
	scanf("%d",&start);
	printf("\n");
	printf("The minimum spanning tree is:\n");
	prims(edgs,vertex,(2*edge),start);
	printf("\n");
	return 0;
}
