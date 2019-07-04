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
auto exponencial(const auto lambda) { 
	auto uni = static_cast <float> (gerador()) / static_cast <float> (2147483647);
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
	std::cout << "Serviço de " << 1 << "s" << std::endl;
}

void inline nova_chegada() {
	auto t = exponencial(lambda);
	std::cout << "Nova chegada em " << t << "s" << std::endl;
	push(chegada, t);
}

int main(int argc, char const *argv[]) {
	nova_chegada(); // primeira chegada
	
	int lim = k;
	while( eventos != tail && --lim) {
		auto e = pop();
		if ( e->tipo == chegada )
			nova_chegada();
		else if ( e->tipo == fregues )
			serve();
	}

	return 0;
}