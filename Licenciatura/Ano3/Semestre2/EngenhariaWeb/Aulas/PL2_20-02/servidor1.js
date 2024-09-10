var http = require('http')

//Criar o servidor
http.createServer((req,res) => {
    // Tudo o que envio para a pag web é pelo res
    // Para receber é pelo req

    res.writeHead(200, {'Content-Type' : 'text/plain'})
    // res.end é tipo um flush, quando pomos isso, ele envia
    res.end('Hello World\n')
}).listen(2002) // A porta do servidor

console.log("Servidor à escuta na porta 2002...");