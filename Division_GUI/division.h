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

/**
 * @brief printDebugger Global function for printing a list of double.
 * @param list of doubles
 */
void printDebugger(const QList<double>& list);

/**
 * @brief The Divisor class Responsible for computing the result of the polynomial long
 * division. It basically does all the backend heavy lifting.
 */
class Divisor{
public:
    /**
     * @brief setParameters Store the required parameters for performing the computation.
     * @param numerator as a list of double
     * @param denominator as a list of double
     * @param coeff The coefficient of the numerator and denominator(x, z etc)
     * @param maxPower (Not used right now)
     */
    void setParameters(const QList<double>& numerator, const QList<double>& denominator, QChar coeff, int maxPower);

    /**
     * @brief setRepititions Set the required number of quotients.
     * @param repititions
     */
    void setRepititions(int repititions);

    /**
     * @brief performDivision Performs the division and saves the result in m_Dresult QString.
     */
    void performDivision();

    /**
     * @brief adjustDenominator This function is used to make the leading term of the denominator
     * equal to 1 to make the division faster.
     */
    void adjustDenominator();

    /**
     * @brief getResult Const getter for m_Dresult.
     * @return m_Dresult the result of the long division as a QString.
     */
    QString getResult()const;
private:
    /// Numerator
    QList<double> m_Dnumerator{};
    /// Denominator
    QList<double> m_Ddenominator{};
    /// The coefficient(could be x, z etc)
    QChar m_Dcoeff{};
    /// Not used right now
    int  m_DmaxPower{};
    /// The required number of quotients.
    int  m_Drepititions{};
    /// The final result of the division.
    QString m_Dresult{};
};


#endif // DIVISION_H
