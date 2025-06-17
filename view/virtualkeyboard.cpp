#include "virtualkeyboard.h"

VirtualKeyboard::VirtualKeyboard(QWidget *parent)
    : QWidget(parent)
    , targetLineEdit(nullptr)
    , isShiftPressed(false)
    , isCapsLockOn(false)
    , shiftButton(nullptr)
    , capsLockButton(nullptr)
    , rightShiftButton(nullptr)
    , closeButton(nullptr)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    mainLayout = new QGridLayout(this);
    createButtons();
    setFixedSize(800, 320);
    
    // Thêm style cho bàn phím với màu xám tối
    setStyleSheet(R"(
        QWidget {
            background-color: #2b2b2b;
            border: 1px solid #3f3f3f;
            border-radius: 5px;
        }
        QPushButton {
            background-color: #3f3f3f;
            color: white;
            border: 1px solid #4f4f4f;
            border-radius: 3px;
            padding: 5px;
            min-width: 30px;
            min-height: 40px;
            font-size: 16px;
        }
        QPushButton:hover {
            background-color: #4f4f4f;
        }
        QPushButton:pressed {
            background-color: #5f5f5f;
        }
        #closeButton {
            background-color: #ff4444;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 2px;
            min-width: 28px;
            min-height: 28px;
            font-size: 14px;
        }
        #closeButton:hover {
            background-color: #ff6666;
        }
    )");
}

void VirtualKeyboard::setTargetLineEdit(QLineEdit *lineEdit)
{
    targetLineEdit = lineEdit;
}

void VirtualKeyboard::createButtons()
{
    // Xóa layout cũ nếu có
    QLayoutItem *child;
    while ((child = mainLayout->takeAt(0)) != nullptr) {
        delete child;
    }

    const int totalCols = 12;

    // Nút đóng (X) sát góc phải trên cùng
    closeButton = new QPushButton("X", this);
    closeButton->setObjectName("closeButton");
    closeButton->setFixedSize(28, 28);
    connect(closeButton, &QPushButton::clicked, this, &VirtualKeyboard::closeKeyboard);
    QHBoxLayout *closeLayout = new QHBoxLayout();
    closeLayout->addStretch();
    closeLayout->addWidget(closeButton);
    closeLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(closeLayout, 0, 0, 1, totalCols);

    // Hàng 1: 1-0 + Backspace (Backspace chiếm 2 cột)
    QStringList numbers = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    for (int i = 0; i < numbers.size(); ++i) {
        QPushButton *button = new QPushButton(numbers[i], this);
        connect(button, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
        mainLayout->addWidget(button, 1, i, 1, 1);
    }
    QPushButton *backspaceButton = new QPushButton("Backspace", this);
    connect(backspaceButton, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
    mainLayout->addWidget(backspaceButton, 1, 10, 1, 2);

    // Hàng 2: QWERTYUIOP (10 phím), Enter (2 cột cuối)
    QStringList row1 = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
    for (int i = 0; i < row1.size(); ++i) {
        QPushButton *button = new QPushButton(row1[i], this);
        connect(button, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
        mainLayout->addWidget(button, 2, i, 1, 1);
    }
    QPushButton *enterButton = new QPushButton("Enter", this);
    connect(enterButton, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
    mainLayout->addWidget(enterButton, 2, 10, 1, 2);

    // Hàng 3: (1 ô trống) A S D F G H J K L - (2 ô trống cuối)
    QStringList row2 = {"A", "S", "D", "F", "G", "H", "J", "K", "L", "-"};
    for (int i = 0; i < row2.size(); ++i) {
        QPushButton *button = new QPushButton(row2[i], this);
        connect(button, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
        mainLayout->addWidget(button, 3, i + 1, 1, 1);
    }
    // 1 ô đầu và 1 ô cuối trống

    // Hàng 4: Caps Lock (2 cột), Z X C V B N M . Shift (2 cột cuối)
    capsLockButton = new QPushButton("Caps Lock", this);
    connect(capsLockButton, &QPushButton::clicked, this, &VirtualKeyboard::toggleShift);
    mainLayout->addWidget(capsLockButton, 4, 0, 1, 2);
    QStringList row3 = {"Z", "X", "C", "V", "B", "N", "M", "."};
    for (int i = 0; i < row3.size(); ++i) {
        QPushButton *button = new QPushButton(row3[i], this);
        connect(button, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
        mainLayout->addWidget(button, 4, i + 2, 1, 1);
    }
    rightShiftButton = new QPushButton("Shift", this);
    connect(rightShiftButton, &QPushButton::clicked, this, &VirtualKeyboard::toggleShift);
    mainLayout->addWidget(rightShiftButton, 4, 10, 1, 2);

    // Hàng 5: Space (chiếm 6 cột, căn giữa)
    QPushButton *spaceButton = new QPushButton("Space", this);
    connect(spaceButton, &QPushButton::clicked, this, &VirtualKeyboard::handleButtonClicked);
    mainLayout->addWidget(spaceButton, 5, 3, 1, 6);

    // Căn đều các cột và hàng
    for (int i = 0; i < totalCols; ++i) mainLayout->setColumnStretch(i, 1);
    for (int i = 1; i <= 5; ++i) mainLayout->setRowStretch(i, 1);

    // Sau khi tạo xong các nút, cập nhật nhãn phím chữ
    updateKeyLabels();
}

void VirtualKeyboard::updateKeyLabels()
{
    // Hàng 2: QWERTYUIOP
    QStringList row1 = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
    for (int i = 0; i < row1.size(); ++i) {
        QLayoutItem *item = mainLayout->itemAtPosition(2, i);
        if (item && item->widget()) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                button->setText((isShiftPressed || isCapsLockOn) ? row1[i] : row1[i].toLower());
            }
        }
    }
    // Hàng 3: A S D F G H J K L -
    QStringList row2 = {"A", "S", "D", "F", "G", "H", "J", "K", "L", "-"};
    for (int i = 0; i < row2.size(); ++i) {
        QLayoutItem *item = mainLayout->itemAtPosition(3, i + 1);
        if (item && item->widget()) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Dấu '-' giữ nguyên
                if (row2[i] == "-")
                    button->setText("-");
                else
                    button->setText((isShiftPressed || isCapsLockOn) ? row2[i] : row2[i].toLower());
            }
        }
    }
    // Hàng 4: Z X C V B N M .
    QStringList row3 = {"Z", "X", "C", "V", "B", "N", "M", "."};
    for (int i = 0; i < row3.size(); ++i) {
        QLayoutItem *item = mainLayout->itemAtPosition(4, i + 2);
        if (item && item->widget()) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Dấu '.' giữ nguyên
                if (row3[i] == ".")
                    button->setText(".");
                else
                    button->setText((isShiftPressed || isCapsLockOn) ? row3[i] : row3[i].toLower());
            }
        }
    }
}

