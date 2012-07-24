'''
example4-1.c
Modifying an existing XML document: create a new node.
'''

from lxml import etree
from sys import stdout



docin = '../../data/simple.xml'
docout = '../../data/out4-1py.xml'

# Parse and show the original document
doc = etree.parse(docin)
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Create a new node under 'room' where 'id' = 'bedroom'
room = doc.xpath('//room[@id="bedroom"]')[0]
carpet = etree.SubElement(room, 'carpet')
carpet.text = 'a carpet appeared'

# Show and save the modified document
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
