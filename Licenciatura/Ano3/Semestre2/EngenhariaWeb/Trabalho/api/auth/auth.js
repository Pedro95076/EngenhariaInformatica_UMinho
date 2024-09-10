var jwt = require('jsonwebtoken')

module.exports.verificaAcesso = function (req, res, next){
    var myToken = req.query.token || req.body.token || req.headers['authorization'];
    if(myToken){
      jwt.verify(myToken, "EngWeb2024", function(e, payload){
        if(e){
          res.status(401).jsonp({error: e})
        }
        else{
          next()
        }
      })
    }
    else{
      res.status(401).jsonp({error: "Token inexistente!"})
    }
  }

  module.exports.verificaMesmoUser = function(req, res, next) {
    var myToken = req.query.token || req.body.token || req.headers['authorization'];
    if (myToken) {
      if (myToken.startsWith('Bearer ')) {
        myToken = myToken.slice(7, myToken.length);
      }
      jwt.verify(myToken, "EngWeb2024", function(e, payload) {
        if (e) {
          res.status(401).jsonp({ error: e });
        } else {
          console.log(payload.sub)
          console.log(req.params.id)
          if (payload.sub === req.params.id || payload.level === 'admin') {
            req.user = payload;
            next();
          } else {
            res.status(403).jsonp({ error: "Access denied" });
          }
        }
      });
    } else {
      res.status(401).jsonp({ error: "Token inexistente!" });
    }
  };
