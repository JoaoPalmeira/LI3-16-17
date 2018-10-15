#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

//teste
long AUX_all_articles(ABP Art);
long AUX_unique_articles(ABP Art);
long AUX_all_revisions(ABP Art);
void AUX_top_10_contributors(ABP_C Cont,ABP_C Root, long* v, int n);
char* AUX_contributor_name(long contributor_id, ABP_C Cont);
void AUX_top_20_largest_articles(ABP Art,ABP Root, long* v, int n);
char* AUX_article_title(long article_id, ABP Art);
void AUX_top_N_articles_with_more_words(ABP Art, ABP Root, long* v, int n);
char** AUX_titles_with_prefix (ABP a, char** s, char* prefix);
char* AUX_article_timestamp(long article_id, long revision_id, ABP Art);