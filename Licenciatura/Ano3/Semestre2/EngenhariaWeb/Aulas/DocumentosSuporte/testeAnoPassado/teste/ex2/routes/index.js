var express = require('express');
var router = express.Router();
var axios = require('axios');

router.get('/', function(req, res) {
  var data = new Date().toISOString().substring(0, 16);

  axios.get('http://localhost:15030/plantas')
    .then(dados => {
      res.render('plantas', { plantas: dados.data, d: data });
    })
    .catch(erro => {
      res.render('error', {error: erro});
    });
});

router.get('/:id', function(req, res) {
  var data = new Date().toISOString().substring(0, 16);

  axios.get('http://localhost:15030/plantas/' + req.params.id)
    .then(dados => {
      res.render('planta', { planta: dados.data, d: data });
       
    })
    .catch(erro => {
      res.render('error', {error: erro});
    });
});

router.get('/especies/:id', function(req, res) {
  var data = new Date().toISOString().substring(0, 16);

  axios.get('http://localhost:15030/plantas?especie=' + req.params.id)
    .then(dados => {
      var nome_cientifico = dados.data[0]["Nome Científico"];
      res.render('especie', { especie:req.params.id,cientifico: nome_cientifico, plantas: dados.data, d: data });
    })
    .catch(erro => {
      res.render('error', {error: erro});
    });
});

module.exports = router;
