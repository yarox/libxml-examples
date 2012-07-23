/*
example3-2.c
Find elements in a XML document with namespaces.
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <libxml/xpathInternals.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>



char
*strip(char *str)
{
	char *end;


	// Trim leading space
  	while(isspace(*str)) str++;

	// All spaces?
	if(*str == 0)
	return NULL;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end + 1) = 0;

	return str;
}

static void
print_text_nodes(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;
    xmlChar *content;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) 
    {
        if (cur_node->type == XML_TEXT_NODE) 
        {
            content = xmlNodeGetContent(cur_node);
            
            if (content != NULL)
            {
                printf("%s: %s\n", cur_node->parent->name, content);
            }
        }

        print_text_nodes(cur_node->children);
    }
}

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
	int i, status;
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
    char *docname, *description, *time, *name, *value, *type;
    xmlChar *xpath, *ns_prefix[2], *ns_uri[2];
    xmlXPathObjectPtr result1, result2;
    int i, size, num_children;
    xmlNodePtr node1, node2;
    xmlDocPtr doc;
    
    
	doc = getdoc("../../data/namespaces.xml");
	
	// Set the namespaces	
	ns_prefix[0] = BAD_CAST "xsi";
	ns_uri[0] = BAD_CAST "http://www.w3.org/2001/XMLSchema-instance";
	
	ns_prefix[1] = BAD_CAST "ems";
	ns_uri[1] = BAD_CAST "http://www.esa.int/esa/egos/GS/MC/GSC/SSDS";
	
	// Retrieve all spacecraft nodes, and print the text of the first five ones
	xpath = BAD_CAST "//ems:Pass/ems:spacecraft";
	result1 = getnodeset(doc, xpath, ns_prefix, ns_uri, 2);

    if (result1)
    {     
        for(i = 0; i < 5; i++)
        {  
            node1 = result1->nodesetval->nodeTab[i];
            printf("%s\n", xmlNodeGetContent(node1));
        }
        xmlXPathFreeObject(result1);
    }
    	
	// Retrieve all critical jobs, and print the descriptions and times of the
    // first five ones
    xpath = BAD_CAST "//ems:Job[@criticalEntry=\"critical\"]/ems:description";
	result1 = getnodeset(doc, xpath, ns_prefix, ns_uri, 2);

    xpath = BAD_CAST "//ems:Job[@criticalEntry=\"critical\"]/ems:startSpec";
    result2 = getnodeset(doc, xpath, ns_prefix, ns_uri, 2);

    if (result1)
    {     
        for(i = 0; i < 5; i++)
        {  
            node1 = result1->nodesetval->nodeTab[i];
            node2 = result2->nodesetval->nodeTab[i];
            
            description = strip(xmlNodeGetContent(node1));
            time = xmlGetProp(node2, BAD_CAST "time");
            
            printf("%s at %s\n", description, time);
        }
        xmlXPathFreeObject(result1);
        xmlXPathFreeObject(result2);
    }
	
	// Retrieve all 'ems:argument' nodes with type 'ems:TimeArgType', and print 
    // the 'xsi:type', 'name', and 'value' attributes
	xpath = BAD_CAST "//ems:argument[@xsi:type=\"ems:TimeArgType\"]";
	result1 = getnodeset(doc, xpath, ns_prefix, ns_uri, 2);

    if (result1)
    {     
        for(i = 0; i < 5; i++)
        {  
            node1 = result1->nodesetval->nodeTab[i];
            
            value = xmlGetProp(node1, BAD_CAST "value");
            name = xmlGetProp(node1, BAD_CAST "name");
            type = xmlGetNsProp(node1, BAD_CAST "type", ns_uri[0]);
            
            printf("%s %s %s\n", type, name, value);
        }
        xmlXPathFreeObject(result1);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return(0);
}
