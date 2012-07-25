/*
example4-6.py
Modifying an existing XML document: modify the node's properties.
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
    xmlChar *xpath, *ns_prefix[3], *ns_uri[3];
    xmlXPathObjectPtr result;
    char *docin, *docout;
    xmlNodePtr node; 
    xmlDocPtr doc;
    
    
    docin = "../../data/namespaces-short.xml";
    docout = "../../data/out4-6c.xml";
    
    // Parse and show the original document
	doc = getdoc(docin);

	printf(">>> ORIGINAL\n");
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
	
	// Set the namespaces	
	ns_prefix[0] = BAD_CAST "ns1";
	ns_uri[0] = BAD_CAST "http://a.b/c";
	
	ns_prefix[1] = BAD_CAST "ns2";
	ns_uri[1] = BAD_CAST "http://d.e/f";
	
	ns_prefix[2] = BAD_CAST "ns3";
	ns_uri[2] = BAD_CAST "http://g.h/i";
		
	// Select a node and add some new properties
	xpath = BAD_CAST "//ns1:child1";
	result = getnodeset(doc, xpath, ns_prefix, ns_uri, 3);
    
    if (result)
    {     
        node = result->nodesetval->nodeTab[0];
        xmlNewProp(node, xmlBuildQName(BAD_CAST "a", ns_prefix[1], NULL, 0), 
                   BAD_CAST "new property");
        
        xmlXPathFreeObject(result);
    }
    
    // Select a node and change the value of an existing property
	xpath = BAD_CAST "//ns2:child2";
	result = getnodeset(doc, xpath, ns_prefix, ns_uri, 3);
    
    if (result)
    {     
        node = result->nodesetval->nodeTab[0];
        xmlSetProp(node, BAD_CAST "property", BAD_CAST "new value");
        
        xmlXPathFreeObject(result);
    }
    
    // Select a node and delete a property
	xpath = BAD_CAST "//child4";
	result = getnodeset(doc, xpath, ns_prefix, ns_uri, 3);
    
    if (result)
    {     
        node = result->nodesetval->nodeTab[0];
        xmlUnsetProp(node, BAD_CAST "bar");
        
        xmlXPathFreeObject(result);
    }
	
	// Show and save the modified document
	printf(">>> MODIFIED\n");
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
	xmlSaveFormatFileEnc(docout, doc, "UTF-8", 1);
	
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return(0);
}
