'''
example4-4.py
Modifying an existing XML document: modify the node's tag.
'''

from lxml import etree
from sys import stdout



docin = '../../data/namespaces-short.xml'
docout = '../../data/out4-4py.xml'

# Parse and show the original document
doc = etree.parse(docin)

print('>>> ORIGINAL')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Set the namespaces
NS1 = 'http://a.b/c'
NS2 = 'http://d.e/f'
NS3 = 'http://g.h/i'

NS_MAP = {'ns1': NS1, 'ns2': NS2, 'ns3': NS3}

# Select a couple of nodes and update their tag value
root = doc.getroot()
node1 = doc.xpath('//child3', namespaces=NS_MAP)[0]
node2 = doc.xpath('//ns1:child1', namespaces=NS_MAP)[0]

node1.tag = etree.QName(NS2, 'new_child3')
node2.tag = 'new_child1'

# Show and save the modified document
print('>>> MODIFIED')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
