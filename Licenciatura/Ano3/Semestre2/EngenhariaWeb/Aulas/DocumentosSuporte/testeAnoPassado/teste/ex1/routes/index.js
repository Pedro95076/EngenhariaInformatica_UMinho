var express = require('express');
var router = express.Router();
var Planta = require('../controllers/planta');


/* GET /plantas/freguesias */
router.get('/plantas/freguesias', function(req, res, next) {
  Planta.getFreguesias()
    .then(listas => {
      res.jsonp(listas)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção das lista de freguesias"})
    })
});

/* GET /plantas/especies */
router.get('/plantas/especies', function(req, res, next) {
  Planta.getEspecies()
    .then(listas => {
      res.jsonp(listas)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção das lista de especies"})
    })
});


/* GET /plantas 
   GET /plantas?especie=EEEE
   GET /plantas?implant=AAAA
*/
router.get('/plantas', function(req, res, next) {
  if(req.query.especie){
    Planta.getPlantaEspecie(req.query.especie)
      .then(listas => {
        res.jsonp(listas)
      })
      .catch(erro => {
        res.render('error', {error: erro, message: "Erro na obtenção das lista de plantas"})
      })
  }
  else if(req.query.implant){
    Planta.getPlantaImplant(req.query.implant)
      .then(listas => {
        res.jsonp(listas)
      })
      .catch(erro => {
        res.render('error', {error: erro, message: "Erro na obtenção das lista de plantas"})
      })
  }
  else{
    Planta.list()
      .then(listas => {
        res.jsonp(listas)
      })
      .catch(erro => {
        res.render('error', {error: erro, message: "Erro na obtenção das lista de plantas"})
      })
  }
});


/* GET /plantas/:id */
router.get('/plantas/:id', function(req, res, next) {
  Planta.getPlanta(req.params.id)
    .then(p => {
      res.jsonp(p)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção da planta" + req.params.id})
    })
});

/* POST /plantas 

Example of new plant:
{
    "Número de Registo": 9999999999999,
    "Código de rua": 1667044,
    "Rua": "Avenida General Carmona",
    "Local": "Estoril",
    "Freguesia": "U.F. Cascais e Estoril",
    "Espécie": "catalpa bola",
    "Nome Científico": "Catalpa bungei",
    "Origem": "",
    "Data de Plantação": "20/02/2013",
    "Estado": "Jovem",
    "Caldeira": "Sim",
    "Tutor": "Sim",
    "Implantação": "Arruamento",
    "Gestor": "DGEV",
    "Data de actualização": "23/07/2021 19:47:51",
    "Número de intervenções": 5
  }

Example post using curl:
curl -X POST -H "Content-Type: application/json" -d '{"_id": 0,"Número de Registo": 9999999999999,"Código de rua": 1667044,"Rua": "Avenida General Carmona","Local": "Estoril","Freguesia": "U.F. Cascais e Estoril","Espécie": "catalpa bola","Nome Científico": "Catalpa bungei","Origem": "","Data de Plantação": "20/02/2013","Estado": "Jovem","Caldeira": "Sim","Tutor": "Sim","Implantação": "Arruamento","Gestor": "DGEV","Data de actualização": "23/07/2021 19:47:51","Número de intervenções": 5}' localhost:15030/plantas
*/
router.post('/plantas', function(req, res, next) {
  Planta.addPlanta(req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na inserção da planta"})
    })
});

/* PUT /plantas/:id */
router.put('/plantas/:id', function(req, res, next) {
  req.body._id = req.params.id
  Planta.updatePlanta(req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na atualização da planta"})
    })
});

/* DELETE /plantas/:id 

Example delete using curl:
curl -X DELETE localhost:15030/plantas/52270501
*/
router.delete('/plantas/:id', function(req, res, next) {
  Planta.deletePlanta(req.params.id)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na eliminação da planta"})
    })
});



module.exports = router;
