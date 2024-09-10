var http = require('http')
var meta = require('./aux') // ./ --> diretoria atual

//Criar o servidor
http.createServer((req,res) => {
    console.log(req.method + " " + req.url );  // Para imprimir na consola que metodos são chamados, etc.

    res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'})
    res.write("<h1>Uma página Web </h1>")
    res.write("<p>Página criada com node.js por "
    + meta.myName()
    + " em "
    + meta.myDateTime()
    + " na turma "
    + meta.turma
    )
    
    res.end()
}).listen(2002)

console.log("Servidor à escuta na porta 2002...");