#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>
#include <iterator>

enum evolveErrors
{
	errUnknown = -1000,
	errInvalidCrossProbability,
	errInvalidMutateProbability,
	errInvalidOffspring,
	errInvalidMutationRange
};
template <typename IndividualType>
using IndividualFuncType = std::function<double(const IndividualType&)>;


template <typename GeneType = double, int NumGenes = 2>
class CIndividual
{
public:
    CIndividual(const CIndividual& other) {
        genes_.assign(other.genes_.begin(), other.genes_.end());
        minGen_ = other.minGen_;
        maxGen_ = other.maxGen_;
        evaluateFn_ = other.evaluateFn_;
        fitness_ = other.fitness_;
		selected_ = other.selected_;
    }

    CIndividual& operator = (const CIndividual& other) {
        genes_.assign(other.genes_.begin(), other.genes_.end());
        minGen_ = other.minGen_;
        maxGen_ = other.maxGen_;
        evaluateFn_ = other.evaluateFn_;
        fitness_ = other.fitness_;
		selected_ = other.selected_;

        return *this;
    }

    CIndividual(const double& minGenVal, const double&  maxGenVal, const IndividualFuncType<CIndividual<GeneType, NumGenes>>& fn)
		: minGen_(minGenVal), maxGen_(maxGenVal), evaluateFn_(fn), fitness_(0.0f), selected_(false) {
        genes_.resize(NumGenes);
    }

    void generate() {
        static std::random_device device;
        static std::mt19937 range(device());

        std::uniform_real_distribution<double> distribution(minGen_, maxGen_);

        for (auto i = 0U; i < NumGenes; ++i) {
            genes_[i] = distribution(range);
        }
    }
    double evaluate() const {
        return evaluateFn_(*this);
    }

    const std::vector<GeneType>& genes() const {
        return genes_;
    }

    void fitness(const double& fitness) {
        fitness_ = fitness;
    }

    const double& fitness() const {
        return fitness_;
    }

    CIndividual cross(const CIndividual& other) const {
        static std::random_device device;
        static std::mt19937 range(device());

        std::uniform_real_distribution<double> distribution(0, 1.0f);

        CIndividual tmp(*this);

        for (auto i = 0U; i < genes_.size(); ++i) {
            double a = distribution(range);
            tmp.genes_[i] = tmp.genes_[i] * a + other.genes_[i] * (1.0f - a);
        }

        return tmp;
    }

    void mutate(double r, double k) {
        static std::random_device device;
        static std::mt19937 range(device());

        std::uniform_int_distribution<int> distribution(0, 1);
        std::uniform_real_distribution<double> distribution2(0, 1.0f);
		//not exactly real valued mutation, but close to it, and better in my opinion
        for (auto i = 0.0f; i < genes_.size(); ++i) {
            double a = double(distribution(range));
			double b = pow(2.0f, -distribution2(range) * k);
			double c = (1.0f - (a * 2.0f));
			genes_[int(i)] = genes_[int(i)] + r * c *  k  * b;
        }
    }
	bool selected() const {
		return selected_;
	}

	void selected(bool val) const {
		selected_ = val;
	}

	friend std::ostream& operator<< (std::ostream& os, const CIndividual & obj)
	{
		for (size_t i = 0; i < obj.genes_.size(); ++i)
			os << "genes[" << i << "] = " << obj.genes_[i] << " ";
        //they are same for all, but still - its properties of Individual so they belong here
 		//os << "min:" << obj.minGen_;
		//os << "max:" << obj.maxGen_;
		os << " fitness: " << obj.fitness_;
		os << std::endl;
		return os;
	}
private:
    std::vector<GeneType> genes_;
    IndividualFuncType<CIndividual<GeneType, NumGenes>> evaluateFn_;
    double minGen_, maxGen_;
    double fitness_;
	mutable bool selected_;
};


template <typename PopulationType>
using FitnessFuncType = std::function<void(PopulationType&)>;

template <typename PopulationType>
using TerminationFuncType = std::function<bool(const PopulationType&, size_t)>;

template <typename IndividualType>
class CPopulation
{
public:
    CPopulation(const CPopulation<IndividualType>& other) {
        population_.assign(other.population_.begin(), other.population_.end());
        evaluateFn_ = other.evaluateFn_;
    };

    CPopulation& operator = (const CPopulation<IndividualType>& other) {
        population_.assign(other.population_.begin(), other.population_.end());
        evaluateFn_ = other.evaluateFn_;

        return *this;
    }

    CPopulation(const IndividualFuncType<IndividualType>& evaluateFn)
        : evaluateFn_(evaluateFn)
    {
    }

    typename std::vector<IndividualType>::iterator begin() {
        return population_.begin();
    }

    typename std::vector<IndividualType>::iterator end() {
        return population_.end();
    }

    typename std::vector<IndividualType>::const_iterator begin() const {
        return population_.begin();
    }

    typename std::vector<IndividualType>::const_iterator end() const {
        return population_.end();
    }

    void addIndividual(const IndividualType& individual) {
        population_.push_back(individual);
    }

    CPopulation<IndividualType> copy(size_t numIndividuals) const {
        CPopulation<IndividualType> tmp(evaluateFn_); //rvo
        const size_t numIndividualsToCopy = std::min(population_.size(), numIndividuals);
        tmp.population_.assign(population_.begin(), population_.begin() + numIndividualsToCopy);
        return tmp;
    }

