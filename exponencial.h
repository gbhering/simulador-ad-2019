#include <cmath>
#include <limits>

// Função para gerar intervalos exponenciais, 
// utilizando uma uniforme(0,1) e a inversa da CDF exponencial
inline float exponencial(float const _taxa) {
	auto uni = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return -log(1.0-uni)/_taxa;
} 