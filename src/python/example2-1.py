'''
example2-1.py
Create an XML document including different nodes.
'''

from lxml import etree


docname = '../../data/out2-1py.xml'

root = etree.Element('root')
child1 = etree.SubElement(root, 'child1')
child2 = etree.SubElement(root, 'child2', foo='foo', bar='bar')
child3 = etree.SubElement(child2, 'child3')
child3.text = 'some text'

print(etree.tostring(root, pretty_print=True, xml_declaration=True, 
                      encoding='utf-8'))

tree = etree.ElementTree(root)
tree.write(docname, pretty_print=True, xml_declaration=True, encoding='utf-8')
