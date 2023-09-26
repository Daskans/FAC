# Semaine 5 : HTTP - GET et POST

On souhaite continuer l'application web du td4.

L'objectif est de permettre à l'utilisateur d'ajouter des commentaires sur les images.

L'objectif optionnel est d'ajouter des likes sur les images.

## Exercice 1 - Formulaire de commentaires

### Question 1

Créer une nouvelle page web (**image-description.html**) qui soit accessible statiquement et qui contienne un formulaire HTML permettant de saisir un commentaire sur une image.
Le formulaire doit contenir les champs suivants:

- un champ pour saisir le numéro de l'image à commenter
- un champ de saisie de texte pour le commentaire
- un bouton de validation.

La soumission du commentaire doit être effectuée en utilisant la méthode HTTP POST.

L'URL cible du commentaire doit être **/image-description**.

Faites en sorte que la page web **image-description.html** soit accessible via un lien hypertexte dans le mur d'images (en haut, avant les images).

### Question 2

Ajouter une nouvelle route dans le serveur web pour traiter les requêtes POST sur l'URL **/image-description**. Cette route doit récupérer les valeurs saisies dans le formulaire et les afficher dans la console du serveur web (utiliser la fonction JS **console.log()**).

Elle doit aussi ajouter le commentaire dans un tableau de commentaires dans le serveur web.

Enfin, elle doit renvoyer une page dynamique indiquant que le commentaire a bien été ajouté.

### Question 3

La dernière question du TD4 demande la génération dynamique des pages permettant d'afficher les images en grand. Modifiez cette génération dynamique pour que les commentaires soient affichés sous l'image de cette page.

## Exercice 2 - Lien pour ajouter un like (Optionnel)

1. Modifiez le mur d'images pour qu'il affiche une icône de pouce vers le haut (*like*) pour chaque image avec un nombre à côté qui indique combien de fois le pouce a été cliqué.

2. Faites en sorte qu'un clic sur le pouce envoie une requête GET vers l'URL http://localhost:8080/j-aime/i (le *i* à la fin de l'URL doit correspondre au numéro de l'image).

3. Ajoutez une route à votre serveur pour traiter les requêtes */j-aime/i*. Votre serveur devra incrémenter le compteur de *like* pour l'image i et retourner le mur d'images mis à jour.
