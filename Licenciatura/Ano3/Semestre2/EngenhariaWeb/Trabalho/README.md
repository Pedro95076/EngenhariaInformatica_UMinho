# Relatório do Projeto: Mapa das Ruas de Braga

**Membros do Projeto (grupo 7):**

-   A94015: João Daniel da Silva Carvalho
-   A95076: Pedro Marcelo Bogas Oliveira
-   A95458: Inês Meneses de Castro

Para executar o programa basta correr o comando `sudo docker compose up --build` ou `sudo docker-compose up --build`, e aceder ao site pela link `http://localhost:7001`.

## Índice

1. [Introdução](#introdução)
2. [Arquitetura do Sistema](#arquitetura-do-sistema)
    - [Manipulação de Dados XML](#manipulação-de-dados-xml)
    - [API](#api)
    - [Interface do Utilizador](#interface-do-utilizador)
    - [Gestão de Utilizadores](#gestão-de-utilizadores)
3. [Utilização do Docker no Projeto](#utilização-do-docker-no-projeto)
4. [Backup e Restauração da Base de Dados MongoDB](#backup-e-restauração-da-base-de-dados-mongodb)
5. [Conclusão](#conclusão)

## Introdução

O projeto “Mapa das Ruas de Braga” visa disponibilizar interativamente um dos documentos mais importantes da história iconográfica de Braga: o mapa das ruas desenhado pelo padre Ricardo Rocha há 250 anos. Este mapa não é apenas um documento cartográfico, mas uma janela para a memória da cidade, capturando a sua essência e evolução ao longo dos séculos.

Para concretizar este objetivo, foi desenvolvida uma aplicação web que permite aos utilizadores navegar, adicionar e editar informações sobre o mapa. A aplicação está dividida em três partes principais: uma API para fornecer dados, uma interface de usuário para interação e scripts para manipulação de dados XML.

Este relatório detalha a arquitetura do sistema, os processos principais envolvidos na ingestão, administração e disseminação dos dados, as funcionalidades comuns implementadas, a gestão de utilizadores e os detalhes técnicos da implementação. O objetivo é fornecer uma visão abrangente do projeto, destacando as suas principais características e funcionamento.

## Arquitetura do Sistema

### Manipulação de Dados XML

A manipulação de dados XML no projeto “Mapa das Ruas de Braga” é realizada por meio de vários scripts Python, cada um responsável por diferentes aspetos do processamento e conversão de dados. A seguir, uma descrição detalhada de cada script:

#### 1. `converte.py`

O script `converte.py` é responsável por consolidar dados XML de vários ficheiros num único arquivo `datas.xml`. O processo envolve:

-   **Leitura de arquivos XML:** Percorre o diretório `./texto` em busca de todos os ficheiros XML.
-   **Parsing e extração de dados:** Utiliza `xml.etree.ElementTree` para analisar os arquivos e extrair elementos `<data>`.
-   **Criação de novo elemento XML:** Para cada elemento `<data>` encontrado, cria um elemento com subelementos `<nome>`, `<rua>`, e `<_id>`, preenchidos com as informações extraídas e um ID único gerado com `uuid`.
-   **Formatação e armazenamento:** Usa `xml.dom.minidom` para formatar o XML gerado e guardar o resultado em `datas.xml`.

#### 2. `entidades.py`

O script `entidades.py` cria o ficheiro `entidades.xml`, onde armazena informações sobre entidades extraídas dos arquivos XML no diretório `./texto`. O processo segue uma lógica semelhante ao `converte.py`:

-   **Leitura e parsing de arquivos XML.**
-   **Extração e transformação:** Extrai entidades, converte os seus nomes para maiúsculas, e adiciona elementos `<tipo>`, `<nome>`, e `<rua>`.
-   **Geração e formatação de novo XML:** Utiliza `minidom` para formatação e guarda o XML final em `entidades.xml`.

#### 3. `insertImage.py`

O script `insertImage.py` adiciona informações de imagens ao ficheiro `output.json`. As imagens são correspondidas com entradas específicas com base em padrões de nomes de ficheiros.

-   **Extração de dados das imagens:** Usa expressões regulares para extrair IDs e tipos das imagens.
-   **Atualização do JSON:** Insere objetos de imagem na estrutura de dados carregada a partir de `output.json`.

#### 4. `lugares.py`

Este script cria o arquivo `lugares.xml`, adicionando informações sobre lugares.

-   **Leitura de arquivos XML no diretório `./texto`.**
-   **Criação de elementos XML para lugares:** Inclui elementos `<nome>`, `<rua>`, e `<posição>` para cada lugar encontrado.
-   **Formatação e armazenamento:** Utiliza `minidom` para guarda o arquivo XML formatado.

#### 5. `main.py`

O script `main.py` integra todos os dados processados anteriormente num arquivo JSON `output.json`.

-   **Extração e agregação de dados:** Lê múltiplos arquivos XML e agrega dados de entidades, datas e lugares com base no número da rua.
-   **Estruturação dos dados:** Cria uma estrutura de dados JSON organizada por ruas, com todas as informações relevantes integradas.
-   **Armazenamento:** Guarda o JSON resultante como `output.json`.

Estes scripts combinam-se para formar uma robusta pipeline de processamento de dados XML, garantindo que as informações das ruas de Braga sejam agregadas, formatadas e apresentadas de forma estruturada e acessível na aplicação web.

#### Organização dos Dados no `output.json`

O ficheiro `output.json` é o resultado da integração e processamento dos dados XML extraídos dos arquivos presentes no diretório `./texto`. Este arquivo JSON contém todas as informações relevantes das ruas de Braga, organizadas de forma estruturada para facilitar o acesso e uso na aplicação.

Cada entrada representa uma rua específica e contém diversas propriedades detalhadas sobre essa rua. A estrutura é composta por uma lista de objetos JSON, onde cada objeto corresponde a uma rua e possui os seguintes campos:

-   **`_id`**: Identificador único da rua. É um número inteiro que ajuda a distinguir cada rua individualmente.
-   **`nome`**: Nome da rua.
-   **`para`**: Lista de parágrafos, cada entrada na lista é uma string representando uma descrição ou informação histórica.
-   **`figuras`**: Uma lista de objetos, cada um representando uma imagem ou figura associada à rua. Cada objeto contém:
    -   `id`: Identificador único da figura.
    -   `figuraId`: Tipo da figura (por exemplo, “atual” ou “imagem”).
    -   `imagem`: Caminho relativo da imagem.
    -   `legenda`: Legenda da imagem.
-   **`lista_casas`**: Lista de objetos de casas. Cada objeto contém:
    -   `_id_`: Número da casa.
    -   `enfiteuta`: Nome do enfiteuta.
    -   `foro`: Informações sobre o foro.
    -   `desc`: Descrição detalhada da casa.
-   **`datas`**: Lista de objetos de datas importantes. Cada objeto contém:
    -   `rua`: Referência à rua.
    -   `nome`: Nome ou descrição da data.
    -   `posição`: Identificador único da posição.
-   **`entidades`**: Lista de objetos de entidades. Cada objeto contém:
    -   `rua`: Referência à rua.
    -   `tipo`: Tipo de entidade (por exemplo, “instituição”).
    -   `nome`: Nome da entidade.
    -   `posição`: Identificador único da posição.
-   **`lugares`**: Lista de objetos de lugares significativos. Cada objeto contém:
    -   `rua`: Referência à rua.
    -   `nome`: Nome do lugar.
    -   `posição`: Identificador único da posição.

Essa estrutura detalhada garante que todas as informações relevantes sobre cada rua sejam armazenadas de forma organizada e facilmente acessível, permitindo uma análise e visualização eficazes dos dados na aplicação.

### API

A API foi desenvolvida para gerir um sistema de posts, ruas e utilizadores, e possui diferentes componentes, incluindo controladores, modelos e rotas. Cada componente desempenha um papel específico no funcionamento da API.

#### Controladores

Os controladores são responsáveis por gerir a lógica de negócios e interação com os modelos. Abaixo estão os controladores principais da API:

1. **Auth Controller (auth.js)**:

    - `verificaAcesso`: Verifica se um token de acesso válido foi fornecido. Caso contrário, retorna um erro 401.
    - `verificaMesmoUser`: Verifica se o utilizador do token corresponde ao utilizador solicitado ou se é um administrador. Retorna 403 se o acesso for negado.

2. **Post Controller (post.js)**:

    - `list`: Retorna uma lista de todos os posts.
    - `findById`: Retorna um post específico pelo ID.
    - `findByUserId`: Retorna todos os posts de um utilizador específico.
    - `findCommentsByPostId`: Retorna os comentários de um post específico.
    - `insert`: Insere um novo post.
    - `update`: Atualiza um post existente.
    - `remove`: Remove um post pelo ID.
    - `removeC`: Remove um comment de um post pelo ID.
    - `addComment`: Adiciona um comentário a um post específico.

3. **Rua Controller (rua.js)**:

    - `list`: Retorna uma lista de todas as ruas.
    - `findById`: Retorna uma rua específica pelo ID.
    - `insert`: Insere uma nova rua.
    - `update`: Atualiza uma rua existente.
    - `remove`: Remove uma rua pelo ID.

4. **User Controller (users.js)**:
    - `list`: Retorna uma lista de todos os utilizadores.
    - `getUser`: Retorna um utilizador específico pelo ID.
    - `addUser`: Adiciona um novo utilizador.
    - `updateUser`: Atualiza as informações de um utilizador.
    - `updateUserStatus`: Atualiza o status ativo/inativo de um utilizador.
    - `updateUserPassword`: Atualiza a palavra-passe de um utilizador.
    - `deleteUser`: Remove um utilizador pelo ID.

#### Modelos

Os modelos definem a estrutura dos dados no MongoDB. Abaixo estão os modelos principais:

1. **Post Model (post.js)**:

    - Estrutura de um post com campos como `_id`, `rua_id`, `user_id`, `data`, `desc` e uma lista de comentários.
    - Cada comentário possui campos como `_id`, `post_id`, `user_id`, `comentario` e `data`.

2. **Rua Model (rua.js)**:

    - Estrutura de uma rua com campos como `_id`, `nome`, `para`, `figuras`, `listaCasas`, `datas`, `entidades` e `lugares`.
    - Figuras, casas, datas, entidades e lugares são subesquemas no esquema de rua.

3. **User Model (user.js)**:
    - Estrutura de um utilizador com campos como `username`, `password`, `email`, `filiacao`, `name`, `image`, `level`, `dateLastAccess` e `dateCreated`.
    - Utiliza o plugin `passport-local-mongoose` para autenticação local.

#### Rotas

As rotas definem os endpoints da API e como as requisições HTTP são tratadas. Abaixo estão as rotas principais:

1. **Post Routes (post.js)**:

    - `GET /`: Lista todos os posts.
    - `GET /:id`: Consulta um post específico pelo ID.
    - `GET /user/:userId`: Consulta todos os posts de um utilizador específico.
    - `GET /comments/:id`: Consulta os comentários de um post específico.
    - `POST /`: Cria um novo post.
    - `PUT /:id`: Atualiza um post específico.
    - `PUT /:id/comment`: Adiciona um comentário a um post específico.
    - `DELETE /:id`: Remove um post específico.

2. **Rua Routes (rua.js)**:

    - `GET /`: Lista todas as ruas.
    - `GET /:id`: Consulta uma rua específica pelo ID.
    - `POST /`: Cria uma nova rua, incluindo upload de imagens.
    - `PUT /:id`: Atualiza uma rua específica, incluindo upload de imagens.
    - `DELETE /:id`: Remove uma rua específica e a suas imagens associadas.

3. **User Routes (user.js)**:
    - `GET /`: Lista todos os utilizadores.
    - `GET /:id`: Consulta um utilizador específico pelo ID.
    - `POST /`: Adiciona um novo utilizador (autenticação necessária).
    - `POST /register`: Regista um novo utilizador.
    - `POST /login`: Autentica um utilizador e retorna um token JWT.
    - `PUT /:id`: Atualiza as informações de um utilizador específico.
    - `PUT /:id/desativar`: Desativa um utilizador específico.
    - `PUT /:id/ativar`: Ativa um utilizador específico.
    - `PUT /:id/password`: Atualiza a palavra-passe de um utilizador específico.
    - `DELETE /:id`: Remove um utilizador específico.

#### Autenticação na API

A autenticação na API é gerida principalmente via tokens JWT (JSON Web Tokens). Aqui está como ela é implementada em diferentes partes da API:

1. **Middleware de Verificação de Acesso (`auth.js`)**:

    - **`verificaAcesso`**: Este middleware verifica se o token JWT está presente e válido nos cabeçalhos da requisição (`Authorization`). Se o token estiver ausente ou inválido, retorna um erro de não autorizado (`401 Unauthorized`).
    - **`verificaMesmoUser`**: Este middleware verifica se o token JWT pertence ao utilizador cujo ID é especificado nos parâmetros da rota (`req.params.id`). Além disso, permite acesso se o utilizador possuir o nível de permissão `admin`. Caso contrário, retorna um erro de acesso proibido (`403 Forbidden`).

2. **Rotas de Utilizadores (`user.js`)**:

    - **GET `/users/:id`**: Utiliza o middleware `verificaAcesso` para validar o token antes de permitir o acesso aos detalhes do utilizador. Isso garante que apenas utilizadores autenticados possam consultar detalhes específicos de um utilizador.
    - **POST `/users/`**: Utiliza o middleware `verificaAcesso` para garantir que apenas utilizadores autenticados possam adicionar novos utilizadores à API.
    - **PUT `/users/:id`, DELETE `/users/:id`, PUT `/users/:id/desativar`, PUT `/users/:id/ativar`, PUT `/users/:id/password`, DELETE `/users/:id`**: Todos esses endpoints também utilizam o middleware `verificaAcesso` para garantir que apenas utilizadores autenticados possam realizar operações de atualização, desativação, ativação, alteração de senha e exclusão de utilizadores.

3. **Rota de Login (`user.js`)**:
    - **POST `/users/login`**: Esta rota utiliza o middleware `passport.authenticate('local')` para autenticar o utilizador com base nas credenciais fornecidas (nome de utilizador e senha). Se a autenticação for bem-sucedida, um token JWT é gerado usando `jwt.sign`, sendo então retornado no corpo da resposta.

##### Funcionamento da Autenticação

-   A autenticação é baseada em
    tokens JWT, que são gerados após um usuário se autenticar com sucesso
    através do endpoint `/users/login`.
-   O token JWT contém informações
    como o `username`, `level` e `sub` (ID do usuário), e é utilizado para
    autorizar acessos subsequentes aos recursos protegidos.
-   Todos os
    endpoints que requerem autenticação utilizam os middlewares
    `verificaAcesso` ou `verificaMesmoUser` para validar o token JWT antes
    de permitir o acesso.
-   Caso o token não seja válido ou não esteja
    presente, a API retorna um erro de não autorizado (401) para indicar que
    o acesso é negado.

##### Benefícios e Considerações

-   **Segurança**: O uso de tokens JWT garante que as comunicações entre cliente e servidor sejam seguras e que apenas utilizadores autenticados tenham acesso aos recursos da API.
-   **Flexibilidade**: Permite a implementação de diferentes níveis de permissão (por exemplo, administrador relativamente ao utilizador normal) com base nas informações contidas nos tokens JWT.
-   **Integração**: Integrado com o `passport` para suportar autenticação baseada em sessão e autenticação local de forma transparente.

### Interface do Utilizador

Este capítulo explora a interface do sistema, destacando as suas funcionalidades e o uso de templates Pug para renderização dinâmica de páginas.

#### Diretórios e Ficheiros Principais

1. **auth.js**: Ficheiro relacionado com a autenticação e controlo de acesso da aplicação. Ele define funções middleware para verificar o token JWT e controlar o acesso com base nos níveis de permissão.

2. **routes/index.js**: Define as rotas principais da aplicação, como rota inicial, operações CRUD para ruas, posts, e gestão de comentários, entre outras.

3. **views/**: Contém os ficheiros de visualização (templates EJS) os quais são renderizados pelo servidor.

-   **layout.pug**: Layout base para todas as páginas. Define a estrutura comum de todas as páginas HTML, incluindo metadados, estilos, corpo principal e rodapé. Inclui blocos que podem ser substituídos pelos templates que estendem este layout.

-   **home.pug**: Página inicial do site, que apresenta uma breve descrição do site e botões de navegação.

-   **registar.pug**: Página de registo para novos utilizadores, com um formulário para capturar o nome de utilizador e definir o nível de utilizador como 'user'.

-   **login.pug**: Página de login, com um formulário para autenticar utilizadores. Inclui campos para nome de utilizador e palavra-passe, além de um link para a página de registo.

-   **logout.pug**: Página de confirmação de logout, que confirma que o logout foi realizado com sucesso e oferece um botão para retornar à página de login.

-   **perfil.pug**: Página de perfil de utilizador. Mostra detalhes do seu perfil, incluindo nome, email, filiação, data de registo, nível de acesso e postagens associadas. Além disso, inclui um botão para editar o perfil do usuário.

-   **editPerfil**: Página de edição do perfil do utilizador para ser possível editar informações do seu perfil, como o nome de utilizador, palavra-passe, etc.

-   **ruas.pug**: Página principal que lista “Ruas de Braga”. Utiliza Pug para renderizar uma lista de ruas dinamicamente. Inclui um cabeçalho, campo de pesquisa, lista dinâmica de ruas, e um rodapé.

-   **rua.pug**: Página de detalhes de uma rua específica, como nome, imagens associadas, parágrafos descritivos, e lista de casas.

-   **addRua.pug**: Página de adição de uma nova rua, permitindo adicionar nome, descrição, imagens, casas, entidades, datas e lugares associados à rua, utilizando um formulário para inserção desses dados.

-   **editRua.pug**: Página de edição de detalhes de uma rua, que permite editar nome, descrição, imagens, casas, entidades, datas e lugares associados à rua.

-   **posts.pug**: Página de posts que exibe uma lista de posts com detalhes como utilizador, data, rua associada, figuras e parágrafos.

-   **post.pug**: Página de detalhes de um post específico. Mostra detalhes específicos de um post, como utilizador, data, rua associada, figuras, parágrafos e comentários. Além disso, inclui um formulário para adicionar comentários ao post.

-   **addPost.pug**: Página para adicionar um novo post ao sistema, que permite criar um post com título, conteúdo, imagens e categorias associadas. Para isso, inclui um formulário para inserção dos seguintes elementos, título, conteúdo (texto completo), upload de imagens, seleção de **categorias** e opções de formatação e estilo para o conteúdo.

-   **error.pug**: Página de erro, que mostra detalhes de erros, como status e pilha de chamadas.

## Utilização do Docker no Projeto

Utilizamos Docker neste projeto para facilitar o desenvolvimento, a implementação e a gestão dos nossos serviços.

O ficheiro `docker-compose.yml` define a configuração dos serviços que compõem a nossa aplicação. Utilizamos a versão 3.8 do Docker Compose e configuramos três serviços principais: `mongo`, `api` e `interface`.

### 1. Serviço Mongo

-   **Imagem**: `mongo:latest`
-   **Container Name**: `mongo`
-   **Portas**: Mapeia a porta 27017 do conteiner para a porta 27017 do host.
-   **Volumes**:
    -   `mongo-data`: Armazena os dados do MongoDB de forma persistente.
    -   `./xml`: Contém os arquivos XML carregados no banco de dados durante a inicialização.

### 2. Serviço API

-   **Build**: Define o caminho para o Dockerfile da API (`./api`).
-   **Portas**: Mapeia a porta 3000 do contêiner para a porta 3000 do host.
-   **Variáveis de Ambiente**: Define a URL de conexão com o MongoDB (`MONGO_URL=mongodb://mongo:27017/ruas`).
-   **Dependências**: O serviço `api` depende do serviço `mongo` e só inicia após o MongoDB estar disponível.
-   **Volumes**: Mapeia o diretório da API local (`./api`) para o diretório `/usr/src/app` dentro do contêiner.

#### 3. Serviço Interface

-   **Build**: Define o caminho para o Dockerfile da Interface (`./interface`).
-   **Portas**: Mapeia a porta 7001 do contêiner para a porta 7001 do host.
-   **Variáveis de Ambiente**: Define a URL da API (`API_URL=http://api:3000`).
-   **Dependências**: O serviço `interface` depende do serviço `api` e só inicia após a API estar disponível.
-   **Volumes**: Mapeia o diretório da Interface local (`./interface`) para o diretório `/usr/src/app` dentro do contêiner.

Ao executar o comando `sudo docker-compose up --build`, todos os serviços são iniciados conforme a ordem de dependências especificada.

## Backup e Restauração da Base de Dados MongoDB

Neste projeto é essencial garantir a integridade e segurança dos dados. Para isso, utilizamos scripts que automatizam o processo de backup e restauração do banco de dados MongoDB, assegurando que os dados possam ser facilmente salvos e recuperados em caso de necessidade.

### Script de Backup

O script de backup (`backup.sh`) é responsável por criar uma cópia de segurança do banco de dados MongoDB. Aqui está um resumo de como ele funciona:

1. **Preparação do Ambiente**: O script cria um diretório de backup dentro do conteiner MongoDB, se ele ainda não existir.
2. **Execução do Backup**: Utiliza a ferramenta `mongodump` para gerar um ficheiro de backup compactado do banco de dados, armazenando-o dentro do conteiner.
3. **Transferência para o Host**: O ficheiro de backup é copiado do conteiner para o sistema host, garantindo que uma cópia externa do banco de dados esteja disponível.

### Script de Restauração

O script de restauração (`restore.sh`) é utilizado para restaurar o banco de dados MongoDB a partir de um ficheiro de backup. Aqui está um resumo do seu funcionamento:

1. **Preparação do Ambiente**: O script verifica e cria, se necessário, o diretório de backup dentro do conteiner MongoDB.
2. **Transferência do Backup**: Copia o ficheiro de backup do sistema host para dentro do conteiner MongoDB.
3. **Execução da Restauração**: Utiliza a ferramenta `mongorestore` para restaurar o banco de dados a partir do ficheiro de backup, substituindo as coleções existentes para garantir uma restauração completa e atualizada.

## Conclusão

Em resumo, o projeto “Mapa das Ruas de Braga” alcançou avanços na criação de uma plataforma interativa para explorar o património histórico da cidade.
Enfrentamos desafios, mas conseguimos superá-los com sucesso através de colaboração e planeamento.

Este relatório destaca não apenas as conquistas alcançadas, mas também o potencial contínuo para aprimoramentos e novas descobertas no campo da preservação do património cultural através da tecnologia digital.
