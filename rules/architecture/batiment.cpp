#include "all_includes.hh"

Mur::Mur(Segment _s) : s(_s) {}

void Mur::addSplitPoint(float position) {
	(void)position;
}

bool Mur::addDoor(float start, float end) {
	(void)start; (void)end;
	return true;
}

bool Mur::addWindow(float start, float end) {
	(void)start; (void)end;
	return true;
}

Piece::Piece(Quad _c, Mur* n, Mur* e, Mur* s, Mur* w) : c(_c) {
	murs[0] = n;
	murs[1] = e;
	murs[2] = s;
	murs[3] = w;
}

BatimentQuad_::BatimentQuad_(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentQuad_::split() {
	unsigned int trynumber = 0;
	unsigned int tryseed = hash2(seed, trynumber);
	std::queue<Piece*> queue;
	for (int i = 0; i < 4; i++)
		murs.push_back(new Mur(Segment(c[NE+i], c[SE+i])));
	queue.push(new Piece(c, murs[0], murs[1], murs[2], murs[3]));

	// TODO : placer la porte d'entrée ?

	Piece* piece;
	while (!queue.empty()) {
		piece = queue.front(); queue.pop();
		pieces.push_back(piece);
		if (piece->c.surface() < 14 * 100 * 100)
			continue;
		switch (hash2(tryseed, 0) % 2) {
		case 0: { // rectangle
			if (piece->c.surface() > 100 * 100 * 100 && piece->c.minLength() > 10) {
				float size = piece->c.minLength() / 3.f;
				Quad takeN = piece->c.inset(N, size);
				Quad takeS = takeN.inset(S, size);
				Quad takeE = takeS.inset(E, size);
				Quad takeW = takeS.inset(W, size);
				Quad q[4];
				q[N] = Quad(piece->c[NE], takeN[NE], takeN[NW], piece->c[NW]);
				q[E] = Quad(takeS[SE], takeE[SE], takeE[NE], takeS[NE]);
				q[S] = Quad(piece->c[SW], takeS[SW], takeS[SE], piece->c[SW]);
				q[W] = Quad(takeS[NW], takeW[NW], takeW[SW], takeS[SW]);
				Quad qC = takeW;
				Mur* m[4];
				m[N] = new Mur(Segment(q[N][SW], q[N][SE]));
				m[E] = new Mur(Segment(q[E][SW], q[E][SE]));
				m[S] = new Mur(Segment(q[S][SW], q[S][SE]));
				m[W] = new Mur(Segment(q[W][SW], q[W][SE]));
				Piece* p[4];
				p[N] = new Piece(q[N], piece->murs[N], piece->murs[E], m[N], piece->murs[W]);
				p[E] = new Piece(q[E], piece->murs[E], m[S], m[E], m[N]);
				p[S] = new Piece(q[S], piece->murs[S], piece->murs[W], m[S], piece->murs[E]);
				p[W] = new Piece(q[W], piece->murs[W], m[N], m[W], m[S]);
				Piece* pC = new Piece(qC, m[N], m[E], m[S], m[W]);
				for (int i = 0; i < 4; i++) {
					murs.push_back(m[N+i]);
					queue.push(p[N+i]);
				}
				queue.push(pC);
				// TODO connecter les pièces avec des addDoor (sur les murs les séparant, et/ou à la pièce centrale) ???
				break;
			}
		}
		case 1: // donut
		default: {
			Cardinal offset = piece->c.maxLengthSide();
			Vertex n = Segment(piece->c[NW + offset], piece->c[NE + offset]).randomPos(tryseed, 1, 1.f/3.f, 2.f/3.f);
			Vertex s = Segment(piece->c[SE + offset], piece->c[SW + offset]).randomPos(tryseed, 1, 1.f/3.f, 2.f/3.f);
			piece->murs[offset]->addSplitPoint(0); // TODO
			piece->murs[offset+2]->addSplitPoint(0); // TODO
			Mur* mur = new Mur(Segment(n, s));
			Piece* p1 = new Piece(Quad(n, piece->c[NE+offset], piece->c[SE+offset], s), piece->murs[offset], piece->murs[offset+1], piece->murs[offset+2], mur);
			Piece* p2 = new Piece(Quad(s, piece->c[SW+offset], piece->c[NW+offset], n), piece->murs[offset+2], piece->murs[offset+3], piece->murs[offset], mur);
			murs.push_back(mur);
			queue.push(p1);
			queue.push(p2);
			// TODO : addDoor(start, end); sur le mur les séparant. ?
			break;
		}
		}
	}

	std::vector<Piece*>::iterator it;
	for (it = pieces.begin(); it != pieces.end(); ++it) {
		Quad c = (*it)->c.insetNESW(50);
		addGPUQuad(c, Couleurs::cielHaut);
	}
	//Quad ch = c.offsetNormal(Dimensions::hauteurEtage);
	//addChild(new ToitQuad(ch, Dimensions::hauteurToit));
	return true;
}

void BatimentQuad_::triangulation() {
	Quad ch = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUQuad(ch, Couleurs::toit);
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(c[NE+i], c[SE+i], ch[SE+i], ch[NE+i]), Couleurs::mur);
}

void BatimentQuad_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}

BatimentTri_::BatimentTri_(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentTri_::split() {
	return false;
}

void BatimentTri_::triangulation() {
	Triangle th = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i]), Couleurs::mur);
}

void BatimentTri_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}
