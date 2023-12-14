-- QUERY
SELECT * FROM images;
SELECT * FROM commentaires;
SELECT * FROM photographes;

SELECT type, nom_fichier, nom, prenom FROM images JOIN photographes ON id_photographe=photographes.id;