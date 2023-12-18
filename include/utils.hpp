#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>

#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <stack>
#include <queue>
#include <list>

#include <numeric>
#include <type_traits>
#include <any>
#include <variant>
#include <optional>

#include <algorithm>

#include <memory>

#include <random>
#include <chrono>

typedef std::vector<int> Ints;
typedef std::vector<double> Doubles;
typedef std::vector<float> Floats;
typedef std::vector<std::string> Strings;

int rng(int min, int max) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

long long get_current_unix_timestamp_in_millisecond(){
    // example : 
    // input current datetime

    // https://www.epochconverter.com
    // Assuming that this timestamp is in milliseconds:
    // GMT: Monday, 18 December 2023 12:02:08.034
    // Your time zone: Monday, 18 December 2023 17:32:08.034 GMT+05:30

    // output : 1702900928034
    return  std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
}

constexpr std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> from_unix_time_in_millisecond(long long timestamp) {
    return std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>{std::chrono::milliseconds(timestamp)};
}

template<typename vector_type>
void print(const vector_type& vector){
    std::cout << std::endl;
    for(auto& element: vector){std::cout << " " << element;}
    std::cout << std::endl;
}

template<typename Sequence_type>
double sum_of_squared(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}
    return std::accumulate(data.cbegin(), data.cend(), 0.0, [](double total, double element) {
        return total + element * element;
    });
}

template<typename Sequence_type>
double mean(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}
    return std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
}

template <typename Sequence_type>
double median(const Sequence_type& data){
    if(data.empty()) {throw std::invalid_argument("Input vector cannot be empty");}
    Sequence_type seq_copy;
    std::transform(data.cbegin(), data.cend(), std::back_inserter(seq_copy), [](const auto& element){return element;});
    std::sort(seq_copy.begin(), seq_copy.end());
    size_t middleIndex = seq_copy.size() / 2;
    if(seq_copy.size() % 2 == 0){
        return (seq_copy[middleIndex] + seq_copy[middleIndex - 1]) / 2.0;
    }else{
        return seq_copy[middleIndex];
    }
}

