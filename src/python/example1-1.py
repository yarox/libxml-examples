'''
example1-1.py
Show the contents of an XML document.
'''

from lxml import etree



doc = etree.parse('../../data/simple.xml')
print(etree.tostring(doc, xml_declaration=True, encoding='utf-8'))
