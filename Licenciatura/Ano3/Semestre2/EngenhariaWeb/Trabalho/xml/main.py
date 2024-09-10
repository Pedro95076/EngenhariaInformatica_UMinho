import os
import xml.etree.ElementTree as ET
import json

input_directory = "./texto"
entidades_file = "entidades.xml"
datas_file = "datas.xml"
lugares_file = "lugares.xml"

data = []

def extract_additional_data(file_path, tag_name, rua_data, key, child_elements, rua_value):
    with open(file_path, "r", encoding="utf-8") as file:
        tree = ET.parse(file)
        root = tree.getroot()
        for element in root.findall(f'.//{tag_name}'):
            rua = element.find('rua').text
            if rua == rua_value:
                data_entry = {"rua": rua}
                for child in child_elements:
                    data_entry[child] = element.find(child).text
                rua_data[key].append(data_entry)

for xml_file in os.listdir(input_directory):
    if xml_file.endswith('.xml') and xml_file not in [entidades_file, datas_file, lugares_file]:
        file_path = os.path.join(input_directory, xml_file)

        with open(file_path, "r", encoding="utf-8") as file:
            tree = ET.parse(file)
            root = tree.getroot()

            rua_meta = root.find('meta')
            rua_corpo = root.find('corpo')

            numero = int(rua_meta.find('número').text)
            rua_nome = rua_meta.find('nome').text

            rua_data = {
                "_id": numero,
                "nome": rua_nome,
                "para": [],
                "figuras": [],
                "lista_casas": [],
                "datas": [],
                "entidades": [],
                "lugares": []
            }

            for para in rua_corpo.findall('para'):
                rua_data["para"].append(ET.tostring(para, encoding='unicode', method='text').strip())

            for figura in rua_corpo.findall('figura'):
                img_path = figura.find('imagem').attrib['path']
                legend = figura.find('legenda').text
                rua_data["figuras"].append({
                    "id": figura.get('id'),
                    "figuraId": 'imagem',
                    "imagem": img_path,
                    "legenda": legend
                })

            lista_casas = rua_corpo.find('lista-casas')
            if lista_casas is not None:
                for casa in lista_casas.findall('casa'):
                    number = casa.find('número').text if casa.find('número') is not None else 'Desconhecido'
                    enfiteuta = casa.find('enfiteuta').text if casa.find('enfiteuta') is not None else 'Desconhecido'
                    foro = casa.find('foro').text if casa.find('foro') is not None else 'Desconhecido'
                    desc_element = casa.find('desc')
                    if desc_element is not None and desc_element.find('para') is not None:
                        desc = ''.join(desc_element.find('para').itertext())
                    else:
                        desc = 'Desconhecido'
                    rua_data["lista_casas"].append({
                        "número": number,
                        "enfiteuta": enfiteuta,
                        "foro": foro,
                        "desc": desc
                    })

            extract_additional_data(os.path.join(input_directory, entidades_file), "entidade", rua_data, "entidades", ["tipo", "nome", "posição"], str(numero))
            extract_additional_data(os.path.join(input_directory, datas_file), "data", rua_data, "datas", ["nome", "posição"], str(numero))
            extract_additional_data(os.path.join(input_directory, lugares_file), "lugar", rua_data, "lugares", ["nome", "posição"], str(numero))

            data.append(rua_data)

data = sorted(data, key=lambda x: x["_id"])

with open('output.json', 'w', encoding='utf-8') as json_file:
    json.dump(data, json_file, ensure_ascii=False, indent=4)
