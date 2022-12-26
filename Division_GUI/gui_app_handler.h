#ifndef GUI_APP_HANDLER_H
#define GUI_APP_HANDLER_H

#include <QVector>
#include <QLabel>
#include "division.h"
#include "qmessagebox.h"

class Gui_app_handler
{
public:
    Gui_app_handler();

    /**
     * @brief parseInputData A public function to receive input data
     * from the main window.
     * @param repititions R-value reference received from the plaintext function
     * @param numerator   R-value reference received from the plaintext function
     * @param denominator R-value reference received from the plaintext function
     */
    void parseInputData(QString&& repititions,
                        QString&& numerator,
                        QString&& denominator,
                        QLabel* errorOutput);

    /**
     * @brief checkCoeff A function to find and return the coefficient from the
     * entered user input.
     * @param num_den   Either the numerator and denomitor.
     * @return The coefficient extracted from the user input
     */
    QChar checkCoeff(const QString& num_den);

    /**
     * @brief maxPower A function that returns the max power
     * in the format "15x^1+1x^0..."
     * @param num_den A required string
     * @return the maximum power found
     */
    int maxPower(const QString& num_den);

    /**
     * @brief verifyPolynomial A function that uses regex to verify if the user
     * has entered a polynomial in the valid form. (For some reason Qt regex is not working
     * therefore std::regex is used).
     * @param polynomial The user input in string format
     * @return returns true if the polynomial is valid
     */
    bool verifyPolynomial(const QString& polynomial);
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
    static QRegularExpression m_regex1;

    /**
     * @brief m_divisor A pointer to the class that is responsible for the heavy lifting.
     */
    Divisor* m_divisor;

    /**
     * @brief m_displayResult Opens a dialog to display the computed result,
     * if computation is successfull.
     */
    QMessageBox* m_displayResult;
};




#endif // GUI_APP_HANDLER_H