    void merge(const CPopulation<IndividualType>& other) {
        population_.insert(population_.end(), other.population_.begin(), other.population_.end());
    }

    void sort() {
        std::sort(population_.begin(), population_.end(),
            [](const IndividualType& left, const IndividualType& right) -> double {
            return left.fitness() > right.fitness();
        }
        );
    }

    void generate(const double& minGeneVal, const double& maxGeneVal, const size_t& size) {
        for (auto i = 0U; i < size; ++i) {
            IndividualType individual(minGeneVal, maxGeneVal, evaluateFn_);
            individual.generate();
            population_.push_back(individual);
        }
    }

    const IndividualType& tournamentSelect(const size_t& K) const {
        static std::random_device device;
        static std::mt19937 range(device());

        std::uniform_int_distribution<int> distribution(0, population_.size() - 1);

        double bestFitness = std::numeric_limits<double>::min();
        size_t winner = 0;

        for (auto i = 0U; i < K; ++i) {
            auto id = distribution(range);

            auto& fitness = population_[id].fitness();
			if (fitness > bestFitness && !population_[id].selected()) {
                winner = id;
                bestFitness = fitness;
            }
        }

		population_[winner].selected(true);
		return population_[winner];
    }

    void killAll() {
        population_.clear();
    }

    size_t size() const {
        return population_.size();
    }

    IndividualType& individual(const size_t& i) {
        return population_.at(i);
    }

    const IndividualType& individual(const size_t& i) const {
        return population_.at(i);
    }

	const IndividualType& operator[] (const size_t& i) const {
		return population_.at(i);
	}

private:
    IndividualFuncType<IndividualType> evaluateFn_;
    std::vector<IndividualType> population_;
};
//abstract class - not really needed here, but I HAD TO make use of abstract classes and inheritance, so...
class CGeneticAlgorithmInterface
{
public:
	virtual bool init(const double& minGeneVal, const double& maxGeneVal, const size_t& size) = 0;
};
template <typename IndividualType>
class CGenericGeneticAlgorithm : public CGeneticAlgorithmInterface
{
public:
	virtual int evolve(const double& crossProbability, const double& mutateProbabillity, const size_t& offspringK,
		const FitnessFuncType<CPopulation<IndividualType>>& fitnessFn,
		const TerminationFuncType<CPopulation<IndividualType>>& terminationFn, double mutationRange)
	{
		return 0;
	}
};
template <typename IndividualType>
class CGeneticAlgorithm : public CGenericGeneticAlgorithm<IndividualType> {
public:
    CGeneticAlgorithm(const CGeneticAlgorithm&) = delete;
    CGeneticAlgorithm& operator = (const CGeneticAlgorithm&) = delete;

	CGeneticAlgorithm(const IndividualFuncType<IndividualType>& evalFn)
		: population_(evalFn), offspringPool_(evalFn), generationNumber_(0)
    {

    }

    bool init(const double& minGeneVal, const double& maxGeneVal, const size_t& size)
	{
		bool result = true;
		try
		{
			population_.generate(minGeneVal, maxGeneVal, size);
		}
		//example of exception handling - also just as an example of catching
		//going from specific exceptions to generic
		catch (const std::bad_alloc &) {
			result = false;
		}
		catch (const std::exception &) {
			result = false;
		}
		catch (...) {
			result = false;
		}
		return result;
    }
	inline size_t generationNumber() { return generationNumber_; }
    int evolve(const double& crossProbability, const double& mutateProbabillity, const size_t& offspringK,
        const FitnessFuncType<CPopulation<IndividualType>>& fitnessFn,
        const TerminationFuncType<CPopulation<IndividualType>>& terminationFn,double mutationRange)
	{
		if (crossProbability < 0)
			return evolveErrors::errInvalidCrossProbability;
		if (mutateProbabillity < 0)
			return evolveErrors::errInvalidMutateProbability;
		if (offspringK == 0)
			return evolveErrors::errInvalidOffspring;
		if (mutationRange == 0)
			return evolveErrors::errInvalidMutationRange;
        //evaluate initial fitness

        fitnessFn(population_);

		while (!terminationFn(population_, generationNumber_)) {
            offspringPool_.killAll();
			generationNumber_++;
            const auto& totalOffsprings = population_.size() * offspringK;
            
            while (offspringPool_.size() < totalOffsprings) {
				const IndividualType& individual1 = population_.tournamentSelect(population_.size() / 4);
                const IndividualType& individual2 = population_.tournamentSelect(population_.size() / 4);


                IndividualType offspring1 = individual1.cross(individual2);
                IndividualType offspring2 = individual2.cross(individual1);

				offspring1.selected(false);
				offspring2.selected(false);

				offspring1.mutate(mutateProbabillity, mutationRange);
				offspring2.mutate(mutateProbabillity, mutationRange);

                offspringPool_.addIndividual(offspring1);
                offspringPool_.addIndividual(offspring2);

				individual1.selected(false);
				individual2.selected(false);

            }

            fitnessFn(offspringPool_);
			for (const auto& i : population_) {
				offspringPool_.addIndividual(i);
			}
            offspringPool_.sort();
            auto size = population_.size();
            population_ = offspringPool_.copy(size);
			//here we output every population
            std::cout << " "; 
			for (auto const& poolElement : population_)
				std::cout << poolElement << ' ';
			std::cout << "-------------------------------------";
        }
		return generationNumber_;
    } 
private:
    CPopulation<IndividualType> population_;
    CPopulation<IndividualType> offspringPool_;
	size_t generationNumber_;
};