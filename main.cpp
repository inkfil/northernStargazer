#include <iostream>
#include <string>
#include <vector>

#include <utils.hpp>
#include <SimpleLinearRegression.hpp>

int main(){

    Doubles x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
    Doubles y_data = {2.0, 4.0, 6.0, 8.0, 10.0};

    double a, b, alpha, epoch;

    SimpleLinearRegression slr(a, b, alpha, epoch);

    slr.fit(x_data, y_data);

    std::cout << slr.predict(6.0);

    return 0;
}