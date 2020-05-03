#include <time.h>

#include "bellman_algorithms.hpp"


//test
//it is templated with representation of graph. Arguments that are passed:
//@loops - how many times the algorithm will solve objects with the same parameters(the more the more accurate outcome)
//@verTab,@densTab - parameters of objects that will be created

template<typename T>
std::ostream& tests(std::ostream& file, int (&vertTab)[5], double (&densTab)[4], int loops) {

	for (double density : densTab) { //for each density
		for (int vertices : vertTab) { //for each amount of vertices
			double sum = 0;
			for (int iLoops = 0; iLoops < loops; ++iLoops) { //as many times as loops variable was set

				std::shared_ptr<T> graph = std::make_shared<T>(vertices, density); //creating appropriate object
				int startNode = rand() % vertices; //generating rand starting node

				graph->fillGraph(true); //fill graph with loops possibility

				sum += bellmanFord(std::move(graph), startNode, false); //bellman returning time of execution
				std::cout << (iLoops * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			file << sum / loops << " "; //saving the average
			std::cout << vertices << " VERTICES DONE!" << std::endl;
		}
		std::cout << "\n" << density << " DENISTY DONE!\n" << std::endl;
	}
	file << "\n";
	return file;
}


int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	// TEST ZONE //

		/////////////////////////
		// changeable variables//
		int vertTab[5] = {5, 15, 30, 50, 100}; //amounts of vertices to be tested
		double densTab[4] = {0.25, 0.5, 0.75, 1}; //densities to be tested
		int loops = 100;		// how many times the algorithm will solve objects with the same parameters
		/////////////////////////

		std::ofstream file("OutputTimes.txt");
		if (!file.is_open()) {

			std::cerr << "OUTPUT TIMES NOT OPEN!" << std::flush;
			return 1;
		}

		tests<ListGraph>(file, vertTab, densTab, loops); //testing for List
		std::cout << "LIST DONE\n" << std::endl;
		tests<MatrixGraph>(file, vertTab, densTab, loops);	//testing for Matrix
		std::cout << "MATRIX DONE" << std::endl;

		file.close();
		return 0;
}
