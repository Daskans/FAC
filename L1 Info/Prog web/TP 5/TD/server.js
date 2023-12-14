const fs = require("fs");
const http = require("http");
const host = 'localhost';
const port = 8080;
const server = http.createServer();

const descriptions=[]
server.on("request", (req, res) => {
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
    else if (req.url==='/all-images')
    {
        let allImages = fs.readdirSync('./public/images')
        let smallImages = allImages.filter(i => i.endsWith('_small.jpg'));
        let imageWallHTML = "<!DOCTYPE html><html><body><a href='/image-description'>description</a><br>";
        for (let smallImage of smallImages) 
        {
            let largeImage = smallImage.replace('_small.jpg','.jpg');
            imageWallHTML += '<a href="/public/images/'+largeImage+'"><img src="/public/images/'+smallImage+'"></a>';
        }
        imageWallHTML += '</body></html>';
        res.end(imageWallHTML);
    }
    else if (req.url==='/images/')
    {
        //const img=fs.
    }
    else if (req.url==="/image-description")
    {
        const imgDes=fs.readFileSync("./public/image-description.html","utf-8");
        res.end(imgDes);    
    }
    else if (req.method === 'GET' && req.url.startsWith ('/public/')) 
    {
        try 
        {
            const fichier = fs . readFileSync ( '.'+ req.url ) ;
            res.end (fichier) ;
        } 
        catch (err) 
        {
            console.log (err) ;
            res.end ( "erreur ressource" ) ;
        }
    } 
    else if (req.method === "POST" && req.url === "/image-description" ) 
    {
        let donnees ;;
        req . on ( "data" , ( dataChunk ) => 
        {
            donnees += dataChunk . toString () ;
        }) ;
        req.on("end",() => 
        {
            const paramValeur = donnees.split("&") ;
            const imageNumber = paramValeur[0].split("=")[1];
            const description = paramValeur[1].split("=")[1];
            descriptions[imageNumber]=description;
            res.statusCode=200;
            res.end(descriptions.toString());
        }) ;
    }
    else if (req.url==="/index")
    {
        const index=fs.readFileSync("./public/index.html","ascii");
        res.end(index);
    }
    else 
    {
        res.end ("erreur, je n'ai pas de if vers "+req.url) ;
    }
})

server.listen(port, host, () => 
{
    console.log(`Server running at http://${host}:${port}/`);
});