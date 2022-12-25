#ifndef DIVISION_H
#define DIVISION_H

#include <vector>
#include <iostream>
#include <memory>
#include <QDebug>

template<typename T>
size_t finder(const std::vector<T>& vect); // find the first non-zero term's index

/**
 * @brief operator - Overloaded function for subtracting lists of the same length(member wise).
 * @param lhs List1
 * @param rhs List2
 * @return result of List1 - List2, if the lists are not the same size then it will return empty
 * list.
 */
QList<double> operator-(const QList<double>& lhs, const QList<double>& rhs);

/**
 * @brief operator * Overloaded function for multiplying lists with double(member wise).
 * @param multiplier
 * @param rhs
 * @return The multiplied result.
 */
QList<double> operator*(double multiplier, const QList<double>& rhs);

/**
 * @brief operator / Overloaded for dividing a list with a double(member wise).
 * @param num List
 * @param denom A number to perform division
 * @return The list divided by the denom argument
 */
QList<double> operator/(const QList<double> &num, double denom);

class Divisor{
public:
    void setParameters(const QList<double>& numerator, const QList<double>& denominator, QChar coeff, int maxPower);
    void setRepititions(int repititions);
    void performDivision();
    void adjustDenominator();
    QString getResult()const;
private:
    QList<double> m_Dnumerator{};
    QList<double> m_Ddenominator{};
    QChar m_Dcoeff{};
    int  m_DmaxPower{};
    int  m_Drepititions{};
    QString m_Dresult{};
};


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
    friend QDebug operator<< (QDebug output, const PowerComputation&);
private:
    std::shared_ptr<Numerator>num;
    std::shared_ptr<Denom>denom;
};

#endif // DIVISION_H
