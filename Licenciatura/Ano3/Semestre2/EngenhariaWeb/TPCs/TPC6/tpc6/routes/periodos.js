var express = require('express');
var router = express.Router();
var Periodo = require('../controllers/periodo');

/* GET users listing. */
router.get('/', function(req, res, next) {
  Periodo.list()
    .then(dados => res.jsonp(dados))
    .catch(erro => res.jsonp(erro))
});

router.post('/', function(req, res, next) {
  Periodo.insert(req.body)
    .then(dados => res.jsonp(dados))
    .catch(erro => res.jsonp(erro))
});

router.put('/:id', function(req, res, next) {
  Periodo.update(req.params.id, req.body)
    .then(dados => res.jsonp(dados))
    .catch(erro => res.jsonp(erro))
});

router.delete('/:id', function(req, res, next) {
  Periodo.delete(req.params.id, req.body)
    // .then(console.log("Deleted " + req.params.id))
    // .catch(erro => res.jsonp(erro))
});

module.exports = router;