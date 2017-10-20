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
struct path{
	int vertex;
	int label;
	struct path *next;
};
struct path *allocateEdge(int v,int l){
	struct path *temp;
	temp=malloc(sizeof(struct path));
	temp->vertex=v;
	temp->label=l;
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
void insertPrior(struct path **start,int ver,int l){
	if((*start)==NULL){
		(*start)=allocateEdge(ver,l);
		return;
	}
	else{
		struct path *p=*start;
		struct path *q=NULL;
		if(((p!=NULL)&&(((p->label)<l)))){
			q=p;
			p=p->next;
		}
		if(q==NULL){
			struct path *temp=allocateEdge(ver,l);
			temp->next=(*start);
			(*start)=temp;
		}
		else{
			struct path *temp=allocateEdge(ver,l);
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
void djiks(edges *edgs,int vertices,int size,int start){
	int *l;
	l=malloc(vertices*sizeof(int));
	int i;
	for(i=0;i<vertices;i++){
		l[i]=999999;
	}
	l[start]=0;
	struct node *b=NULL;
	int c=count(b);
	int n=vertices;
	struct path *pr=NULL;
	while(c!=n){
		int i;
		for(i=0;i<n;i++){
			if(!isPresant(b,i)){
				insertPrior(&pr,i,l[i]);
			}
		}
		int u=pr->vertex;
		insert(&b,u);
		int k,wet;
		for(i=0;i<n;i++){
			if(!isPresant(b,i)){
				for(k=0;k<size;k++){
					if((edgs[k].v1==u)&&(edgs[k].v2==i)){
						wet=edgs[k].wt;
					}
					else{
						wet=999999;
					}
					if(l[i]>(l[u]+wet)){
						l[i]=l[u]+wet;
					}
				}
			}
		}
		c=count(b);
		pr=NULL;
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d\t:",i);
		printf("%d\t\n",l[i]);
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
	printf("Enter the starting vertex:\n");
	int start;
	scanf("%d",&start);
	printf("\n");
	printf("The all pair shortest paths are:\n");
	djiks(edgs,vertex,(2*edge),start);
	printf("\n");
	return 0;
}
