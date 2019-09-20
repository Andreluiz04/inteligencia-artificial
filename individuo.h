struct Individuo{
	Representa representar;
	double aptidao;
	Individuo(){}
	Individuo(Representa rep){
		representar=rep;
	}
	Individuo(Representa representar,double aptidao){
		representar=representar;
		aptidao=aptidao;
	}
	Individuo operador=(const Individuo& B){
		representar=B.representar;
		aptidao=B.aptidao;
		return *(this);
	}
	bool operador ==(const Individuo B)const{
		return (representar==B.representar);
	}
	Individuo cruzamento(const Individuo* B){
		//printf("cruzando\n");
		Representa novo(representar.tamanho());
		bool cromossomo_pai=iniciar(2);
		int tamanho_minimo=3;
		int division=iniciar(representar.tamanho()/2-tamanho_minimo)+tamanho_minimo;
		for (int i=0;i<representar.tamanho()/2;i++){
			if(i==division)
				cromossomo_pai=!cromossomo_pai;
			if(cromossomo_pai)
				novo.cromossomo[i]=representar.cromossomo[i];
			else
				novo.cromossomo[i]=B->representar.cromossomo[i];
		}
		cromossomo_pai=iniciar(2);
		division=representar.tamanho()/2+iniciar(representar.tamanho()/2-tamanho_minimo)+tamanho_minimo;
		for (int i=representar.tamanho()/2;i<representar.tamanho();i++){
			if(i==division)
				cromossomo_pai=!cromossomo_pai;
			if(cromossomo_pai)
				novo.cromossomo[i]=representar.cromossomo[i];
			else
				novo.cromossomo[i]=B->representar.cromossomo[i];
		}
		return Individuo(novo);
	}
	void mutacao_swap(Representa& novo){
		int findice_mutacao=iniciar(representar.tamanho());
		int sindice_mutacao=iniciar(representar.tamanho());
		if(findice_mutacao==sindice_mutacao){
			sindice_mutacao=(sindice_mutacao+1)%representar.tamanho();
		}
		int cromosoma_aleatorio=novo.cromossomo[sindice_mutacao];
		novo.cromossomo[sindice_mutacao]=novo.cromossomo[findice_mutacao];
		novo.cromossomo[findice_mutacao]=cromosoma_aleatorio;
	}
	void mutacao_alter(Representa& novo, int n){
		set<int> S;
		for (int i=0;i<n;i++){
			//novo.cromossomo[iniciar(representar.tamanho())]=iniciar(2);
			int pos=iniciar(representar.tamanho());
			while (S.find(pos)!=S.end()){
				pos=iniciar(representar.tamanho()); 
			}
			novo.cromossomo[pos]=!(novo.cromossomo[pos]);
			S.insert(pos);
		}
	}
	Individuo mutacao(){
		Represent novo(representar.tamanho());
		novo=representar;
		//mutacao_swap(novo); //swap
		mutacao_alter(novo, iniciar(2)+1); //alter
		return Individuo(novo);
	}
	bool operador <(const Individuo& B)const{
		return (aptidao==B.aptidao)?representar<B.representar:aptidao<B.aptidao;
	}
};
