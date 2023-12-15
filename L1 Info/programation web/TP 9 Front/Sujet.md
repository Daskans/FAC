# Semaine 9 : Front 

On souhait continuer l'exercice du TD8 en y ajoutant un script JS qui permet de modifier l'affichage.

## Installation

Nous proposons un code qui permet l'affichage du mur d'images en faisant appel à la base de données.
Il faut donc créer la base de données et la remplir avec les données du fichier `photo.sql`.

Dans le **shell psql**, exécuter la commande suivante pour exécuter le fichier `photo.sql`:

    \i photo.sql
    
Dans le **shell linux ou windows**, exécuter la commande suivante pour télécharger les bibliothèques JS nécessaires à notre TD:
    
    npm install


Vous pouvez maintenant exécuter le serveur web avec la commande suivante (**shell linux ou windows**):

    node server.js

## JS dans la console du navigateur

Ouvrez la console JS dans les outils du développeur.  

Q1 : Quel élément du DOM la variable titrePage référence-t-elle quand vous exécutez la commande suivante ?

    titrePage = document.querySelector('h1')


Q2 : Que ce passe-t-il dans la page web quand vous tapez la commande suivante ?

    titrePage.textContent = "Super Mur"

Q3 : Que ce passe-t-il dans la page web quand vous tapez la commande suivante ?

    titrePage.style.color = 'red'

Q4 : Tapez la commande permettant de centrer le titre.

Q5 : Quels éléments du DOM la variable images référence-t-elle quand vous exécutez la commande suivante ? 

    images = document.querySelectorAll('img')

Q6 : Que ce passe-t-il dans la page web quand vous tapez la commande suivante ?

    images[0].style.border = 'solid 2px red'

Q7 : Que ce passe-t-il dans la page web quand vous tapez la commande suivante ?

    images[0].style.border = 'none'

Q8 : Que ce passe-t-il dans la page web quand vous tapez la commande suivante ?

    images.forEach((image) => image.style.border = 'yellow 2px solid')

Q9 : Tapez la commande permettant de changer le display de toutes les images (soit en **inline** soit en **block**).

Q10 : Quel élément du DOM la variable bouton référence-t-elle quand vous exécutez la commande suivante ?

    bouton = document.querySelector('button')

Q11 : Que ce passe-t-il quand vous tapez la commande suivante ?

    bouton.addEventListener('click', () => console.log('click'))

Q12 : Tapez la commande permettant de changer le display de toutes les images (soit en **inline** soit en **block**) quand on clique sur le bouton.

Q13 : Que ce passe-t-il quand vous tapez la commande suivante ?

    window.addEventListener("scroll",() => console.log('scroll'))

Q14 : Que ce passe-t-il quand vous tapez les commandes suivantes ?

    murImages = document.getElementById('mur-images')
    nouvelleImage = document.createElement('img')
    nouvelleImage.src = 'public/image16_small.jpg'
    murImages.appendChild(nouvelleImage)

Q15 : Tapez la commande permettant de rajouter une image dans le mur quand on scroll.
    
## Ajout d'un script JS dans la page web

Le script **mur.js** qui se trouve dans le dossier **public** est déjà lié à la page web du mur d'images.

Q16 : Ajoutez dans ce script les commandes permettant de faire en sorte qu'un click sur le boutton change le layout de la page (soit en **inline** soit en **block** pour les photos).

Q17 : Ajoutez dans ce script les commandes permettant de faire en sorte qu'un scroll ajoute une nouvelle photo.
Vous pouvez modifiez **server.js** pour que la page n'affiche que 5 photos au départ.