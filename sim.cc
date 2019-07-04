#include <iostream>
#include <random>
#include <cmath>

// Constantes da simulação
auto const k = 4;
auto const mi = 1;
auto const lambda = 0.5;
auto const rho = lambda / mi;
auto const FCFS = true;
auto const verbose = true;

// Objeto gerador de números pseudo-aleatórios com seed 51520191
std::minstd_rand0 gerador (51520191);
float tempo_chegada() { 
	float uni = static_cast <float> (gerador()) / static_cast <float> (2147483647);
	return -log(1.0-uni)/lambda; 
}

// Para conveniencia, os tipos de eventos tem nomes legiveis definidos aqui
enum evento_t { head, chegada, fregues };

// Estrutura de dados que descreve cada evento
struct Evento {
	evento_t tipo;
	unsigned dur;
	Evento *next = NULL;
	Evento(evento_t tipo, unsigned dur): tipo(tipo), dur(dur) {};
};

Evento* eventos = new Evento(head,0);
Evento* tail = eventos;

void inline push(const evento_t t, int dur = 0) {
	tail->next = new Evento(t, dur);
	tail = tail->next;
}

auto inline pop() {
	if (eventos == tail) 
		return eventos;
	auto e = eventos->next;
	if (eventos->next == tail)
		tail = eventos;
	eventos->next = eventos->next->next;
	return e;
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