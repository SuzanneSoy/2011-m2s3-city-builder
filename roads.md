Réseaux de routes/quartiers
===========================

On part d'un quartier qu'on subdivise en plus petits quartiers en y
trançant des rues.

Un quartier est un polygone (pas forcément convexe !). Sur les côtés
du polygone, des routes entrantes et sortantes peuvent être
marquées. La somme des entrées (+) et sorties (-) du polygone est
nulle.

Concentrique
------------

C'est équivalent à dé-polariser le repère et construire un « mur »
(sorte de grille avec beaucoup d'horizontales de grande longueur).

Il faut trouver un algorithme de construction de mur, puis le
re-polariser afin de pouvoir le lancer avec plusieurs centres.

Grille
------

Algo 1

* Choisir un angle.
* Tracer des routes suivant cet angle et cet angle + 90°.
* Les routes doivent pouvoir être assez longues (le tracé doit
  survivre à une intersection).

Algo 2

* Choisir un angle.
* Tracer des petits segments de route suivant l'angle et l'angle+90°
* Inhiber la subdivision de segments (ne pas les couper en deux).
* Raccrocher les bouts des routes à des points proches si possible (et
  tant qu'on ne dévie pas trop en angle).

Algo 3
* Prendre une grille carrée / rectangulaire.
* La tourner d'un certain angle.
* Rattacher au bord du quartier les segments de la grille qui le
  croisent.
* Supprimer aléatoirement certains segments, en gardant le graphe
  connexe.

Algo 4
* Choisir un angle pour dessiner les croix.
* Dessiner une grosse croix avec des angles de 90° entre les segments,
  ± au milieu du quartier.
* Subdiviser de la même manière les quatre (ou plus si le quartier
  d'origine n'est pas convexe) quartiers ainsi créés, en gardant le
  même angle (petites variations possibles).

« Mur »
-------

Comme une grille, mais les angles ne sont pas vraiment à 90°, et il y
a beaucoup de longues rues dans l'une ou l'autre des directions.

    .________________________.
    |   |        |      |    |
    |___|________|______|____|
    |         |       |______|
    |_________|_______|      |
    |______|__________|______|

TODO : trouver un algo pour générer des « murs »

Arborescent
-----------

On subdivise le quartier en polygones plus ou moins réguliers (grille,
voronoi, …), et on fait partir un arbre depuis un point, qu'on étend
jusqu'à avoir touché tous les polygones. Chaque polygone est un
sous-quartier.

Il est possible de s'arrêter avant d'avoir touché tous les polygones,
auquel cas il faut regrouper les polygones non touchés avec d'autres
pour qu'ils forment un seul quartier.

Courbes de niveau
-----------------

Faire des routes suivant les courbes de niveau, avec la possibilité de
monter ou descendre très légèrement pour rejoindre une autre ligne.

* Partir d'un point, et choisir le point à X de distance qui minimise
  le dénivellé
* Continuer à partir du point ainsi créé, en s'interdisant les retours
  en arrière trop brutaux
* Arrêter la ligne quand le dénivellé devient trop important, ou quand
  on rejoint une autre ligne.

Calculs nécessaires
===================

Polygones
---------

Il faut pouvoir, à partir d'une liste de lignes, déterminer les
polygones ainsi découpés (ou bien maintenir un arbre de polygones
qu'on découpe au fur et à mesure qu'on trace des lignes traversant un
polygone), pour connaître les sous-quartiers créés en traçant les
routes.

Points proches
--------------

Énumérer les points proches d'un point donné.

Pour cela, faire un quadtree (un arbre avec 4 fils à chaque noeud)
représentant des carrés composés de quatre carrés, et stocker dans
chaque noeud s'il contient des points dans son sous-arbre ou non. Les
noeuds feuille listent les points qu'ils contiennent. Quand on dépasse
un certain seuil pour le nombre de points contenus dans un noeud
feuille, on le subdivise.

Lignes proches
--------------

Énumérer les lignes proches d'un point donné.

Quand on ajoute un point au graphe des routes, on l'insère à la bonne
position dans le quadtree.

Quand on trace un segment entre deux points, on indique sa présence
dans tous les noeuds qu'il traverse. *TODO* : cela coûte cher en temps
et en espace !

Autre possibilité : forcer les routes à être sur le bord de polygones
(comme les rivières). Quand on veut tracer une route quelque part, on
subdivise le polygone contenant pour que le nouveau point soit sommet
d'au moins un des polygones, et la route côté de ce polygone.

Intérieur d'un polygone
--------------------

Pouvoir sélectionner aléatoirement des points à l'intérieur d'un
polygone (pour pouvoir faire les centres des réseaux concentriques par
exemple).

Angles et vecteurs
------------------

Pouvoir ajouter un vecteur à un point, appliquer une rotation sur le
vecteur…

Algo déformation de coordonées
==============================

Partir d'une grille idéale carrée et appliquer des déformations de
coordonnées dessus, plus une fonction de densité de points (taille des
bâtiments). Dé-transformer la fonction de densité de points,
l'utiliser pour générer la grille parfaite avec des densités
différentes, puis transformer cette grille.

Algo champs de force
====================

* Choisir des champs de force. `f(x,y,vecteur)` renvoie tous les
  vecteurs de routes qu'on peut faire partir du point `(x,y)`,
  lorsqu'on y arrive par la direction `vecteur`.
* Initialiser `fifo` à vide.
* Choisir un point de départ aléatoire, une direction aléatoire, et
  insérer `(x,y,vecteur,0)` dans `fifo`.
* Tant qu'on n'a pas suffisemment créé de routes :
  * Prendre le point `(x,y,vecteur,n)` en tête de `fifo`.
  * new = f(x,y,vecteur,n).
  * Si new != NULL, tracer le segment `(x,y)--(new)`.
  * insérer `(x,y,vecteur,n+1)` dans `fifo` si new dit que n+1 existe.
  * insérer `(new,(x,y)--(new),0) dans `fifo`.

Représentation simpliste des segments et routes
===============================================

* Dans chaque vertex, avoir un pointeur vers un des segments auxquels
  il appartient.
* Dans chaque segment, avoir un pointeur vers le segment de même
  origine suivant dans le sens des aiguilles d'une montre.
* Dans chaque segment, avoir un pointeur vers le segment de même
  extrémité suivant dans le sens des aiguilles d'une montre.
