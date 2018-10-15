#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BaseBTree.h"

struct nodo{
    char* Titulo; //titulo de um artigo
    char* Autor; //nome do autor de uma revisão
    char* Timestamp; //timestamp de uma revisão
    long dups; //Duplicados
    long id;  // id do artigo ou revisão
    long IDautor; // id do autor da revisão
    long nchar; //tamanho do artigo
    long nwords; //numero de palavras do artigo
    long nrevisoes;  //numero de revisoes do artigo

    struct ABP *revisoes; // arvore de revisões do artigo.
};

struct ABP{
    struct nodo *info; //informação do nodo

    int height; //altura da arvore.
    struct ABP *ptEsq; 
    struct ABP *ptDir;
};


Nodo ABP_nodeInit(int art)
{
    //inicialização da struct nodo
    Nodo new = (Nodo) malloc(sizeof(struct nodo));
    new->Titulo = NULL;
    new->Autor = NULL;
    new->Timestamp = NULL;
    new->nchar = -1;
    new->nwords = -1;
    new->dups = -1;
    new->id = -1;
    new->IDautor = -1;
    new->nrevisoes = -1;
    //caco seja artigo inializa arvore de revisões.
    if(art){
        new->revisoes = ABP_init(0);
    }
    else new->revisoes = NULL;

    return new;
}

ABP ABP_init (int art)
{
    //Inicializa uma arvore.
    ABP new = (ABP) malloc(sizeof(struct ABP));
    //implementa as diferentes versões da nodeInit caso seja um artigo ou não.
    if(art)
        new->info = ABP_nodeInit(1);
    else 
        new->info = ABP_nodeInit(0); 
    new->ptDir = new->ptEsq = NULL;
    new->height = 0;
    return new;
}

ABP ABP_initRoot(Nodo root)
{
    //é possivel que nao usemos isto...................................................
    ABP n = (ABP) malloc(sizeof(struct ABP));
    n->info = root;
    n->ptEsq = n->ptDir = NULL;
    return n;
}

//verifica que existe arvore na esquerda
int ABP_hasLeft(ABP n)
{
    if (n->ptEsq != NULL) return 1;
    else return 0;
}
//verifica se existe arvore na direita
int ABP_hasRight(ABP n)
{
    if (n->ptDir != NULL) return 1;
    else return 0;
}
//devolve arvore da esquerda
ABP ABP_left(ABP a)
{
    return a->ptEsq;
}
//devolve arvore da direita
ABP ABP_right(ABP a)
{
    return a->ptDir;
}
//verifica se existe nodo
int ABP_hasNode(ABP a){
    if (a->info)
        return 1;
    else 
        return 0;
}

//Devolve arvore de revisões do artigo com o id passado como argumento
ABP ABP_getRevisoes(ABP a, long id)
{

    if((a->info)->id > id) return ABP_getRevisoes(a->ptEsq, id);
    else if((a->info)->id < id) return ABP_getRevisoes(a->ptDir, id);
    else return a->info->revisoes;
}

//Devolve o 'Nodo' com a informação. Maioritariamente utilizado em gets desta estrutura.
Nodo ABP_getInfo(ABP a, long id)
{
    Nodo r = NULL;
    if(a){
        r = ABP_nodeInit(0);
        if((a->info)->id > id)  r = ABP_getInfo(a->ptEsq, id);
        else if((a->info)->id < id) r = ABP_getInfo(a->ptDir, id);
        else r = a->info;
    }

    return r;
}

/*Funções gets que permitem ir à estrutura e retornar qualquer tipo de informação relativa ao artigo ou à revisão.*/
char* ABP_getTitulo(ABP a, long ID)
{
    Nodo info = ABP_getInfo(a, ID);
    if(info)
        return info->Titulo;
    else return NULL;
}

char* ABP_getAutor(ABP a, long ID)
{
    Nodo info = ABP_getInfo(a,ID);
    if(info)
        return info->Autor;
    else return NULL;
}

char* ABP_getTimestamp(ABP a, long ID)
{
    Nodo info = ABP_getInfo(a,ID);
    if(info)
        return info->Timestamp;
    else return NULL;
}
long ABP_getID(ABP a)
{
    if(a && a->info)
        return a->info->id;
    else return -1;
}

long ABP_getDups(ABP a)
{
    if(a && a->info)
        return a->info->dups;
    else 
        return -1;
}

long ABP_getIDAutor(ABP a, long ID)
{
    Nodo info = ABP_getInfo(a,ID);
    if(info)
        return info->IDautor;
    else return -1;
}

long ABP_getNRevisoes(ABP a)
{
    if(a && a->info)
        return a->info->nrevisoes;
    else return -1;
}

long ABP_IDgetNChar(ABP a, long ID)
{
    int r=0;
    if(a && a->info){
        if (a->info->id > ID) r = ABP_IDgetNChar(a->ptEsq, ID);
        else if(a->info->id < ID) r = ABP_IDgetNChar(a->ptDir, ID);
        else r = a->info->nchar;
    }
    return r;
}

long ABP_getNChar(ABP a)
{
        if(a && a->info)
            return a->info->nchar;
        else return -1;
}

long ABP_IDgetNWords(ABP a, long ID)
{
    int r=0;
    if (a && a->info){
        if(a->info->id > ID) r = ABP_IDgetNWords(a->ptEsq, ID);
        else if(a->info->id < ID) r = ABP_IDgetNWords(a->ptDir, ID);
        else r = a->info->nwords;
    }
    return r;
}

long ABP_getNWords(ABP a)
{
    if(a && a->info)
        return a->info->nwords;
    else return -1;
}

