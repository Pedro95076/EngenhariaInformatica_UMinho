var http = require('http')
var url = require('url')
var axios = require('axios')
var fs = require('fs') // manipular ficheiros

http.createServer((req, res) => {
    console.log(req.method + " " + req.url);

    if (req.url == '/') {
        fs.readFile("web.html", (erro, dados) => {
            res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'})
            res.write(dados)
            res.end()
        })    
    } else if(req.url == '/w3.css') {
        fs.readFile('w3.css', (erro, dados) => {
            res.writeHead(200, {'Content-Type' : 'text/css'})
            res.write(dados)
            res.end()
        })
    } else {
        res.writeHead(400, {'Content-Type' : 'text/html; charset=utf-8'});
        res.write("<p>Erro: Pedido não suportado!</p>")
        res.write("<pre>" + req.url + "</pre>")
        res.end();
    }

}).listen(2702)