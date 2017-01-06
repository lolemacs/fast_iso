#include <vector> 
#include <list> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <iterator>     // std::istream_iterator 
#include <algorithm> 

using namespace std;

inline double str2dbl(string Text){
	stringstream ss(Text);
	double result;
	return ss >> result ? result : 0;
}


class Graph {
public:
	Graph();
	void setup(const char*, const char*);
	void generateDegrees(const char*);
	void generateD(const char*);
	void generateDo();

	unsigned n;
	vector<unsigned int> degrees;
	vector< vector<unsigned int> > D;
	vector< vector<unsigned int> > Do;
};