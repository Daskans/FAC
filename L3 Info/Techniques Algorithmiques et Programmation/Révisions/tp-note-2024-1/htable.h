#ifndef __HTABLE_H__
#define __HTABLE_H__

//////////////////////////////////////////////////////////////////////
//
// Table de hachage dynamique pour des entrées (key,value) de type
// (int,void*). Les opérations autorisées sont:
//
// - ht_create/ht_free: créer ou détruire une table de hachage
// - ht_write: T[key] = value, ajouter (key,value) à la table T
// - ht_read: return T[key], lire dans T la value correspondant à key
// - ht_reset: supprime toutes les entrées de T, sans détruire T
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// Aspects techniques.
//
// La taille de la table est de la forme 2^k, avec k entier > 0. Pour
// distribuer key sur une entrée de la table, disons h, on utilise le
// hash de Fibonacci, les k bits de poids forts d'une grande
// multiplication: h = (key * HT_MAGIC) >> (64-k) où HT_MAGIC est un
// entier sur 64 bits lié au nombre d'or (voir plus loin). La gestion
// des collisions se fait par un adressage ouvert, via un sondage
// linéaire: on prend la première entrée libre suivante (modulo
// 2^k). La table est dynamique et croît par doublement dès qu'il y a
// collision et que son taux de remplissage dépasse 50%. Il faut alors
// re-hacher l'ancienne table dans la nouvelle. On pourrait passer ce
// taux à 100%, pour consommer moins d'espaces, mais cela augmenterait
// significativement le taux de collisions.
//
// Lectures et écritures peuvent prendre, dans le pire des cas, un
// temps linéaire en la taille de la table (2^k) à cause: (1) du
// sondage lors des collisions (mais c'est constant avec un hachage
// uniforme des clés -- en fait, pour un taux de remplissage t<1,
// c'est 1/(1-t) pour un échec et (1/t)*ln(1/(1-t)) pour un succès);
// (2) de la recopie possible et de l'initialisation de la table lors
// du doublement (mais c'est constant en moyenne car amorti sur le
// nombre d'insertions).
//
//////////////////////////////////////////////////////////////////////


typedef struct{
  int *key;       // liste des clés de la table
  void* *value;   // liste de valeurs de la table
  char *state;    // liste des états de chaque entrée (key,value)
  unsigned n;     // nombre d'entrées (key,value) présentes dans la table
  unsigned mask;  // mot binaire de la forme 2^k-1 pour un modulo rapide
  unsigned shift; // décalage pour le calcul rapide du hash
} *htable;


// Constante multiplicative pour le calcul du hash (soit l'indice h de
// key dans la table). Il s'agit du hash de Fibonacci. Cette constante
// correspond au nombre impair le plus proche de 2^64 / φ, où φ =
// (1+√5)/2 est le nombre d'or. Elle est sur 64 bits, de type
// "unsigned long long" (ou uint64), d'où le suffixe "llu".
#define HT_MAGIC 11400714819323198485llu


// Taille d'initialisation de la table, doit être une puissance de
// 2. Elle influence directement le temps de ht_create() et
// ht_reset(). En lien avec la constante HT_FLS_INIT_SIZE qui
// correspond au nombre de bits pour représenter un indice de [0,
// HT_INIT_SIZE[. En fait, HT_FLS_INIT_SIZE = fls(HT_INIT_SIZE), mais
// malheureusement fls() n'existe pas sous Linux (sous Mac OS, si).
#define HT_INIT_SIZE 4
#define HT_FLS_INIT_SIZE 2


// Crée une table de hachage. Cette création nécessite une
// initialisation en temps O(HT_INIT_SIZE) = O(1).
htable ht_create(void);


// Supprime la table de hachage créer par ht_create(). Les objets
// insérés dans la table (value) ne sont pas désalloués.
void ht_free(htable T);


// Ajoute de (key,value) dans la table T en écrasant l'ancienne valeur
// (si elle existait). Renvoie la valeur écrasée ou bien NULL si key
// n'était pas dans la table.
void* ht_write(htable T, int key, void* value);


// Lit la valeur correspondant à key dans T. Renvoie NULL si key n'est
// pas dans la table.
void* ht_read(htable T, int key);


