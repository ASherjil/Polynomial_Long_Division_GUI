#include <QDebug>
#include <QRegularExpression>
#include <regex>
#include "division.h"
#include "gui_app_handler.h"

// Initialising static member variable
QRegularExpression Gui_app_handler::m_regex1 = QRegularExpression("\\^-?\\d+");

void Gui_app_handler::parseInputData(QString &&repititions,
                                     QString &&numerator,
                                     QString &&denominator,
                                     QLabel* errorOutput)
{
    if (!repititions.size() || !numerator.size() || !denominator.size()){
        errorOutput->setText("Cannot compute result, empty fields detected.\n"
                             "Please click the 'HELP' button for more information.");
        errorOutput->setAlignment(Qt::AlignJustify);
        return;
    }

    QString _repititions = repititions.remove(' ');
    QString _numerator   = numerator  .remove(' ');
    QString _denominator = denominator.remove(' ');

    if (!verifyPolynomial(_numerator) || !verifyPolynomial(_denominator)){
        errorOutput->setText("Cannot compute result, either the numerator or denominator is entered incorrectly.\n"
                             "Please click the 'HELP' button for more information.");
        errorOutput->setAlignment(Qt::AlignJustify);
        return;
    }

    m_repititions = _repititions.toInt();

    int numPower = maxPower(_numerator);
    int denPower = maxPower(_denominator);

    if (numPower < denPower){
        int difference = denPower - numPower;
        for (int i{}; i< difference; ++i){
            m_numerator.prepend(0);
        }
    }
    else if(numPower > denPower){
        int difference = numPower - denPower;
        for (int i{}; i< difference; ++i){
            m_denominator.prepend(0);
        }
    }

    // parse and store the input data into the member variables
    m_numerator   = parseInputData(_numerator);
    m_denominator = parseInputData(_denominator);

    QVector<double> _temp1 =m_numerator.toVector();
    QVector<double> _temp2 =m_denominator.toVector();
    std::vector<double> _temp11(_temp1.begin(), _temp1.end());
    std::vector<double> _temp21(_temp2.begin(), _temp2.end());

    Numerator num1(_temp11, m_repititions, 0);
    Denom     den1(_temp21, 0);


    num1.print();
    qDebug() << "/";
    den1.print();
    qDebug() << "=\n";


    //-------------------------create pointers
    std::shared_ptr<Numerator>ptr1 = std::make_shared<Numerator>((num1 / den1)); // perform the calculation
    std::shared_ptr<Denom>ptr2 = std::make_shared<Denom>(den1);
    PowerComputation displayPower(ptr1, ptr2);
    //------------------------display result

    qDebug() << displayPower;
}

QList<double> Gui_app_handler::parseInputData(QString &data)
{
    QChar coeff = checkCoeff(data);
    data.remove(m_regex1);
    QList<QString> _splitter = data.split(coeff);
    QList<double> ret;

    // transform into double from QString
    for (int i{};i<_splitter.size();++i){
        if (_splitter[i] != ""){
            ret.push_back(_splitter[i].toDouble());
        }
    }

    return ret;
}

QChar Gui_app_handler::checkCoeff(const QString &num_den)
{
    int coeffIndex{};
    bool conversionSatus = true;
    for (int i{};i<num_den.size();++i){
        QString(num_den[i]).toInt(&conversionSatus, 10);
        if (conversionSatus == false){ // the first non-number found
            coeffIndex = i;
            break;
        }
    }
    return num_den[coeffIndex];
}

int Gui_app_handler::maxPower(const QString &num_den){
    int startIndex{};
    int endIndex{};

    for (startIndex = 0;startIndex<num_den.size(); ++startIndex){
        if (num_den[startIndex] == '^'){
            if (num_den[startIndex+1] == '-'){
                for (endIndex =startIndex+2; num_den[endIndex] != '+'&& num_den[endIndex] != '-';
                    ++endIndex){}
                    startIndex +=2;
                    break; // break out of the loop
            }
            else if (num_den[startIndex+1] == '+'){
                for (endIndex =startIndex+2; num_den[endIndex] != '+'&& num_den[endIndex] != '-';
                    ++endIndex){}
                    startIndex +=2;
                    break; // break out of the loop
            }
            else{
                for (endIndex =startIndex+1; num_den[endIndex] != '+'&& num_den[endIndex] != '-';
                    ++endIndex){}
                    startIndex +=1;
                    break; // break out of the loop
            }
        }
    }
    std::string _num_den = num_den.toStdString();
    std::string number(_num_den.begin()+startIndex, _num_den.begin()+endIndex);
    return std::stoi(number);
}

bool Gui_app_handler::verifyPolynomial(const QString &polynomial){
    const std::regex _regex("((-|\\+)?[0-9]+[a-z]\\^(-|\\+)?[0-9]+)+");
    return regex_match(polynomial.toStdString(), _regex);
}

