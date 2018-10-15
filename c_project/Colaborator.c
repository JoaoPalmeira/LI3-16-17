#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colaborator.h"

struct ABP_C{
    char* Autor; //Nome do autor
    long IDautor; //ID do autor
    int nContribuicoes; //Numero de contribuições do autor


    int height; //Altura da arvore
    struct ABP_C *ptEsq;
    struct ABP_C *ptDir;
};


ABP_C ABP_C_init ()
{
    //Inicialização da estrutura.
    ABP_C new = (ABP_C) malloc(sizeof(struct ABP_C));
    new->Autor = NULL;
    new->IDautor = -1;
    new->nContribuicoes = -1;
    new->height = 0;
    new->ptEsq = NULL;
    new->ptDir = NULL;
    return new;
}

//Verifica se existe arvore na esquerda
int ABP_C_hasLeft(ABP_C n)
{
    if (n->ptEsq != NULL) return 1;
    else return 0;
}
//Verifica se existe arvore na direita
int ABP_C_hasRight(ABP_C n)
{
    if (n->ptDir != NULL) return 1;
    else return 0;
}
//Devolve arvore da esquerda
ABP_C ABP_C_left(ABP_C a)
{
    return a->ptEsq;
}
//Devolve arvore da direita
ABP_C ABP_C_right(ABP_C a)
{
    return a->ptDir;
}

/*Funções gets que permitem ir à estrutura buscar qualquer tipo de informação relativa ao contribuidor.*/
char* ABP_C_IDgetAutor(ABP_C a, long id)
{
    char* r=NULL;
    if(a){
        if(a->IDautor > id) r = ABP_C_IDgetAutor(a->ptEsq, id);
        else if(a->IDautor < id) r = ABP_C_IDgetAutor(a->ptDir, id);
        else{
            if(a->Autor)
                r = strdup(a->Autor);
        }
    }
    return r;
}

char* ABP_C_getAutor(ABP_C a)
{
    return  a->Autor;
}

long ABP_C_getIDautor(ABP_C a)
{
    return a->IDautor;
}

int ABP_C_IDgetNCont(ABP_C a, long id)
{
    int r=0;
    if(a){
        if(a->IDautor > id) r = ABP_C_IDgetNCont(a->ptEsq, id);
        else if(a->IDautor < id) r = ABP_C_IDgetNCont(a->ptDir, id);
        else r = a->nContribuicoes;
    }
    return r;
}
int ABP_C_getNCont(ABP_C a)
{
    return a->nContribuicoes;
}

/*Funções de balanceamento das árvores.*/
ABP_C ABP_C_rotateLeft(ABP_C n)
{
    ABP_C newroot = n->ptDir;
    ABP_C temp = newroot->ptEsq;
    newroot->ptEsq = n;
    n->ptDir = temp;
    
    return newroot;

}

ABP_C ABP_C_rotateRight(ABP_C n)
{
    ABP_C newroot = n->ptEsq;
    ABP_C temp = newroot->ptDir;
    newroot->ptDir = n;
    n->ptEsq = temp;
    
    return newroot;
}

int ABP_C_getBalance(ABP_C n){
    if (n == NULL)
        return 0;
    return ABP_C_height(n->ptEsq) - ABP_C_height(n->ptDir);
}
//Verifica se existe autor com o id passado como argumento
int ABP_C_procuraID(int id, ABP_C a)
{
    ABP_C temp = a;
    while(temp && temp->IDautor != id)
    {
        if(temp->IDautor > id) temp = temp->ptEsq;
        else temp = temp->ptDir;
    }
    if(temp) return 1;
    else return 0;
}

//Liberta o espaça alocado por esta estrutura.
void ABP_C_destroi(ABP_C raiz) {
    if (raiz != NULL) {
        ABP_C_destroi(raiz->ptEsq);
        ABP_C_destroi(raiz->ptDir);
        free (raiz);
    }
}
//Devolve altura da arvore.
int ABP_C_height(ABP_C n){
    if (n == NULL)
        return 0;
    return n->height;
}


//Maximo de 2 inteiros.
int ABP_C_max(int a, int b)
{
    return (a > b)? a : b;
}


/*Funções de inserção nas árvores.*/

/*INSERIR COLABORADOR MANTENDO ORGANIZAÇÃO INORDER DA ARVORE*/
ABP_C ABP_C_insert(ABP_C node, char* username, long colaboratorId)
{
    //Caso o nodo seja NULL insere o Autor.
    if (node == NULL){
        node = ABP_C_init();
        (node->Autor) = strdup(username);
        node -> IDautor = colaboratorId;
        node -> nContribuicoes = 1;
        return node;
    }
 
    else if (colaboratorId < (node->IDautor))
        //Recursividade para a esquerda
        node->ptEsq  = ABP_C_insert(node->ptEsq, username, colaboratorId);
    else if (colaboratorId > (node -> IDautor))
        //Recursividade para a direita
        node->ptDir = ABP_C_insert(node->ptDir, username, colaboratorId);
    else {
        //incrementa o numero de contribuições quando o autor ja existe na arvore.
        (node->nContribuicoes)++;
        return node;
    }

    //Atualiza a altura da arvore
    node->height = 1 + ABP_C_max(ABP_C_height(node->ptEsq),
                           ABP_C_height(node->ptDir));
    //Verifica se a arvore esta balanceada
    int balance = ABP_C_getBalance(node);
    //Caso nao esteja balanceada aplica os rotates.
    if (balance > 1 )
        node = ABP_C_rotateRight(node);
 
    else if (balance < -1)
        node = ABP_C_rotateLeft(node);

    return node;
}