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

