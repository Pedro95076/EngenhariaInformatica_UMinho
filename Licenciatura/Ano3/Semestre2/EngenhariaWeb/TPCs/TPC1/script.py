import os
import shutil
import xml.etree.ElementTree as ET
from xmldt import XmlDt


#funcao para gerar o codgido html do indice
def index():

    inicioHTML = """
    <!DOCTYPE html>
    <html>
        <head>
            <title>Mapa das Ruas de Braga</title>
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <link rel="stylesheet" href="w3.css">
            <meta charset="UTF-8">
        </head>
        <body>
            <div class="w3-card-4">
                <header class="w3-container w3-pale-red">
                    <h3>Mapa das Ruas de Braga</h3>
                </header>

                <div class="w3-container">
                    <ul class="w3-ul w3-card-4" style="width:50%">
    """

    fimHTLM = """
                    </ul>
                </div>

                <footer class="w3-container w3-pale-red">
                    <h5>TPC1::EngWeb2024::a95076</h5>
                </footer>            
            </div>
        </body>
    </html> 
    """

    conteudo = ""

    os.chdir('MapaRuas-materialBase/texto')

    ruas = []
    #guardar a lista das ruas
    for file in os.listdir():

        tree = ET.parse(file)
        root = tree.getroot()

        for child in root:
            if child.tag == 'meta':

                for second_child in child:

                    if second_child.tag == 'número':
                        numb = int(second_child.text)

                    elif second_child.tag == 'nome':
                        name = second_child.text

        if numb and name:
            ruas.append((numb, name, file))

    #organizar a lista
    ruas.sort(key=lambda x: int(x[0]))

    #criar corpo html
    for numb, name, file in ruas:

        ficheiro = f"{file.split('.')[0]}.html"
        conteudo += f"""
                        <li>
                            <a href="MapaRuas-materialBase/htmls/{ficheiro}">{numb} | {name}</a>
                        </li>
            """

    #concatenar html final
    html = inicioHTML + conteudo + fimHTLM

    os.chdir('../..')

    with open('index.html', 'w') as f:
        f.write(html)


#classe para alterar o formato de xml para html
class conteudo (XmlDt):
    def número(s, e): 
        e.tag = "h3" 
        e.c = "N: " + e.c 
        return e.xml
    def nome(s, e)  :      
        e.tag = "h1" 
        return e.xml
    def corpo(s, e):       
        e.tag = "body"
        return e.xml
    def para(s, e):       
        e.tag = "p"   
        return e.xml
    def lugar(s, e):      
        e.tag = "b"   
        return e.xml
    def lista_casas(s, e): 
        e.tag = "ul" 
        return e.xml 
    def imagem(s, e):     
        e.tag = "img" 
        e['src'] = e['path'] 
        return e.xml
    def legenda(s, e): 
        e.tag = "h4"  
        e.c = "Figura : "    + e.c 
        return e.xml
    def enfiteuta(s, e):  
        e.tag = "li"  
        e.c = "Inquilino: " + e.c
        return e.xml 
    def foro(s, e):     
        e.tag = "li"  
        e.c = "Pensão: "    + e.c
        return e.xml
    def desc(s, e):      
        e.tag = "li" 
        e.c = "Descrição: " + e.c
        return e.xml


#funcao que cria as paginas de cada rua
def paginas():

    #mudar para a diretoria onde esta o texto
    os.chdir('MapaRuas-materialBase')

    #criar (se necessario) a diretoria para os htmls de cada pagina
    if not os.path.exists('htmls'):
            os.mkdir('htmls')

    #criar a pagina para cada xml
    for file in os.listdir("texto"):

        #alterar o conteudo para o formato html, adicionando a opcao de voltar ao indice
        pagina = conteudo(filename = f"texto/{file}") + "<li><a href=\"../../index.html\">Voltar</a></li>"
        
        #criar o nome do ficheiro
        name = file[:-3] + "html"
        
        #guardar a pagina html
        with open(f"htmls/{name}", "w", encoding="utf-8") as f:
            f.write(pagina)
        
        
def main():
    index()
    paginas()

if __name__ == "__main__":
    main()




