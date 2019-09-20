template<class Indiv>
struct Problema{
	typedef Indiv indiv;
	int populacao;
	int geracao;
	int cromossomos;
	Problema(){}
	Problema(int P, int G,int C){
		populacao=P;
		geracao=G;
		cromossomos=C;
	}
	void novo_individuo(Indiv& B){}
	int valor_aleatorio(int max){
		return iniciar(max);
	}
	double valor_aleatorio(double max){
		long long aleatorio = iniciar(100000000);
		return (max*aleatorio)/double(100000000);
	}
	double aptidao(Indiv& individuo){
		return -1;
	}
};

template<class Indiv>
struct pratica2: Problema<Indiv>{
	pratica2(int P, int G,int C):
		Problema<Indiv>(P, G, C){
	}
	int num_cromossomo(){
		return this->cromossomos;
	}
	void novo_individuo(Indiv& B){
		Representa novo(num_cromossomo());
		for (int i=0;i<num_cromossomo();i++){
			novo_cromossomo[i]=iniciar(2);
		}
		B.representa=novo;
	}
	double func(double x1, double x2){
		double x=max(sqrt(x1*x1+x2*x2),eps);
		double z=sin(pi*x)/(pi*x);
		return z*z;
	}
	double aptidao(Indiv& individuo){
		double x1,x2;
		x1=individuo.representa.getX().first;
		x2=individuo.representa.getX().second;
		return (func(x1,x2)+1)*1000;//(func(x1,x2));
	}
};
