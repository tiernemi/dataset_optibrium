#ifndef DATASET_HPP_JUU0HODF
#define DATASET_HPP_JUU0HODF

/*
 * =====================================================================================
 *
 *       Filename:  dataset.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/07/16 21:52:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Tierney (MT), tiernemi@tcd.ie
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <tuple>
#include <iostream>
#include "tuple_m.hpp"

/* 
 * ===  CLASS  =========================================================================
 *         Name:  Dataset
 *       Fields:  
 *  Description:  
 * =====================================================================================
 */

template <typename keyType, typename... dataTypes>
class Dataset {
 public:
	typedef typename std::tuple<dataTypes...> storedType ;
 public:
	Dataset(const std::vector<std::string> & fields, int key) ;
	bool insert(const storedType & input) ;
	template <typename setType>
	bool setFieldByIndex(const std::string & field, int rowNum, const setType & var) ;
	const keyType & getKey(int index) ;
	storedType & getDataByIndex(int index) ;
	storedType & getDataByKey(keyType key) ;
	const storedType & getDataByIndex(int index) const ;
	const storedType & getDataByKey(keyType key) const ;
	void printData(std::ostream & output) ;
	bool searchDataset(keyType key) ;
	const std::unordered_map<std::string,int> & getFields() const { return fields ; } ;
	int getNumMembers() const { return map.size() ; } ;
	int getNumFields() const { return fields.size() ; } ;
	int getKeyIndex() const { return keyIndex ; } ;
	std::string getKeyField() const { return keyField ; } ;
	void clear() ;
 private:
	int keyIndex ;
	std::string keyField ;
	std::unordered_map<std::string,int> fields ;
	std::unordered_map<keyType,storedType> map ;
} ;		/* -----  end of class Dataset  ----- */


template <typename keyType, typename... dataTypes>
Dataset<keyType,dataTypes...>::Dataset(const std::vector<std::string> & fields, int key) {
	for (int i = 0 ; i < fields.size() ; ++i) {
		this->fields.insert(std::pair<std::string,int>(fields[i],i)) ;
	}
	keyIndex = key ;
	keyField = fields[key] ;
}


template <typename keyType, typename... dataTypes>
template <typename setType>
bool Dataset<keyType,dataTypes...>::setFieldByIndex(const std::string & field, int rowNum, const setType & var) {
	typename decltype(fields)::iterator iter ;
	if ((iter = fields.find((field))) != fields.end()) {
		int colIndex = (*iter).second ;
		if (colIndex == keyIndex) {
			if (map.find(var) != map.end()) {
				return false ;
			}
			auto rowLoc = map.begin() ;
			std::advance(rowLoc,rowNum) ;
			keyType oldKey = (*rowLoc).first ;
			set(colIndex,(*rowLoc).second, var) ;
			storedType tempTuple = (*rowLoc).second ;
			map.erase(oldKey) ;
			map[var] = tempTuple ;
		} else {
			auto rowLoc = map.begin() ;
			std::advance(rowLoc,rowNum) ;
			set(colIndex,(*rowLoc).second, var) ;
			return true ;
		}
	} else {
		return false ;
	}
}


template <typename keyType, typename... dataTypes>
bool Dataset<keyType,dataTypes...>::searchDataset(keyType key) {
	if (map.find(key) != map.end()) {
		return true ;
	} else {
		return false ;
	}
}

template <typename keyType, typename... dataTypes>
const keyType & Dataset<keyType,dataTypes...>::getKey(int index) {
	auto iter = map.begin() ;
	std::advance(iter,index) ;
	return (*iter).first ;
}

template <typename keyType, typename... dataTypes>
std::tuple<dataTypes...> & Dataset<keyType,dataTypes...>::getDataByIndex(int index) {
	auto iter = map.begin() ;
	std::advance(iter,index) ;
	return (*iter).second ;
}


template <typename keyType, typename... dataTypes>
std::tuple<dataTypes...> & Dataset<keyType,dataTypes...>::getDataByKey(keyType key) {
	return map.at(key) ;
}

template <typename keyType, typename... dataTypes>
const std::tuple<dataTypes...> & Dataset<keyType,dataTypes...>::getDataByIndex(int index) const {
	auto iter = map.begin() ;
	std::advance(iter,index) ;
	return (*iter).second ;
}

template <typename keyType, typename... dataTypes>
const std::tuple<dataTypes...> & Dataset<keyType,dataTypes...>::getDataByKey(keyType key) const {
	return map.at(key) ;
}


template <typename keyType, typename... dataTypes>
bool Dataset<keyType,dataTypes...>::insert(const storedType & input) {
	keyType key = boost::get<keyType>(get(keyIndex,input)) ;
	return map.insert(std::pair<keyType,storedType>(key, input)).second ;
}

template <typename keyType, typename... dataTypes>
void Dataset<keyType,dataTypes...>::printData(std::ostream & output) {
	// Reorder Fields. //
	std::vector<std::string> fieldVec(getNumFields()) ;
	for (auto i = fields.begin(); i != fields.end(); ++i) {
		fieldVec[(*i).second] = (*i).first ;
	}
	for (int i = 0 ; i < fieldVec.size() ; ++i) {
		output << fieldVec[i] << '\t' ;
	}
	output << std::endl ;

	// Output data. //
	for (auto i = map.begin() ; i != map.end() ; ++i) {
		for (int j = 0 ; j < std::tuple_size<storedType>::value ; ++j) {
			output << get(j,(*i).second) << '\t' ;
		}
		output << std::endl ;
	}
	output << std::endl ;
}

template <typename keyType, typename... dataTypes>
void Dataset<keyType,dataTypes...>::clear() {
	map.clear() ;
}

#endif /* end of include guard: DATASET_HPP_JUU0HODF */
