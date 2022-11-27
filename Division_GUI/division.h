#ifndef DIVISION_H
#define DIVISION_H

#include <vector>
#include <iostream>
#include <memory>

template<typename T>
size_t finder(const std::vector<T>& vect); // find the first non-zero term's index


class Denom
{
public:
    Denom(const std::vector<double>& v1, int max) { denominator = v1; this->max = max; }
    double& operator[](size_t i);
    size_t getSize()const { return denominator.size(); }
    double getElement()const; // extract non-zero element
    void print()const;
    std::vector<double> getDenominator()const { return denominator; }
private:
    std::vector<double>denominator;
    int max{};
};


class Numerator
{
public:
    Numerator(const std::vector<double>& v1, int temp, int max)
    {
        numerator = v1;
        repetition = temp;
        this->max = max;
    }
    Numerator& operator/(Denom&);// does the heavy lifting
    void print()const;
    std::vector<double> getNumerator()const { return numerator; }
    std::vector<double> getAnswer()const { return answer; }

private:
    std::vector<double>numerator;
    std::vector<double>answer;
    int repetition{}, max{};
};


class PowerComputation
{
public:
    PowerComputation(std::shared_ptr<Numerator>num, std::shared_ptr<Denom>denom);// take in pointers
    friend std::ostream& operator<<(std::ostream& output, const PowerComputation&);
private:
    std::shared_ptr<Numerator>num;
    std::shared_ptr<Denom>denom;
};

#endif // DIVISION_H