// Supprime toutes les entrées de la table sans modifier la taille de
// la table. Permet de réutiliser la même table en évitant la
// réallocation dynamique et le re-hachage. Prend un temps
// proportionnel à la taille de la table, pas au nombre d'entrées
// quelle contient.
void ht_reset(htable T);


#endif


// TODO_1: Gérer les suppressions.
//
// Il faut faire attention qu'après la suppression de (k1,v1) on peut
// faire une recherche de (k2,v2) qui va passer par (k1,v1). Faut-il
// alors s'arrêter ? On peut faire une suppression paresseuse: on
// marque comme supprimé les éléments, mais on ne réécrit jamais sur
// ces entrées là, sauf lors d'un rehachage pour l'aggrandissement ou
// la diminuation de la table. Par exemple, si lors d'une suppression,
// 4n < T->mask, alors on réalloue et on rehache. La recherche se
// passe comme si les éléments supprimés existaient encore.
//
// TOTO_2: Accélérer le sondage en cas de collisions. On pourrait
// mémoriser des sauts lors des collisions: s'il y a une collision
// pour la clé c' à la même place h que la clé c, alors on stocke en h
// le saut +j (modulo 2^k) qu'il faut faire pour atteindre c'. Donc au
// prochain accès à c', on accèdera à c puis on pourra aller
// directement à l'indice h+j. Il faudra stocker en h aussi c' car on
// pourrait avoir une collision en h pour une autre clé. C'est peut
// être intéressant seulement pour les écritures. En cas de collision
// en h pour c', on stocke le plus grand saut d'une écriture en
// collision, si bien qu'à la prochaine écriture en collision avec h,
// on pourra poursuivre le sondage à partir de h+j. Il faudra alors
// mettre à jour le saut à la fin du sondage. Cependant, il n'est pas
// clair qu'en pratique cela ait beaucoup d'intérêt, sachant qu'une
// cherche linéaire est préférable à la recherche dichotomique s'il y
// a moins de 256 éléménts.
//
// TODO_3: Faire un sondage quadratique.
//
//   h = ancien indice
//   h_i = indice pour le sondage numéro i = 1..n
//   h_i = (h + (-1)^{i+1} * floor(i/2)^2) % 2^k
//
// C'est censé être plus efficace (moins de collisions en cas de
// grumelage des clés). Cependant il est moins clair de savoir si ce
// sondage aboutit toujours, en particulier s'il ne reste qu'une seule
// entrée libre. C'est aussi moins rapide en pratique à cause du cache
// plus adapté au sondage linéaire.
//
// TODO_4: Accélérer le re-hachage. Actuellement, c'est fait avec un
// appel récursif:
//
//    for(int i=0; i<m; i++)
//      if( S[i] == ST_SET )
//        ht_lookup(T,K[i],V[i],OP_WRITE);
//
// Au prix d'une duplication de code, on pourrait éviter un certain
// nombre de switch(op) puisqu'on sait que op = OP_WRITE, ce qui est
// lourd à cause du sondage linéaire.
//
// TODO_5: Itération d'une fonction sur les éléments de la
// table. Typiquement faire un free() sur tous les éléments de la
// table. Il faudrait que l'algorithme soit en O(n) et pas en
// O(2^mask).
//
// Pour l'implémentation, le plus simple serait d'avoir une table
// supplémentaire indiquant les indices de T qui sont utilisés lors
// des écritures. C'est facile à gérer (ajout en fin de liste lors
// d'une écriture). Du coup, c'est une simple itération sur cette
// nouvelle table. Cela pose cependant des problèmes pour la
// suppression.
//
// struct{
// ...
// int *index; // table des éléments écrits
// ...
// } *htable;
//
// Ex. d'utilisation:
//
// for(i=0; i<T->n; i++){
//   v = T[T->index[i]]->value;
//   k = T[T->index[i]]->key;
//   ...
// }
//
// On pourrait optimiser ht_reset() en fonction du taux de
// remplissage. Style si taux > 25% alors reset via bzero, sinon via
// une boucle sur T->index[].
//
// On pourrait aussi ajouter une fonction ht_free_obj(T) qui libère
// les objets de la table en O(n) via une boucle sur T->index[], avant
// de supprimer la table comme le fait ht_free(T).
//
