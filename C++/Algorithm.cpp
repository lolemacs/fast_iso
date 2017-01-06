#include "Algorithm.h"  

#define stuck 0 
#define success 1 
#define finish 2 
#define fail 3

Algorithm::Algorithm(const char* distPath1, const char* degPath1, const char* distPath2, const char* degPath2){
	//Inicializando Grafo 1  
	g1.setup(distPath1, degPath1);

	//Inicializando Grafo 2  
	g2.setup(distPath2, degPath2);

	bGraph = vector<vector<unsigned int> >(g1.n);
	for (unsigned int i = 0; i < g1.n; i++)
		bGraph.at(i).resize(g1.n);

	Msp = vector<int>(g1.n);
	fill(Msp.begin(), Msp.end(), -1);

	cout << g1.n << endl;
	
	//Alocando memória 
	dosAndDegreesMatches = vector<vector<unsigned int> > (g1.n);
	for (unsigned int i = 0; i < g1.n; i++){
		dosAndDegreesMatches.at(i).resize(g1.n);
	}
	cout << "Tamanho" << dosAndDegreesMatches.size() << endl;
	
}

void Algorithm::run(){
	int ret = 0;
	int iter = 0;
	createDosAndDegreesMatchesMatrix();
	while (true){
		cout << "Iteration " << iter << endl;
		generateGraph();
		ret = lockEdges();
		switch (ret){
		case stuck:
			cout << "Algorithm got stuck" << endl;
			cout << "Fraction of vertices mapped (from 0 to 1): " << (M.size()) / (float)g1.n << endl;
			return;
		case success:
			break;
		case finish:
			cout << "Finish - Isomorphism found" << endl;
			return;
		case fail:
			cout << "Fail - No isomorphism found" << endl;
			return;
		}
		iter++;
	}
}

void Algorithm::generateGraph(){
	unsigned int n = g1.n;

	for (unsigned int i = 0; i < n; i++)
		bGraph.at(i).clear();

	if (n != g2.n) return;
	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			if (checkDosAndDegrees(i, j)){
				if (isEqualMappedDs(i, j)){
					bGraph.at(i).push_back(j);
				}
			}
		}
	}
}

int Algorithm::lockEdges(){
	bool isStuck = true;
	bool failed = false;
	unsigned int n = g1.n;

	for (unsigned int i = 0; i < n; i++){
		if (bGraph.at(i).size() == 1){
			if (Msp.at(i) == -1){
				isStuck = false;
				M.push_back(i);
				Msp.at(i) = bGraph.at(i).at(0);
			}
		}
		else if (bGraph.at(i).size() == 0)
			failed = true;
	}

	if (isStuck == true){
		//cria uma nova bifurcação na árvore, salvando as variáveis M, Msp, v (vértice com menor grau) e c (aresta a ser fixada no chute)
		int index = getMinDegVertex();

		State s = State();
		
		s.M = M;
		s.Msp = Msp;
		s.v = index;
		s.c = 0;

		cout << "Creating new tree path at vertex " << index << endl;

		tree.push_back(s);

		M.push_back(index);
		Msp.at(index) = bGraph.at(index).at(0);

		return success;
	}

	else if (failed){
		State s;
		bool climbing = true;

		//subir na árvore até poder ir para o lado
		while (climbing){
			cout << "Tree path failed, climbing tree" << endl;
			s = tree.back();
			s.c += 1;
			if (s.c <= bGraph.at(s.v).size() - 1)
				climbing = false;
			else{
				if (tree.size() > 1)
					tree.pop_back();
				else
					return fail;
			}
		}

		M.push_back(s.v);
		Msp.at(s.v) = bGraph.at(s.v).at(s.c);
		return success;
	}

	else if (M.size() == n)
		return finish;

	else
		return success;
}

int Algorithm::getMinDegVertex(){
	unsigned int n = g1.n;
	int min = n + 1;
	int index = -1;
	int deg;

	for (unsigned int i = 0; i < n; i++){
		deg = bGraph.at(i).size();
		if (deg > 1 && deg < min){
			min = bGraph.at(i).size();
			index = i;
		}
	}
	return index;
}

bool Algorithm::isEqualDegrees(unsigned int itG1, unsigned int itG2){
	if (g1.degrees.at(itG1) == g2.degrees.at(itG2))
		return true;
	return false;
}

//Assume que tamanho de Dos é igual!  
bool Algorithm::isEqualDos(unsigned int itG1, unsigned int itG2){
	//Do sendo lista 
	//list <unsigned int> Do1 = g1.Do.at(itG1); 
	//list <unsigned int> Do2 = g2.Do.at(itG2); 

	//list<unsigned int>::iterator it1 = Do1.begin(); 
	//list<unsigned int>::iterator it2 = Do2.begin(); 

	//while (it1 != Do1.end()) 
	//{ 
	//  if ((*it1) != (*it2)) 
	//      return false; 
	//  it1++; 
	//  it2++; 
	//} 

	//Do sendo vetor 
	vector <unsigned int> Do1 = g1.Do.at(itG1);
	vector <unsigned int> Do2 = g2.Do.at(itG2);

	for (unsigned int i = 0; i < g1.n; ++i){

		if (Do1.at(i) != Do2.at(i))
			return false;
	}


	return true;
}

bool Algorithm::isEqualMappedDs(unsigned int itG1, unsigned int itG2){
	vector <unsigned int> D1 = g1.D.at(itG1);
	vector <unsigned int> D2 = g2.D.at(itG2);

	for (vector<unsigned int>::iterator itM = M.begin(); itM != M.end(); ++itM) {

		if (D1.at(*itM) != D2.at(Msp.at(*itM)))
			return false;
	}

	return true;

}

void Algorithm::createDosAndDegreesMatchesMatrix(){

	//Let run loop tell the bad news 
	if (g1.n != g2.n) return;

	unsigned int n = g1.n;
	//cycle through every pair of nodes 
	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			//cout << "Tamanho" << dosAndDegreesMatches.size() << endl;
			//cout << i << " " << j << endl;
			if (isEqualDegrees(i, j))
			{
				if (isEqualDos(i, j))
					dosAndDegreesMatches.at(i).at(j) = 1;
				else
					dosAndDegreesMatches.at(i).at(j) = 0;
			}
			else
				dosAndDegreesMatches.at(i).at(j) = 0;
		}
	}
}

bool Algorithm::checkDosAndDegrees(unsigned int itG1, unsigned int itG2){
	if (dosAndDegreesMatches.at(itG1).at(itG2) == 1)
		return true;
	return false;
}
