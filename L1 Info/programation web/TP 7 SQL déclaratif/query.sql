--images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe)
--commentaires (commentaire, id_image)
--photographes (nom, prenom)

-- AFFICHE ALL
    --SELECT * FROM images;
    --SELECT * FROM commentaires;
    --SELECT * FROM photographes;

/*Q1 : Ecrivez la requête SQL pour lister toutes les photos.*/
--SELECT * FROM images;

/*Q2 : Ecrivez la requête SQL pour lister toutes les photos de type_image portrait.*/
--SELECT nom_fichier, type_image FROM images WHERE type_image='portrait';

/*Q3 : Ecrivez la requête SQL pour lister tous les commentaires d'une photo.*/
--SELECT nom_fichier, commentaire FROM images JOIN commentaires ON images.id=id_image ORDER BY id_image;

/*Q4 : Ecrivez la requête SQL pour lister toutes les photo dont la largueur est au moins égale à 600 et dont la hauteur est au moins égale à 400.*/
--SELECT nom_fichier, largeur, longueur FROM images WHERE largeur >= 600 AND longueur >= 400;

/*Q5 : Ecrivez la requête SQL qui retourne toutes les photos de type_image portrait qui ont plus de 10 likes*/
--SELECT type_image, nom_fichier, likes FROM images WHERE type_image='portrait' AND likes > 10;

/*Q6 : Ecrivez la requête SQL qui retourne tous les commentaires mis sur toutes les photos de type portrait.*/
--SELECT commentaire, nom_fichier, type_image FROM commentaires JOIN images ON id_image=images.id WHERE type_image='portrait' ORDER BY id_image;

/*Q7 : Ecrivez la requête SQL qui retourne tous les commentaires mis sur toutes les photos d'un photographe donné.*/
--SELECT commentaire FROM commentaires JOIN images JOIN photographes ON id_photographe=photographes.id ON id_image=images.id WHERE nom='ROUSSEL' AND prenom='Jean-Michel';

/*Q8 : Ecrivez la requête SQL qui retourne les photos sur lesquelles il n'y a pas de commentaires.*/
--SELECT nom_fichier FROM images JOIN commentaires ON images.id=id_image WHERE commentaires=NULL;

/*Q9 : Ecrivez la requête SQL qui retourne la photo avec le plus de likes.*/
--SELECT MAX(likes) FROM images;

/*Q11 : Construisez la ou les tables permettant de mettre en oeuvre ces concepts.*/
