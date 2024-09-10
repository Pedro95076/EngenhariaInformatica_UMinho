var express = require('express');
var router = express.Router();
var Ficheiro = require("../controllers/aluno")

/* GET users listing. */
router.get('/', function(req, res, next) {
  if(req.query.tpc){
    Ficheiro.listAllIfTpc(req.query.tpc)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  }else{
    Ficheiro.list()
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
  }
});

router.get('/:id', function(req, res, next) {
  Ficheiro.findById(req.params.id)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.get('/:id/tpc', function(req, res, next) {
  Ficheiro.findAlunoTpcById(req.params.id)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.post('/', function(req, res, next) {
  console.log(req.body)
  Ficheiro.insert(req.body)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.post('/:id/tpc', function(req, res, next) {
  // TODO: ...
});

router.put('/:id', function(req, res, next) {
  Ficheiro.update(req.params.id, req.body)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.put('/:id/tpc/:idTpc', function(req, res, next) {
  Ficheiro.invertTpc(req.params.id, req.params.idTpc)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.delete('/:id', function(req, res, next) {
  return Ficheiro.remove(req.params.id)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

module.exports = router;
