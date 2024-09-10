import os
import uuid
import xml.etree.ElementTree as ET
from xml.dom import minidom

input_directory = "./texto"
output_file = 'lugares.xml'

lugares = ET.Element('lugares')

for xml_file in os.listdir(input_directory):
    if xml_file.endswith('.xml'):
        file_path = os.path.join(input_directory, xml_file)
        
        tree = ET.parse(file_path)
        root = tree.getroot()

        for lugar in root.findall('.//lugar'):
            lugar_elem = ET.Element('lugar')
            
            nome_elem = ET.SubElement(lugar_elem, 'nome')
            nome_elem.text = lugar.text.upper()
            
            rua_num = root.find('.//meta/número').text
            rua_elem = ET.SubElement(lugar_elem, 'rua')
            rua_elem.text = rua_num
            
            pos_elem = ET.SubElement(lugar_elem, 'posição')
            pos_elem.text = str(uuid.uuid4().hex)
            
            lugares.append(lugar_elem)

def prettify(element):
    rough_string = ET.tostring(element, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="    ")

xml_str = prettify(lugares)
with open(output_file, 'w', encoding='utf-8') as f:
    f.write(xml_str)
