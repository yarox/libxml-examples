'''
example2-2.py
Create an XML document with namespaces.
'''

from lxml import etree
from sys import stdout


docname = '../../data/out2-2py.xml'

NS1 = 'http://a.b/c'
NS2 = 'http://d.e/f'
NS3 = 'http://g.h/i'

NS_MAP = {'ns1': NS1, 'ns2': NS2, 'ns3': NS3}

root = etree.Element(etree.QName(NS1, 'root'), nsmap=NS_MAP)

# Create some prefixed nodes
child1 = etree.SubElement(root, etree.QName(NS1, 'child1'))
child2 = etree.SubElement(root, etree.QName(NS2, 'child2'), property='value')

# Create a prefixed property name
child3 = etree.SubElement(root, 'child3')
child3.set(etree.QName(NS3, 'foo'), 'prefixed property name')

# Create a prefixed property value
child4 = etree.SubElement(root, 'child4')
child4.set('bar', etree.QName(NS1, 'prefixed_value'))

tree = etree.ElementTree(root)
tree.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
tree.write(docname, pretty_print=True, xml_declaration=True, encoding='utf-8')
