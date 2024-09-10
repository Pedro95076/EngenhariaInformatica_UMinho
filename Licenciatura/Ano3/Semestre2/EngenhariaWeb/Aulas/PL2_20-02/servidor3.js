var http = require('http')
var url = require('url')
var meta = require('./aux') // ./ --> diretoria atual

//Criar o servidor
http.createServer((req,res) => {
    console.log(req.method + " " + req.url );  // Para imprimir na consola que metodos são chamados, etc.

    res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'})
    
    // Pega no url de uma quest
    var q1 = url.parse(req.url, true)
    res.write("True: <pre>" + JSON.stringify(q1) + "</pre>")

    var q2 = url.parse(req.url, false)
    res.write("False: <pre>" + JSON.stringify(q2) + "</pre>")
    
    res.end()
}).listen(2002)

console.log("Servidor à escuta na porta 2002...");