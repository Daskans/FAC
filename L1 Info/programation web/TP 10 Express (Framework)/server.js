const fs = require("fs");
const express = require('express');
const { Client } = require('pg');

const host = 'localhost';
const port = 8080;

const app = express();

// Client pour la base de données
const client = new Client({
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

// Les ROUTES

// Route statique 
// le premier paramètre est le chemin de la route
// le deuxième paramètre est le chemin du répertoire
app.use('/public', express.static('./public'));

app.get('/', (req, res) => {
    res.redirect('/index');
});


app.get('/index', (req, res) => {
    res.redirect('/public/index.html');
});

app.get('/index.html', (req, res) => {
    res.redirect('/public/index.html');
});

app.get('/mur-images', async (req, res) => {
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
        

        res.render('mur', {title:"Mur d'image", images:fichiersImage})
    }catch (e) {
        console.log(e);
        //Si la requête échoue, on renvoie un message d'erreur
        res.end(e);
    }
});



app.get('/image/:num', (req, res) => {
    let num = req.params.num;
    res.render('image', {nImage:num})
})

app.get('/path-with-parameter/:num', (req, res) => {
    let num = req.params.num;
    let html = `<!DOCTYPE html>`;
    html += `<html>`;
    html += `<head>`;
    html += `<title>Parameter</title>`;
    html += `</head>`;
    html += `<body>`;
    html += `<h1>Parameter</h1>`;
    html += `<p>Parameter is ${num}</p>`;    
    html += `</body>`;
    html += `</html>`;
    res.send(html);
});


// EJS 
app.set('view engine', 'ejs');
app.set ('views', './ejs-templates');

app.get('/ejs-test', (req, res) => {
  res.render('test', {name: 'slim'});
});

app.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});
