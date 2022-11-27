#include <QDebug>
#include <QRegularExpression>
#include "division.h"
#include "gui_app_handler.h"

// Initialising static member variable
QRegularExpression Gui_app_handler::m_regex = QRegularExpression("\\^-?\\d+");

void Gui_app_handler::parseInputData(QString &&repititions,
                                     QString &&numerator,
                                     QString &&denominator)
{
    QString _repititions = repititions.remove(' ');
    QString _numerator   = numerator  .remove(' ');
    QString _denominator = denominator.remove(' ');


    m_repititions = _repititions.toInt();
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
    data.remove(m_regex);
    data.remove('+');
    data.remove('-');
    QList<QString> _splitter = data.split(coeff);
    QList<double> ret;

    // transform into double from QString
    for (int i{};i<_splitter.size();++i){
        ret.push_back(_splitter[i].toDouble());
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
