'''
example4-5.py
Modifying an existing XML document: modify the node's text value.
'''

from lxml import etree
from sys import stdout



docin = '../../data/simple.xml'
docout = '../../data/out4-5py.xml'

# Parse and show the original document
doc = etree.parse(docin)

print('>>> ORIGINAL')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')

# Select a node and update its text
root = doc.getroot()
node = doc.xpath('//bed')[0]
node.text = 'now, it\'s a bed just for one'

# Show and save the modified document
print('>>> MODIFIED')
doc.write(stdout, pretty_print=True, xml_declaration=True, encoding='utf-8')
doc.write(docout, pretty_print=True, xml_declaration=True, encoding='utf-8')
