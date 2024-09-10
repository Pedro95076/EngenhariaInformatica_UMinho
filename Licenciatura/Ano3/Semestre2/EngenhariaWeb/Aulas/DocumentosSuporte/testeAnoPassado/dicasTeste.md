# 1 ==> API de dados

## 1.1 ==> Setup

**Exemplo:**

```txt
Para a persistência dos dados foi utilizado mongoDB.
O dataset deve ser alterado de modo a que o campo "Id" passe a ser "_id". —> Usar o remplace do sublime
De seguida o dataset deve ser importado para o MongoDB com o seguinte comando:
mongoimport -d plantas -c plantas --file plantas.json --jsonArray
Tendo o cuidado de ver so o import foi bem sucedido:
29617 document(s) imported successfully. 0 document(s) failed to import.
```

## 1.2 ==> Queries

**Exemplo:**

```txt
Antes de realizar as queries deve-se entrar na base de dados com o comando: use plantas

Exemplo de queries:

Database é “plantas”

1. db.plantas.count()
Resposta: 29617
2. db.plantas.find({"Freguesia": "São Domingos de Rana"}).count()
Resposta: 5903
3. db.plantas.distinct("Freguesia").sort()
Resposta: [
'',
'Abóboda',
'Alcabideche',
'São Domingos de Rana',
'U.F. Carcavelos e Parede',
'U.F. Cascais e Estoril'
]
4. db.plantas.aggregate([{$group: {_id: "$Freguesia", count: {$sum: 1}}}])
Resposta: [
{ _id: 'Alcabideche', count: 4034 },
{ _id: 'U.F. Cascais e Estoril', count: 12023 },
{ _id: '', count: 26 },
{ _id: 'São Domingos de Rana', count: 5903 },
{ _id: 'Abóboda', count: 2 },
{ _id: 'U.F. Carcavelos e Parede', count: 7629 }
]
5. db.plantas.aggregate([{$group: {_id: "$Espécie", count: {$sum: 1}}}])
Resposta: [
{ _id: 'freixo', count: 411 },
{ _id: 'liquidambar', count: 182 },
{ _id: 'damasqueiro', count: 1 },
...
]
```

## 1.3 ==> API de Dados

```txt
Desenvolve agora uma API de dados, que responde na porta 15030 e que responda às seguintes rotas/pedidos:

GET /plantas: devolve uma lista com todos os registos;
GET /plantas/:id: devolve o registo com identificador id;
GET /plantas?especie=EEEE: devolve a lista dos registos correspondentes à espécie EEEE;
GET /plantas?implant=AAA: devolve a lista dos registos com implantação AAA;
GET /plantas/freguesias: devolve a lista de freguesias ordenada alfabeticamente e sem repetições;
GET /plantas/especies: devolve a lista das espécies vegetais ordenada alfabeticamente e sem repetições;
POST /plantas: acrescenta um registo novo à BD;
DELETE /plantas/:id: elimina da BD o registo com o identificador id.
Antes de prosseguires, testa as rotas realizadas com o Postman ou similar.
```

```txt
Entrar na pasta "ex1"
Instalar dependencias utilizando o comando `npm install`
Executar o script utilizando o comando `npm start`

Para testar as varias rotas podem ser executados os seguintes comandos:

1. curl http://localhost:15030/plantas > plantas.json
• `GET /plantas`: devolve uma lista com todos os registos;

2. curl http://localhost:15030/plantas/20615564 > planta_20615564.json
• `GET /plantas/:id`: devolve o registo com identificador `id`;

3. curl http://localhost:15030/plantas?especie=catalpa > catalpas.json
• `GET /plantas?especie=EEEE`: devolve a lista dos registos correspondentes à espécie `EEEE`;

4. curl http://localhost:15030/plantas?implant=Arruamento > arruamento.json
• `GET /plantas?implant=AAA`: devolve a lista dos registos com implantação `AAA`;

5. curl http://localhost:15030/plantas/freguesia > freguesias.json
• `GET /plantas/freguesias`: devolve a lista de freguesias ordenada alfabeticamente e sem repetições;

6. curl http://localhost:15030/plantas/especies > especies.json
• `GET /plantas/especies`: devolve a lista das espécies vegetais ordenada alfabeticamente e sem repetições;

7. curl -X POST -H "Content-Type: application/json" -d '{"_id": 0,"Número de Registo": 9999999999999,"Código de rua": 1667044,"Rua": "Avenida General Carmona","Local": "Estoril","Freguesia": "U.F. Cascais e Estoril","Espécie": "croacia","Nome Científico": "Catalpa bungei","Origem": "","Data de Plantação": "20/02/2013","Estado": "Jovem","Caldeira": "Sim","Tutor": "Sim","Implantação": "Arruamento","Gestor": "DGEV","Data de actualização": "23/07/2021 19:47:51","Número de intervenções": 5}' localhost:15030/plantas > resposta_put.json
• `POST /plantas`: acrescenta um registo novo à BD;

8. curl -X DELETE localhost:15030/plantas/20615564 > resposta_delete.json
• `DELETE /plantas/:id`: elimina da BD o registo com o identificador `id`.
```

**O que fazer:**
1 - Modificar "www"
2 - Modificar "app.js"
3 - Modificar "planta.js" em "models"
4 - Modificar "index.js" em "routes"
5 - Modificar “planta.js” em “controllers” para criar todas as funções que foram chamadas no ponto anterior

# Inteface

```txt
Tendo a API desenvolvida, desenvolve agora um novo serviço, que responde na porta 15031 e que irá responder da seguinte forma:

Se colocares no browser o endereço http://localhost:15031 deverás obter a página principal constituída por:

Um cabeçalho com metainformação à tua escolha;
Uma tabela contendo a lista de registos, um por linha, com os campos: _id, Freguesia, Espécie, Estado e Número de intervenções;
O campo _id deverá ser um link para a página do contrato com esse identificador;
O campo Espécie deverá ser um link para a página dessa espécie.
Se colocares no browser o endereço http://localhost:15031/:id deverás obter a página do registo com o identificador passado na rota:

Esta página deverá conter todos os campos do registo e um link para voltar à página principal.
Se colocares no browser o endereço http://localhost:15031/especies/:id deverás obter a página da espécie cujo nome corresponde ao parâmetro passado na rota (como fazes a associação do parâmetro à espécie é contigo, usa a imaginação):

Na página de cada espécie deverá constar o nome e a designação científica da espécie e uma tabela com a lista de registos dessa espécie (tabela com estrutura semelhante à da página principal).
```

```txt
Entrar na pasta "ex2"
Instalar dependencias utilizando o comando `npm install`
Executar o script utilizando o comando `npm start`

Para testar as varias rotas podem ser executados os seguintes comandos:

1. Aceder ao link 'http://localhost:15031/'
2. Aceder ao link 'http://localhost:15031/20615564'
3. Aceder ao link 'http://localhost:15031/especies/catalpa'
```

**O que fazer:**
1 - Modificar “www”
2 - Criar uma view em pug para cada página que pede no enunciado (modificar “layout”)
3 - Modificar “index.js” em “routes”, criar uma rota para cada alínea do enunciado
