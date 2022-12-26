#ifndef DIVISION_H
#define DIVISION_H

#include <QDebug>



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


void printDebugger(const QList<double>& list);

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


#endif // DIVISION_H
