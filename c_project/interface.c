#include "interface.h"


struct TCD_istruct
{
	ABP MTree;
	ABP_C ConTree;
};

TAD_istruct init(){
	TAD_istruct qs = (TAD_istruct) malloc(sizeof(struct TCD_istruct));
	qs -> MTree = NULL; //árvore dos artigos/revisões
	qs -> ConTree = NULL; //árvore dos contribuidores
	return qs;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char * snaps_paths[]){


    if(nsnaps < 1){
        printf("Não existe documento\n");
        return qs;
    }

    int i=0;
    while(i<nsnaps){
        parseDoc (snaps_paths[i], &qs->MTree, &qs->ConTree);
        i++;
    }
    return qs;
}

/*Função que retorna todos os artigos encontrados nos backups analisados.*/
long all_articles(TAD_istruct qs){
	long c=0;
	c = AUX_all_articles(qs->MTree);
	return c;
}

/*Função que retorna todos os artigos únicos nos backups analisados.*/
long unique_articles(TAD_istruct qs){
	long c=0;
	c = AUX_unique_articles(qs->MTree);
	return c;
}

/*Função que retorna quantas revisões foram efetuadas nos backups analisados.*/
long all_revisions(TAD_istruct qs){
	long r=0;
	r = AUX_all_revisions(qs->MTree);
	return r;
}

void quicksort_long0(long arr[10],long low,long high, ABP_C Cont)
{
	long pivot,temp;
	int j,i;

	if(low<high){
		pivot = low;
		i = low;
		j = high;
		while(i<j){
    		while( (ABP_C_IDgetNCont(Cont, arr[i]) >= ABP_C_IDgetNCont(Cont, arr[pivot])) && (i<high)){
    			i++;
   			}
   			while(ABP_C_IDgetNCont(Cont, arr[j]) < ABP_C_IDgetNCont(Cont, arr[pivot])){
    			j--;
   			}
	   		if(i<j){ 
    			temp=arr[i];
				arr[i]=arr[j];
    			arr[j]=temp;
	   		}
  		}
 
	  	temp=arr[pivot];
  		arr[pivot]=arr[j];
  		arr[j]=temp;
  		quicksort_long0(arr,low,j-1,Cont);
  		quicksort_long0(arr,j+1,high,Cont);
 	}
}

/*Função que devolve um array com os identificadores dos 10 autores
 que contribuíram para um maior número de versões de artigos.*/
long* top_10_contributors(TAD_istruct qs){
	long* v = (long*)malloc( 10 * sizeof(long));
	int i=0;
	//preenchimento dos valores do array
	while(i<10){
		v[i] = -1;
		i++;
	}
	AUX_top_10_contributors(qs->ConTree,qs->ConTree, v, 10);
	i=0;
	quicksort_long0(v, 0, 9, qs->ConTree);
	printf("Contribuidores:\n");
	while(i<10){
		printf("ID: %ld -> Contri: %d \n", v[i], ABP_C_IDgetNCont(qs->ConTree,v[i]));
		i++;
	}
	return v;
}

/*Função que devolve o nome do autor com um determinado identificador.*/
char* contributor_name(long contributor_id, TAD_istruct qs){
	return AUX_contributor_name(contributor_id, qs->ConTree);
}
void quicksort_long1(long arr[10],long low,long high, ABP Art)
{
	long pivot,temp;
	int j,i;

	if(low<high){
		pivot = low;
		i = low;
		j = high;
		while(i<j){
    		while( (ABP_IDgetNChar(Art, arr[i]) >= ABP_IDgetNChar(Art, arr[pivot])) && (i<high)){
    			i++;
   			}
   			while(ABP_IDgetNChar(Art, arr[j]) < ABP_IDgetNChar(Art, arr[pivot])){
    			j--;
   			}
	   		if(i<j){ 
    			temp=arr[i];
				arr[i]=arr[j];
    			arr[j]=temp;
	   		}
  		}
 
	  	temp=arr[pivot];
  		arr[pivot]=arr[j];
  		arr[j]=temp;
  		quicksort_long1(arr,low,j-1,Art);
  		quicksort_long1(arr,j+1,high,Art);
 	}
}

