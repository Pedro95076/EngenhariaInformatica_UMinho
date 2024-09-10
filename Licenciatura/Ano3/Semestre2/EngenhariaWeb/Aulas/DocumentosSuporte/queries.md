# Mongo

**Instalação**

1. `docker pull mongo`
2. `docker network create NET1`
3. `docker volume create VOL1`
4. `docker run -d --network NET1 -h mongo --name mongo -p 27017:27017 -v VOL1:/data/db mongo`

Para depois dar run com a app do docker:

1. Entrar no Docker
2. Dar run ao container "mongo"

**Entrar pela app "MongoDB Compass"**

1. Abrir a aplicação "MongoDB Compass"
2. Conectar se a "mongodb://localhost:27017"

**Entrar na shell do mongo"**

1. docker exec -it <container-id> bash
2. mongosh

# Ficheiro inscritos.json

Tem erros e temos de os corrigir.

A correção foi foi corrigir os atributos, mudando por exemplo 'nome' para '"nome"'.
Este json tem as entradas colocadas em linha, não tem o formato comum de um json, é possível importar para o mongodb com este formato. Este json tem o formato de cada linha ser uma entrada para um documento {...} e no final de cada linha não tem ','.

## Copiar o ficheiro json para dentro do docker do mongo para a pasta tmp (f.. é o container id)

`docker cp inscritos.json f56b14b2eaa4:/tmp`

## Importa o ficheiro json para dentro do mongo

`mongoimport -d <database> -c <collection> <ficheiro.json>`
OU
Colocamos este ficheiro no formato correto para importar para o mongo.
Os dados desse ficheiro estão dentro de '[{...},{...},...]', logo é um jsonArray, por isso temos que acrescentar isso no comando a seguir.
`mongoimport -d <database> -c <collection> <ficheiro.json> --jsonArray`

## Comandos importantes para o mongodb

-   `show dbs`
-   `use <database>`
-   `show collections`
-   `db.<collection>.<query>`

## Queries

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

### Mais exemplos

=> Quantos exames estão registados?
`db.exames.count();`

=> Quantos exames tiveram um resultado válido?
`db.exames.count({ resultado: true });`

=> Qual a distribuição dos exames por género?

```
db.exames.aggregate([
    {
        $group: {
            _id: "$género",
            total: { $sum: 1 }
        }
    }
]);
```

=> Qual a distribuição dos exames por modalidade?

```
db.exames.aggregate([
    {
        $group: {
            _id: "$modalidade",
            count: { $sum: 1 }
        }
    }
]);
```

=> Quantos atletas federados do "GDGoma" fizeram EMD?

```
db.exames.count({
    "clube": "GDGoma",
    "federado": true,
    "dataEMD": { $exists: true }
});
```

=> Quantos atletas do género feminino que praticam Triatlo fizeram EMD?

```
db.exames.count({
    "modalidade": "Triatlo",
    "género": "F",
    "dataEMD": { $exists: true }
});
```
