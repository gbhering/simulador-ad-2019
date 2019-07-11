#include <cmath>
#include <iostream>
#include <limits>
using namespace std;

// constantes do programa
unsigned const RODADAS = 10;
unsigned const KMIN = 1000000;
float const MI = 1.0;
float const LAMBDA = 0.9;

float exponencial(float const _taxa) {
	auto uni = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return -log(1.0-uni)/_taxa;
} 

float T = 0.0;
float W_0 = 0.0;
unsigned R = 0;
float prox_chegada = 0.0;

void rodada_fcfs() {
	float w_i = 0, n = 0;
	while (n < KMIN) {
		T += prox_chegada;
		W_0 = prox_chegada > W_0 ? 0 : W_0 - prox_chegada;
		w_i = (w_i*n + W_0)/(n+1);
		n += 1;
		W_0 += exponencial(1.0);
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