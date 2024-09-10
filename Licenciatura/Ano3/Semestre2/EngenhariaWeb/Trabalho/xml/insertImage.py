import re
import json
from pathlib import Path

directory = Path("../api/public/images/atual/")
images = directory.glob("*")

expId = re.compile(r'\d+(?=-)')
expType = re.compile(r'(\d+-[A-Z](\w+|\.)+-Vista\d)(?=\.)')
expName = re.compile(r'(?<=-)([A-Z](\w+|\.)+-Vista\d)(?=\.)')

with open('output.json', 'r', encoding='utf-8') as fr:
    data = json.load(fr)

def add_image(id_img, image):
    for id_obj in data:
        if int(id_img) == int(id_obj["_id"]):
            id_obj["figuras"].insert(0, image)
            print(id_obj["figuras"])
            break

def make_obj():
    for image_path in images:
        image_name = image_path.name
        number_match = expId.search(image_name)
        id_img_match = expType.search(image_name)
        name_match = expName.search(image_name)

        if number_match and id_img_match and name_match:
            number = number_match.group(0)
            id_img = id_img_match.group(0)
            name = name_match.group(0)
            
            image_obj = {
                "id": id_img,
                "figuraId": "atual",
                "imagem": f"../atual/{image_name}",
                "legenda": name
            }
            
            add_image(number, image_obj)
    
    with open('output.json', 'w', encoding='utf-8') as fw:
        json.dump(data, fw, indent=2, ensure_ascii=False)

make_obj()
