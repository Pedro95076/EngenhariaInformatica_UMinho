var express = require('express');
var router = express.Router();

/* GET users */
router.get('/', function(req, res, next) {
    res.send('resource')
});

module.exports = router;
