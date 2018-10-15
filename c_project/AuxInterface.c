#include "AuxInterface.h"


long AUX_all_articles(ABP Art)
{
	long c = 0;
	if(ABP_hasNode(Art))
		c = 1 + ABP_getDups(Art); //incrementa c para o numero de duplicados do artigo no node atual mais o artigo original.
	if(ABP_right(Art))
		c += AUX_all_articles(ABP_right(Art)); //incrementa c para o numero total de artigos e duplicados na arvore da direita.
	if(ABP_left(Art))
		c += AUX_all_articles(ABP_left(Art)); //incrementa c para o numero total de artigos e duplicados na arvore da esquerda.
	return c;
}

long AUX_unique_articles(ABP Art)
{
	long c = 0;
	if(ABP_hasNode(Art)) 
		c++; //incrementa c para o artigo do nodo atual.
	if(ABP_right(Art))
		c += AUX_unique_articles(ABP_right(Art)); //incrementa c para os artigos da arvore da direita.
	if(ABP_left(Art))
		c += AUX_unique_articles(ABP_left(Art)); //incrementa c para os artigos da arvore da esquerda.
	return c;
}

long AUX_all_revisions(ABP Art)
{
	long c = 0;
	if(ABP_hasNode(Art)) 
		c =  ABP_getNRevisoes(Art); //Devolve o numero de revisões do artigo atual
	if(ABP_right(Art))
		c += AUX_all_revisions(ABP_right(Art)); //Devolve o numero de revisoes da arvore da direita.
	if(ABP_left(Art))
		c += AUX_all_revisions(ABP_left(Art)); //Devolve o numero de revisões da arvore da esquerda.
	return c;
}
// v inicializado com todas as posições a '-1'
void AUX_top_10_contributors(ABP_C Cont, ABP_C Root, long* v, int n)
{
    int i, contributos, minpos =0; 
    int min = ABP_C_IDgetNCont(Root, v[0]); 
    /*valor de comparação para determinar o local do array no inicio da invocação
      onde se encontra o autor com menos contribuições*/
    if(Cont){
        AUX_top_10_contributors(ABP_C_left(Cont),Root, v, n); //recursividade para a arvore da esquerda.
        int cc = ABP_C_getNCont(Cont); //Numero de contribuições do contribuidor do nodo atual da arvore de contribuidores
        long ic = ABP_C_getIDautor(Cont); //ID do contribuidor do nodo atual da mesma arvore
        for(i = 0; i<n; i++)
        {
            //Preenchimento de posições livres.
            if(v[i] == -1){
                minpos = i;
                min = -1;
                break;
            }
            contributos = ABP_C_IDgetNCont(Root,v[i]); //Numero de contributos do autor com id 'v[i]' 
            /*Reatribuição do minimo e a posição do mesmo no array, caso o numero de contribuição do autor
              na posição atual do vetor seja menor que o que atualmente é considerado minimo*/
            if(min > contributos){
                min = contributos;
                minpos = i;
            }
        }
        //Preenchimento do array com o id do autor do nodo atual caso verifique as condições
        if(cc > min || (cc == min && ic < v[minpos]) ) 
            v[minpos] = ic;
    
        //Recursividade para a arvore da direita.
        AUX_top_10_contributors(ABP_C_right(Cont), Root, v, n);
        
    }
}
char* AUX_contributor_name(long contributor_id, ABP_C Cont)
{
    char* s = NULL;
    if( ABP_C_IDgetAutor(Cont,contributor_id) )
	   s = strdup(ABP_C_IDgetAutor(Cont,contributor_id)); //copiar a nome do autor com id "contributor_id" para s
    return s; 
}

