#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

typedef std::vector<double> Doubles;
typedef std::vector<float> Floats;
typedef std::vector<int> Ints;
typedef std::vector<std::string> Strings;
typedef std::vector<int> Ints;
typedef std::vector<std::string> Strings;

// template<typename vector_type>
// void print(const vector_type& vector);

// template<typename Sequence_type>
// double mean(const Sequence_type& data);

// template<typename Sequence_type>
// double standard_deviation(const Sequence_type& data);

// template<typename Sequence_type>
// Sequence_type normalise(const Sequence_type& data);

template<typename vector_type>
void print(const vector_type& vector){
    std::cout << std::endl;
    for(auto& element: vector){std::cout << " " << element;}
    std::cout << std::endl;
}

template<typename Sequence_type>
double mean(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}
    return std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
}

template<typename Sequence_type>
double standard_deviation(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}
    double mean_res = mean(data);
    Doubles squaredDeviations;
    std::for_each(data.cbegin(), data.cend(), [&mean_res, &squaredDeviations](double x) {
        squaredDeviations.push_back(std::pow(x - mean_res, 2));
    });
    double variance = mean(squaredDeviations);
    return sqrt(variance);
}

template<typename Sequence_type>
Sequence_type normalise(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}
    double data_mean = mean(data);
    double data_sd = standard_deviation(data);
    Sequence_type result;
    for(int i = 0; i < data.size(); i++){
        result.push_back((data.at(i) - data_mean) / data_sd);
    }
    return result;
}

#endif // UTILS_HPP