#include <iostream>
#include <random>

// Objeto gerador de números pseudo-aleatórios com seed 51520191
std::minstd_rand0 gerador (51520191);

// Para conveniencia, os tipos de eventos tem nomes legiveis definidos aqui
enum evento_t { head, chegada };

// Estrutura de dados que descreve cada evento
struct Evento {
	evento_t tipo;
	Evento *next = NULL;
	Evento(evento_t tipo): tipo(tipo) {};
};

Evento* eventos = new Evento(head);
Evento* tail = eventos;

void inline serve() {
	std::cout << "Serviço de " << ( gerador() % 1000 ) << " segundos" << std::endl;
}

void simul(Evento* e) {
	if( e->tipo == chegada )
		serve();
}

auto inline push(const evento_t t) {
	tail->next = new Evento(t);
	tail = tail->next;
}

int main(int argc, char const *argv[]) {
	auto e = eventos;
	push(chegada);
	push(chegada);
	
	while(e->next) {
		e = e->next;
		simul(e);
	}

	return 0;
}