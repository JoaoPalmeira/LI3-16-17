#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include "parser.h"


/*Função que retorna o título existente dentro da tag "title"*/
char* parsePageTitle(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"title"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna o id do artigo existente dentro da tag "id"*/
char* parsePageId(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"id"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna o id da revisão existente dentro da tag "id"*/
char* parsePageRevisionId(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"id"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna a data da revisão existente dentro da tag "timestamp"*/
char* parsePageRevisionTime(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"timestamp"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna o nome de utilizador do colaborador existente dentro da tag "username"*/
char* parsePageRevisionColaboratorUsername(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"username"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna o id do colaborador existente dentro da tag "username"*/
char* parsePageRevisionColaboratorID(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"id"))){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    (cod) = strdup((char*)key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que retorna o número de palavras de uma dada string*/
long nwords (char* s){
	long r=0,i;
	for(i=1;s[i];i++){
	    if(s[i]==' '&& s[i-1]!=' ' && s[i-1]!='\n'&& s[i-1]!='\t'){
	        r++;
	    }
	    else if (s[i+1]=='\0'&& s[i]!=' ' && s[i]!='\n'&& s[i]!='\t'){
	        r++;
	    }
	}
	
	if(s[0]=='\0'){
	    r=0;
	}
	return r;
}

/*Função que retorna o número de caracteres de uma dada string*/
long nchar (char* s){
	long c;
	for(c = 0; s[c]; c++);
	return c;
}

/*Função que retorna o texto da revisão existente dentro da tag "text"*/
char* parsePageRevisionText(xmlDocPtr doc, xmlNodePtr cur){
	xmlChar *key = NULL;
	char* cod;
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
	    if((!xmlStrcmp(cur->name, (const xmlChar *)"text"))){
		    if((xmlNodeListGetString(doc, cur->xmlChildrenNode, 1))!=NULL){
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			(cod) = strdup((char*)key);
		    xmlFree(key);
		    }
 	    }
	cur = cur->next;
	}
    return cod;
}

/*Função que entra nos diferentes níveis do ficheiro xml,
sendo que também insere os diferentes dados nas estruturas*/
void parseDoc(char *docname, ABP* a, ABP_C* c){
	xmlDocPtr doc;
	xmlNodePtr cur;
	char* title = NULL;
	long id = 0;
	long idRev = 0;
	char* timestamp = NULL;
	char* username = NULL;
	long colaboratorID = 0;
	long revText = 0;
	long charRev = 0;

	
	char* titulo;
	char* time;
	char* user;

	doc = xmlParseFile(docname);
	
	if(doc == NULL ){
		fprintf(stderr,"Parser do documento não executado com sucesso. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if(cur == NULL){
		fprintf(stderr,"Documento vazio.\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if(xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")){
		fprintf(stderr,"Documento do tipo errado.");
		xmlFreeDoc(doc);
		return;
	}
	
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
		if((!xmlStrcmp(cur->name, (const xmlChar *)"page"))){
			title = parsePageTitle(doc, cur);
			titulo = strdup(title);
			id = atol(parsePageId(doc, cur));
			xmlNodePtr ruc = cur->xmlChildrenNode;
			while(ruc!=NULL){
				if((!xmlStrcmp(ruc->name, (const xmlChar *)"revision"))){
					idRev = atol(parsePageRevisionId(doc, ruc));
					timestamp = parsePageRevisionTime(doc, ruc);
					time = malloc((strlen(timestamp)+1));
					time = strdup(timestamp);
					xmlNodePtr urc = ruc->xmlChildrenNode;
					while(urc!=NULL){
						if((!xmlStrcmp(urc->name, (const xmlChar *)"contributor"))){
							username = parsePageRevisionColaboratorUsername(doc, urc);
							user = malloc((strlen(username)+1));
							user = strdup(username);
							if(parsePageRevisionColaboratorID(doc, urc)!=NULL){
								colaboratorID = atol(parsePageRevisionColaboratorID(doc, urc));
							}
						}
						urc=urc->next;
					}
					revText = nwords((char*)parsePageRevisionText(doc, ruc));
					charRev = nchar((char*)parsePageRevisionText(doc, ruc));
				}
				ruc=ruc->next;
			}

				
		(*a) = ABP_insert((*a), titulo, id, idRev, time, user, colaboratorID, charRev, revText);	


		(*a) = ABP_insertRev((*a), id, idRev, time, user, colaboratorID);
		

		(*c) = ABP_C_insert((*c), user, colaboratorID);

		}

		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}