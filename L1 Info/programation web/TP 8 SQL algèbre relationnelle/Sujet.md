# Semaine 8 : Base de données (SQL - Algèbre relationnelle - SQL dans le Serveur Web)

## Question de cours

Q1 : Supposons que R a 12 nuplets et S 4. Les deux relations ont des schémas distincts. Combien de nuplets sont dans leur produit cartésien ?

Q2 : La selection d'une relation R permet-elle d'obtenir une relation qui contient des doublons ?

## Base des images

On considère la base de données photo qui contient 4 tables.

Table Photographes :
* id du photographe (**clé**)
* nom du photographe
* prénom du photographe

Table Orientations :
* id de l'orientation (**clé**)
* orientation (portrait, paysage)

Table Photos : 
* id de la photo (**clé**)
* nom de la photo
* date de prise de vue
* orientation (**clé étrangère**)
* fichier
* likes
* id du photographe (**clé étrangère**)


Table des commentaires : 
* id du commentaire (**clé**)
* text
* id de la photo (**clé étrangère**)

## Algèbre relationnelle sur une table

Q3 : En algèbre relationnelle, écrivez la requête qui liste les orientations des photos.

Q4 : En algèbre relationnelle, écrivez la requête qui liste tous les id des photos de type portrait.

## Requêtes sur plusieurs tables

Q5 : En algèbre relationnelle, écrivez à l'aide d'une jointure la requête qui retourne tous les commentaires mis sur toutes les photos de type portrait.

Q6 : En algèbre relationnelle, écrivez à l'aide d'une jointure la requête qui retourne tous les commentaires mis sur toutes les photos d'un photographe donné.


## Conception et requêtes 

Nous proposons un code qui permet l'affichage du mur d'images en faisant appel à la base de données.
Il faut donc créer la base de données et la remplir avec les données du fichier `photo.sql`.

Dans le shell psql, exécuter la commande suivante pour exécuter le fichier `photo.sql`:

    \i photo.sql
    
Dans le shell linux ou windows, exécuter la commande suivante pour télécharger les bibliothèques JS nécessaires à notre TD:
    
    npm install


Vous pouvez maintenant exécuter le serveur web avec la commande suivante:

    node server.js


Q7 : Modifier le code du server.js pour que la requête qui liste les images ne choisisse que les photos orientées en mode portrait.

Q8 : Modifier le code du server.js pour que la page qui affiche une image (route '/image') affiche aussi les informations sur la photo (son titre et son photographe).

## Reprise du TD5 (Optionnel)

Reprenez le code du TD5 et intégrez une base de données.

