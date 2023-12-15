# Semaine 10 : Express 

Ce TP introduit les bases du framework Express.
Une lecture approfondie de la documentation est nécessaire pour aller plus loin.

## Installation

Dans le **shell psql**, exécuter la commande suivante pour exécuter le fichier `photo.sql`:

    \i photo.sql
    
Dans le **shell linux ou windows**, exécuter la commande suivante pour télécharger les bibliothèques JS nécessaires à notre TD:
    
    npm install


Vous pouvez maintenant exécuter le serveur web avec la commande suivante (**shell linux ou windows**):

    node server.js

## 2 erreurs (mode statique et page d'accueil)

Q1 : Le serveur web ne fonctionne pas. Trouvez la ligne qui permet de configurer la page retournée lorsqu'on ouvre la page http://localhost:8080 et corrigez la.

Q2 : Le serveur web ne fonctionne pas. Trouvez la ligne qui permet de configurer le répertoire du mode statique et corrigez l'erreur.


## Route de la page affichant une photo

serveur.js contient une route qui permet d'afficher le mur d'image et une route de test qui illustre la façon d'intégrer un paramètre dans le chemin de l'URL .

Q3 : Ajouter la route permettant d'afficher une photo. Cette route doit prendre en paramètre l'identifiant de la photo et retourner la page qui affiche la photo correspondante.


## EJS 

serveur.js contient une route '/ejs-test' qui présente l'utilisation des template EJS.
Le template **test** se trouve dans le répertoire **ejs-templates** (fichier **test.ejs**).
La fonction **render** permet d'appeler la génération du template en passant des paramètres.

Q4 : Changer la route du mur d'image pour qu'elle utilise le template **mur** et qu'elle passe en paramètre le titre de la page et la liste des fichiers images.

Q5 : Changer la route de la page affichant une photo pour qu'elle utilise le template **image**.

