Liens
-----

* [Différents algos](http://www.sluniverse.com/php/vb/project-development/34994-automatically-generated-terrain-map.html) : Ridged Perlin Noise, Hills Algorithm, Craters, Erosion.
* [Plein d'algos](http://planetgenesis.sourceforge.net/docs15/noise/noise.html#tileworley) dont plusieurs basés sur une sorte de voronoi donc à priori trop lents.
* Affichage avec Ogre : [forum](http://www.ogre3d.org/forums/viewtopic.php?f=5&t=67177&p=442222), [doc](http://www.ogre3d.org/docs/api/html/classOgre_1_1BillboardSet.html)

Perlin noise
------------

Ridged Perlin Noise
-------------------

[Démo de Ridged Perlin Noise](http://www.inear.se/2010/04/ridged-perlin-noise/)

    // Fait des crêtes de montagnes ou vallées.
    abs(perlinNoise());

Hills Algorithm
---------------

Inverse de craters : on ajoute plein de cercles :

    repeat 1000 times :
        r=random();
	cx=random();
	cy=random();
	terrain[x][y] += r**2 + ((x-cx)**2 – (y-cy)**2)

Craters
-------

Soustraire des cercles (profondeur = f(distance au centre)) au terrain
existant.
Ou : générer un terrain nu, et soustraire plein de cercles aléatoirs.

Erosion
-------

Modélisation correcte : trop lent. À la place, outil "courbes" de gimp.
