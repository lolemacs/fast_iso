#include <vector>  
#include <iterator>  

using namespace std;

class State {
public:
	State() {};

	vector<int> Msp;
	vector<unsigned int> M;
	int v;
	int c;
};