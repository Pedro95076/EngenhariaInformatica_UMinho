var createError = require('http-errors');
var express = require('express');
var path = require('path');
var logger = require('morgan');
var mongoose = require('mongoose');

var indexRouter = require('./routes/index');
var composerRouter = require('./routes/compositores');
var periodRouter = require('./routes/periodos');

var mongoDB = 'mongodb://127.0.0.1/tpc6'

mongoose.connect(mongoDB);

var db = mongoose.connection

db.on('error', console.error.bind(console, 'Erro na ligação à BD'))

db.once('open', () => {
  console.log("Conexão à BD realizada com sucesso!")
})

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/compositores', composerRouter);
app.use('/periodos', periodRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
