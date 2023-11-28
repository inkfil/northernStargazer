#include <utils.hpp>

class SimpleLinearRegression {
private:
  double a, b; // Parameters (intercept and slope)
  double alpha; int epoch; // Parameters (alpha and epoch)
  double x_mean, y_mean;
public:
    // SimpleLinearRegression() = delete;
    // SimpleLinearRegression(const SimpleLinearRegression& other) = delete;
    SimpleLinearRegression(double a, double b, double alpha, int epoch);
    ~SimpleLinearRegression();

    // template<typename Sequence_type>
    // void fit(const Sequence_type& x_data, const Sequence_type& y_data);

    template<typename Sequence_type>
    void fit(const Sequence_type& x_data, const Sequence_type& y_data){
        x_mean = mean(x_data);
        y_mean = mean(y_data);

        Sequence_type x_norm = normalise(x_data);
        Sequence_type y_norm = normalise(y_data);

        for(int i = 0; i < epoch; i++){
            double a_grad = 0.0, b_grad = 0.0;

            for(int j = 0; j < x_data.size(); j++){
                double h = a + b * x_norm[j];
                double error = y_norm[j] - h;

                a_grad += error;
                b_grad += x_norm[j] * error;
            }

            a_grad /= x_data.size();
            b_grad /= x_data.size();

            a -= alpha * a_grad;
            b -= alpha * b_grad;
        }
    }

    double predict(double x);
};