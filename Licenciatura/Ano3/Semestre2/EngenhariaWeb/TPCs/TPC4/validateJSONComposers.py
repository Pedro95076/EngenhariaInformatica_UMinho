import json

def validar(compositor):
    required_keys = ["id", "nome", "bio", "dataNasc", "dataObito", "periodo"]
    return all(key in compositor for key in required_keys)

with open('compositores.json', 'r', encoding='utf-8') as file:
    data = json.load(file)

compositores_validos = [compositor for compositor in data["compositores"] if validar(compositor)]

novo_json = {"compositores": compositores_validos}

with open('compositoresValidos.json', 'w', encoding='utf-8') as file:
    json.dump(novo_json, file, indent=2)