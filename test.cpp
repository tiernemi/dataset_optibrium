#include "dataset.hpp"
#include "merge_func.hpp"

int main(int argc, char *argv[]) {
	
	std::string ids("ID") ;
	std::string names("Molecule") ;
	std::string solubility("Sol") ;
	std::string molec("RMM") ;
	std::string color("Color") ;
	std::vector<std::string> fields1 = {ids,names, solubility, molec} ;
	Dataset<int,int,std::string,float,int> dataset1(fields1, 0) ;


	std::tuple<int,std::string,float,int> data11(1, "Paracetemol", 4.97, 151) ;
	std::tuple<int,std::string,float,int> data12(2, "Caffeine", 5.05, 194) ;
	std::tuple<int,std::string,float,int> data13(3, "Indomethacin", 0.4, 358) ;
	std::tuple<int,std::string,float,int> data14(4, "Trimethoprim", 3.14, 290) ;
	dataset1.insert(data11) ;
	dataset1.insert(data12) ;
	dataset1.insert(data13) ;
	dataset1.insert(data14) ;
	dataset1.printData(std::cout) ;

	std::vector<std::string> fields2 = {ids, names, molec, color} ;
	Dataset<int,int,std::string,int,std::string> dataset2(fields2,0) ;
	std::tuple<int,std::string,int,std::string> data21(2, "Caffeine", 194, "Brown") ;
	std::tuple<int,std::string,int,std::string> data22(5, "Benzine   ", 200, "Green") ;
	std::tuple<int,std::string,int,std::string> data23(6, "Arsenic   ", 130, "White") ;
	dataset2.insert(data21) ;
	dataset2.insert(data22) ;
	dataset2.insert(data23) ;
	dataset2.printData(std::cout) ;

	std::vector<std::string> fields3 = {ids, names, solubility, molec, color} ;
	Dataset<int,int,std::string,float,int,std::string> dataset3(fields3, 0) ;

	mergeDatasets(dataset1,dataset2,dataset3,MERGE_D1_PREF) ;

	dataset3.printData(std::cout) ;
	
	return 0;
}
