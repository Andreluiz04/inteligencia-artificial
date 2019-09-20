#include "represent.h"
#include "individuo.h"
#include "problema.h"

template <class P, class Indiv=typename P::indiv>
struct Genetico{
	set<Indiv>* populacao;
	P* problema; 
	double Prob_cruzamento;
	double Prob_mutacao;
	double aptidao_total;
	bool elitismo;

	Genetico(P* p,double c, double m,bool e=false){//R
		aptidao_total=0;
		populacao = new set<Indiv>();
		problema=p;
		Prob_cruzamento=c;
		Prob_mutacao=m;
		elitismo=e;
		crear_populacao();
	}

	void criar_populacao(){//R
		while(populacao->size()<problema->tam_populacao){
			Indiv novo_individuo;
			problema->gerar_novo_individuo(novo_individuo);
			novo_individuo.aptidao=problema->aptidao(novo_individuo);
			aptidao_total+=novo_individuo.aptidao;
			populacao->insert(novo_individuo);
		}
	}

	bool selecao_rodar(double aptidao){//R
		double ruleta = problema->valor_aleatorio(aptidao_total);
		return ruleta<aptidao;
	}

	void selecao_individuo(map<int,Indiv*>& individuos_cruzamento){//R
		int i=0;
		for (auto it=populacao->begin();it!=populacao->end();it++){
			if(selecao_rodar(it->aptidao)){
				individuos_cruzamento[i++]=new Indiv(*it);
			}
		}
	}

	Indiv* selecao_pai(map<int,Indiv*>& individuos_cruzamento){//R
		int aleatorio=problema->valor_aleatorio((int)individuos_cruzamento.size());
		auto it=individuos_cruzamento.lower_bound(aleatorio);
		if(it==individuos_cruzamento.end()){
			it=individuos_cruzamento.lower_bound(0);
		}
		Indiv* pai = it->second;
		individuos_cruzamento.erase(it);
		return pai;
	}

	void cruzar_individuos(){//R
		map<int,Indiv*> individuos_cruzamento;
		selecao_individuo(individuos_cruzamento);
		while (individuos_cruzamento.size()>1){
			Indiv* pai = selecao_pai(individuos_cruzamento);
			Indiv* pai2 = selecao_pai(individuos_cruzamento);
			if(!elitismo){
				Indiv filho=pai->cruzamento(pai2);
				filho_aptidao=problema->aptidao(filho);
				aptidao_total+=filho_aptidao;
				populacao->insert(filho);
				Indiv filho2=pai2->cruzamento(pai);
				filho2.aptidao=problema->aptidao(filho2);
				aptidao_total+=filho2.aptidao;
				populacao->insert(filho2);
				if(populacao->size()-problema->tam_populacao==2){
					populacao->erase(*pai);
					populacao->erase(*pai2);
				} else if (populacao->size()-problema->tam_populacao==1){
					populacao->erase(*pai);
				}
			} else {
				Indiv filho=pai->cruzamento(pai2);
				filho_aptidao=problema->aptidao(filho);
				aptidao_total+=filho_aptidao;
				populacao->insert(filho);
			}
		}
	}

	Indiv getIndividuo(int i){
		auto it=populacao->begin();
		for (int j=0;j<i;j++){
			it++;
		}
		return *it;
	}

	void mutar_individuos(){//R
		set<Indiv> Eliminar;
		set<Indiv> Nuevos;
		for(auto it=populacao->begin();it!=populacao->end();it++){
			double aleatorio=problema->valor_aleatorio(double(1));
			if(aleatorio<Prob_mutacao){
				Indiv mutacion=Indiv(*it).mutacion();
				mutacion.aptidao=problema->aptidao(mutacion);
				if(!elitismo){
					if(populacao->find(mutacion)==populacao->end() && Nuevos.find(mutacion)==Nuevos.end()){
						Nuevos.insert(mutacion);
						Eliminar.insert(*it);
					} else {
						if(Eliminar.find(mutacion)!=Eliminar.end()){
							Eliminar.erase(mutacion);
							Eliminar.insert(*it);
						}
					}
				} else {
					Nuevos.insert(mutacion);
				}
			}
		}
		for (auto it=Nuevos.begin();it!=Nuevos.end();it++){
			populacao->insert(*it);
		}
		for (auto it=Eliminar.begin();it!=Eliminar.end();it++){
			populacao->erase(*it);
		}
	}

	virtual Indiv sel_eliminar(){
		if(elitismo)
			return *(populacao->begin());
		else
			return getIndividuo(XorShift(populacao->size()));
	}

	virtual void ajustar_populacao(){//R
		while(populacao->size()>problema->tam_populacao){
			Indiv condenado=sel_eliminar();
			aptidao_total-=condenado.aptidao;
			populacao->erase(condenado);
		}
	}

	virtual void gerar_nova_populacao(){//R
		cruzar_individuos();
		mutar_individuos();
		ajustar_populacao();
	}

	Indiv obter_menor(){
		Indiv mejor=*(populacao->rbegin());
		for (auto it=populacao->begin();it!=populacao->end();it++){
			if(it->aptidao>menor_aptidao){
				mejor=*it;
			}
		}
		pair<double,double> X=menor_representa.getX();
		return mejor;
	}

	Indiv iniciar(bool limite=true){//R
		Indiv mejor;
		gerar_nova_populacao();
		mejor=obter_menor();
		bool estable=false;
		int modificacao=0;
		double menor.aptidao=menor_aptidao;
		int i=1;
		while ((limite && i<problema->numero_de_generaciones) || (!limite && !estable)){
			gerar_nova_populacao();
			mejor=obter_menor();
			if(menor_aptidao>menor.aptidao){
				menor.aptidao=menor_aptidao;
				modificacao=i;
				pair<double,double> X=menor_representa.getX();
				cout << i << "; " << this->problema->func(X.first,X.second) << endl;
			} else if(menor_aptidao==menor.aptidao){
					if(i-modificacao>10)
						estable=true;
			} else {
				pair<double,double> X=menor_representa.getX();
				cout << i << "; " << this->problema->func(X.first,X.second) << endl;
				modificacao=i;
			}
			i++;
		}
		pair<double,double> X=menor_representa.getX();
		cout << i << "; " << this->problema->func(X.first,X.second) << endl;
		//cout << i << " iteraciones" << endl;
		return mejor;
	}
};
