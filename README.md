# libxml-examples
Some __libxml__ examples for __C__ and __Python__, featuring some common 
actions.

# Dependecies
This examples have been tested under `Ubuntu Linux 12.04` with the following
configuration:

+ `gcc 4.6.3` and `libxml2 2.7.8` 
+ `Python 2.7.3` and `lxml 2.3.4`

# How to run the examples
## Python
Open a terminal, navigate to `src/python` and run `python exampleX-Y.py`

## C
Open a terminal, navigate to `src/c` and run:
    
    gcc -o exampleX-Y `xml2-config --cflags` exampleX-Y.c `xml2-config --libs`
    ./exampleX-Y

# Examples
## 1. Reading an XML document
1. Show the contents of a document.

## 2. Creating a new XML document
1. Create a document including different nodes.
2. Create a document with namespaces. 

## 3. Finding elements in an XML document
1. Find elements in a simple document.
2. Find elements in a document with namespaces.

## 4. Modifying an existing XML document
1. Create new node.
2. Delete node.
3. Replace a node.
4. Modify the node's tag.
5. Modify the node's text value.
6. Modify the node's properties.

# References
1. http://infohost.nmt.edu/tcc/help/pubs/pylxml/web/index.html
2. http://lxml.de/tutorial.html
3. http://www.w3schools.com/xpath/
