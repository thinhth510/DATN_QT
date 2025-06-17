#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QtWidgets> // Bao gồm QWidget, QPushButton, QGridLayout, QLineEdit, QApplication
#include <QtGui> // Bao gồm QMouseEvent
#include <QtCore> // Bao gồm QChar

class VirtualKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualKeyboard(QWidget *parent = nullptr);
    void setTargetLineEdit(QLineEdit *lineEdit);

private slots:
    void handleButtonClicked();
    void toggleShift();
    void closeKeyboard();

private:
    QGridLayout *mainLayout;
    QLineEdit *targetLineEdit;
    bool isShiftPressed;
    bool isCapsLockOn;
    QPushButton *shiftButton; // Shift phải
    QPushButton *capsLockButton; // Caps Lock trái
    QPushButton *rightShiftButton; // Shift phải
    QPushButton *closeButton;

    void createButtons();
    void updateKeyLabels();
};

#endif // VIRTUALKEYBOARD_H 