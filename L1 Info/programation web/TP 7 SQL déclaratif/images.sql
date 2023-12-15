
--DROP DATABASE IF EXISTS images;
--CREATE DATABASE images;

--DROP ALL TABLES
DROP TABLE IF EXISTS images;
DROP TABLE IF EXISTS commentaires;
DROP TABLE IF EXISTS photographes;


--CREATE ALL TABLES
CREATE TABLE images (
    id SERIAL PRIMARY KEY NOT NULL,
    type_image VARCHAR(30),
    nom_fichier VARCHAR(100),
    date DATE,
    largeur INT,
    longueur INT,
    likes INT,
    id_photographe INT
);

CREATE TABLE commentaires (
    id SERIAL PRIMARY KEY NOT NULL,
    commentaire VARCHAR(240),
    id_image INT
);

CREATE TABLE photographes (
    id SERIAL PRIMARY KEY NOT NULL,
    nom VARCHAR(100),
    prenom VARCHAR(100)
);

-- INSERT ALL DATA
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('portrait', 'image1.jpg', '20064-10-30', 2015, 4521, 10, 1);
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('art', 'image4.jpg', '2015-07-20', 5126, 5126, 2, 5);
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('paysage', 'image6.jpg', '2006-03-26', 3165, 2196, 85, 4);
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('portrait', 'image10.jpg', '2010-12-26', 3152, 4091, 30, 3);
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('paysage', 'image12.jpg', '2001-11-09', 7625, 3458, 25, 2);
INSERT INTO images ( type_image, nom_fichier, date, largeur, longueur, likes, id_photographe) VALUES ('portrait', 'image13.jpg', '20020-04-22', 6519, 3264, 36, 1);


INSERT into commentaires (commentaire, id_image) VALUES ('nul', 2);
INSERT into commentaires (commentaire, id_image) VALUES ('incroyable', 2);
INSERT into commentaires (commentaire, id_image) VALUES ('inimaginable', 3);
INSERT into commentaires (commentaire, id_image) VALUES ('amogus', 1);
INSERT into commentaires (commentaire, id_image) VALUES ('hey guys did you know that', 4);
INSERT into commentaires (commentaire, id_image) VALUES ('sublime', 2);
INSERT into commentaires (commentaire, id_image) VALUES ('splendide', 6);
INSERT into commentaires (commentaire, id_image) VALUES ('pourrie', 5);
INSERT into commentaires (commentaire, id_image) VALUES ('excellent', 5);
INSERT into commentaires (commentaire, id_image) VALUES ('légendaire', 3);
INSERT into commentaires (commentaire, id_image) VALUES ('can I put m-', 4);
INSERT into commentaires (commentaire, id_image) VALUES ('E', 4);

INSERT INTO photographes (nom, prenom) VALUES ('ROUSSEL', 'Jean-Michel');
INSERT INTO photographes (nom, prenom) VALUES ('DUPONT', 'Louise');
INSERT INTO photographes (nom, prenom) VALUES ('LEGRAND', 'Alexandre');
INSERT INTO photographes (nom, prenom) VALUES ('DUPOND', 'Louise');
INSERT INTO photographes (nom, prenom) VALUES ('PERVANCHE', 'Sabine');


