\c postgres;
DROP DATABASE IF EXISTS photo;
CREATE DATABASE photo;

\c photo;

CREATE TABLE photographes (
  id SERIAL PRIMARY KEY,
  nom VARCHAR(50) NOT NULL,
  prenom VARCHAR(50) NOT NULL
);

CREATE TABLE orientations (
  id SERIAL PRIMARY KEY,
  nom VARCHAR(50) NOT NULL
);

CREATE TABLE photos (
  id SERIAL PRIMARY KEY,
  nom VARCHAR(50) NOT NULL,
  date DATE NOT NULL,
  orientation INTEGER NOT NULL REFERENCES orientations(id),
  fichier VARCHAR(100) NOT NULL,
  likes INTEGER NOT NULL DEFAULT 0,
  id_photographe INTEGER NOT NULL REFERENCES photographes(id)
);

CREATE TABLE commentaires (
  id SERIAL PRIMARY KEY,
  texte VARCHAR(200) NOT NULL,
  id_photo INTEGER NOT NULL REFERENCES photos(id)
);

INSERT INTO photographes (nom, prenom) VALUES ('Duchamp', 'Marcel');
INSERT INTO photographes (nom, prenom) VALUES ('Von Gloeden', 'Elisa');
INSERT INTO photographes (nom, prenom) VALUES ('Mapplethorpe', 'Gil');
INSERT INTO photographes (nom, prenom) VALUES ('Renoir', 'Pierre-Auguste');

SELECT * FROM photographes;

INSERT INTO orientations (nom) VALUES ('portrait');
INSERT INTO orientations (nom) VALUES ('paysage');

SELECT * FROM orientations;

INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Portrait bleu', '2000-01-01', 1, 'image1.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Marcheur', '2000-01-01', 1, 'image2.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Sol Rouge', '2000-01-01', 2, 'image3.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Bulles chaudes', '2010-01-01', 2, 'image4.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Nature morte', '1985-01-01', 2, 'image5.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Grotte vivante', '2000-01-01', 2, 'image6.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Travail Soir', '2000-01-01', 1, 'image7.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Citron salade', '2000-01-01', 1, 'image8.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Floue artistique', '2000-01-01', 1, 'image9.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Auto', '2000-01-01', 2, 'image10.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Feuilles violettes', '2000-01-01', 1, 'image11.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Ville Nuit', '2000-01-01', 1, 'image12.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Baignade', '1999-01-01', 2, 'image13.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Caverne Espoir', '2000-01-01', 1, 'image14.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Cerveau Cardiaque', '2000-01-01', 2, 'image15.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Rayons Luminieux', '2000-01-01', 2, 'image16.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Lunette Triangle', '2000-01-01', 1, 'image17.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Route Nuit', '2000-01-01', 1, 'image18.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Sapin Hall', '2000-01-01', 1, 'image19.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Vacances Ski', '2000-01-01', 1, 'image20.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Ocean Matin', '2000-01-01', 1, 'image21.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Escalator Panne', '1986-03-01', 1, 'image22.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Voiture Jaune', '2010-01-01', 2, 'image23.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Cascade', '2020-07-15', 1, 'image34.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Désert', '2021-05-20', 2, 'image35.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Architecture', '2021-01-15', 2, 'image36.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Feu d artifice', '2022-07-14', 1, 'image37.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Château', '2022-06-01', 2, 'image38.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Aurore Boréale', '2021-12-25', 1, 'image39.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Papillon', '2023-04-20', 2, 'image40.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Pluie de météores', '2023-08-12', 1, 'image41.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Vague géante', '2022-11-30', 2, 'image42.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Parc d automne', '2023-10-15', 1, 'image43.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Soleil levant', '2023-05-01', 2, 'image44.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Paysage de montagne', '2023-09-15', 1, 'image45.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Chaton', '2023-07-30', 2, 'image46.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Scène urbaine', '2023-04-10', 1, 'image47.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Champ de tournesols', '2023-08-25', 2, 'image48.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Pont la nuit', '2023-10-05', 1, 'image49.jpg', 2);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Forêt brumeuse', '2023-11-11', 2, 'image50.jpg', 3);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Espace', '2023-12-12', 1, 'image51.jpg', 4);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Rivière calme', '2024-01-18', 2, 'image52.jpg', 1);
INSERT INTO photos (nom, date, orientation, fichier, id_photographe) VALUES ('Tempête en mer', '2024-02-24', 1, 'image53.jpg', 2);



SELECT * FROM photos;

