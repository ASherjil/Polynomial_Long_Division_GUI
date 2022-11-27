#include <QDebug>
#include <QRegularExpression>
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
}

QList<double> Gui_app_handler::parseInputData(QString &data)
{
    QChar coeff = checkCoeff(data);
    data.remove(m_regex);
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
    for (int i{};i<num_den.size();++i){
        if (!QString(num_den[i]).toInt()){ // the first non-number found
            coeffIndex = i;
            break;
        }
    }
    return num_den[coeffIndex];
}
