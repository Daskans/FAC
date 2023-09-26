const fs = require("fs");
const express = require('express');
const { Client } = require('pg');

const host = 'localhost';
const port = 8080;

const app = express();


// Client pout la base de données
const client = new Client({
    database: 'photo', 
    port : 18568
});

// Connection à la base de données
client.connect()
.then(() => {
    console.log('Connected to database')
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
    res.redirect('/mur-images');
})

app.get('/mur-images', async (req,res) => {
    try {
        const sqlQuery = 'SELECT fichier FROM photos';
        const sqlResult = await client.query(sqlQuery);
        console.log(sqlResult.rows);

        const fichiersImage = sqlResult.rows.map(row => row.fichier);
        console.log(fichiersImage);

        res.render('mur', {title:"Mur d'image", images:fichiersImage, })
    }catch (e) {
        console.log(e);
        res.end(e);
    }
});
var commentaire = []
for (let i = 0 ; i<53; i++) {
    commentaire.push([])
}
app.get('/image/:num', async (req, res) => {
    let num = req.params.num;
    const sqlQuery = 'SELECT nom FROM photos WHERE id='+num+';';
    const sqlQueryPhotographe = 'SELECT photographes.nom, photographes.prenom FROM photographes JOIN photos ON photographes.id=photos.id_photographe WHERE photos.id='+num+';';
    const sqlResult = await client.query(sqlQuery)
    const sqlResultPhotographe = await client.query(sqlQueryPhotographe)
    //console.log(sqlResult.rows);
    //console.log(sqlResultPhotographe.rows);
    res.render('image', {nImage:num, nom:sqlResult.rows[0].nom, photographe:sqlResultPhotographe.rows[0].nom+' '+sqlResultPhotographe.rows[0].prenom, com:commentaire[num]})
    
});


app.post('/image/:num', async (req, res) => {
    let num = req.params.num;
    let donnees;;
    req.on("data", (dataChunk) => {
        donnees += dataChunk.toString();
    });
    req.on("end", () => {
        const paramValeur = donnees.split("=")[1];
        commentaire[num].push(paramValeur);
        
        console.log(commentaire[num]);
    });
})

// EJS
app.set('view engine', 'ejs');
app.set('views', './ejs-templates');

app.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});