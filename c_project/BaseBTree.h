#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo *Nodo;
typedef struct ABP *ABP;

Nodo ABP_nodeInit(int first);
ABP ABP_init(int art);
ABP ABP_initRoot(Nodo root);
int ABP_hasLeft(ABP n);
int ABP_hasRight(ABP n);
ABP ABP_left(ABP a);
ABP ABP_right(ABP a);
int ABP_hasNode(ABP a);
ABP ABP_getRevisoes(ABP a, long id);
Nodo ABP_getInfo(ABP a, long id);
char* ABP_getTitulo(ABP a, long ID);
char* ABP_getAutor(ABP a, long ID);
char* ABP_getTimestamp(ABP a, long ID);
long ABP_getID(ABP a);
long ABP_getDups(ABP a);
long ABP_getIDAutor(ABP a, long ID);
long ABP_getNRevisoes(ABP a);
long ABP_IDgetNChar(ABP a, long ID);
long ABP_getNChar(ABP a);
long ABP_IDgetNWords(ABP a, long ID);
long ABP_getNWords(ABP a);
ABP ABP_rotateLeft(ABP n);
ABP ABP_rotateRight(ABP n);
void ABP_insereOrd (ABP n, Nodo a);
int ABP_procuraID(long id, ABP a);
void ABP_destroi(ABP raiz);
int ABP_height(ABP n);
int ABP_getBalance(ABP n);
int ABP_max(int a, int b);
ABP ABP_insertRev (ABP node, long id, long idrev, char* timeStamp, char* username, long colaboratorId);
ABP ABP_insertRevAUX(ABP node, long id, char* timeStamp, char* username, long colaboratorId);
ABP ABP_insert(ABP node, char* title, long id, long idrevision, char* timeStamp, char* autor, long Autor_Id, long nchar, long nwords);

