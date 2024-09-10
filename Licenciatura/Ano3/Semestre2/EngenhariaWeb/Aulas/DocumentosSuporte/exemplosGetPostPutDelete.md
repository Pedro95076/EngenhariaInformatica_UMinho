# Exemplo simples de um GET

```
const axios = require('axios')

axios.get('http://localhost:3000/pessoas')
    .then(function(resp){
        var pessoas = resp.data
        console.log("Recuperei " + pessoas.length + " registos")
        console.log(pessoas[3].nome)
    })
    .catch(erro => {
        console.log("Erro: " + erro)
    })
```

# Exemplos simples de um POST

```
const axios = require('axios')

axios.post('http://localhost:3000/pessoas', {
    id: '112',
    CC: '12345',
    nome: 'Maria JosÃ©'
  })
    .then(function(resp){
        console.log(resp.status)
    })
    .catch(erro => {
        console.log("Erro: " + erro)
    })
```

# Exemplo simples de um PUT

```
const axios = require('axios');

axios.put('http://localhost:3000/pubs/DAW2020', {
    "id": "DAW2020",
    "title": "Aula5",
    "year": "2020",
    "authors": [
        "Alexandra LourenÃ§o",
        "JosÃ© Carlos Ramalho"
    ]
}).then(resp => {
    console.log(resp.data);
}).catch(error => {
    console.log(error);
});
```

# Exemplo simples de um DELETe

```
const axios = require('axios');

axios.delete('http://localhost:3000/pubs/DAW2020')
.then(resp => {
    console.log(resp.data);
}).catch(error => {
    console.log(error);
});
```

-   **GET** - Pedir info (200 se correu bem)
-   **POST** - Enviar info (201 se correu bem)
-   **PUT** - Enviar e alterar info
-   **DELETE** - Apagar info
-   400's e 500's são erros
