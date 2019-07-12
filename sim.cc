#include <iostream>
#include <queue>
#include <deque>
#include "eventos.h"
#include "exponencial.h"
using namespace std;

// Constantes do programa
bool const FCFS = true;
unsigned const RODADAS = 10;
float const KMIN = 100000;
float const MI = 1.0;
float const LAMBDA = 0.4;
unsigned const VERBOSE = 1;

float W[RODADAS] = {};
float N_q[RODADAS] = {};

// Variaveis da execução
float T = 0.0;					// Tempo do simulador
float N = 0;					// Pessoas encontradas no sistema 
unsigned R = 0;					// Contador de Rodada
priority_queue<Evento> fila;	// Nossa fila de eventos
deque<Evento> espera;			// Os tempos de chegada para medida futura

/* 
	A única dinstinção entre as duas disciplinas implementadas está aqui.
	Os tempos de chegadas na fila são em uma fila de duas pontas quando
	um evento de chegada é processado. Esta função agenda um novo evento
	de partida e consome uma chegada computada, da frente da fila se FCFS
	ou de trás se LCFS. Tempos de espera são calculados aqui. Apenas se
	a chegada consumida pertence a rodada atual.
*/
void entra_servidor(float& w_i, float& k) {
	fila.emplace(partida, T + exponencial(MI), R);
	if constexpr (FCFS) {
		Evento proximo = espera.front();
		espera.pop_front();
		k += (proximo.r == R);
		w_i += (proximo.r == R) ? T - proximo.t : 0;
	}
	else {
		Evento proximo = espera.back();
		espera.pop_back();
		k += (proximo.r == R);
		w_i += (proximo.r == R) ? T - proximo.t : 0;
	}
}

/*
	Esta função é a que executa o loop de cada rodada. Até que KMIN coletas de 
*/
void rodada() {
	float k = 0, w_i = 0, N_qi = 0, t0 = T;
	while (k <= KMIN and !fila.empty()) {
		Evento e = fila.top();	fila.pop();
		float delta = e.t - T;
		T = e.t;
		N_qi += espera.size()*delta;
		if ( e.tipo == chegada ) {
			espera.push_back(e);
			N++;
			fila.emplace(chegada, T + exponencial(LAMBDA), R);
			if ( N == 1 ) 
				entra_servidor(w_i, k);
		} 
		else if ( e.tipo == partida ) {
			N--;
			if ( N > 0 ) 
				entra_servidor(w_i, k);
		}
	}

	W[R] = w_i/KMIN; N_q[R] = N_qi/(T-t0);
	if (VERBOSE > 0) 
		cout << "W"<<R<<"=" << W[R] << " Nq"<<R<<"=" << N_q[R] << endl;
} 


int main(void) {
	srand(51520191);
	cout << "rodadas=" << RODADAS 
		 << " kmin=" << KMIN 
		 << " lambda=" << LAMBDA 
		 << endl;

	fila.emplace(chegada, T + exponencial(LAMBDA), R);
	while (R++ < RODADAS) 
		rodada();

	float ENq = 0, VNq = 0, EW = 0, VW = 0;
	for (unsigned i = 0; i <= RODADAS; ++i) {
		ENq += N_q[i]/RODADAS;
		EW += W[i]/RODADAS;
	}
	for (unsigned i = 0; i <= RODADAS; ++i) {
		VNq += ( (N_q[i]-ENq) * (N_q[i]-ENq) ) / ( RODADAS-1 );
		VW += ( (W[i]-EW) * (W[i]-EW) ) / ( RODADAS-1 );
	}
	cout << "E[W]=" << EW << " E[Nq]=" << ENq << endl;
	cout << "Var[W]=" << VW << " Var[Nq]=" << VNq << endl;

	return 0;
}