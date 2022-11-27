#ifndef GUI_APP_HANDLER_H
#define GUI_APP_HANDLER_H

#include <QVector>


class Gui_app_handler
{
public:
    /**
     * @brief parseInputData A public function to receive input data
     * from the main window.
     * @param repititions R-value reference received from the plaintext function
     * @param numerator   R-value reference received from the plaintext function
     * @param denominator R-value reference received from the plaintext function
     */
    void parseInputData(QString&& repititions,
                        QString&& numerator,
                        QString&& denominator);

    /**
     * @brief checkCoeff A function to find and return the coefficient from the
     * entered user input.
     * @param num_den   Either the numerator and denomitor.
     * @return The coefficient extracted from the user input
     */
    QChar checkCoeff(const QString& num_den);
private:
    /**
     * @brief parseInputData A private helper function that modifies
     * the string and removes the powers from the string.
     * "15x^-2+21x^-3" -> "15,21"
     * @param data           Numerator/denominator with whitespaces removed
     * @return A list containing all the doubles
     */
    QList<double> parseInputData(QString& data);

    int m_repititions;
    QList<double> m_numerator;
    QList<double> m_denominator;

    /// The regex static variable, to improve performance. This removes
    /// all the power from the input numerator/denominator.
    static QRegularExpression m_regex;
};



#endif // GUI_APP_HANDLER_H