template<typename Sequence_type>
double standard_deviation(const Sequence_type& data){
    if (data.empty()) {throw std::invalid_argument("Data vector cannot be empty");}

    // Calculate the mean of sequence.
    double mean_res = mean(data);
    Doubles squaredDeviations;
    std::for_each(data.cbegin(), data.cend(), [&mean_res, &squaredDeviations](double x) {
        squaredDeviations.push_back(std::pow(x - mean_res, 2));
    });

    // Calculate the variance from squared deviations.
    double variance = mean(squaredDeviations);

    // Calculate the Standard Deviation from variance.
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

template <typename Sequence_type>
double l1_regularization(const Sequence_type& data, double lambda) {
    if (data.empty()) {throw std::invalid_argument("Input vector cannot be empty");}

    // Calculate the sum of absolute elements.
    double sum_of_absolutes = std::accumulate(data.cbegin(), data.cend(), 0.0, [](double total, double element) {
        return total + std::abs(element);
    });

    // Calculate the L1 penalty.
    return lambda * sum_of_absolutes;

    // simple worked out example:
    // sequence {-5, 6, 7, 4, 3, 2, 1, 0}

    // |---------|-----------------|-------------|
    // | element |         squared | accumulated |
    // |     (A) | (B) = (A) * (A) |         (C) |
    // |---------|-----------------|-------------|
    // |      -5 |               5 |           5 |
    // |       6 |               6 |          11 |
    // |       7 |               7 |          18 |
    // |       4 |               4 |          22 |
    // |       3 |               3 |          25 |
    // |       2 |               2 |          27 |
    // |       1 |               1 |          28 |
    // |       0 |               0 |          28 |
    // |---------|-----------------|-------------|

    // l1_regularization = 28 * 0.1 = 2.8
}

template <typename Sequence_type>
double l2_regularization(const Sequence_type& data, double lambda) {
    if (data.empty()) {throw std::invalid_argument("Input vector cannot be empty");}

    // Calculate the sum of squared elements.
    double sum_of_squares = sum_of_squared(data);

    // Calculate the L2 penalty.
    return lambda * sum_of_squares / 2.0;

    // simple worked out example:
    // sequence {-5, 6, 7, 4, 3, 2, 1, 0}

    // |---------|-----------------|-------------|
    // | element |         squared | accumulated |
    // |     (A) | (B) = (A) * (A) |         (C) |
    // |---------|-----------------|-------------|
    // |      -5 |              25 |         25  |
    // |       6 |              36 |         61  |
    // |       7 |              49 |         110 |
    // |       4 |              16 |         126 |
    // |       3 |               9 |         135 |
    // |       2 |               4 |         139 |
    // |       1 |               1 |         140 |
    // |       0 |               0 |         140 |
    // |---------|-----------------|-------------|

    // l2_regularization = (140 * 0.1) / 2.0 = 14 / 2.0 = 7.0
}

template <typename Sequence_type>
double mean_squared_error(const Sequence_type& actual, const Sequence_type& predicted) {
    if (actual.size() != predicted.size() || actual.empty()) {throw std::invalid_argument("Input vectors must be equal in size and non-empty")}

    // Calculate the sum of squared differences
    double sum_of_squares = std::accumulate(actual.cbegin(), actual.cend(), 0.0, [&predicted](double total, double actual_value, size_t index) {
        double predicted_value = predicted.at(index);
        return total + (actual_value - predicted_value) * (actual_value - predicted_value);
    });

    // Calculate the MSE
    return sum_of_squares / actual.size();

    // simple worked out example:

    // sequence1 {-5.0, 6.0, 7.0, 4.0, 3.0, 2.0, 1.0, 0.0} : Actual values
    // sequence2 {-5.2, 6.1, 7.3, 4.1, 3.2, 2.1, 1.0, 0.0} : Predicted values

    // |-----------|-----------|-----------------|-----------------|-----------------------|-----------------------|-----------------|------------------|------------------------------|
    // | element_a | element_p |       squared_a |       squared_p | accumulated_squared_a | accumulated_squared_p |        diff_a_p | squared_diff_a_p | accumulated_squared_diff_a_p |
    // |       (A) |       (B) | (C) = (A) * (A) | (D) = (B) * (B) |                   (E) |                   (F) | (G) = (A) - (B) | (H) =  (G) * (G) |                          (I) |
    // |-----------|-----------|-----------------|-----------------|-----------------------|-----------------------|-----------------|------------------|------------------------------|
    // |        -5 |      -5.2 |              25 |           27.04 |                    25 |                 27.04 |             0.2 |             0.04 |                         0.04 |
    // |         6 |       6.2 |              36 |           37.21 |                    61 |                 64.25 |            -0.1 |             0.01 |                         0.05 |
    // |         7 |       7.3 |              49 |           53.29 |                   110 |                117.54 |            -0.3 |             0.09 |                         0.14 |
    // |         4 |       4.1 |              16 |           16.81 |                   126 |                134.35 |            -0.1 |             0.01 |                         0.15 |
    // |         3 |       3.2 |               9 |           10.24 |                   135 |                144.59 |            -0.2 |             0.04 |                         0.19 |
    // |         2 |       2.1 |               4 |            4.41 |                   139 |                149.00 |            -0.1 |             0.01 |                         0.20 |
    // |         1 |       1.0 |               1 |             1.0 |                   140 |                150.00 |             0.0 |             0.00 |                         0.20 |
    // |         0 |       0.0 |               0 |             0.0 |                   140 |                150.00 |             0.0 |             0.00 |                         0.20 |
    // |-----------|-----------|-----------------|-----------------|-----------------------|-----------------------|-----------------|------------------|------------------------------|

    // mse = 0.20 / 8.0 = 0.025
}

template <typename Sequence_type>
double root_mean_squared_error(const Sequence_type& actual, const Sequence_type& predicted) {
    if (actual.size() != predicted.size() || actual.empty()) {throw std::invalid_argument("Input vectors must be equal in size and non-empty")}

    // Calculate the sum of squared differences
    double mse = mean_squared_error(actual, predicted);
    return std::sqrt(mse);

    // simple worked out example:

    // sequence1 {-5.0, 6.0, 7.0, 4.0, 3.0, 2.0, 1.0, 0.0} : Actual values
    // sequence2 {-5.2, 6.1, 7.3, 4.1, 3.2, 2.1, 1.0, 0.0} : Predicted values

    // mse = 0.025
    // rmse = sqrt(0.025) = 
}

template <typename Sequence_type>
double mean_absolute_error(const Sequence_type& actual, const Sequence_type& predicted) {
    if (actual.size() != predicted.size() || actual.empty()) {throw std::invalid_argument("Input vectors must be equal in size and non-empty");}

    // Calculate the sum of absolute differences
    double sum_of_absolutes = std::accumulate(actual.cbegin(), actual.cend(), 0.0, [&predicted](double total, double actual_value, size_t index) {
        double predicted_value = predicted.at(index);
        return total + std::abs(actual_value - predicted_value);
    });

    // Calculate the MAE
    return sum_of_absolutes / actual.size();
}

template <typename Sequence_type>
double huber_loss(const Sequence_type& actual, const Sequence_type& predicted, double delta) {
    if (actual.size() != predicted.size() || actual.empty()) {throw std::invalid_argument("Input vectors must be equal in size and non-empty");}

    // Calculate the sum of losses
    double sum_of_losses = std::accumulate(actual.begin(), actual.end(), 0.0, [&predicted, delta](T total, T actual_value, size_t index) {
        double predicted_value = predicted.at(index);
        double absolute_difference = std::abs(actual_value - predicted_value);
        return total + ((absolute_difference <= delta) ? 0.5 * absolute_difference * absolute_difference : delta * (absolute_difference - 0.5 * delta));
    });

    // Calculate the average loss
    return sum_of_losses / actual.size();
}


#endif // UTILS_HPP