/*
example4-3.c
Modifying an existing XML document: replace a node.
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <libxml/xpathInternals.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>



xmlDocPtr
getdoc (char *docname) 
{
	xmlDocPtr doc;
	
	
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) 
	{
		fprintf(stderr,"Document not parsed successfully. \n");
		return NULL;
	}

	return doc;
}

xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath, xmlChar *ns_prefix[], 
            xmlChar *ns_uri[], int ns_count) 
{
	int i;
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;


	context = xmlXPathNewContext(doc);
	
	if (context == NULL) 
	{
		printf("Error in xmlXPathNewContext\n");
		return NULL;
	}
	
	for (i = 0; i < ns_count; i += 1)
	{
	    xmlXPathRegisterNs(context, ns_prefix[i], ns_uri[i]);   
	}
	
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
    xmlXPathObjectPtr result;
    xmlNodePtr old, new;
    char *docin, *docout;
    xmlChar *xpath, *ns_prefix[3], *ns_uri[3];
    xmlDocPtr doc;
    
    
    docin = "../../data/namespaces-short.xml";
    docout = "../../data/out4-3c.xml";
    
    // Parse and show the original document
	doc = getdoc(docin);
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
	
	// Set the namespaces	
	ns_prefix[0] = BAD_CAST "ns1";
	ns_uri[0] = BAD_CAST "http://a.b/c";
	
	ns_prefix[1] = BAD_CAST "ns2";
	ns_uri[1] = BAD_CAST "http://d.e/f";
	
	ns_prefix[2] = BAD_CAST "ns3";
	ns_uri[2] = BAD_CAST "http://g.h/i";
	
	// Select a node and delete it
	xpath = BAD_CAST "//child3";
	result = getnodeset(doc, xpath, ns_prefix, ns_uri, 3);
    
    if (result)
    {     
        old = result->nodesetval->nodeTab[0];
        new = xmlNewNode(NULL, BAD_CAST "new_child3");
        xmlNodeAddContent(new, BAD_CAST "brand new replaced node");
        xmlReplaceNode(old, new);
    
        xmlXPathFreeObject(result);
    }
	
	// Show and save the modified document
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
	xmlSaveFormatFileEnc(docout, doc, "UTF-8", 1);
	
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return(0);
}
