#include <cmath>
#include <iostream>
#include <queue>
#include <deque>
#include "eventos.h"
#include "exponencial.h"
using namespace std;

// Constantes do programa
bool const FCFS = true;
unsigned const RODADAS = 200;
float const KMIN = 100;
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
	tempos de espera sejam feitas, a rodada continua. 
*/
void rodada() {
	float k = 0, w_i = 0, N_qi = 0, t0 = T;
	while (k <= KMIN and !fila.empty()) {
		// Pirmeiro evento da fila é extraído
		Evento e = fila.top();	fila.pop();
		float delta = e.t - T;
		// Tempo avança
		T = e.t;
		// Número de pessoas é computado
		N_qi += espera.size()*delta;
		// Caso o próximo evento seja uma chegada...
		if ( e.tipo == chegada ) {
			// Uma nova pessoa entra no sistema 
			N++; 
			// Próxima chegada é agendada
			espera.push_back(e);
			// Esta chegada é aramazenada
			fila.emplace(chegada, T + exponencial(LAMBDA), R);
			// Caso seja a única pessoa no sistema, 
			if ( N == 1 ) 
				// entra imediatemente no servidor
				entra_servidor(w_i, k);
		} 
		// Caso o próximo evento seja uma partida...
		else if ( e.tipo == partida ) {
			// Uma pessoa sai do sistema
			N--;
			// Se ainda há pessoas no sistema, agenda uma nova partida
			if ( N > 0 ) 
				entra_servidor(w_i, k);
		}
	}

	// Guarda-se as estatisticas ao fim da rodada em vetores 
	// O total de tempo esperado é dividido pelo número de pessoas
	W[R] = w_i/KMIN; 
	// O resultado da área do gráfico é dividido pelo tempo total 
	N_q[R] = N_qi/(T-t0);
	if (VERBOSE > 0) 
		cout << R<< '(' << W[R] << ", " << N_q[R] << ')' << endl;
} 


int main(void) {
	cout << "rodadas=" << RODADAS 
		 << " kmin=" << KMIN 
		 << " lambda=" << LAMBDA 
		 << endl;

	// primeira chegada é agendada
	fila.emplace(chegada, T + exponencial(LAMBDA), R);
	while (R++ < RODADAS) 
		rodada();

	// ao fim das rodadas, calculamos as médias...
	float ENq = 0, VNq = 0, EW = 0, VW = 0;
	for (unsigned i = 0; i <= RODADAS; ++i) {
		ENq += N_q[i]/RODADAS;
		EW += W[i]/RODADAS;
	}
	// ...depois as variancias
	for (unsigned i = 0; i <= RODADAS; ++i) {
		VNq += pow( (N_q[i]-ENq), 2 ) / ( RODADAS-1 );
		VW += pow( W[i]-EW, 2 ) / ( RODADAS-1 );
	}
	cout << "E[W]=" << EW << " E[Nq]=" << ENq << endl;
	cout << "Var[W]=" << VW << " Var[Nq]=" << VNq << endl;

	cout << "Ultimo estado do gerador: " << gen << endl;

	return 0;
}