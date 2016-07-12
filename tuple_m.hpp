#ifndef TUPLE_M_HPP_VNRS3UBI
#define TUPLE_M_HPP_VNRS3UBI

#include <tuple>
#include <stdexcept>
#include <boost/variant.hpp>

template <size_t N, typename... dataTypes>
boost::variant<dataTypes...> getElement(size_t i, const std::tuple<dataTypes...> & tup) {
    if (i == N) {
        return std::get<N>(tup) ;
	} else if (N == sizeof...(dataTypes) - 1) {
        throw std::out_of_range("Tuple element out of range.") ;
	}
    else {
		// Go further
        return getElement<(N < sizeof...(dataTypes)-1 ? N+1 : 0)>(i, tup) ;
	}
}

template <typename... dataTypes>
boost::variant<dataTypes...> get(size_t i, const std::tuple<dataTypes...> & tup) {
    return getElement<0>(i, tup);
}

template <size_t N, typename... dataTypes, typename inputType>
void setElement(size_t i, std::tuple<dataTypes...> & tup, const inputType & input) {// const boost::variant<dataTypes...> & input) {
    if (i == N) {
        std::get<N>(tup) = input; // boost::get<typename std::tuple_element<N,std::tuple<dataTypes...>>::type>(input) ;
	} else if (N == sizeof...(dataTypes) - 1) {
        throw std::out_of_range("Tuple element out of range.") ;
	}
    else {
		// Go further
        setElement<(N < sizeof...(dataTypes)-1 ? N+1 : 0)>(i, tup, input) ;
	}
}

template <typename... dataTypes, typename inputType>
void set(size_t i, std::tuple<dataTypes...> & tup, const inputType & var) {
    setElement<0>(i, tup, var);
}

// Variant overloads. //

template <size_t N, typename... dataTypes, typename... inputTypes>
void setElement(size_t i, std::tuple<dataTypes...> & tup, const boost::variant<inputTypes...> & input) {// const boost::variant<dataTypes...> & input) {
    if (i == N) {
        std::get<N>(tup) = boost::get<typename std::tuple_element<N,std::tuple<dataTypes...>>::type>(input) ;
	} else if (N == sizeof...(dataTypes) - 1) {
        throw std::out_of_range("Tuple element out of range.") ;
	}
    else {
		// Go further
        setElement<(N < sizeof...(dataTypes)-1 ? N+1 : 0)>(i, tup, input) ;
	}
}

template <typename... dataTypes, typename... inputTypes>
void set(size_t i, std::tuple<dataTypes...> & tup, const boost::variant<inputTypes...> & var) {
    setElement<0>(i, tup, var);
}



#endif /* end of include guard: TUPLE_M_HPP_VNRS3UBI */
