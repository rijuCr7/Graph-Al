#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *next;
};
struct node *allocateNode(int item){
	struct node *temp;
	temp=malloc(sizeof(struct node));
	temp->val=item;
	temp->next=NULL;
	return temp;
}
void insert(struct node **rear,int item){
	struct node *p=*rear;
	if((*rear)==NULL){
		(*rear)=allocateNode(item);
	}
	else{
		for(;(p->next)!=NULL;p=p->next){
			;
		}
		p->next=allocateNode(item);
	}
	return;
}
int delete(struct node **front){
	struct node *p=*front;
	int v;
	if((*front)==NULL){
		return -9999;
	}
	else{
		v=p->val;
		(*front)=(*front)->next;
	}
	return v;
}
int isEmpty(struct node *queue){
	if(queue==NULL){
		return 1;
	}
	return 0;
}
void bfs(int *vptr,int *eptr,int size,int vertices,int start){
	int *d,*sig,i;
	d=malloc(vertices*sizeof(int));
	sig=malloc(vertices*sizeof(int));
	for(i=0;i<vertices;i++){
		d[i]=-1;
		sig[i]=0;
	}
	struct node *queue=NULL;
	d[start]=0;
	sig[start]=1;
	insert(&queue,start);
	while(isEmpty(queue)!=1){
		int v=delete(&queue);
		printf("%d\t",v);
		for(i=vptr[v];i<vptr[v+1];i++){
			int w=eptr[i];
			if(d[w]<0){
				d[w]=d[v]+1;
				insert(&queue,w);
			}
		}
	}
}
int main(){
	FILE *fp;
	fp=fopen("bfs.txt","r");
	if(fp==NULL){
		printf("Unable to open file\n");
		return 0;
	}
	int vertex,edge,x,y,i,a=1;
	edges *edgs;
	fscanf(fp,"%d",&vertex);
	fscanf(fp,"%d",&edge);
	int *eptr,*vptr;
	eptr=malloc((2*edge)*sizeof(int));
	vptr=malloc(vertex*sizeof(int));
	while(fscanf(fp,"%d,%d",&x,&y)==2){
		if(x!=a){
			vptr[x]=i;
			a=x;
		}
		eptr[i]=y;
		i++;
	}
	fclose(fp);
	vptr[vertex]=(2*edge);
	for(i=0;i<vertex;i++){
		printf("%d\t",vptr[i]);
	}
	printf("\n");
	for(i=0;i<(2*edge);i++){
		printf("%d",eptr[i]);
	}
	printf("\n");
	int start;
	printf("==========================\n");
	printf("Enter the starting symbol:\n");
	scanf("%d",&start);
	printf("============================\n");
	printf("The bfs traversal is:\n");
	printf("============================\n");
	bfs(vptr,eptr,(2*edge),vertex,start);
	printf("\n");
	printf("============================\n");
	return 0;
}

	