void AUX_top_20_largest_articles(ABP Art, ABP Root, long* v, int n)
{
    int i, nCar, minpos = 0;
    int min = ABP_IDgetNChar(Root, v[0]);
    if(Art){
        //recursividade para a arvore da esquerda
        AUX_top_20_largest_articles(ABP_left(Art),Root, v, n);
        //Numero de carateres do artigo
        int cr = ABP_getNChar(Art);
        //id do artigo
        long ia = ABP_getID(Art);
        for(i = 0; i<n; i++)
        {
            //preenchimeto de posições livres
            if(v[i] == -1){
                minpos = i;
                min = -1;
                break;
            }
            //Numero de carateres do artigo com id v[i]
            nCar = ABP_IDgetNChar(Root,v[i]);
            if(min > nCar){
                min = nCar;
                minpos = i;
            }
        }
        /*preenchimento do array caso o numero de carateres do artigo atual seja superior
        ao minimo, ou caso igual se o id for inferior ao id do minimo.*/
        if(cr > min || (cr == min && ia < v[minpos]) ) 
            v[minpos] = ia;

        //Recursividade para a arvore da direita
        AUX_top_20_largest_articles(ABP_right(Art),Root, v, n);
    }
}

char* AUX_article_title(long article_id, ABP Art)
{
	char* s = NULL;
    if(ABP_getTitulo(Art, article_id)) 
        s = strdup(ABP_getTitulo(Art, article_id)); //Copia do titulo do artigo com id 'article_id' para s
	return s;
}

void AUX_top_N_articles_with_more_words(ABP Art,ABP Root, long* v, int n)
{
    int i, nPal, minpos = 0;
    int min = ABP_IDgetNWords(Root, v[0]);
    if(Art){
        //recursividade para a esquerda.
        AUX_top_N_articles_with_more_words(ABP_left(Art), Root, v, n);
        //numero de palavra do artigo no nodo atual.
        int pr = ABP_getNWords(Art);
        //id do artigo do nodo atual
        long ia = ABP_getID(Art);
        for(i = 0; i<n; i++)
        {
            //preenchimento de posições livres do vetor
            if(v[i] == -1){
                minpos = i;
                min = -1;
                break;
            }
            nPal = ABP_IDgetNWords(Root,v[i]);
            if(min > nPal){
                min = nPal;
                minpos = i;
            }
        }
        /*preenchimento do vetor caso verifique que o numero de palavras do artigo é maior
         do que o min ou caso seja igual o id seja inferior.*/
        if(pr > min || (pr == min && ia < v[minpos]) ) 
            v[minpos] = ia;

        //Recursividade para a direita.
        AUX_top_N_articles_with_more_words(ABP_right(Art),Root, v, n);
    }
}

char** AUX_titles_with_prefix (ABP a, char** s, char* prefix){
    int i = 0, j=0;
    if(a){
        //Recursividade para a esquerda
        s = AUX_titles_with_prefix(ABP_left(a), s, prefix);
        //copia do titulo do artigo do nodo atual.
        char* v = strdup(ABP_getTitulo(a, ABP_getID(a)));
        //Verifica se o 'prefix' é prefixo do titulo.
        while(prefix[i] == v[i] && prefix[i] != '\0')
            i++;
        //caso seja prefixo procura uma posição livre no array de strings.
        while(prefix[i] == '\0' && s[j] != NULL)
            j++;
        //caso seja prefixo preenche uma posição livre com o titulo do artigo do nodo atual
        if(prefix[i] == '\0') s[j] = strdup(v);
        //liberta o espaço alocado pela "strdup"
        free(v);
        //recursividade para a direita.
        s = AUX_titles_with_prefix(ABP_right(a), s, prefix);
    }
    return s;
}

char* AUX_article_timestamp(long article_id, long revision_id, ABP Art)
{
	char* s = NULL;
    if( ABP_getTimestamp(ABP_getRevisoes(Art, article_id), revision_id) )
        //Copia o timestamp da revisão pedida para s.
	   s = strdup(ABP_getTimestamp(ABP_getRevisoes(Art, article_id), revision_id));
	return s;

}
