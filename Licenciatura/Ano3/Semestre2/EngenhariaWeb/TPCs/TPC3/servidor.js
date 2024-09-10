var http = require('http');
var axios = require('axios');
var fs = require('fs');




http.createServer((req, res) => {
    // Write in the terminal the method and the url
    console.log(req.method + " " + req.url);

    if (req.url == '/films') {
        axios.get("http://localhost:3000/films?_sort=title") // No need for query parameters here
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Films list</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`
                let data=resp.data

                res.write(header);
                res.write("<h1>Films List</h1>")
                res.write("<p>Click on the film you want to know more about.</p>")
                res.write('<ul class="custom-list">')
                data.forEach(element => {
                    res.write('<li><a href="films/' + element.id + '">' + element.title + '</a></li>');
                });
                res.write('</ul>')

                res.end();
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
    
    } else if (req.url == '/style.css') {
        fs.readFile("style.css", (error, data) => {
            if (error) {
                res.writeHead(404, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Not Found</h1>");
            } else {
                res.writeHead(200, { 'Content-Type': 'text/css' })
                res.write(data)
                res.end()
            }
        })
    }else if(req.url.match(/\/films\/.*/)){
        let id=req.url.substring(7);
        axios.get("http://localhost:3000/films?id="+id+"")
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let data=resp.data
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Film Page</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`
    
                res.write(header);
    
                // Arrays para armazenar todas as promessas do Axios
                let axiosPromises_cast = [];
                let axiosPromises_genres = [];
    
                data.forEach(element => {
                    res.write("<h1>"+element.title+"</h1>")
                    res.write("<p><b>Id: </b>"+element.id+"</p>")
                    res.write("<p><b>Year: </b>"+element.year+"</p>")
    
                    element.cast.forEach(actor_id => {
                        // Armazena a promessa do Axios em um array
                        axiosPromises_cast.push(axios.get(`http://localhost:3000/cast?id=${actor_id}`));
                    });
    
                    element.genres.forEach(genre_id => {
                        // Armazena a promessa do Axios em um array
                        axiosPromises_genres.push(axios.get(`http://localhost:3000/genres?id=${genre_id}`));
                    });
                })
    
                // Aguarda todas as promessas do Axios para o elenco serem resolvidas
                Promise.all(axiosPromises_cast)
                    .then(responses => {
                        res.write("<p><b>Cast: </b></p>")
                        res.write('<ul class="without_underlines li a">');

                        responses.forEach(resp2 => {
                            let data2=resp2.data
                            data2.forEach(element2 => {
                                res.write('<li><a href="/cast/' + element2.id + '">' + element2.actor+ '</a></li>');
                            });
                            
                        });
                        res.write("</ul>")
                        // Aguarda todas as promessas do Axios para os gêneros serem resolvidas
                        return Promise.all(axiosPromises_genres);
                    })
                    .then(responses => {
                        res.write("<p><b>Genres: </b></p>")
                        res.write('<ul class="without_underlines li a">');
                        responses.forEach(resp2 => {
                            let data2=resp2.data
                            data2.forEach(element2 => {
                                res.write('<li><a href="/genres/' + element2.id + '">' + element2.genre+ '</a></li>');
                            });
                        });
                        res.write("</ul>")
                        res.write('<button onclick="window.location.href=\'/films\'">Back</button>');
                        res.end('</body></html>');
                    })
                    .catch(error => {
                        console.error(error)
                        res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                        res.end("<h1>Internal Server Error</h1>")
                    });
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
        
    }else if(req.url == '/genres'){
        axios.get("http://localhost:3000/genres?_sort=genre") // No need for query parameters here
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Genres list</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`
                let data=resp.data

                res.write(header);
                res.write("<h1>Genres List</h1>")
                res.write("<p>Click on the genre you want to know more about.</p>")
                res.write('<ul class="custom-list">')
                data.forEach(element => {
                    res.write('<li><a href="genres/' + element.id + '">' + element.genre + '</a></li>');
                });
                res.write('</ul>')

                res.end();
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
    
    }else if(req.url.match(/\/genres\/.*/)){
        let id=req.url.substring(8);
        axios.get("http://localhost:3000/genres?id="+id+"")
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let data=resp.data
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Genre Page</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`

                data.forEach(element => {
                    res.write("<h1>"+element.genre+"</h1>")
                    res.write('<button onclick="window.location.href=\'/genres\'">Back</button>');
                })

                res.end();
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
    
    }else if(req.url == '/cast'){
        axios.get("http://localhost:3000/cast?_sort=actor") // No need for query parameters here
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Actors list</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`
                let data=resp.data

                res.write(header);
                res.write("<h1>Cast</h1>")
                res.write("<p>Click on the actor you want to know more about.</p>")
                res.write('<ul class="custom-list">')
                data.forEach(element => {
                    res.write('<li><a href="cast/' + element.id + '">' + element.actor + '</a></li>');
                });
                res.write('</ul>')

                res.end();
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
    
    }else if(req.url.match(/\/cast\/.*/)){
        let id=req.url.substring(6);
        axios.get("http://localhost:3000/cast?id="+id+"")
            .then(resp => {
                res.writeHead(200, { 'Content-Type': 'text/html;charset=utf-8' });
                let data=resp.data
                let header = `<!DOCTYPE html>
                    <html>
                        <head>
                            <meta charset="utf-8"/>
                            <title>Actor Page</title>
                            <link rel="stylesheet" href="/style.css"/>
                        </head>
                        <body>`

                data.forEach(element => {
                    res.write("<h1>"+element.actor+"</h1>")
                    res.write('<button onclick="window.location.href=\'/cast\'">Back</button>');
                })

                res.end();
            })
            .catch(error => {
                console.error(error)
                res.writeHead(500, { 'Content-Type': 'text/html;charset=utf-8' })
                res.end("<h1>Internal Server Error</h1>")
            });
        

    } else {
        res.writeHead(404, { 'Content-Type': 'text/html;charset=utf-8' })
        res.end("<h1>Not Found</h1>");
    }
}).listen(8080)

console.log('Server running at http://localhost:8080/')
