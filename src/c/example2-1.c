/*
example2-1.c
Create an XML document including different nodes.
*/

#include <stdio.h>

#include <libxml/parser.h>
#include <libxml/tree.h>



int
main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;
    xmlNodePtr root = NULL, child1 = NULL, child2 = NULL, child3 = NULL;
    char *docname = "../../data/out2-1c.xml";


    doc = xmlNewDoc(BAD_CAST "1.0");
    root = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root);

    child1 = xmlNewChild(root, NULL, BAD_CAST "child1", NULL);

    child2 = xmlNewChild(root, NULL, BAD_CAST "child2", NULL);
    xmlNewProp(child1, BAD_CAST "foo", BAD_CAST "foo");
    xmlNewProp(child1, BAD_CAST "bar", BAD_CAST "bar");
    
    child3 = xmlNewChild(child2, NULL, BAD_CAST "child3", NULL);
    xmlNodeAddContent(child3, BAD_CAST "some text");

    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    xmlSaveFormatFileEnc(docname, doc, "UTF-8", 1);

    xmlFreeDoc(doc);

    return(0);
}





















