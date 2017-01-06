#include "Algorithm.h" 
#include "Timer.h" 
  


int main(int argc, char *argv[]){
	string filePath;
	Timer tmr;

	if (argc != 5){
		cout << "Wrong number of arguments. Please pass four filepaths as argument." << endl;
		cout << "Argument 1 - path to distances file of Graph 1." << endl;
		cout << "Argument 2 - path to degrees file of Graph 1." << endl;
		cout << "Argument 3 - path to distances file of Graph 2." << endl;
		cout << "Argument 4 - path to degrees file of Graph 2." << endl;
		cin.get();
		return 1;
	}

	
			
	Algorithm alg = Algorithm(argv[1], argv[2], argv[3], argv[4]);
	
	//Calcula o tempo do algoritmo rodando de fato!
	tmr.reset();
	
	alg.run();

	double t = tmr.elapsed();
    std::cout << "Execution time: " << t << " seconds" << std::endl;	


	return 0;
}
