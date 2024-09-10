var http = require('http')
var url = require('url')
var fs = require('fs')

http.createServer(function (req, res) {
	var regex = /^c\d+$/
	var q = url.parse(req.url, true)
	var str = q.pathname.substring(1)
	if (str == "") {
		console.log("index")
		fs.readFile("./pages/index.html", function(err, data) {
			res.writeHead(200, {"Content-Type": "text/html"})
			res.write(data)
			res.end()
		})
	} else if (str == "w3.css") {
		console.log("css")
		fs.readFile("./pages/w3.css", function(err, data) {
			res.writeHead(200, {"Content-Type": "text/css"})
			res.write(data)
			res.end()
		})
	} else if (str == "custom.css") {
		console.log("css")
		fs.readFile("./pages/custom.css", function(err, data) {
			res.writeHead(200, {"Content-Type": "text/css"})
			res.write(data)
			res.end()
		})
	} else if (regex.test(str)) {
		console.log("cidade")
		fs.readFile("./pages/" + str + ".html", function(err, data) {
			res.writeHead(200, {"Content-Type": "text/html"})
			res.write(data)
			res.end()
		})
	} else {
		console.log("erro: " + str)
		res.writeHead(400, {"Content-Type": "text/html"})
		res.write("<p>Bad request</p>")
		res.write("<pre>" + str + " does not exist")
		res.end()
	}
}).listen(7777)
