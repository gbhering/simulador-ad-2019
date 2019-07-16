#include <cmath>
#include <deque>
#include <iostream>
#include <queue>

#include "eventos.h"
#include "exponencial.h"
#include "gabarito.h"

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace std;

const float LAMBDA = 0.9;
const float MU = 1.0;
const int RODADAS = 320;
const int KMIN = 200;
const bool FCFS = true;

priority_queue<Evento> lista_eventos;
deque<Evento> fila_espera;
float ultima_chegada_agendada = 0.0;
float ultima_partida_agendada = 0.0;
float tempo_atual = 0.0;
bool servidor_ocupado = false;

float Nq_experimento=0, W_experimento=0;

inline void agenda_nova_chegada_exponencial(const int& r) { 
	float t = ultima_chegada_agendada + exponencial(LAMBDA);
	lista_eventos.emplace(chegada, t, r); 
	ultima_chegada_agendada = t;
}

inline void agenda_nova_partida_exponencial(const int& r) { 
	float t = tempo_atual + exponencial(MU);
	lista_eventos.emplace(partida, t, r); 
	ultima_partida_agendada = t;
}

auto prox_fila_espera() {
	if (FCFS) {
		auto proximo_a_ser_atendido = fila_espera.front();
		fila_espera.pop_front(); 
		return proximo_a_ser_atendido;
	}
	else {
		auto proximo_a_ser_atendido = fila_espera.back();
		fila_espera.pop_back(); 
		return proximo_a_ser_atendido;
	}
}

const int eventos_logados = RODADAS*KMIN;
vector<float> tempinhos(eventos_logados);
vector<float> tamaninhos(eventos_logados); 
vector<float> medinhas(eventos_logados, ENq(LAMBDA));
auto counter = 1;
void grafico_pessoas_em_fila() {
	if (counter>=eventos_logados) return;
	tempinhos.at(counter) = tempinhos.at(counter-1);
	tamaninhos.at(counter) = (fila_espera.size());
	counter++;
	if (counter>=eventos_logados) return;
	tempinhos.at(counter) = (tempo_atual);
	tamaninhos.at(counter) = (fila_espera.size());
	counter++;
}

void print_fila_espera() {
	cout<<"Fila de Espera("<<fila_espera.size()<<"): ";
	for (auto x: fila_espera) {
		if (x.tipo != chegada) exit(-100);
		cout<<"("<<x.t<<") ";
	}
	cout<<endl;
}

void print_lista_eventos(priority_queue<Evento> lista) {
	cout<<"Eventos("<<lista.size()<<"): ";
	while (!lista.empty()) {
		auto x = lista.top(); lista.pop();
		cout<<"("<<x.t<<","<<(x.tipo==chegada?"chegada":"partida")<<") ";
	}
	cout<<endl;
}

void debug() {
	cout<<"Servidor "<<(servidor_ocupado?"":"des")<<"ocupado!\n";
	print_lista_eventos(lista_eventos);
	print_fila_espera();
	cin.get();
}

void rodada(const int& r) {
	float Nq_rodada=0, W_rodada=0, t0=tempo_atual;
	for (int k = 0; k < KMIN and !lista_eventos.empty();) {
		Evento prox_evento = lista_eventos.top();
		if ( prox_evento.tipo == chegada ) {
			Nq_rodada+=(prox_evento.t-tempo_atual)*fila_espera.size();
			tempo_atual = prox_evento.t;
			agenda_nova_chegada_exponencial(r);
			if (servidor_ocupado) {
				// entrada na fila de espera
				grafico_pessoas_em_fila();
				fila_espera.push_back(prox_evento);
			}
			else {
				servidor_ocupado = true;
				agenda_nova_partida_exponencial(r);
				k++;
			}
			lista_eventos.pop();
		}
		else if ( prox_evento.tipo == partida ) {
			if ( ultima_chegada_agendada < ultima_partida_agendada ) {
				agenda_nova_chegada_exponencial(r);
			}
			else {
				Nq_rodada+=(prox_evento.t-tempo_atual)*fila_espera.size();
				tempo_atual = prox_evento.t;
				lista_eventos.pop();
				if ( !fila_espera.empty() ) {
					// saída da fila de espera
					grafico_pessoas_em_fila();
					agenda_nova_partida_exponencial(r);
					auto proximo = prox_fila_espera();
					if (proximo.r == r) {
						W_rodada+=(tempo_atual-proximo.t)/KMIN;
						k++;
					}
				}
				else {
					servidor_ocupado = false;
				}
			}
		}
	}
	Nq_rodada /= (tempo_atual-t0);
	if ( r % static_cast<int>(powf(10.0f, floorf(log10f(RODADAS))-1)) == 0 ) {
		cout<<"Rodada "<<r<<":"<<endl;
		cout<<" E[Nq]= "<<(Nq_rodada)<<"("<<ENq(LAMBDA)<<") ";
		cout<<" E[W]= "<<(W_rodada)<<"("<<EW(LAMBDA)<<") ";
		cout<<endl;
	}
	Nq_experimento+=Nq_rodada/RODADAS;
	W_experimento+=W_rodada/RODADAS;
}

int main(void) {
	agenda_nova_chegada_exponencial(0);
	for (int r = 1; r <= RODADAS; ++r)
		rodada(r);

	cout<<endl;

	cout<<"Parametros:"<<endl;
	cout<<" KMIN:"<<KMIN<<" ";
	cout<<" RODADAS:"<<RODADAS<<" ";
	cout<<" LAMBDA:"<<LAMBDA<<" ";
	cout<<" DISC:"<<(FCFS?"FCFS":"LCLS")<<" ";
	cout<<endl;

	cout<<"Resultados do Experimento:"<<endl;
	cout<<" E[Nq]= "<<Nq_experimento<<"("<<ENq(LAMBDA)<<") ";
	cout<<" E[W]= "<<W_experimento<<"("<<EW(LAMBDA)<<") ";
	cout<<endl;

	cout<<"Etc:"<<endl;
	cout<<" Ultima seed: "<<gen();
	cout<<endl;

	plt::plot(tempinhos,tamaninhos);
	plt::plot(tempinhos, medinhas,"r--");
	plt::show();

	return 0;
}