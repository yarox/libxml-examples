'''
example4-2.py
Modifying an existing XML document: delete a node.
'''

from lxml import etree
from sys import stdout



docin = '../../data/namespaces-short.xml'
docout = '../../data/out4-2py.xml'

# Parse and show the original document
doc = etree.parse(docin)
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Set the namespaces
NS1 = 'http://a.b/c'
NS2 = 'http://d.e/f'
NS3 = 'http://g.h/i'

NS_MAP = {'ns1': NS1, 'ns2': NS2, 'ns3': NS3}

# Select a node and delete it
root = doc.getroot()
candidate = doc.xpath('//ns2:child2', namespaces=NS_MAP)[0]
root.remove(candidate)

# Show and save the modified document
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
