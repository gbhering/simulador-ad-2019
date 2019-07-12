// apenas para conveniencia, os tipos tem nomes próprios
enum Tipo { chegada, partida };

// A estrutura que armazena os dados do eventos exponenciais
struct Evento {
	Tipo tipo; 		// Chegada ou partida
	double t; 		// Tempo quando acontece
	unsigned r;		// Identificador da rodada

	// Construtor trivial, existe para que seja possível criar novos eventos com facilidade
	Evento(Tipo tipo, double t, unsigned r) : tipo(tipo), t(t), r(r) {};
	// Comparadores entre eventos, para facilitar identificar quais acontecem antes
	bool operator<(const Evento& that) const { return this->t > that.t; };
	bool operator>(const Evento& that) const { return this->t < that.t; };
};
