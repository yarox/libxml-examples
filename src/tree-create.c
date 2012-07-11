
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>



int
main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;       
    xmlNodePtr root_node = NULL, h1 = NULL, h2 = NULL;
    char buff[256];
    int i, j;


    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "mi_casa");
    xmlDocSetRootElement(doc, root_node);

    h1 = xmlNewChild(root_node, NULL, BAD_CAST "habitacion", NULL);
    xmlNewProp(h1, BAD_CAST "id", BAD_CAST "comedor");
    xmlNewChild(h1, NULL, BAD_CAST "aparador", NULL);
    xmlNewChild(h1, NULL, BAD_CAST "silla", NULL);
    
    h2 = xmlNewChild(root_node, NULL, BAD_CAST "habitacion", NULL);
    xmlNewProp(h2, BAD_CAST "id", BAD_CAST "salon");
    xmlNewChild(h2, NULL, BAD_CAST "mesa", NULL);
    xmlNewChild(h2, NULL, BAD_CAST "sofa", NULL);

    if (argc > 1) {
        xmlSaveFormatFileEnc(argv[1], doc, "UTF-8", 1);
    }else {
        xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return(0);
}