/*Funções de balanceamento das árvores.*/
ABP ABP_rotateLeft(ABP n)
{
    ABP newroot = n->ptDir;
    ABP temp = newroot->ptEsq;
    newroot->ptEsq = n;
    n->ptDir = temp;
    return newroot;

}

ABP ABP_rotateRight(ABP n)
{
    ABP newroot = n->ptEsq;
    ABP temp = newroot->ptDir;
    newroot->ptDir = n;
    n->ptEsq = temp;
    return newroot;
}

int ABP_getBalance(ABP n){
    if (n == NULL)
        return 0;
    return ABP_height(n->ptEsq) - ABP_height(n->ptDir);
}

//Verifica se existe um artigo com o id passdo como argumento na arvore.
int ABP_procuraID(long id, ABP a)
{
    ABP temp = a;
    while(temp && (temp->info)->id != id)
    {
        if((temp->info)->id > id) temp = temp->ptEsq;
        else temp = temp->ptDir;
    }
    if(temp) return 1;
    else return 0;
}
//liberta a memoria alocada para esta estrutura de dados.
void ABP_destroi(ABP raiz) {
    if (raiz != NULL) {
        ABP_destroi(raiz->ptEsq);
        ABP_destroi(raiz->ptDir);
        free (raiz);
    }
}
//Devolve a altura da arvore.
int ABP_height(ABP n){
    if (n == NULL)
        return 0;
    return n->height;
}
//Calcula o maximo entre dois valores inteiros.
int ABP_max(int a, int b)
{
    return (a > b)? a : b;
}


/*Funções de inserção nas árvores.*/

/*INSERIR REVISÃO MANTENDO ARVORE ORDENADA INORDER POR ID*/
ABP ABP_insertRev (ABP node, long id, long idrev, char* timeStamp, char* username, long colaboratorId)
{  
    // 'a' toma o valor do nodo do artigo ao qual pertence a revisão a inserir
    Nodo a = ABP_getInfo(node,id);
    //Caso ainda não exista uma revisão com o id 'idrev' insere e incrementa o numero de revisões do artigo
    if(!ABP_getInfo(a->revisoes,idrev)){  
        a->revisoes = ABP_insertRevAUX(a->revisoes, idrev, timeStamp, username, colaboratorId);
        a->nrevisoes +=1;
    } 
    return node;
}

ABP ABP_insertRevAUX(ABP node, long idrev, char* timeStamp, char* username, long colaboratorId)
{
    //Caso a arvore seja NULL, ou o nodo esteja livre insere a revisão.
    if (node == NULL || node->info->id == -1){
        node = ABP_init(0);
        (node -> info -> Autor) = strdup(username);
        (node -> info -> Timestamp) = strdup(timeStamp);
        node -> info -> id = idrev;
        node -> info -> IDautor = colaboratorId;
        node -> height = 0;
        return node;
    }
    else if (idrev < (node->info->id)){
        //recursividade para a esquerda.
        node->ptEsq  = ABP_insertRevAUX(node->ptEsq, idrev, timeStamp, username, colaboratorId);

    }
    else if (idrev > (node-> info -> id)){
        //recursividade para a direita.
        node->ptDir = ABP_insertRevAUX(node->ptDir, idrev, timeStamp, username, colaboratorId);
    }

    //atualização da altura do nodo atual.
    node->height = 1 + ABP_max(ABP_height(node->ptEsq),
                           ABP_height(node->ptDir));

    // Verifica se o nodo atual esta balanceado.
    int balance = ABP_getBalance(node);

    //Caso o nodo não esteja balanceado aplica as funções de rotate.
    if (balance > 1 )
        node = ABP_rotateRight(node);

    else if (balance < -1) 
        node = ABP_rotateLeft(node);

    return node;

}


/*INSERIR ARTIGO MANTENDO UMA ARVORE ORDENADA INORDER POR ID*/
ABP ABP_insert(ABP node, char* title, long id, long idrevision, char* timeStamp, char* username, long colaboratorId, long nchar, long nwords)
{
    // Caso não exista arvore ou o nodo esteja livre insere o artigo.
    if (node == NULL || node->info->id == -1){
        node = ABP_init(1);
        (node -> info -> Titulo) = strdup(title);
        node -> info -> id = id;
        node -> info -> nchar = nchar;
        node -> info -> nwords = nwords;
        node -> info -> nrevisoes = 0;
        node -> info -> dups = 0;
        node -> height = 0;
        return node;
    }
 
    else if (id < (node->info->id)){
        //recursividade para a esquerda
        node->ptEsq  = ABP_insert(node->ptEsq, title, id, idrevision, timeStamp, username, colaboratorId, nchar, nwords);
    }
    else if (id > (node-> info -> id)){
        //Recursividade para a direita
        node->ptDir = ABP_insert(node->ptDir, title, id, idrevision, timeStamp, username, colaboratorId, nchar, nwords);
    }
    else{
        //Caso id seja igual(Artigo já pertence á arvore):
        node->info->dups++; //incrementa o numero de duplicados
        //Caso o numero de carateres do artigo duplicado seja superior ao anterior este é atualizado
        if(nchar > node->info->nchar) node->info->nchar = nchar;
        //Caso o numero de palavras do artigo duplicado seja superior ao anterior este é atualizado
        if(nwords > node->info->nwords) node->info->nwords = nwords;
        return node;
    }
    //Atualização da altura do nodo.
    node->height = 1 + ABP_max(ABP_height(node->ptEsq),
                           ABP_height(node->ptDir));
    //Determina se a arvore está balanceada
    int balance = ABP_getBalance(node);
    //Caso o nodo não esteja balanceado aplica as funções de rotate
    if (balance > 1)
        node = ABP_rotateRight(node);

    else if (balance < -1) 
        node = ABP_rotateLeft(node);

    return node;
}
