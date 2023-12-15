const { Client } = require('pg');
const fs = require("fs");
const http = require("http");
const host = 'localhost';
const port = 8080;
const server = http.createServer();

// Client pour la base de données
const client = new Client({
    //user: 'postgres',
    //password: 'root',
    database: 'photo', // Mettre le nom de votre base de données  !!
    port : 18568
});

//Connection à la base de données
client.connect()
.then(() => {
    console.log('Connected to database');
})
.catch((e) => {
    console.log('Error connecting to database');
    console.log(e);
});

server.on("request", async (req, res) => {
    if (req.url.startsWith('/public/')) {
        try {
            const ressource = fs.readFileSync("./" + req.url);
            res.end(ressource);
        } catch (error) {
            let html = '<html><body><h1>404 Error</h1>';
            html += '<p>Page not found</p>';
            html += '<a href="/">Retour à l\'accueil</a>';
            html += '</body></html>';
            res.statusCode = 404;
            res.end(html);
        } 
    } else if (req.url === '/mur-images') {
        try {
            const sqlQuery = 'SELECT fichier from photos'; //Requête SQL
            const sqlResult = await client.query(sqlQuery); //Exécution de la requête
            //sqlResult.rows  contient les lignes du résultat de la requête SQL
            //une ligne est un dictionnaire dont les clés sont les noms des colonnes
            //Ici on a donc {fichier: 'image1.jpg'} pour la première ligne  
            console.log(sqlResult.rows);

            //Grâce à la fonction map, on récupère un tableau contenant les valeurs de la colonne fichier
            const fichiersImage = sqlResult.rows.map(row => row.fichier);
            console.log(fichiersImage);
    
            //Si la requête est un succès, on renvoie la première ligne du résultat
            let pageHTML = "<!DOCTYPE html><html><body>";
            pageHTML += '<h1>Mur d\'images</h1>';
            pageHTML += '<div><a href="/public/image-description.html">Décrire une image</a></div>';
            for (let i = 0 ; i < fichiersImage.length ; i++) {
                const fichierSmallImage = fichiersImage[i].split('.')[0] + '_small.jpg';
                const img = '<img src="/public/'+fichierSmallImage+'" />';
                pageHTML += '<a href="/image/'+(i+1)+'" >' + img + '</a>';
            }
            pageHTML += "</body></html>";
            res.end(pageHTML);
        } catch (e) {
            console.log(e);
            //Si la requête échoue, on renvoie un message d'erreur
            res.end(e);
        }
        
    } else if (req.url.startsWith('/image/')) {
        const imgNumber = req.url.split('/')[2];
        let pageHTML = "<!DOCTYPE html><html><body>";
        pageHTML += '<h1>Image</h1>';
        pageHTML += '<img src="/public/image'+imgNumber+'.jpg" width="400" />';
        pageHTML += '</body></html>';
        res.end(pageHTML);
    } else {
        const index = fs.readFileSync("./public/index.html", "utf-8");
        res.end(index);
    }
})

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});
