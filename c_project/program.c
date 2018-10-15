#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"


/*-----------------------------MAIN-------------------------------*/
int main(){

    char** snaps_paths = (char**)malloc(256 * sizeof(char*));
    snaps_paths[0] = "/Users/joaopalmeira/Desktop/trabalhoLI3/snapshot_fev17";
    snaps_paths[1] = "/Users/joaopalmeira/Desktop/trabalhoLI3/snapshot_jan17";
    snaps_paths[2] = "/Users/joaopalmeira/Desktop/trabalhoLI3/snapshot_dec16";

    TAD_istruct qs = NULL;

    qs=init();
    load(qs, 3, snaps_paths);

    printf ("Tem %ld artigos\n",all_articles(qs));
    printf ("%ld artigos unicos\n",unique_articles(qs));
    printf ("%ld total de revisoes\n",all_revisions(qs));

    printf("Titulo de artigo com id(15910): %s \n", article_title(15910 , qs));
    printf("Titulo de artigo com id(25507): %s \n", article_title(25507 , qs));
    printf("Titulo de artigo com id(1111): %s \n", article_title(1111 , qs));
    printf("Contribuidor(28903366): %s \n", contributor_name(28903366 , qs));
    printf("Contribuidor(194203): %s \n", contributor_name(194203 , qs));
    printf("Contribuidor(1000): %s \n", contributor_name(1000 , qs));
    printf("Timestamp(12,763082287): %s \n",article_timestamp(12 , 763082287 , qs));
    printf("Timestamp(12,755779730): %s \n",article_timestamp(12 , 755779730 , qs));
    printf("Timestamp(12,4479730): %s \n", article_timestamp(12 , 4479730 , qs));

    top_10_contributors(qs);
    titles_with_prefix("Anax\0",qs);
    top_N_articles_with_more_words(30,qs);
    top_20_largest_articles(qs);

    return 0;
}

