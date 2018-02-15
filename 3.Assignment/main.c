#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

struct Node
{
char *data;
char dosya[100];
int count;
struct Node *next;
};

int wordControl(struct Node *header,char * word)
{
    if(header!=NULL){
        if(strcmp(header->data,word)==0){
            header->count+=1;     //kelime eger linked listte var olan bir kelimeyse counterini arttiriyor
        }
        else{
            return wordControl(header->next,word);
        }
    }
    else{
        return 0;
    }
}
// Given a reference (pointer to pointer) to the head of a list and an int, appends a new node at the begin
void append(struct Node** head_ref, char *new_data,char dosya[])
{
    int control=wordControl(*head_ref,new_data);
    if(!control){

	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));// allocate memory for node


	new_node->data = new_data;
	strcpy(new_node->dosya,dosya); // hangi txt nin listesi oldugunu anlamak icin
	new_node->count=1;
	new_node->next=NULL;

	// Make next of new node as head
    if((*head_ref)!=NULL) new_node->next = (*head_ref);

    // move the head to point to the new node
    (*head_ref)    = new_node;
    }

}
char *getword2(char *key){
    char word1[30];
    int i=0;

    while(isalnum(key[i])){
        word1[i]=tolower(key[i]);
        i++;
    }
    word1[i]='\0';
    return strdup(word1);
}

// this function is for -a command
void insert_word( char *key,int adet,struct Node **head_ref,char dosya[])
{
    int for_break=0;
    struct Node* tmp= *head_ref;
    while (tmp != NULL)
    {
        if(strcmp(tmp->data,getword2(key))==0){
            tmp->count+=adet;
            for_break=1;
        }
        if(!for_break){
            if(tmp->next==NULL){
            struct Node* new_node=(struct Node*) malloc(sizeof(struct Node));
            new_node->data=getword2(key);
            strcpy(new_node->dosya,dosya);
            new_node->count=adet;
            new_node->next=NULL;
            tmp->next=new_node;
            tmp=new_node;
            }
        }
	tmp = tmp->next;
    }
}

//this function is for -d command
void deleteNode(struct Node **head_ref, char *key)
{
    // Store head node
    struct Node* temp = *head_ref, *prev;
    if (temp != NULL && strcmp(temp->data,key)==0)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    while (temp != NULL && strcmp(temp->data,key)!=0)
    {
        prev = temp;
        temp = temp->next;
    }
    // If key was not present in linked list
    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp);  // Free memory
}

//this function is swapping the nodes.
struct Node *node_swap( struct Node *l1,struct Node *l2 )
{
    l1->next = l2->next;
    l2->next = l1;
    return l2;
}
//this function is sorting linked list by big to small
struct Node *sirala( struct Node *start )
{
    struct Node *p, *q, *top;
    int changed = 1;

     //We need an extra item at the top of the list just to help with assigning switched data to the 'next' of a previous item.
     //It (top) gets deleted after the data is sorted.
    top = (struct Node *)malloc(sizeof(struct Node));
    top->next = start;
    if( start != NULL && start->next != NULL ) {

        while( changed ) {
            changed = 0;
            q = top;
            p = top->next;
            while( p->next != NULL ) {
                if( p->count < p->next->count ) {
                    q->next = node_swap( p, p->next );
                    changed = 1;
                }
                q = p;
                if( p->next != NULL )
                    p = p->next;
            }
        }
    }
    p = top->next;
    free( top );
    return p;
}


// This function prints contents of linked list starting from head
void printList(struct Node *node)
{
    struct Node* tmp=node;
while (tmp != NULL)
{
	printf("%s %s\n",tmp->dosya,tmp->data);
	tmp = tmp->next;
}
}

// this function is check whether or not there is in word
struct Node* find(struct Node* ilk, char* word) {  // kelime yoksa null dondurur

   struct Node* current = ilk;

   //if list is empty
   if(ilk== NULL) {
      return NULL;
   }

   while(strcmp(current->data, word)!=0) {
      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }
   //if data found, return the current Link
   return current;
}

