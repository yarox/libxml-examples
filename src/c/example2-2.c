/*
example2-2.c
Create an XML document with namespaces.
*/

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>



int
main(int argc, char **argv)
{
    xmlNodePtr root, child1, child2, child3, child4;
    char *docname = "../../data/out2-2c.xml";
    xmlNsPtr ns1, ns2, ns3;
    xmlDocPtr doc;


    doc = xmlNewDoc(BAD_CAST "1.0");
    
    // Create the root node and add the namespaces to it
    root = xmlNewNode(NULL, BAD_CAST "root");
    ns1 = xmlNewNs(root, BAD_CAST "http://a.b/c", BAD_CAST "ns1");
    ns2 = xmlNewNs(root, BAD_CAST "http://d.e/f", BAD_CAST "ns2");
    ns3 = xmlNewNs(root, BAD_CAST "http://g.h/i", BAD_CAST "ns3");
    
    // Prefix the root node
    xmlSetNs(root, ns1);
    xmlDocSetRootElement(doc, root);

    // Create some prefixed nodes
    child1 = xmlNewChild(root, NULL, BAD_CAST "child1", NULL);
    xmlSetNs(child1, ns1);
    
    child2 = xmlNewChild(root, NULL, BAD_CAST "child2", NULL);
    xmlSetNs(child2, ns2);
    xmlNewProp(child2, BAD_CAST "property", BAD_CAST "value");
    
    // Create a prefixed property name
    child3 = xmlNewChild(root, NULL, BAD_CAST "child3", NULL);
    xmlSetNs(child3, NULL);
    xmlNewNsProp(child3, ns3, BAD_CAST "foo", BAD_CAST "prefixed property name");
    
    // Create a prefixed property value
    child4 = xmlNewChild(root, NULL, BAD_CAST "child4", NULL);
    xmlSetNs(child4, NULL);
    xmlNewProp(child4, BAD_CAST "bar", BAD_CAST "ns1:prefixed_value");

    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    xmlSaveFormatFileEnc(docname, doc, "UTF-8", 1);

    xmlFreeDoc(doc);

    return(0);
}
