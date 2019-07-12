#include <cmath>
#include <limits>
#include <random>

std::default_random_engine gen(51520191);
std::uniform_real_distribution<double> uniform(0.0,1.0);

// Função para gerar intervalos exponenciais, 
// utilizando uma uniforme(0,1) e a inversa da CDF exponencial
inline float exponencial(float const _taxa) {
	return -log(1.0-uniform(gen))/_taxa;
} 