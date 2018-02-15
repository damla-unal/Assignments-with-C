#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct NaryNode {
 int data ;
 int n ;
struct NaryNode **child ;
};


struct NaryNode *createNode (int data)
{

struct NaryNode *node = ( struct NaryNode*)calloc(1 ,sizeof( struct NaryNode));

node->data =data;
node->n =0;
node->child = (struct NaryNode**)calloc(50,sizeof(struct NaryNode*)) ;

return node ;
}


void appendChild2(struct NaryNode *root, int data)
{

    root->child[ root->n++] = createNode(data);

}

/*void traverse(struct NaryNode *root) // traverse yapip ekrana bastirma kontrol icin
{
    int i;
    if (root)
    {
        printf("%d ", root->data);
        for (i = 0; i <root->n; i++)
            traverse(root->child[i]);
    }

}*/
void traverse2(struct NaryNode *root,FILE *yaz)  // output dosyasina yazdirma
{
    int i;
    if (root)
    {
        fprintf(yaz,"%d ", root->data);
        for (i = 0; i <root->n; i++)
            traverse2(root->child[i],yaz);
    }
}


void getLeafCount(struct NaryNode* root, int *count)
{
    int i;
    if(root->n==0)
    {
        *count=*count+1;
    }

    for (i = 0; i <root->n; i++)
        getLeafCount(root->child[i],count);

}

struct NaryNode** createLeaf_arr(struct NaryNode *root,struct NaryNode **leaf_arry,int *size) // burdan leaf arrayi olustur ve onu yani arrayi döndür.
{
    int i;
    if(root->n==0)
    {

            leaf_arry[*size]=root;
            *size=*size+1;
    }

    for (i = 0; i <root->n; i++)
        createLeaf_arr(root->child[i],leaf_arry,size);

    return leaf_arry;
}

struct NaryNode *temp =NULL;
void searching(struct NaryNode *root,int data)
{
    int i;
    if (root)
    {
        if(root->data==data){
            temp=root;
        }
        for (i = 0; i <root->n; i++)
            searching(root->child[i],data);


    }return;
}


int main()
{
    char first_input[100];
    char second_input[100];

    scanf("%s",first_input);
    scanf("%s",second_input);


    FILE *fp1;  /////////////////////////////input1.txt okuma /////////////////////////////////////////
   	int first_col[200];
   	int secod_col[200];
   	int i=0,c;
   	fp1 = fopen(first_input,"r");

    while(c!=EOF)
    {
        c=fscanf(fp1,"%d %d",&first_col[i],&secod_col[i]);
        if(c!=EOF)
        {
            i++;
        }
    }

    int number_node=i; //////////////// toplam node sayisi//////////////////////////////////
    int arr_size=0;
    int count=0,q,w;

////////////////// agaci olusturma /////////////////////////////////////

    struct NaryNode *tree =NULL;
    tree=createNode(first_col[0]);

    for(q=0;q<secod_col[0];q++)
        appendChild2(tree,first_col[1+q]);


    int x,y,t=1,m;

    for(x=1+q;x<number_node;)
    {

        count=0;
        getLeafCount(tree,&count); // leaf sayisi
        struct NaryNode** leaf_arry=(struct NaryNode**)malloc(count*sizeof(struct NaryNode*)); // leaf array olustu
        arr_size=0;
        createLeaf_arr(tree,leaf_arry,&arr_size);

        if(secod_col[t]>count){

            for(y=0;y<count;y++){
                if(x==number_node)
                break;
                appendChild2(leaf_arry[y],first_col[x]);
                x++;

            }
            for(w=0;w<secod_col[t]-count;w++){

                if(x==number_node)
                break;

                appendChild2(leaf_arry[w%count],first_col[x]);
                x++;

            }
        }

        else if(secod_col[t]<=count){
            for(m=0;m<secod_col[t];m++){
                if(x==number_node)
                    break;
                appendChild2(leaf_arry[m],first_col[x]);
                x++;
            }

        }t++;

    }

   // traverse(tree);

/////////////////////////////// komut.txt kismi/////////////////////////////////////////

    FILE *fp2;
    FILE *yaz;
    char ch[1];
    int val;
    fp2=fopen(second_input,"r");
    yaz=fopen("output.txt","w");


    int c2;
    while (c2 != EOF){

      c2 = fscanf(fp2,"%s %d",ch,&val);

      if (c2 != EOF)
         if(strcmp(ch,"l")==0){
            temp=NULL;
            searching(tree,val);
            traverse2(temp,yaz);
            fprintf(yaz,"%c",'\n');
         }
         else if(strcmp(ch,"d")==0){

         }
    }


    fclose(fp1);
    fclose(fp2);
    fclose(yaz);
    return 0;
}
