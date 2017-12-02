#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

template <class T>
double Langermannz(const T & individual)
{
    //The recommended values of m, c and A, as given by Molga & Smutnicki (2005) 
    const double A[5][2] = {{3.0, 5.0}, {5.0, 2.0}, {2.0, 1.0}, {1.0, 4.0}, {7.0, 9.0}};
    const double c[5] = {1.0, 2.0, 5.0, 2.0, 3.0};
    const unsigned d = 2;

    const unsigned m = 5;

    double ret = 0.0;
    for (unsigned i(0); i < m; ++i)
    {
        double s = 0.0;
        for (unsigned j = 0; j < d; ++j)
            s += std::pow(individual.genes()[0] - A[i][j], 2.0);

		auto cos = std::cos(M_PI * s);
		auto exp = std::exp(- s / M_PI);
		ret += double(c[i] * exp * cos);
    }
	
    return  -ret;
}
template <class T>
double testFunc(const T & individual)
{
    return abs(individual.genes()[0] + individual.genes()[1]);
}
template <class T>
double DeJong(const T & individual)
{
    size_t n = 2;
    double ret = 0;
    for (unsigned i(0); i < n; ++i)
    {
        ret += (individual.genes()[i] * individual.genes()[i]);
    }
    return ret;
}