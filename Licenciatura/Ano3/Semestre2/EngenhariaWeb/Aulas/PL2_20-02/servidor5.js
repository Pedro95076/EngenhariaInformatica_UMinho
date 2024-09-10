var http = require('http')
var url = require('url')
var axios = require('axios') // fazer chamada à api

//Criar o servidor
http.createServer((req,res) => {

    console.log(req.method + " " + req.url ); 

    var q = url.parse(req.url, true);

    res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'})
    
    if(q.pathname == "/cidades"){
        axios.get("http://localhost:4000/cidades") // Para isto funcionar, fazer: $ json-server --watch --port 4000 mapa-virtual.json
            .then((resp) => {
                var data = resp.data

                res.write("<ul>")
                for(i in data){
                    res.write("<li> <a href='" + data[i].nome + "'>" + data[i].nome + "</a></li>")
                }
                res.write("</ul>")
                res.end()
            })
            .catch((erro) =>{
                console.log("Erro: " + erro);
                res.write("<p>" + erro + "</p>")
            })
    } else if (req.url.match(/\/cidades\/c|d+/)){
        let id = req.url.substring(9)
        axios.get("http://localhost:4000/cidades/" + id)
        .then((resp) => {
            var data = resp.data
            res.write("<h1>" + data.nome + "</h1>")
            res.write("<h3>" + data.distrito + "</h3>")
            res.write("<b>População:</b> " + data["população"])
            res.write("<br>")
            res.write(data["descrição"])
            res.write("<h6><a href = ' /cidades'>Voltar</a></h6>")

            res.end()
        })
        .catch((erro) => {
            console.log("Erro: " + erro);
            res.write("<p>" + erro + "</p>")
        })
    } else {
        res.write("Operação não suportada")
    }

    //res.end('Hello World\n')
}).listen(2002)

console.log("Servidor à escuta na porta 2002...");
