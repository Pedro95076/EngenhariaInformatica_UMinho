# Ficha engweb2023-normal
# Avaliação: Engenharia Web Web
## 30 de Maio de 2023
### Licenciatura em Engenharia Informática (3º ano)
## Sinopsis

O objectivo principal deste teste é avaliar os conhecimentos obtidos durante as aulas no desenvolvimento de aplicações Web e outras tarefas afins.

Antes de começares, lê atentamente até ao fim para ficares com uma percepção do todo que se pretende. 
Vais ver que tomarás decisões mais acertadas depois de uma leitura completa.

Os resultados finais deverão ser enviados ao docente da seguinte forma:
* Enviar por email para: `jcr@di.uminho.pt`;
* Colocar no subject/assunto: `ENGWEB2023::Normal::Axxxxx` ou `RPCW2023::Normal::PGxxxxx`, em que `Axxxxx` ou `PGxxxxx` corresponde ao número do aluno;
* Enviar ao docente um link do github para um repositório novo criado especificamente para o exame com o seguinte conteúdo (esta preparação poderá valer 1 valor do exame):
    * O repositório no GitHub deverá chamar-se `ENGWEB2023-Normal`;
    * Dentro do repositório deverá haver um ficheiro, `PR.txt`, contendo uma descrição de como fez a persistência de dados, do setup de bases de dados, respostas textuais pedidas, instruções de como executar as aplicações desenvolvidas, etc...
    * Dentro do repositório deverão existir duas pastas: `ex1`, onde colocarão a aplicação desenvolvida para responder ao primeiro exercício e, `ex2`, onde colocarão a aplicação desenvolvida para responder ao segundo exercício.

Os exercícios que envolvam criação de rotas serão testados com as rotas no enunciado, qualquer rota que seja diferente da pedida será avaliada com 0.

## Recursos

Recursos para a realização da prova:
   * [Distribuição Arbórea nalgumas freguesias portuguesas](plantas.json) (dataset em JSON obtido de `dados.gov.pt`), este ficheiro tem a seguinte estrutura:

```json
[
  {
    "Id": 20615557,
    "Número de Registo": 3,
    "Código de rua": 1685467,
    "Rua": "Rua Júlio Dinis",
    "Local": "Zambujeiro",
    "Freguesia": "Alcabideche",
    "Espécie": "pinheiro manso",
    "Nome Científico": "Pinus pinea",
    "Origem": "",
    "Data de Plantação": "",
    "Estado": "Adulto",
    "Caldeira": "Sim",
    "Tutor": "Sim",
    "Implantação": "Arruamento",
    "Gestor": "DGEV",
    "Data de actualização": "23/07/2021 19:50:54",
    "Número de intervenções": 6
  },
  ...
]
```


## Exercício 1: Plantas (API de dados)

Neste exercício, irás implementar uma API de dados sobre o dataset fornecido.
Encontra-se dividido em 3 partes.

### 1.1 Setup 

Realiza as seguintes tarefas sem alterares os nomes da base de dados e coleção fornecidos:
* Analisa o dataset fornecido;
* Introduz as alterações que achares necessárias no dataset;
* Importa-o numa base de dados em MongoDB com os seguintes parâmetros:
    * database: `-d plantas`
    * collection: `-c plantas`
* Testa se a importação correu bem.

### 1.2 Queries (warm-up)

Especifica queries em MongoDB para responder às seguintes questões:
1. Quantos registos estão na base de dados;
2. Quantos registos de plantação se encontram na freguesia "São Domingos de Rana"?
3. Qual a lista de freguesias (ordenada alfabeticamente e sem repetições)? 
4. Qual a distribuição dos registos por freguesia (quantos registos em cada freguesia)
5. Qual a distribuição dos registos por espécie?

### 1.3 API de dados

Desenvolve agora uma API de dados, que responde na **porta 15030** e que responda às seguintes rotas/pedidos:

* `GET /plantas`: devolve uma lista com todos os registos;
* `GET /plantas/:id`: devolve o registo com identificador `id`;
* `GET /plantas?especie=EEEE`: devolve a lista dos registos correspondentes à espécie `EEEE`;
* `GET /plantas?implant=AAA`: devolve a lista dos registos com implantação `AAA`;
* `GET /plantas/freguesias`: devolve a lista de freguesias ordenada alfabeticamente e sem repetições;
* `GET /plantas/especies`: devolve a lista das espécies vegetais ordenada alfabeticamente e sem repetições;
* `POST /plantas`: acrescenta um registo novo à BD;
* `DELETE /plantas/:id`: elimina da BD o registo com o identificador `id`.

Antes de prosseguires, testa as rotas realizadas com o Postman ou similar.


## Exercício 2: Plantas (Interface)

Tendo a API desenvolvida, desenvolve agora um novo serviço, que responde na **porta 15031** e que irá responder da seguinte forma:
1. Se colocares no browser o endereço `http://localhost:15031` deverás obter a página principal constituída por:
    * Um cabeçalho com metainformação à tua escolha;
    * Uma tabela contendo a lista de registos, um por linha, com os campos: `_id`, `Freguesia`, `Espécie`, `Estado` e `Número de intervenções`;
    * O campo `_id` deverá ser um link para a página do contrato com esse identificador;
    * O campo `Espécie` deverá ser um link para a página dessa espécie.

2. Se colocares no browser o endereço `http://localhost:15031/:id` deverás obter a página do registo com o identificador passado na rota:
    * Esta página deverá conter todos os campos do registo e um link para voltar à página principal.

3. Se colocares no browser o endereço `http://localhost:15031/especies/:id` deverás obter a página da espécie cujo nome corresponde ao parâmetro passado na rota (como fazes a associação do parâmetro à espécie é contigo, usa a imaginação):
    * Na página de cada espécie deverá constar o nome e a designação científica da espécie e uma tabela com a lista de registos dessa espécie (tabela com estrutura semelhante à da página principal).


Bom trabalho e boa sorte 
jcr
