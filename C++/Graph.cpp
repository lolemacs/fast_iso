#include "Graph.h" 


Graph::Graph() { n = 0; }


void Graph::setup(const char* distPath, const char* degPath) {
	generateDegrees(degPath);
	generateD(distPath);
	generateDo();
	n = D.at(0).size();
}


void Graph::generateD(const char* distPath){
	ifstream file;

	try{
		file.open(distPath, std::ifstream::in);
	}

	catch (int e){
		cout << "Error reading file." << endl;
		return;
	}

	vector<unsigned> vec;

	std::string str;

	if (file.is_open()) {
		while (!file.eof()) {
			vec.clear();
			getline(file, str);

			istringstream buf(str);
			istream_iterator<string> beg(buf), end;
			vector<string> tokens(beg, end);

			for (auto& s : tokens)
				vec.push_back(str2dbl(s));

			D.push_back(vec);
		}
	}
	file.close();
}

void Graph::generateDegrees(const char* degPath){
	ifstream file;

	try{
		file.open(degPath, std::ifstream::in);
	}

	catch (int e){
		cout << "Error reading file." << endl;
		return;
	}

	std::string str;

	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, str);

			istringstream buf(str);
			istream_iterator<string> beg(buf), end;
			vector<string> tokens(beg, end);

			for (auto& s : tokens)
				degrees.push_back(str2dbl(s));
		}
	}
	file.close();
}


void Graph::generateDo(){
	vector<unsigned> temp;
	for (unsigned int i = 0; i < D.size(); i++){
		temp = D.at(i);
		sort(temp.begin(), temp.end());
		Do.push_back(vector<unsigned>(temp.begin(), temp.end()));
	}
}