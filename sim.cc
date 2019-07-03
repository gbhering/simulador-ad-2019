#include <iostream>
#include <random>

// Constantes da simulação
auto const k = 4;
auto const FCFS = true;
auto const verbose = true;

// Objeto gerador de números pseudo-aleatórios com seed 51520191
std::minstd_rand0 gerador (51520191);

// Para conveniencia, os tipos de eventos tem nomes legiveis definidos aqui
enum evento_t { head, chegada, servico };

// Estrutura de dados que descreve cada evento
struct Evento {
	evento_t tipo;
	unsigned dur;
	Evento *next = NULL;
	Evento(evento_t tipo, unsigned dur = 0): tipo(tipo), dur(dur) {};
};

Evento* eventos = new Evento(head);
Evento* tail = eventos;

auto inline push(const evento_t t) {
	tail->next = new Evento(t);
	tail = tail->next;
}

void inline serve() {
	std::cout << "Serviço de " << ( /*gerador() %*/ 1000 ) << " segundos" << std::endl;
}

void simul(Evento* e) {
	if( e->tipo == chegada )
		serve();
}

int main(int argc, char const *argv[]) {
	auto e = eventos;
	
	int lim = k;
	while(e->next && lim--) {
		e = e->next;
		simul(e);
	}

	return 0;
}