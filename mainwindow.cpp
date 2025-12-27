#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Rolls a single d6
int rollSingleDie()
{
    constexpr int minValue = 1;
    constexpr int maxValue = 6;

    return QRandomGenerator::global()->bounded(minValue, maxValue + 1);
    }

//Stores previous sum of dices and rewrites itself after another throw
//currentSum is value that we get from calculateDiceResult function
int storeAndGetPreviousSum(int currentSum)
{
    static int previousSum = 0;

    int result = previousSum;
    previousSum = currentSum;

    return (result);
}

//Calculates result of thrown dice and returns a value that gets added or subtracted, needs a cycle to calculate all dices thrown
//Dice == Thrown dice, fortune and badFortune == checkboxes
int calculateDiceResult(int dice, bool fortune, bool badFortune)
{
    if (dice == 6 || dice == 5 || (fortune && dice == 4))
        return 1;

    if (dice == 1 || (badFortune && dice == 2))
        return -1;

    return 0;
}

//Main Window code
void MainWindow::on_button_Throw_clicked()
{
    const int diceCount = ui->txt_NumOfDices->text().toInt();
    int successSum = 0;

    QStringList diceResults;

    const bool fortuneEnabled = ui->cb_Fortune->isChecked();
    const bool badFortuneEnabled = ui->cb_BadFortune->isChecked();

    for (int i = 0; i < diceCount; ++i)
    {
        const int dice = rollSingleDie();
        diceResults << QString::number(dice);

        successSum += calculateDiceResult(dice, fortuneEnabled, badFortuneEnabled);
    }

    ui->txt_Result->setText(diceResults.join(" "));
    ui->txt_Sum->setText(QString::number(successSum));
    ui->txt_History->setText(QString::number(storeAndGetPreviousSum(successSum)));

}

