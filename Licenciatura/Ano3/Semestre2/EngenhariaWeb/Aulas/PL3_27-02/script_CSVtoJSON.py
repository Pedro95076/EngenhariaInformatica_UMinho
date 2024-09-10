import csv
import json

def read_csv_file(file_path):
    bd = []
    try:
        with open(file_path, 'r') as csv_file:
            csv_reader = csv.DictReader(csv_file, delimiter=";")

            for row in csv_reader:
                bd.append(row)
    except FileNotFoundError:
        print ("O ficheiro {file_path} não foi encontrado!")
    except Exception as e:
        print ("Ocorreu um erro: {e}")

    return bd


def pertence(valor, lista):
    encontrado = False
    i = 0
    while i < len(lista) and not encontrado:
        if lista[i]["designacao"] == valor:
            encontrado = True
        i += 1
        
    return encontrado

def calc_especies(bd):
    especies = []
    contador = 1
    for reg in bd:
        if not pertence(reg['BreedIDDesc'], especies) and reg['BreedIDDesc'] != "":
            especies.append({
                "id": contador,
                "designacao": reg['BreedIDDesc']
            })
            contador += 1
        
    return especies

def calc_animais(bd):
    animais = []
    contador = 1
    for reg in bd:
        if not pertence(reg['SpeciesIDDesc'], animais) and reg['SpeciesIDDesc'] != "":
            animais.append({
                "id": contador,
                "designacao": reg['SpeciesIDDesc']
            })
            contador += 1
        
    return animais


file_path = "Health_AnimalBites.csv"
myBD = read_csv_file(file_path)
especies = calc_especies(myBD)
animais = calc_animais(myBD)

novaBD = {
    "ocorrencias": myBD,
    "especies": especies,
    "animais": animais
}

"""
for elem in myBD:
    print(elem)
    print("=====================================")
"""

f = open("mordidas.json", "w")
json.dump(novaBD, f, indent = 2)
f.close()
print("Ficheiro JSON criado com sucesso!")
