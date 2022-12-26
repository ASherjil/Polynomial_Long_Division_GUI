#include <algorithm>
#include "division.h"

QList<double> operator-(const QList<double>& lhs, const QList<double>& rhs){
    QList<double> result{};

    if (lhs.size() != rhs.size()){
        qWarning()<<"Overloaded subtraction cannot be performed because of incorrect "
                    "list sizes";
        return result;
    }

    for (int i{}; i<rhs.size();++i){
        result.push_back(lhs[i]-rhs[i]);
    }
    return result;
}

QList<double> operator*(double multiplier, const QList<double>& rhs){
    QList<double> result{};
    for (int i{};i<rhs.size();++i){
        result.push_back(multiplier * rhs[i]);
    }
    return result;
}

QList<double> operator/(const QList<double> &num, double denom){
    QList<double> result{};
    for (int i{};i<num.size();++i){
        result.push_back(num[i]/denom);
    }
    return result;
}


void Divisor::setParameters(const QList<double> &numerator, const QList<double> &denominator, QChar coeff, int maxPower)
{
    m_Dnumerator  =numerator;
    m_Ddenominator=denominator;
    m_Dcoeff      =coeff;
    m_DmaxPower   =maxPower;
}

void Divisor::setRepititions(int repitions)
{
    m_Drepititions = repitions;
}

void Divisor::performDivision()
{
    QList<double> result;
    QList<double> multipliedDenom;
    double multiplier{};
    int largestLength = std::max(m_Dnumerator.size(), m_Ddenominator.size());

    m_Dresult.clear(); // clear before adding new data

    // Adjust numerator and denominator if the denominator does not have a leading 1
    adjustDenominator();
    QList<double> tempNum = m_Dnumerator;

    qDebug()<<"Adjusted data:";
    printDebugger(m_Dnumerator);
    printDebugger(m_Ddenominator);

//  case 1: Numerator and Denom both have non-zeroes first element
    if (m_Dnumerator[0] && m_Ddenominator[0]){

        for (int i{}; i<m_Drepititions; ++i){
            multiplier = tempNum[0] / m_Ddenominator[0];
            result.push_back(multiplier);


            multipliedDenom = multiplier * m_Ddenominator;
            multipliedDenom.resize(largestLength);
            tempNum.resize(largestLength);

            tempNum = tempNum - multipliedDenom;

            bool zeros = std::all_of(tempNum.begin(), tempNum.end(), [](double i) { return i == 0.0; });

            if (zeros){
                break; // this division is complete
            }
            tempNum.removeFirst();
        }

        int power{};
        for (int i{};i<result.size();++i){
            if (result[i] > 0){
                m_Dresult += QString("%1%2^%3 + ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            else{
                m_Dresult += QString("%1%2^%3 ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            power--;
        }

    }

//  case 2: Numerator has a leading zero
    else if (m_Dnumerator[0] == 0){

        int rotation{};
        for (int i{};i<m_Dnumerator.size();++i){
            if (m_Dnumerator[i]){
                rotation =i;
                break;
            }
        }
        // perform necessary rotation, move the non zero number to the front
        std::rotate(m_Dnumerator.begin(), m_Dnumerator.begin()+rotation, m_Dnumerator.end());
        if (m_Dnumerator.size() > m_Ddenominator.size()){
            m_Ddenominator.resize(m_Dnumerator.size());
        }
        else{
            m_Dnumerator.resize(m_Ddenominator.size());
        }

        tempNum = m_Dnumerator;

        for (int i{}; i<m_Drepititions; ++i){
            multiplier = tempNum[0] / m_Ddenominator[0];
            result.push_back(multiplier);

            multipliedDenom = multiplier * m_Ddenominator;
            multipliedDenom.resize(largestLength);
            tempNum.resize(largestLength);

            tempNum = tempNum - multipliedDenom;

            bool zeros = std::all_of(tempNum.begin(), tempNum.end(), [](int i) { return i==0; });

            if (zeros){
                break; // this division is complete
            }
            tempNum.removeFirst();
        }

        int power = -1* rotation;
        for (int i{};i<result.size();++i){
            if (result[i] > 0){
                m_Dresult += QString("%1%2^%3 + ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            else{
                m_Dresult += QString("%1%2^%3 ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            power--;
        }

    }

//  case 3: Denominator has leading zero
    else if (m_Ddenominator[0] == 0){

        int rotation{};
        for (int i{};i<m_Ddenominator.size();++i){
            if (m_Ddenominator[i]){
                rotation =i;
                break;
            }
        }
        // perform necessary rotation, move the non zero number to the front
        std::rotate(m_Ddenominator.begin(), m_Ddenominator.begin()+rotation, m_Ddenominator.end());
        if (m_Dnumerator.size() > m_Ddenominator.size()){
            m_Ddenominator.resize(m_Dnumerator.size());
        }
        else{
            m_Dnumerator.resize(m_Ddenominator.size());
        }

        for (int i{}; i<m_Drepititions; ++i){
            multiplier = tempNum[0] / m_Ddenominator[0];
            result.push_back(multiplier);

            multipliedDenom = multiplier * m_Ddenominator;
            multipliedDenom.resize(largestLength);
            tempNum.resize(largestLength);

            tempNum = tempNum - multipliedDenom;

            bool zeros = std::all_of(tempNum.begin(), tempNum.end(), [](int i) { return i==0; });

            if (zeros){
                break; // this division is complete
            }
            tempNum.removeFirst();
        }

        int power = rotation;
        for (int i{};i<result.size();++i){
            if (result[i] > 0){
                m_Dresult += QString("%1%2^%3 + ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            else{
                m_Dresult += QString("%1%2^%3 ").arg(result[i]).arg(m_Dcoeff).arg(power);
            }
            power--;
        }

    }

}

void Divisor::adjustDenominator()
{
    int nonZeroIndex{};
    for (int i{};i<m_Ddenominator.size();++i){
        if (m_Ddenominator[i]){
            nonZeroIndex = i;
            break;
        }
    }

    double divident = m_Ddenominator[nonZeroIndex];

    if (divident != 1){
        m_Ddenominator = m_Ddenominator / divident;
        m_Dnumerator   = m_Dnumerator   / divident;
    }
}

QString Divisor::getResult() const
{
    return m_Dresult;
}

void printDebugger(const QList<double> &list){
    for (int i{};i<list.size();++i){
        qDebug()<<list[i]<<" , ";
    }
}
