export PGHOST=/tmp/$LOGNAME
export PGPORT=$UID

psql -d postgres

#CREATE DATABASE images;
#CREATE TABLE images (id INT PRIMARY KEY NOT NULL, type VARCHAR(30), nom_fichier VARCHAR(100), date DATE, largeur INT, longueur INT, likes INT, id_photographe INT);
