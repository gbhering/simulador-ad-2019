#include <iostream>
#include <queue>
#include <deque>
#include "eventos.h"
#include "exponencial.h"
using namespace std;

// Constantes do programa
bool const FCFS = false;
float const RODADAS = 1;
float const KMIN = 10;
float const MI = 1.0;
float const LAMBDA = 0.9;
bool const VERBOSE = true;

// Variaveis da execução
float T = 0.0;					// Tempo do simulador
float W = 0.0;					// Tempo de espera encontrado na chegada 
float N = 0;					// Pessoas encontradas na fila 
float R = 0;					// Contador de Rodada
priority_queue<Evento> fila;	// Nossa fila de eventos
deque<Evento> espera;			// Os tempos de chegada para medida futura

void priwaits() {
	cout << '$' << ' ';
	for (auto x: espera)
		cout << x.t << ' ';
	cout << endl;
}

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
	priwaits();
}

void rodada() {
	float k = 0, w_i = 0, N_qi = 0, t0 = T;
	while (k <= KMIN and !fila.empty()) {
		Evento e = fila.top();	fila.pop();
		float delta = e.t - T;
		T = e.t;
		N_qi += espera.size()*delta;
		if ( e.tipo == chegada ) {
			espera.push_back(e);
			priwaits();
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
	cout << "R" << R << ": E[W]=" << w_i/KMIN << " e E[Nq]=" << N_qi/(T-t0) << " e T=" << T << endl;
} 


int main(void) {
	srand(51520191);
	cout << "rodadas=" << RODADAS << " kmin=" << KMIN << " lambda=" << LAMBDA << endl;
	fila.emplace(chegada, T + exponencial(LAMBDA), R);
	while (R++ < RODADAS)
		rodada();
	return 0;
}