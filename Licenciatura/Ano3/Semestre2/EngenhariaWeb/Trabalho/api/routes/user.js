var express = require('express');
var router = express.Router();
var jwt = require('jsonwebtoken');
var passport = require('passport');
var userModel = require('../models/user');
var auth = require('../auth/auth');
var multer = require('multer');

var upload = multer();

var User = require('../controllers/user');

router.get('/', function(req, res) {
  User.list()
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
});

router.get('/:id', auth.verificaAcesso,function(req, res) {
  User.getUser(req.params.id)
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
});

router.post('/', auth.verificaAcesso, upload.none(), function(req, res) {
  User.addUser(req.body)
    .then(dados => res.status(201).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
});

router.post('/register', upload.none(), function(req, res) {
  console.log('Request body:', req.body);
  var d = new Date().toISOString().substring(0, 19);

  var newUser = new userModel({
    username: req.body.username,
    name: req.body.name,
    email: req.body.email,
    filiacao: req.body.filiacao,
    level: req.body.level,
    dateCreated: d,
    dateLastAccess: d,
  });

  userModel.register(newUser, req.body.password, function(err, user) {
    if (err) {
      console.log('Register error:', err);
      return res.status(500).jsonp({ error: err.message });
    } else {
      console.log('User registered:', user);
      res.status(201).jsonp({ message: 'User registered successfully', user: user });
    }
  });
});
  
router.post('/login', upload.none(), function(req, res, next) {
  passport.authenticate('local', function(err, user, info) {
    if (err) {
      console.log('Authentication error:', err);
      return res.status(500).jsonp({ error: err });
    }
    if (!user) {
      console.log('Authentication failed:', info);
      return res.status(401).jsonp({ error: 'Authentication failed' });
    }
    req.logIn(user, function(err) {
      if (err) {
        console.log('Login error:', err);
        return res.status(500).jsonp({ error: err });
      }
      jwt.sign({
          username: user.username,
          level: user.level,
          sub: user._id // Setting the subject to the user's ID
        },
        "EngWeb2024", {
          expiresIn: 3600
        },
        function(e, token) {
          if (e) {
            console.log('Token generation error:', e);
            return res.status(500).jsonp({ error: "Erro na geração do token: " + e });
          } else {
            return res.status(201).jsonp({ token: token });
          }
        }
      );
    });
  })(req, res, next);
});

router.put('/:id', auth.verificaAcesso, upload.none(), function(req, res) {

  var newUser = new userModel({
    username: req.body.username,
    name: req.body.name,
    email: req.body.email,
    filiacao: req.body.filiacao
  });
  User.updateUser(req.params.id, newUser)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
});

router.put('/:id/desativar', auth.verificaAcesso, upload.none(), function(req, res) {
  User.updateUserStatus(req.params.id, false)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
});

router.put('/:id/ativar', auth.verificaAcesso, upload.none(), function(req, res) {
  User.updateUserStatus(req.params.id, true)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
});

router.put('/:id/password', auth.verificaAcesso, upload.none(), function(req, res) {
  User.updateUserPassword(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
});

router.delete('/:id', auth.verificaAcesso, upload.none(), function(req, res) {
  User.deleteUser(req.params.id)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na remoção do utilizador"})
    })
});

module.exports = router;
