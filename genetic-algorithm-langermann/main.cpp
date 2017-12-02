#include <cstdio>
#include "GA_template_flow.h"
#include "function.h"
#include <iostream>
#include <iomanip>   
#include <conio.h>

using IndividualType = CIndividual<double, 2>;
using PopulationType = CPopulation<IndividualType>;

void fitness(PopulationType& population)
{
	//find minimum value
	double minValue = std::numeric_limits<double>::max();
	std::vector<double> fitness;
	fitness.reserve(population.size());

	for (auto& i : population) {
		auto eval = i.evaluate();
		fitness.push_back(-eval);
		if (minValue > eval) {
			minValue = eval;
		}
	}     

	for (auto i = 0U; i < population.size(); ++i) {
		population.individual(i).fitness(fitness.at(i));
	}
}

int main(int argc, char **argv)
{
	double minError = 0;
	size_t minErrorsCount;
	std::vector<double> debugMinErrors;
    std::cout.precision(8);
    std::setprecision(8);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
	auto terminateFn = [&debugMinErrors, &minErrorsCount, &minError](const PopulationType& population, size_t generationNumber_) -> bool {
		double err = 0;
		double min_err = INT_MAX;
        double avrFitness = 0.0f;

		for (const auto &i : population) {
			err = (i.evaluate());
            avrFitness += err;
			if (err < min_err)
				min_err = err;
		}

        std::cout << std::endl << "POPULATION EVOLVED: NEW AVERAGE FITNESS IS : " << -avrFitness / population.size() << " size: " << population.size() << std::endl << std::endl;

        std::cout << "Press any key to continue..." << std::endl;
        //getchar();

		if (minError != min_err)
			minErrorsCount = 0;
		minError = min_err;
		minErrorsCount++;
		debugMinErrors.push_back(min_err);
		return (generationNumber_ > 1000) || (minErrorsCount > 100);
	};
    /*[](const IndividualType& individual) -> float {
        return - cosf(individual.genes()[0]) * cosf(individual.genes()[1]) * exp(-(individual.genes()[0] - 3.14f)*(individual.genes()[0] - 3.14f) - (individual.genes()[1] - 3.14f) * (individual.genes()[1]  - 3.14f));
        //return sinf(individual.genes()[0]) * cosf(individual.genes()[1]); //for test
        }*/


    CGeneticAlgorithm<IndividualType> ga(DeJong<IndividualType>);
	CGenericGeneticAlgorithm<IndividualType> * gap = &ga;
	if (gap->init(-5.12f, 5.12f, 100))
	{
		int result = gap->evolve(1.0f, 0.1f, 10, fitness, terminateFn, 0.1f);
		switch (result)
		{
		case errInvalidCrossProbability:
			std::cout << "Invalid cross probability";
			break;
		case errInvalidMutateProbability:
			std::cout << "Invalid mutate probability";
			break;
		case errInvalidOffspring:
			std::cout << "Invalid offspring";
			break;
		case errInvalidMutationRange:
			std::cout << "Invalid mutation range";
			break;
		default:
			std::cout << "population evolved in " << ga.generationNumber() << " generation! " << std::endl;
			break;
		}
		
	}
}
