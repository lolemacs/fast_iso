#include <vector>  
#include <iterator>  
#include "Graph.h"  
#include "State.h"

using namespace std;

class Algorithm {
public:
	Algorithm();
	Algorithm(const char*, const char*, const char*, const char*);
	void generateGraph();
	int lockEdges();
	bool isEqualDegrees(unsigned int, unsigned int);
	bool isEqualDos(unsigned int, unsigned int);
	bool isEqualMappedDs(unsigned int, unsigned int);
	void run();
	int getMinDegVertex();

	void createDosAndDegreesMatchesMatrix();
	bool checkDosAndDegrees(unsigned int, unsigned int);

private:
	Graph g1;
	Graph g2;

	vector<State> tree;

	//Contйm mapeamentos de G1 para G2  
	vector<int> Msp;
	//Contйm vйrtices de G1 jб mapeados  
	vector<unsigned int> M;
	vector< vector<unsigned int> > bGraph;

	//Guarda os pares de vertices que podem ser combinados pelo criterio do Do e dos Graus 
	//Inclui o grau porque ele tambйm nгo precisa ser feito vбrias vezes. 
	// Os graus dos vйrtices nгo mudam nos grafos originais durante a simulaзгo. 
	//Preferi nгo colocar estados no bipartido pra indicar isso, assim й mais fбcil de fazer. 
	vector< vector<unsigned int> > dosAndDegreesMatches;
};