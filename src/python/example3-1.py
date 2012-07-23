'''
example3-1.py
Find elements in a simple XML document.
'''

from lxml import etree



doc = etree.parse('../../data/simple.xml')

# Retrieve all room elements and print tag, 'id' property, and number of 
# children
rooms = doc.xpath('/house/room')
for room in rooms:
    print '{0}: a {1} with {2} objects'.format(room.tag, room.attrib['id'], 
                                                len(room.getchildren()))

# Retrieve all red chairs ('chair' nodes with property 'color' = 'red') and 
# print color, name, and room
red_chairs = doc.xpath('//chair[@color="red"]')
for chair in red_chairs:
    print 'a {1} {2} from the {0}'.format(chair.getparent().attrib['id'], 
                                           chair.attrib['color'], chair.tag)
    
# List nodes whith text, if any
for element in doc.iter():    
    if element.text and element.text.strip():
        print '{0}: {1}'.format(element.tag, element.text)
