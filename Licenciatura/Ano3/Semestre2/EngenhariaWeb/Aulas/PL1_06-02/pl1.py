import json
import os
import shutil

html = '''
<!DOCTYPE html>
<html>
<head>
    <title>EngWeb2024</title>
    <meta charset="UTF-8">
</head>
<body>
'''

template = html

file = open('mapa.json', 'r', encoding='utf-8').read()

if os.path.exists('html'):  # Verifica se a pasta existe
    shutil.rmtree('html')  # Remove a pasta
os.mkdir('html') # Cria a pasta 

content = json.loads(file)


html += "<ul>"

listaCidades = []
for elem in content['cidades']:
    listaCidades.append(elem['nome'])
    
    templateCidade = template
    templateCidade += f"<h1>{elem['nome']}</h1>"
    templateCidade += f"<h3>{elem['distrito']}</h3>"
    templateCidade += f"<p><b>População:</b> {elem['população']}</p>"
    templateCidade += f"<p><b>Descrição:</b> {elem['descrição']}</p>"
    templateCidade += f"<h6><a href='../mapa.html'>Voltar</a></h6>"
    templateCidade += "</body>"
    templateCidade += "</html>"
    
    fileCidade = open(f"html/{elem['nome']}.html", "w", encoding="utf-8")
    fileCidade.write(templateCidade)
    fileCidade.close()
    
for elem in sorted(listaCidades):
    html += f"<li><a href='html/{elem}.html'>{elem}</a></li>"
    
html += "</ul>"
html += "</body>"
html += "</html>"

file = open("mapa.html", "w", encoding="utf-8")
file.write(html)
file.close()
