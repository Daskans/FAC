const fs = require("fs");
const http = require("http");
const host = 'localhost';
const port = 8080;
const server = http.createServer();

server.on('request', ( req,res ) => 
{
    if (req.url.startsWith('/images/')) 
    {
        try 
        {
            const image = fs.readFileSync ('.'+req.url);
            res.end(image);
        } 
        catch(err) 
        {
            console.log(err);
            res.end('erreur ressource inconnue');
        }
    } 
    else 
    {
        res.end ("erreur URL invalide") ;
    }
}) ;

server.listen(port, host, () =>    
{
    console.log(`Server running at http://${host}:${port}/`);
});