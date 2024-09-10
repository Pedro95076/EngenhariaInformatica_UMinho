const jwt = require('jsonwebtoken');

module.exports.verificaAcesso = function (niveisPermitidos) {
  return function (req, res, next) {
    const myToken = req.cookies.token;
    console.log('Received token:', myToken);
    
    if (myToken) {
      jwt.verify(myToken, "EngWeb2024", (err, payload) => {
        if (err) {
          console.log('Token verification error:', err.message);
          return res.status(401).render('login');
        } else {
          req.user = payload;
          console.log('Token payload:', payload);
          console.log(req.user.level)

          // Verifique se os níveis permitidos incluem o nível do usuário
          if (!niveisPermitidos || niveisPermitidos.includes(req.user.level)) {
            return next();
          } else {
            return res.status(401).render('error', { message: "Acesso restrito" });
          }
        }
      });
    } else {
      return res.status(401).render('login');
    }
  };
};
