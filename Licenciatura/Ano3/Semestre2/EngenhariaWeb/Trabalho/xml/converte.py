import os
import uuid
import xml.etree.ElementTree as ET
from xml.dom import minidom

input_directory = "./texto"
output_file = 'datas.xml'

datas = ET.Element('datas')

for xml_file in os.listdir(input_directory):
    if xml_file.endswith('.xml'):
        file_path = os.path.join(input_directory, xml_file)
        
        tree = ET.parse(file_path)
        root = tree.getroot()

        for data in root.findall('.//data'):
            data_elem = ET.Element('data')
            
            nome_elem = ET.SubElement(data_elem, 'nome')
            nome_elem.text = data.text
            
            rua_num = root.find('.//meta/número').text
            rua_elem = ET.SubElement(data_elem, 'rua')
            rua_elem.text = rua_num
            
            pos_elem = ET.SubElement(data_elem, '_id')
            pos_elem = uuid.uuid4().hex
            
            datas.append(data_elem)

def prettify(element):
    rough_string = ET.tostring(element, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="    ")

xml_str = prettify(datas)
with open(output_file, 'w', encoding='utf-8') as f:
    f.write(xml_str)
