import os
import xml.etree.ElementTree as ET
from xml.dom import minidom

input_directory = "./texto"
output_file = 'entidades.xml'

entidades = ET.Element('entidades')

for xml_file in os.listdir(input_directory):
    if xml_file.endswith('.xml'):
        file_path = os.path.join(input_directory, xml_file)
        
        tree = ET.parse(file_path)
        root = tree.getroot()

        for entidade in root.findall('.//entidade'):
            entidade_elem = ET.Element('entidade')
            
            tipo_elem = ET.SubElement(entidade_elem, 'tipo')
            tipo_elem.text = entidade.get('tipo')
            
            nome_elem = ET.SubElement(entidade_elem, 'nome')
            nome_elem.text = entidade.text.upper()
            
            rua_num = root.find('.//meta/número').text
            rua_elem = ET.SubElement(entidade_elem, 'rua')
            rua_elem.text = rua_num
            
            pos_elem = ET.SubElement(entidade_elem, '_id')
            pos_elem.text = (id(entidade))
            
            entidades.append(entidade_elem)

def prettify(element):
    rough_string = ET.tostring(element, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="    ")

new_tree = ET.ElementTree(entidades)
xml_str = prettify(entidades)

with open(output_file, 'w', encoding='utf-8') as f:
    f.write(xml_str)
