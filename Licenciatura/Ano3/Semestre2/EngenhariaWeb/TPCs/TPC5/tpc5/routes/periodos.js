var express = require('express');
var router = express.Router();
var axios = require('axios')

router.get('/', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://localhost:3000/periodos")
  .then(resp => {
    var periodos = resp.data
    res.status(200).render("periodsListPage", {"plist" : periodos, "data" : d})
  })
  .catch(erro => {
    res.status(501).render("error", {"error" : erro})
  })
});
module.exports = router;

// ----------------------------------------------------------------//
// ----------------------------------------------------------------//
// ------------------------    REGISTO    -------------------------//
// ----------------------------------------------------------------//
// ----------------------------------------------------------------//

router.get('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  res.status(200).render("periodFormPage", {"data" : d})
});

router.post('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var result = req.body
  console.log(result)

  axios.post("http://localhost:3000/periodos", result)
  .then(resp => {
    //axios put 
    res.status(201).redirect('/')
  })
  .catch(erro => {
    res.status(502).render("error", {"error" : erro})
  })
});

// ----------------------------------------------------------------//
// ----------------------------------------------------------------//
// ------------------------    EDIT    ----------------------------//
// ----------------------------------------------------------------//
// ----------------------------------------------------------------//

router.get('/edit/:idPeriodo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://localhost:3000/periodos/" + req.params.idPeriodo)
  .then(resp => {
      var periodo = resp.data
      res.status(200).render("periodFormEditPage", {"p" : periodo, "data" : d})
  })
  .catch(erro => {
      res.status(503).render("error", {"error" : erro})
  })
});

router.post('/edit/:idPeriodo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var periodo = req.body
  axios.put("http://localhost:3000/periodos/" + req.params.idPeriodo, periodo)
  .then(resp => {
    console.log(periodo)
    res.status(202).redirect("/")
  })
  .catch(erro => {
      res.status(504).render("error", {"error" : erro})
  })
});

// ----------------------------------------------------------------//
// ----------------------------------------------------------------//
// -----------------------    DELETE    ---------------------------//
// ----------------------------------------------------------------//
// ----------------------------------------------------------------//

router.get('/delete/:idPeriodo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.delete("http://localhost:3000/periodos/" + req.params.idPeriodo)
  .then(resp => {
      res.redirect("/")
  })
  .catch(erro => {
      res.status(505).render("error", {"error" : erro})
  })
});

// ----------------------------------------------------------------//
// ----------------------------------------------------------------//
// --------------------    COMPOSER PAGE    -----------------------//
// ----------------------------------------------------------------//
// ----------------------------------------------------------------//

router.get('/:idPeriodo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://localhost:3000/periodos/" + req.params.idPeriodo)
  .then(resp => {
    var compositores = resp.data.compositores
    var periodoInfo = resp.data
    if(!compositores){
      res.status(200).render("emptyComposerList", {"data" : d})
    }
    else {
      res.status(200).render("composersPorPeriodo", {"compositores" : compositores, "pInfo" : periodoInfo,"data" : d})
    }
  })
  .catch(erro => {
      res.status(506).render("error", {"error" : erro})
  })
});