
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>



xmlDocPtr
getdoc (char *docname) 
{
	xmlDocPtr doc;
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return NULL;
	}

	return doc;
}

xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath, xmlChar *ns_prefix, xmlChar *ns_uri) 
{
	int status;
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;

	context = xmlXPathNewContext(doc);
	
	if (context == NULL) 
	{
		printf("Error in xmlXPathNewContext\n");
		return NULL;
	}
	
	xmlXPathRegisterNs(context, ns_prefix, ns_uri);
	
	result = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	if (result == NULL) 
	{
		printf("Error in xmlXPathEvalExpression\n");
		return NULL;
	}
	
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
        printf("No result\n");
		return NULL;
	}
	
	return result;
}

int
main (int argc, char **argv)
{
    int i, size, num_children;
    char *docname, *xpath, *ns_prefix, *ns_uri;
    xmlChar *keyword;
    xmlDocPtr doc = NULL;
    xmlNodePtr node = NULL;
	xmlXPathObjectPtr result;
	xmlNodeSetPtr nodeset;

    docname = argv[1];
    xpath = argv[2];
    ns_prefix = argv[3];
    ns_uri = argv[4];
    
	doc = getdoc(docname);
	result = getnodeset(doc, BAD_CAST xpath, BAD_CAST ns_prefix, BAD_CAST ns_uri);

    if (result)
    {
        printf("%d match(es)\n", result->nodesetval->nodeNr);
     
        for(i = 0; i < result->nodesetval->nodeNr; i++)
        {
            node = result->nodesetval->nodeTab[i];
            num_children = (int) xmlChildElementCount(node);
            printf("+ %s: %s.\n> %i subnode(s)\n", node->name, node->content, 
                   num_children);
        }
        
        xmlXPathFreeObject(result);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return(0);
}