void VirtualKeyboard::toggleShift()
{
    QPushButton *senderBtn = qobject_cast<QPushButton*>(sender());
    if (senderBtn == capsLockButton) {
        isCapsLockOn = !isCapsLockOn;
        // Đổi màu nút Caps Lock
        if (isCapsLockOn) {
            capsLockButton->setStyleSheet("background-color: #4CAF50; color: white;");
        } else {
            capsLockButton->setStyleSheet("");
        }
    } else if (senderBtn == rightShiftButton) {
        isShiftPressed = true;
        rightShiftButton->setStyleSheet("background-color: #4CAF50; color: white;");
    }

    // Sau khi đổi trạng thái, gọi updateKeyLabels()
    updateKeyLabels();
}

void VirtualKeyboard::handleButtonClicked()
{
    if (!targetLineEdit) return;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QString text = button->text();
    if (text == "Space") {
        targetLineEdit->insert(" ");
    } else if (text == "Backspace") {
        targetLineEdit->backspace();
    } else if (text == "Enter") {
        closeKeyboard();
    } else if (text == "Caps Lock" || text == "Shift") {
        // Đã xử lý ở toggleShift
    } else {
        // Xác định trạng thái hoa/thường
        bool upper = isShiftPressed || isCapsLockOn;
        if (upper) {
            targetLineEdit->insert(text.toUpper());
        } else {
            targetLineEdit->insert(text.toLower());
        }
        // Nếu vừa nhấn Shift thì tắt Shift sau 1 ký tự
        if (isShiftPressed) {
            isShiftPressed = false;
            rightShiftButton->setStyleSheet("");
        }
    }

    // Sau khi nhấn phím, gọi updateKeyLabels()
    updateKeyLabels();
}

void VirtualKeyboard::closeKeyboard()
{
    hide();
    if (targetLineEdit) {
        targetLineEdit->clearFocus();
    }
} 