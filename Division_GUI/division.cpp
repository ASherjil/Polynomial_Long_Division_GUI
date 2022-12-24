#include <algorithm>
#include "division.h"

template<typename T>
size_t finder(const std::vector<T>& vect)
{
    for (size_t i{}; i < vect.size(); ++i)
    {
        if (vect[i])
        {
            return i; // return the vector index
        }
    }
    return 0; // otherwise return nothing
}

double Denom::getElement()const// extract the first non-zero element from the denom
{
    return denominator[finder(denominator)];
}

double& Denom::operator[](size_t i)
{
    return denominator[i];
}


Numerator& Numerator::operator/(Denom& denom)
{
    if (numerator[0] == 0)
    {
        answer.push_back(0);// first answer is always zero in this case
        answer.push_back(numerator[1] / denom.getElement());

        // vector(names array for simplicity) for intermediate steps
        std::vector<double>array1{ 0 };
        std::vector<double>array2{ 0 };


        for (size_t i{}; i < denom.getSize(); ++i)// multiply
        {
            array1.push_back((numerator[1] / denom.getElement()) * denom[i]);
        }

        for (size_t i{}; i < denom.getSize(); ++i)// subtract
        {
            array2.push_back(numerator[i] - array1[i]);
        }

        for (size_t i{}; i < denom.getSize(); ++i) // store next value
        {
            if (array2[i])
            {
                answer.push_back((array2[i] / denom.getElement()));
                break;
            }
        }

        for (size_t rr{}; rr < repetition - 3; ++rr)// 3 answers have already been stored
        {

            for (size_t i{}; i < denom.getSize(); ++i) // create new subtracting factor
            {
                if (array2[i])
                {
                    for (size_t k{}; k < denom.getSize(); ++k)
                    {
                        array1[k] = (array2[i] / denom.getElement()) * denom[k];
                    }
                    break;
                }
            }



            size_t counter = finder(array2);

            std::rotate(array2.begin(), array2.begin() + counter, array2.end()); // shift the vector for subtraction


            for (size_t i{}; i < denom.getSize(); ++i) // subtract for next step
            {
                array2[i] = array2[i] - array1[i];
            }



            answer.push_back(array2[1] / denom.getElement());
        }
        return *this;

    }

    /* -------------------------------------------------------if the first answer value is not 0----*/
    else {
        answer.push_back(numerator[0] / denom.getElement());
        // vector(named array for simplicity) for intermediate steps
        std::vector<double>array1;
        std::vector<double>array2;


        for (size_t i{}; i < denom.getSize(); ++i)// multiply
        {
            array1.push_back((numerator[0] / denom.getElement()) * denom[i]);
        }

        size_t counter = finder(array1);

        std::rotate(array1.begin(), array1.begin() + counter, array1.end()); // shift the vector for subtraction

        for (size_t i{}; i < denom.getSize(); ++i)// subtract
        {
            array2.push_back(numerator[i] - array1[i]);
        }

        for (size_t i{}; i < denom.getSize(); ++i) // store next value
        {
            if (array2[i])
            {
                answer.push_back(array2[i] / denom.getElement());
                break;
            }
        }

        for (size_t rr{}; rr < (repetition - 2); ++rr) // two values have already been stored
        {
            for (size_t i{}; i < denom.getSize(); ++i) // create new subtracting factor
            {
                if (array2[i])
                {
                    for (size_t k{}; k < denom.getSize(); ++k)
                    {
                        array1[k] = (array2[i] / denom.getElement()) * denom[k];
                    }
                    break;
                }
            }



            counter = finder(array2);// re-use counter

            std::rotate(array2.begin(), array2.begin() + counter, array2.end()); // shift the vector for subtraction

            if (finder(array1) > 0)// align the vectors for subtraction
            {
                std::rotate(array1.begin(), array1.begin() + finder(array1), array1.end()); // shift the vector for subtraction
            }


            for (size_t i{}; i < denom.getSize(); ++i) // subtract for next step
            {
                array2[i] = array2[i] - array1[i];
            }


            if (!(array2[1] / denom.getElement()))
            {
                answer.push_back(array2[1] / denom.getElement());
                std::cout << "This is fully divisable.\n";
                return *this;
                break;// terminate if in rare cases answer is zero
            }


            answer.push_back(array2[1] / denom.getElement());
        }

        return *this;
    }

}

void Numerator::print()const
{
    qDebug() << "[ ";
    for (int i{}; i < numerator.size(); ++i)
    {
       qDebug() << numerator[i] << "z^" << max - i << " ";
    }
    qDebug() << " ]";
}

void Denom::print()const
{
    qDebug() << "[ ";
    for (int i{}; i < denominator.size(); ++i)
    {
        qDebug() << denominator[i] << "z^" << max - i << " ";
    }
    qDebug() << " ]";
}



PowerComputation::PowerComputation(std::shared_ptr<Numerator>num, std::shared_ptr<Denom>denom)
    : num(std::move(num)), denom(std::move(denom)) {}

QDebug operator<< (QDebug output, const PowerComputation& pow)
{
    int minus{};// arbitrary integer for power

    if (finder(pow.num->getNumerator()))//check if the numerator has a leading zero term
    {
        output << "[";
        for (int i{}; i < pow.num->getAnswer().size(); ++i)
        {
            if ((pow.num->getAnswer())[i])
            {
                output << pow.num->getAnswer()[i] << "z^"
                    << -1 * static_cast<int>(finder(pow.num->getNumerator())) - minus << " ";
                ++minus;
            }
            else
            {
                output << pow.num->getAnswer()[i] << " ";
            }

        }
        output << "]\n";
        return output;
    }


    if (finder(pow.denom->getDenominator()))//check if the denominator has a leading zero term
    {
        output << "[";
        for (int i{}; i < pow.num->getAnswer().size(); ++i)
        {
            if ((pow.num->getAnswer())[i])
            {
                output << pow.num->getAnswer()[i] << "z^"
                    << static_cast<int>(finder(pow.denom->getDenominator())) - minus << " ";
                ++minus;
            }
            else
            {
                output << pow.num->getAnswer()[i] << " ";
            }

        }
        output << "]\n";
        return output;
    }

    else// no leading zero terms
    {
        output << "[";
        for (int i{}; i < pow.num->getAnswer().size(); ++i)
        {
            output << pow.num->getAnswer()[i] << "z^"
                << static_cast<int>(finder(pow.num->getNumerator())) - minus << " ";
            ++minus;
        }
        output << "]\n";

        return output;

    }
}
