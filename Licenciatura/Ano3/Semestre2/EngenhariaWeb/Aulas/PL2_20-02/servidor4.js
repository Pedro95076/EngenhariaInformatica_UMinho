var http = require('http')
var url = require('url')
var meta = require('./aux') // ./ --> diretoria atual

//Criar o servidor
http.createServer((req,res) => {
    console.log(req.method + " " + req.url );  // Para imprimir na consola que metodos são chamados, etc.

    res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'})
    
    // Pega no url de uma quest
    var q = url.parse(req.url, true)
 
    if(q.pathname == "/add") {
        var n1 = parseInt(q.query, 10)
        var n2 = parseInt(q.query, 10)
        var soma = n1 + n2
        res.write("<pre>" 
            + n1
            + "+"
            + n2
            + "="
            + soma
        )
    } else if(q.pathname == "/sub"){
        var n1 = parseInt(q.query, 10)
        var n2 = parseInt(q.query, 10)
        var sub = n1 - n2
        res.write("<pre>" 
            + n1
            + "-"
            + n2
            + "="
            + sub
        )
    } else {
        res.write("Operação não suportada")
    }

    res.end()
}).listen(2002)

console.log("Servidor à escuta na porta 2002...");