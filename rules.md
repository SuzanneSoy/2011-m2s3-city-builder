rectangle suffisemment petit, résidentiel → maison
rectangle suffisemment petit, commercial → magasin
…

// TODO : condition : les routes présentes sur le bord du rectangle doivent être signalées.
// TODO : largeur des routes
// TODO : quand on trace une route jusqu'au bord, faire un carrefour / T avec la route voisine.


// TODO : faire pour des angles entre 70° et 110°.

// TODO : distinguer à la création les RectangleRoutes avec (all sides length > 10) et les autres cas.

RectangleRoutes r (all sides length > 10) {
  Vertex split = { .x = randomInRange(r.seed, 0, r.no.x+5, r.ne.x-5), .y = randomInRange(r.seed, 1, r.no.x+5, r.ne.x-5) };
  Carrefour(split + (1,1), split - (1,1))
  // routes au NESW du carrefour
  Route((r.ne.x, split.y) + (0,1)), split + (1,1))
  Route((split.x, r.se.y) + (1,0)), split + (-1,1))
  Route((r.so.x, split.y) + (0,-1)), split + (-1,-1))
  Route((split.x, r.no.y) + (-1,0)), split + (1,-1))
  // subrectangles
  RectangleRoutes(split + (1,1),   r.ne, newSeed(r.seed, 2));
  RectangleRoutes(split + (1,-1),  r.se, newSeed(r.seed, 3));
  RectangleRoutes(split + (-1,-1), r.so, newSeed(r.seed, 4));
  RectangleRoutes(split + (-1,1),  r.no, newSeed(r.seed, 5));
}

// rectangle suffisemment grand → rectangle*4 avec un T de routes au milieu.
Rectangle r (r.width > 10 && r.height > 10) {
  Vertex split = randomPointInRect(r);
  Carrefour(split + (1,1), split - (1,1))
  // routes au NESW du carrefour
  Route((r.ne.x, split.y) + (0,1)), split + (1,1))
  Route((split.x, r.se.y) + (1,0)), split + (-1,1))
  Route((r.so.x, split.y) + (0,-1)), split + (-1,-1))
  // subrectangles
  Rectangle((r.so.x,split.y) + (0,1), r.ne);
  Rectangle(split + (1,-1),  r.se);
  Rectangle(split + (-1,-1), r.so);
}
