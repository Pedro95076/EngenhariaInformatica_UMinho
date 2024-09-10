var express = require("express");
var router = express.Router();
var Aluno = require("../controllers/alunos");

/* GET */
router.get("/", function (req, res, next) {
    Aluno.list()
        .then((data) => res.jsonp(data))
        .catch((e) => res.jsonp(e));
});

/* POST */
router.post("/", function (req, res, next) {
    Aluno.insert(req.body)
        .then((data) => res.jsonp(data))
        .catch((e) => res.jsonp(e));
});

/* PUT */
router.put("/:id", function (req, res, next) {
    Aluno.update(req.params.id, req.body)
        .then((data) => res.jsonp(data))
        .catch((e) => res.jsonp(e));
});

/* DELETE */
router.delete("/:id", function (req, res, next) {
    Aluno.remove(req.params.id)
        .then((data) => res.jsonp(data))
        .catch((e) => res.jsonp(e));
});

module.exports = router;
