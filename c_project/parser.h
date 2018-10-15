#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include "Colaborator.h"
#include "BaseBTree.h"

char* parsePageTitle(xmlDocPtr doc, xmlNodePtr cur);
char* parsePageId(xmlDocPtr doc, xmlNodePtr cur);
char* parsePageRevisionId(xmlDocPtr doc, xmlNodePtr cur);
char* parsePageRevisionTime(xmlDocPtr doc, xmlNodePtr cur);
char* parsePageRevisionColaboratorUsername(xmlDocPtr doc, xmlNodePtr cur);
char* parsePageRevisionColaboratorID(xmlDocPtr doc, xmlNodePtr cur);
long nwords (char* s);
long nchar (char* s);
char* parsePageRevisionText(xmlDocPtr doc, xmlNodePtr cur);
void parseDoc(char *docname, ABP* a, ABP_C* c);