/*
example3-1.c
Find elements in a simple XML document.
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <libxml/xpathInternals.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>



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
			content = strip(xmlNodeGetContent(cur_node));
            
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
	char *docname = "../../data/simple.xml", *id, *color;
	int i, size, num_children;
	xmlXPathObjectPtr result;
	xmlNodeSetPtr nodeset;
	xmlChar *keyword;
	xmlNodePtr node;
	xmlDocPtr doc;
    
        
	doc = getdoc(docname);
	
	// Retrieve all room elements and print tag, 'id' property, and number of 
	// children
	result = getnodeset(doc, BAD_CAST "/house/room", NULL, NULL);

	if (result)
	{     
		for(i = 0; i < result->nodesetval->nodeNr; i++)
		{  
			node = result->nodesetval->nodeTab[i];
			num_children = (int) xmlChildElementCount(node);
			id = xmlGetProp(node, BAD_CAST "id");
            
			printf("%s: a %s with %i objects\n", node->name, id, num_children);
		}
        
		xmlXPathFreeObject(result);
    }
    
	// Retrieve all red chairs ('chair' nodes with property 'color' = 'red') and 
	// print color, name, and room
	result = getnodeset(doc, BAD_CAST "//chair[@color='red']", NULL, NULL);

	if (result)
	{
		for(i = 0; i < result->nodesetval->nodeNr; i++)
		{  
			node = result->nodesetval->nodeTab[i];
			num_children = (int) xmlChildElementCount(node);
			color = xmlGetProp(node, BAD_CAST "color");
			id = xmlGetProp(node->parent, BAD_CAST "id");

			printf("a %s %s from the %s\n", color, node->name, id);
	}
        
		xmlXPathFreeObject(result);
	}
    
	// List nodes whith text, if any
	print_text_nodes(xmlDocGetRootElement(doc));

	xmlFreeDoc(doc);
	xmlCleanupParser();
    
	return(0);
}