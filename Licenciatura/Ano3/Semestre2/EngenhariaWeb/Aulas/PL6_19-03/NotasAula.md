# Ficheiro inscritos.json

Tem erros e temos de os corrigir.

A correção foi corrigir os atributos, mudando por exemplo 'nome' para '"nome"'.
Este json tem as entradas colocadas em linha, não tem o formato comum de um json, é possível importar para o mongodb com este formato. Este json tem o formato de cada linha ser uma entrada para um documento {...} e no final de cada linha não tem ','.

## Copiar o ficheiro json para dentro do docker do mongo para a pasta tmp (f.. é o container id)

`docker cp inscritos.json f56b14b2eaa4:/tmp`

## Importa o ficheiro json para dentro do mongo criando a database "tp2ew2024" e a collection "atletas"

`mongoimport -d tp2ew2024 -c atletas inscritos.json`

## Comandos importantes para o mongodb

-   `show dbs`
-   `use <database>`
-   `show collections`
-   `db.<collection>.<query>`

    --> Mostra os atletas

    ```
    db.atletas.find()
    ```

    --> Mostra somente o nome e a morada

    ```
    db.atletas.find({},{_id:0, nome:1, morada:1})
    ```

    --> Quantos atletas estão inscritos em cada corrida

    ```
    db.atletas.aggregate([
        {
            $group: {
                _id: "$prova",
                total: {$sum:1}
            }
        }
    ])
    ```

    --> Quantas atletas (femininas) estão inscritos

    ```
    db.atletas.countDocuments({
        prova: /Ultra/, escalao: /Fem/
    })
    ```

    --> Procura por documentos onde o campo equipa contenha a palavra "turbulentos" (ou "Turbulentos"), e então retorna o número de documentos encontrados.

    ```
    db.atletas.find(
        {equipa:/turbulentos/i},
        {nome:1, dataNasc:1}
        ).count()
    ```

## Formatação do alunos.json

Colocamos este ficheiro no formato correto para importar para o mongo.
Os dados desse ficheiro estão dentro de '[{...},{...},...]', logo é um jsonArray, por isso temos que acrescentar isso no comando a seguir.

`docker cp alunos.json f56b14b2eaa4:/tmp`

`mongoimport -d tp2ew2024 -c alunos alunos.json --jsonArray`

## Programação seguinte da aula

`npx express-generator apiAlunos`
`npm install`
`npm install mongoose`
`npm start`