//kac tane ortak olmayan kelime varsa j sayisi verir
int findortak_degil(char *x[], char* word) {
    int i,j=0;
    for(i=0;i<10;i++){
        if(strcmp(x[i],word)!=0){
            j++;
        }
    }
  return j;
}

//Her iki txt dosyasinin ilk 10 kelimesinin birlesim vektorunu olusturur
int birlesim_liste(struct Node* head1,struct Node* head2,char *x[]){

    struct Node* tmp3=head2;
    int tmp4;
    int i,counter=0;

    for(i=0;i<10;i++){
        tmp4=findortak_degil(x,tmp3->data);
        if(tmp4==10){
            counter++;
            x[9+counter]=tmp3->data; // ortak olmayan kelimeleri listeye ekler
        }
        tmp3=tmp3->next;
    }
    return counter;
}

//benzerlik bulmak icin kullanilcak matrisi olusturur
int design2Darray(struct Node* head1,struct Node* head2,int **dizi,char *x[])
{
    struct Node* tmp=head1;
    struct Node* tmp2;
    struct Node* x1;
    struct Node* x2;
    struct Node* tmp3=head1;
    struct Node* tmp4=head2;

    int i,t;
    for(i=0;i<10;i++){
        dizi[0][i]=tmp->count; // ilk txt dosyasinin ilk 10 kelimesinin count u matrise koyuldu
        x[i]=tmp->data;
        tmp2=find(head2,tmp->data);
        if(tmp2){
            dizi[1][i]=tmp2->count; //ikinici txt dosyasindaki count degerleri matrise koyuldu
        }
        else{
            dizi[1][i]=0; // eger elime yoksa count u 0 oldu
        }
        tmp = tmp->next;
    }

    int no_common=birlesim_liste(head1,head2,x); // ortak olmayan kelime sayisi

   for(t=10;t<10+no_common;t++){
        x1=find(tmp3,x[t]);
        x2=find(tmp4,x[t]);
    if(x1!=NULL)
       dizi[0][t]=find(tmp3,x[t])->count;
    else
        dizi[0][t]=0;
    if(x2!=NULL)
       dizi[1][t]=find(tmp4,x[t])->count;
    else
        dizi[1][t]=0;

    }

    return no_common;
}

// dosyadan okunan kelimeleri splitler
char *getWord(FILE *fp){
    char word[100];
    int ch, i=0;

    while(EOF!=(ch=fgetc(fp)) && !isalnum(ch))
        ;
    if(ch == EOF)
        return NULL;
    do{
        word[i++] = tolower(ch);
    }while(EOF!=(ch=fgetc(fp)) && isalnum(ch));

    word[i]='\0';
    return strdup(word);
}

// this function is created matrix
int ** createMatrix()
{
    int **dizi=(int **)malloc(2*sizeof(int*));
    int i;
    for(i=0;i<2;i++){
        dizi[i]=malloc(20*sizeof(int));
    }
    return dizi;

}
void free_memory(int **arr) // function to free memory for 2D array
{
    int i1;
    for( i1 = 0; i1 <2; i1++ )
    {
        free(arr[i1]);
    }
    free(arr);
}

