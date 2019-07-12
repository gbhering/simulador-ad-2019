enum Tipo { chegada, partida };

struct Evento {
	Tipo tipo; 
	double t; 
	unsigned r;

	Evento(Tipo tipo, double t, unsigned r) : tipo(tipo), t(t), r(r) {};
	bool operator<(const Evento& that) const { return this->t > that.t; };
	bool operator>(const Evento& that) const { return this->t < that.t; };
};
