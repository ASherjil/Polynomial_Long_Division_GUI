#ifndef GUI_APP_HANDLER_H
#define GUI_APP_HANDLER_H

#include <QVector>


class Gui_app_handler
{
public:
    void parseInputData(QString&& repititions,
                        QString&& numerator,
                        QString&& denominator);

    QChar checkCoeff(const QString& num_den);
private:

    QList<double> parseInputData(QString& data);
    int m_repititions;
    QList<double> m_numerator;
    QList<double> m_denominator;
    static QRegularExpression m_regex;
};



#endif // GUI_APP_HANDLER_H
