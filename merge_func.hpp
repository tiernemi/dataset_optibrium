#ifndef MERGE_FUNC_HPP_A870DWHM
#define MERGE_FUNC_HPP_A870DWHM

#include "dataset.hpp"

enum MERGE_MODES { 
	MERGE_D1_PREF,
	MERGE_D2_PREF,
	MERGE_ASK_USER
} ;

template <typename keyType1, typename... dataTypes1, typename keyType2, 
		 typename... dataTypes2, typename newKeyType, typename... newDataTypes>
bool mergeDatasets(const Dataset<keyType1,dataTypes1...> & dataset1, 
	const Dataset<keyType2,dataTypes2...> & dataset2, Dataset<newKeyType,newDataTypes...> & newDat,
	int mode = MERGE_D1_PREF) {

	newDat.clear() ;
	// Get overlapping fields. //
	std::unordered_map<std::string,int> newFieldMap = newDat.getFields() ;
	std::string keyField = newDat.getKeyField() ;	
	std::unordered_map<std::string,int> d1FieldMap = dataset1.getFields() ;
	std::unordered_map<std::string,int> d2FieldMap = dataset2.getFields() ;

	if (newFieldMap.find(keyField) == newFieldMap.end()) {
		return false ;
	}

	if (mode == MERGE_D1_PREF) {
		for (int i = 0 ; i < dataset1.getNumMembers() ; ++i) {
			std::tuple<newDataTypes...> temp ;
			auto data = dataset1.getDataByIndex(i) ;
			for (auto j = newFieldMap.begin() ; j != newFieldMap.end() ; ++j) {
				int indexND = (*j).second ;
				decltype(d1FieldMap)::iterator iter ; 
				if ((iter = d1FieldMap.find((*j).first)) != d1FieldMap.end()) {
					int indexD1 = (*iter).second ;
					auto oldData = get(indexD1,data) ;
					set(indexND,temp,oldData) ; 
				} else {
					set(indexND,temp,NULL) ; 
				}
			}
			newDat.insert(temp) ;
		}

		for (int i = 0 ; i < dataset2.getNumMembers() ; ++i) {
			std::tuple<newDataTypes...> temp ;
			auto data = dataset2.getDataByIndex(i) ;
			for (auto j = newFieldMap.begin() ; j != newFieldMap.end() ; ++j) {
				int indexND = (*j).second ;
				decltype(d2FieldMap)::iterator iter ; 
				if ((iter = d2FieldMap.find((*j).first)) != d2FieldMap.end()) {
					int indexD2 = (*iter).second ;
					auto oldData = get(indexD2,data) ;
					set(indexND,temp,oldData) ; 
				} else {
					set(indexND,temp,NULL) ; 
				}
			}
			newDat.insert(temp) ;
		}
	} else if (mode == MERGE_D2_PREF) {
		for (int i = 0 ; i < dataset2.getNumMembers() ; ++i) {
			std::tuple<newDataTypes...> temp ;
			auto data = dataset2.getDataByIndex(i) ;
			for (auto j = newFieldMap.begin() ; j != newFieldMap.end() ; ++j) {
				int indexND = (*j).second ;
				decltype(d2FieldMap)::iterator iter ; 
				if ((iter = d2FieldMap.find((*j).first)) != d2FieldMap.end()) {
					int indexD2 = (*iter).second ;
					auto oldData = get(indexD2,data) ;
					set(indexND,temp,oldData) ; 
				} else {
					set(indexND,temp,NULL) ; 
				}
			}
			newDat.insert(temp) ;
		}

		for (int i = 0 ; i < dataset1.getNumMembers() ; ++i) {
			std::tuple<newDataTypes...> temp ;
			auto data = dataset1.getDataByIndex(i) ;
			for (auto j = newFieldMap.begin() ; j != newFieldMap.end() ; ++j) {
				int indexND = (*j).second ;
				decltype(d1FieldMap)::iterator iter ; 
				if ((iter = d1FieldMap.find((*j).first)) != d1FieldMap.end()) {
					int indexD1 = (*iter).second ;
					auto oldData = get(indexD1,data) ;
					set(indexND,temp,oldData) ; 
				} else {
					set(indexND,temp,NULL) ; 
				}
			}
			newDat.insert(temp) ;
		}
	} 
}

template <typename keyType1, typename... dataTypes1, typename keyType2, 
		 typename... dataTypes2, typename newKeyType, typename... newDataTypes>
void getIntersection(const Dataset<keyType1,dataTypes1...> & dataset1,
	const Dataset<keyType2,dataTypes2...> & dataset2, Dataset<newKeyType,newDataTypes...> & newDat) {
	newDat.clear() ;

	for (int i = 0 ; i < dataset1.getNumRows() ; ++i) {
		auto key = dataset1.getKey(i) ;
		if (dataset2.searchDataset(key)) {
		}
	}
}



#endif /* end of include guard: MERGE_FUNC_HPP_A870DWHM */
