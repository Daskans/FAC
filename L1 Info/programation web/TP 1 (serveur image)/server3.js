const fs = require("fs");
const http = require('http');
const host = 'localhost';
const port = 8080;
const server = http.createServer();

server.on('request',(req,res) => 
{
    if (req.url === '/image')
    {
        const images = fs.readFileSync("./images.html",'utf-8');
        res.end(images);
    }
    else if (req.url === '/formes')
    {
        const formes = fs.readFileSync("sujet/images/formes.png");
        res.end(formes);
    }
    else if (req.url === '/reponse')
    {
        const reponse = fs.readFileSync("sujet/images/sens_vie.png");
        res.end(reponse);
    }
    else if (req.url === '/tiger')
    {
        const tiger = fs.readFileSync("sujet/images/tiger.png");
        res.end(tiger);
    }
    else if (req.url === '/formes_small')
    {
        const formes = fs.readFileSync("sujet/images/formes_small.png");
        res.end(formes);
    }
    else if (req.url === '/reponse_small')
    {
        const reponse = fs.readFileSync("sujet/images/sens_vie_small.png");
        res.end(reponse);
    }
    else if (req.url === '/tiger_small')
    {
        const tiger = fs.readFileSync("sujet/images/tiger_small.png");
        res.end(tiger);
    }
    else
    {
        const indexPage = fs.readFileSync("./index.html",'utf-8');
        res.end(indexPage);
    }
});

server.listen(port, () => 
{
    console.log(`incroyable le serveur marche`)
});