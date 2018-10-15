#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ABP_C *ABP_C;

ABP_C ABP_C_init();
int ABP_C_hasLeft(ABP_C n);
int ABP_C_hasRight(ABP_C n);
char* ABP_C_IDgetAutor(ABP_C a, long id);
int ABP_C_IDgetNCont(ABP_C a, long id);
char* ABP_C_getAutor(ABP_C a);
long ABP_C_getIDautor(ABP_C a);
int ABP_C_getNCont(ABP_C a);
ABP_C ABP_C_left(ABP_C a);
ABP_C ABP_C_right(ABP_C a);
ABP_C ABP_C_rotateLeft(ABP_C n);
ABP_C ABP_C_rotateRight(ABP_C n);
int ABP_C_procuraID(int id, ABP_C a);
void ABP_C_destroi(ABP_C raiz);
int ABP_C_height(ABP_C n);
int ABP_C_getBalance(ABP_C n);
int ABP_C_max(int a, int b);
ABP_C ABP_C_insert(ABP_C node, char* autor, long Autor_Id);