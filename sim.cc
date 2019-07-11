#include <iostream>
#include "eventos.h"
#include "exponencial.h"
using namespace std;

// Constantes do programa
unsigned const RODADAS = 10;
unsigned const KMIN = 1000000;
float const MI = 1.0;
float const LAMBDA = 0.9;

// Variaveis da execução
float T = 0.0;				// Tempo do simulador
float W_0 = 0.0;			// Tempo de espera encontrado na chegada 
unsigned R = 0;				// Contador de Rodada
float prox_chegada = 0.0;	// Tempo até próxima chegada

void rodada_fcfs() {
	float w_i = 0, n = 0;
	while (n < KMIN) {
		T += prox_chegada;
		W_0 = prox_chegada > W_0 ? 0 : W_0 - prox_chegada;
		w_i = (w_i*n + W_0)/(n+1);
		n += 1;
		W_0 += exponencial(MI);
		prox_chegada = exponencial(LAMBDA);
	}
	cout << "R" << R << ": E[W]=" << w_i << " e E[Nq]=" << w_i*n/T << " e T=" << T << endl;
	T = 0.0;
} 


int main(void) {
	srand(51520191);
	cout << "rodadas=" << RODADAS << " kmin=" << KMIN << " lambda=" << LAMBDA << endl;
	prox_chegada = exponencial(LAMBDA);
	while (R++ < RODADAS)
		rodada_fcfs();
	return 0;
}