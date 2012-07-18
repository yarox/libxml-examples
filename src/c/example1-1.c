/* 
example1-1.c
Show the contents of an XML document.
*/

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>



xmlDocPtr
getdoc (char *docname) 
{
	xmlDocPtr doc;
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr, "Document not parsed successfully.\n");
		return NULL;
	}

	return doc;
}

int
main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;
    char *docname = "../../data/simple.xml";

    doc = getdoc(docname);
    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return(0);
}
