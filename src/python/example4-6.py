'''
example4-6.py
Modifying an existing XML document: modify the node's properties.
'''

from lxml import etree
from sys import stdout



docin = '../../data/namespaces-short.xml'
docout = '../../data/out4-6py.xml'

# Parse and show the original document
doc = etree.parse(docin)

print('>>> ORIGINAL')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Set the namespaces
NS1 = 'http://a.b/c'
NS2 = 'http://d.e/f'
NS3 = 'http://g.h/i'

NS_MAP = {'ns1': NS1, 'ns2': NS2, 'ns3': NS3}

# Select a few nodes
root = doc.getroot()

node1 = doc.xpath('//ns1:child1', namespaces=NS_MAP)[0]
node2 = doc.xpath('//ns2:child2', namespaces=NS_MAP)[0]
node3 = doc.xpath('//child4', namespaces=NS_MAP)[0]

# Add a new property
node1.attrib[etree.QName(NS2, 'a')] = 'new property'

# Change the value
node2.attrib['property'] = 'new value'

# Delete a property
del node3.attrib['bar']

# Show and save the modified document
print('>>> MODIFIED')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
