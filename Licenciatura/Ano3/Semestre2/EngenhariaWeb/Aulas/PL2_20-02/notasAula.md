Vamos abordar o json-server.

1. Criamos o ficheiro bd.json

2. $ json-server --watch bd.json

3. Ver o "http://localhost:3000"
    a. http://localhost:3000/lista --> Para ver a lista toda
    b. http://localhost:3000/lista/1 --> Para ver somente o id 1
        ? --> Usado para fazer queries
    c. http://localhost:3000/lista?_sort=nome --> Para ver a lista ordenada pelos nomes
    d. http://localhost:3000/lista?quantidade=2 --> Para ver os que têm quandidade = 2

4. $ json-server --watch --port 4000 mapa-virtual.json
    a. Cidade id = c50 --> http://localhost:4000/cidades/c50
    b. Lista de cidades ordenadas por nome --> http://localhost:4000/cidades?_sort=nome
    c. Lista de cidades do distrito de braga ordenadas por nome --> http://localhost:4000/cidades?_sort=nome&distrito=Braga
    d. ligações com origem em c1 --> http://localhost:4000/ligacoes?origem=c1
    e. ligações com destino em c10 --> http://localhost:4000/ligacoes?destino=c10

5. Criamos o "servidor1.js"

6. $ node servidor1.js 

7. Criamos o "aux.js"

8. Criamos o "servidor2.js"

9. $ node servidor2.js 

10. Criamos o "servidor3.js"

11. $ node servidor3.js   

12. http://localhost:2002/
13. http://localhost:2002/atum?peixe=3

    a. TRUE: {..."search":"?peixe=3","query":{"peixe":"3"},"pathname":"/atum","path":"/atum?peixe=3","href":"/atum?peixe=3"}

    A seção "TRUE" descreve a resposta correta do servidor para essa solicitação. Ele retorna um objeto com detalhes sobre a URL, como "search", "query", "pathname", "path" e "href". O "query" é um objeto com a chave "peixe" definida como "3", indicando que o servidor interpretou corretamente o parâmetro de consulta.

    B. FALSE: {..."search":"?peixe=3","query":"peixe=3","pathname":"/atum","path":"/atum?peixe=3","href":"/atum?peixe=3"}

    A seção "FALSE" descreve uma resposta incorreta do servidor para essa solicitação. Em vez de retornar um objeto para o "query", ele retorna uma string "peixe=3". Isso indica que o servidor não interpretou corretamente o parâmetro de consulta e o tratou como uma string simples em vez de um objeto com chaves e valores.

14. Criamos o "servidor4.js"

15. $ node servidor4.js  (calculadora)  

16. http://localhost:2002/add?n1=5&n2=3
    http://localhost:2002/sub?n1=10&n2=4

17. Criamos o "servidor5.js" (axios)

16. $ json-server --watch --port 4000 mapa-virtual.json

17. $ node servidor5.js 


 