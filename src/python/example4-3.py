'''
example4-3.py
Modifying an existing XML document: replace a node.
'''

from lxml import etree
from sys import stdout



docin = '../../data/namespaces-short.xml'
docout = '../../data/out4-3py.xml'

# Parse and show the original document
doc = etree.parse(docin)
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Set the namespaces
NS1 = 'http://a.b/c'
NS2 = 'http://d.e/f'
NS3 = 'http://g.h/i'

NS_MAP = {'ns1': NS1, 'ns2': NS2, 'ns3': NS3}

# Select a node to replace, create a substitute, and perform the replacement
root = doc.getroot()
old = doc.xpath('//child3', namespaces=NS_MAP)[0]

new = etree.Element('new_child3')
new.text = 'brand new replaced node'

root.replace(old, new)

# Show and save the modified document
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