int main()
{
    struct Node* head = NULL;
    struct Node* head2 = NULL;

    char *x[20]; // benzerlik bulmak icin tutulan kelimeler listesi
    int **dizi=createMatrix();


    char komut[10];
    printf("Please Enter Command:\n");


    while(strcmp(komut,"-q")!=0)
    {
        scanf("%s",komut);
    if(strcmp(komut,"-r")==0)///////////READ FILE and ADD LINKED LIST//////////////
    {
        char dosyaadi[100];
        char file1[100];

        char *split[20];
        int i=0;


        scanf("%s",dosyaadi);

        strcpy(file1,dosyaadi);
        split[i]=strtok(file1,"/");
        while(split[i]!=NULL)
        {
        split[++i] = strtok(NULL,"/");
        }


        if(head==NULL){ // d1.txt
            FILE *fp = fopen(dosyaadi,"r");
            char *word1;
            while((word1=getWord(fp))){
                append(&head, word1,split[i-1]);
                head=sirala(head);
            }
        }
        else if (head2==NULL){ //d2.txt
            FILE *fp = fopen(dosyaadi,"r");
            char *word1;
            while((word1=getWord(fp))){
                append(&head2, word1,split[i-1]);
                head2=sirala(head2);
            }
        }
        else{
            printf("Only you can read two files.\n");
        }
printList(head);
    }
    else if(strcmp(komut,"-a")==0){//////////APPEND the LINKED LIST//////////////
        char kelime[30];
        int adet;
        char file[100];
        scanf("%s",kelime);
        scanf("%d",&adet);
        scanf("%s",file);

        if(head2==NULL && head==NULL) printf("Lutfen ilk once dosya okuma komutunu giriniz.\n");

        else if(strcmp(head->dosya,file)==0){
            insert_word(kelime,adet,&head,file);
            head=sirala(head);
        }
        else if(strcmp(head2->dosya,file)==0){
            insert_word(kelime,adet,&head2,file);
            head2=sirala(head2);
        }

    }

    else if(strcmp(komut,"-d")==0)/////////////DELETE NODE//////////////
    {
        char kelime[30];
        char file[100];
        scanf("%s",kelime);
        scanf("%s",file);

        if(head2==NULL && head==NULL) printf("Lutfen ilk once dosya okuma komutunu giriniz.\n");

        else if(strcmp(head->dosya,file)==0){
            deleteNode(&head,kelime);
        }
        else if(strcmp(head2->dosya,file)==0){
            deleteNode(&head2,kelime);
        }

    }
    else if(strcmp(komut,"-n2")==0)
    {
        char dosya[100];
        scanf("%s",dosya);
        printf("Not found.Try other commands \n");
    }

    else if (strcmp(komut,"-s")==0)////////CALCULATE SIMILARITY//////////////////
    {
        char dosya1[100];
        char dosya2[100];
        scanf("%s",dosya1);
        scanf("%s",dosya2);

        if(head2==NULL || head==NULL) printf("Lutfen ilk once dosya okuma komutunu giriniz.\n");

        else if(strcmp(head->dosya,dosya1)==0){
            int no_common=design2Darray(head,head2,dizi,x);
            int multi=0;//ic carpim
            double norm1=0;//ilk alinan dosyanin vektorunun normu
            double norm2=0;//ikinci alinan dosyanin vektorunun normu
            int m=0;
            for(m=0;m<10+no_common;m++){
                multi+=dizi[0][m]*dizi[1][m];
                norm1+=dizi[0][m]*dizi[0][m];
                norm2+=dizi[1][m]*dizi[1][m];
            }
            float sim;
            if(sqrt(norm1)*sqrt(norm2)==0){//division zero oldugunda benzerligi 0 yapiyor
                sim=0;
            }
            else{
                sim=multi/(sqrt(norm1)*sqrt(norm2));
            }
            printf("Cosine Similarity of %s and %s is %.3f\n",dosya1,dosya2,sim);

        }

        else if(strcmp(head2->dosya,dosya1)==0){
            int no_common=design2Darray(head2,head,dizi,x);
            int multi=0;//ic carpim
            double norm1=0;//ilk alinan dosyanin vektorunun normu
            double norm2=0;//ikinci alinan dosyanin vektorunun normu
            int m=0;
            for(m=0;m<10+no_common;m++){
                multi+=dizi[0][m]*dizi[1][m];
                norm1+=dizi[0][m]*dizi[0][m];
                norm2+=dizi[1][m]*dizi[1][m];
            }
            float sim;
            if(sqrt(norm1)*sqrt(norm2)==0){//division zero oldugunda benzerligi 0 yapiyor
                sim=0;
            }
            else{
                sim=multi/(sqrt(norm1)*sqrt(norm2));
            }
            printf("Cosine Similarity of %s and %s is %.3f\n",dosya1,dosya2,sim);
        }
    }

    }printf("---GOOD BYE---\n");
    free_memory(dizi);
    return 0;
}
