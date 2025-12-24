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
int result,DiceAmount;
int rollDice()
{
    int roll;
    int min = 1;
    int max = 6;

    roll = rand() % (max - min + 1) + min;

    return roll;
}

void MainWindow::on_BttnPlus_clicked()
{
    int diceAmount = ui->txtFirstNum->text().toInt();
    int sum = 0;
    QVector<int> dices;
    QString resultText;

    for (int i = 0; i < diceAmount; i++)
    {
        int dice = rollDice();
        dices.append(dice);
        resultText += QString::number(dice) + " ";
        if (dice == 6 || dice == 5 || (ui->CBFortune->isChecked() && dice == 4))
        {
            sum += 1;
        }
        if (dice == 1 || (ui->CBBadFortune->isChecked() && dice == 2))
        {
            sum -= 1;
        }
    }
    ui->txtResult->setText(resultText);
    ui->txtSum->setText(QString::number(sum));
}