/*Função que devolve um array com os identificadores dos 20 artigos que 
possuem textos com um maior tamanho em bytes.*/
long* top_20_largest_articles(TAD_istruct qs){
	long* v = (long*)malloc(sizeof(long)*20);
	int i=0;
	//preenchimento dos valores do array
	while(i<20){
		v[i] = -1;
		i++;
	}
	AUX_top_20_largest_articles(qs->MTree,qs->MTree, v, 20);
	int e;
	quicksort_long1(v, 0, 19, qs->MTree);
	printf("top 20 largest articles: \n");
	for(e=0; e < 20; e++){
		printf("id: %ld ->bytes: %ld \n", v[e], ABP_IDgetNChar(qs->MTree, v[e]));
	}
	return v;
}

/*Função que devolve o título do artigo com um determinado identificador.*/
char* article_title(long article_id, TAD_istruct qs){
	return AUX_article_title(article_id, qs->MTree);
}

void quicksort_long2(long arr[10],long low,long high, ABP Art)
{
	long pivot,temp;
	int j,i;
	if(low<high){
		pivot = low;
		i = low;
		j = high;
		while(i<j){
    		while( (ABP_IDgetNWords(Art, arr[i]) >= ABP_IDgetNWords(Art, arr[pivot])) && (i<high)){
    			i++;
   			}
   			while(ABP_IDgetNWords(Art, arr[j]) < ABP_IDgetNWords(Art, arr[pivot])){
    			j--;
   			}
	   		if(i<j){ 
    			temp=arr[i];
				arr[i]=arr[j];
    			arr[j]=temp;
	   		}
  		} 
	  	temp=arr[pivot];
  		arr[pivot]=arr[j];
  		arr[j]=temp;
  		quicksort_long2(arr,low,j-1,Art);
  		quicksort_long2(arr,j+1,high,Art);
 	}
}

/*Função que devolve um array com os identificadores dos N artigos
que possuem textos com um maior número de palavras.*/
long* top_N_articles_with_more_words(int n, TAD_istruct qs){
	long* v = (long*)malloc(sizeof(long)*n);
	int i=0;
	//preenchimento dos valores do array
	while(i<n){
		v[i] = -1;
		i++;
	}
	AUX_top_N_articles_with_more_words(qs->MTree, qs->MTree, v, n);
	int e;
	quicksort_long2(v, 0, n-1, qs->MTree);
	printf("top n articles with moar words:\n");
	for(e=0; e < n; e++){
		printf("id: %ld -> nwords: %ld \n", v[e], ABP_IDgetNWords(qs->MTree, v[e]));
	}
	return v;
}

void swap_str_ptrs(char **arg1, char **arg2)
{
    char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}

void quicksort_strs(char *args[], int len)
{
    int i, pvt=0;

    if (len <= 1)
        return;
    //troca o valor aleatório pelo último valor do array
    swap_str_ptrs(args+((int)rand() % len), args+len-1);
    //redifine o valor do pivot como zero e faz o scan
    for (i=0;i<len-1;++i)
    {
        if (strcmp(args[i], args[len-1]) < 0)
            swap_str_ptrs(args+i, args+pvt++);
    }
    //move o valor do pivot para a sua posição
    swap_str_ptrs(args+pvt, args+len-1);

    quicksort_strs(args, pvt++);
    quicksort_strs(args+pvt, len - pvt);
}

/*Função que devolve um array de títulos de artigos que começam com
 um prefixo passado como argumento da interrogação.*/
char** titles_with_prefix(char* prefix, TAD_istruct qs){
	long ua= unique_articles(qs);
	int len = 0;
	char** s = (char**) malloc(ua * sizeof(char*));
	for(int i = 0; i < ua; i++) s[i] = NULL;
	s = AUX_titles_with_prefix(qs->MTree, s, prefix);
	for(len = 0; s[len]; len++);
	quicksort_strs(s, len);
	for(int k = len; k < ua; k++) free(s[k]);
	printf("prefix: %s ____titles: \n", prefix);
	for(int j = 0; j<len; j++){
		printf("%s\n", s[j]);
	}
	return s;
}

/*Função que devolve o timestamp para uma certa revisão de um artigo.*/
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	return AUX_article_timestamp(article_id,revision_id, qs->MTree);
}

TAD_istruct clean(TAD_istruct qs){
	ABP_destroi(qs->MTree);
	ABP_C_destroi(qs->ConTree);
	free(qs);
	return NULL;
}
