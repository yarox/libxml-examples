'''
example3-2.py
Find elements in a XML document with namespaces.
'''

from lxml import etree



doc = etree.parse('../../data/namespaces.xml')

# Set the namespaces
xsi = 'http://www.w3.org/2001/XMLSchema-instance'
ems = 'http://www.esa.int/esa/egos/GS/MC/GSC/SSDS'
NS_MAP = {'xsi': xsi, 'ems': ems}

# Retrieve all spacecraft nodes, and print the text of the first five ones
nodes = doc.xpath('//ems:Pass/ems:spacecraft', namespaces=NS_MAP)

for node in nodes[:5]:
    print node.text
    
# Retrieve all critical jobs, and print the descriptions and times of the first 
# five ones
nodes = doc.xpath('//ems:Job[@criticalEntry="critical"]', namespaces=NS_MAP)

for node in nodes[:5]:
    description, startSpec = node.getchildren()
    print '{0} at {1}'.format(description.text, startSpec.attrib['time'])
    
# Retrieve all 'ems:argument' nodes with type 'ems:TimeArgType', and print the 
# 'type', 'name', and 'value' attributes
nodes = doc.xpath('//ems:argument[@xsi:type="ems:TimeArgType"]', 
                  namespaces=NS_MAP)

for node in nodes[:5]:
    type = node.attrib[etree.QName(xsi, 'type')]
    print '{0} {1[name]} {1[value]}'.format(type, node.attrib)
