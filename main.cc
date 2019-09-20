#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#include "iniciar.h" 
#include "matematica.h" 
#include "genetico.h"

int main(int argc, char **argv){
	SeedXorShift();
	//Algoritmo genetico
	/*pratica2<Individuo> P2g(200,300,18);
	Genetico<pratica2<Individuo> > G(&P2g,0.3,0.2,false);
	Individuo menorg=G.iniciar(false);*/

	//Algoritmo genetico con eletismo
	pratica2<Individuo> P2g(200,300,24);
	Genetico<pratica2<Individuo> > G(&P2g,0.3,0.2,true);
	Individuo menorg=G.iniciar(false);
	return 0;
}
