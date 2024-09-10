# Explorar o que tem dentro da dir galunos

## Pasta *public*
Com imagens e o estilo css.

## Dataset *alunos* em csv e json
Temos o dataset dos alunso em csv e o mesmo convertido em json.

## Module *server*
Teremos que completer o switch com o GETs e os POSTs.

## Module *static*
Um módulo estático serve para servir recursos estáticos, como arquivos CSS, imagens e ícones, a partir de uma pasta pública em uma aplicação web. Esses recursos são acessados diretamente pelo navegador do cliente e não são processados dinamicamente pelo servidor. O módulo estático ajuda a simplificar o processo de entrega desses recursos e a melhorar o desempenho da aplicação, pois permite que o servidor os sirva de forma eficiente, sem a necessidade de processamento adicional.

## Moduile *templates*
O módulo "templates" geralmente serve para lidar com a geração dinâmica de conteúdo HTML em aplicativos da web. Ele permite a definição de modelos (templates) que incorporam variáveis e lógica de controle, facilitando a criação de páginas da web dinâmicas. Com o módulo de templates, é possível separar o código HTML do código JavaScript, facilitando a manutenção e o desenvolvimento de aplicativos web mais escaláveis e organizados.


# Comandos da aula

**$** json-server --watch alunos.json

**$** node server.js 

## Links

### GET "/" OU GET "/alunos"
http://localhost:3050
http://localhost:3050/alunos

### GET "/alunos/:id"
http://localhost:3050/alunos/A95345

### GET "/alunos/edit/id"
###### PUT "/alunos/edit/:id"
http://localhost:3050/alunos/edit/A95345

### GET "/alunos/registo"
###### POST "/alunos/registo"
http://localhost:3050/alunos/registo

### GET "/alunos/delete/:id"
###### DELETE "/alunos/delete/:id"
http://localhost:3050/alunos/delete/A100758

## HTTP response status codes
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#information_responses

