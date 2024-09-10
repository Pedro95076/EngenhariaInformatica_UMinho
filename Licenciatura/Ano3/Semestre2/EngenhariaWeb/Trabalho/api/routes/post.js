var express = require('express');
var router = express.Router();
var Post = require('../controllers/post');

/* Listar os Posts (R) */
router.get('/', function (req, res) {
    Post.list()
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Consultar um Post (R) */
router.get('/:id', function (req, res) {
    Post.findById(req.params.id)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

router.get('/user/:userId', function (req, res) {
    Post.findByUserId(req.params.userId)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Fetch comments for a specific post (R) */
router.get('/comments/:id', function (req, res) {
    Post.findCommentsByPostId(req.params.id)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Criar um Post (C) */
router.post('/', async function (req, res) {

    const nextPostId = await Post.getNextPostId();

    var post = {
        _id: nextPostId,
        rua_id: req.body.rua_id,
        user_id: req.body.user_id,
        data: req.body.data,
        desc: req.body.desc,
        comentarios: req.body.comentarios ? (Array.isArray(req.body.comentarios) ? req.body.comentarios : (req.body.comentarios)) : [],
    };

    console.log('Received post:', post)

    Post.insert(post)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Atualizar um Post (U) */
router.put('/:id', function (req, res) {
    var post = {
        rua_id: req.body.rua_id,
        titulo: req.body.titulo,
        texto: req.body.texto,
        data: req.body.data
    };

    Post.update(req.params.id, post)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Adicionar um Comentário a um Post (U) */
router.put('/:id/comment', async function (req, res) {

    const nextCommentId = await Post.getNextCommentId();
    var comment = {
        _id: nextCommentId,
        post_id: req.body.post_id,
        user_id: req.body.user_id,
        comentario: req.body.comentario,
        data : req.body.data
    }
    console.log(comment)
    Post.addComment(req.params.id, comment)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Remover um Post (D) */
router.delete('/delete/:id', function (req, res) {
    Post.remove(req.params.id)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

router.delete('/delete/:id/comment/:idC', function (req, res) {
    Post.removeC(req.params.id, req.params.idC)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro))
})


module.exports = router;
