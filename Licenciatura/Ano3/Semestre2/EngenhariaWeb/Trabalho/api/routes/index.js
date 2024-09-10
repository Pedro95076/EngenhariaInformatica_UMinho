var express = require('express');
var router = express.Router();

// Define your routes here
router.get('/', function(req, res, next) {
  res.send('Welcome to the API');
});

module.exports = router;

