Instalar Express: npx express-generator --view=pug

**Iniciar Express:** npm init:

-   entry point: app.js
-   Acrescentar o start no package.json
-   E agora podemos usar por exemplo "npm start"
-   Cria 3 pastas:

-   controllers: Obtem os dados solicitados dos modelos

```
var axios = require('axios')

// Student list
module.exports.list = () => {
	return axios.get('http://localhost:3000/alunos?_sort=nome')
			.then(resposta => {
				return resposta.data
			})
			.catch(erro => {
				return erro
			})
}

module.exports.getAluno = id => {
	return axios.get('http://localhost:3000/alunos/' + id)
			.then(resposta => {
				return resposta.data
			})
			.catch(erro => {
				return erro
			})
}
```

-   views: Modelos, em pug, usados pelos controladores para renderizar os dados.

-   routes: Envia as gets, posts, etc para as funções de controle apropriadas.

```
var express = require('express');
var router = express.Router();
var Aluno = require('../controllers/aluno')

/* GET home page. */
router.get('/', function(req, res, next) { // trata de um pedido get que fizer match com a rota '/' e se fizem match executa a callback
  var data = new Date().toISOString().substring(0, 16)
  Aluno.list()
  	.then(alunos => {
  		res.render('index', { slist: alunos, d: data }); // template que vai usar a estrutura de dados passada à template
  	})
 	.catch(erro => {
 		res.render('error', {error: erro, message: "Erro na obtenção na lista de alunos"})
 	})
});

/* GET Student page. */
router.get('/alunos/:idAluno', function(req, res, next) { // trata de um pedido get que fizer match com a rota '/' e se fizem match executa a callback
  var data = new Date().toISOString().substring(0, 16)
  Aluno.getAluno(req.params.idAluno)
  	.then(aluno => {
  		res.render('aluno', { a: aluno, d: data });
  	})
 	.catch(erro => {
 		res.render('error', {error: erro, message: "Erro na obtenção do registo de aluno"})
 	})
});

module.exports = router;
```
