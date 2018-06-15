#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    picWin.setWindowTitle("Signals Image");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonGen_clicked()
{
    int type = ui->comboBoxTyp->currentIndex();
    picWin.para.type = type;
    picWin.para.amplitude = ui->lineEditAmp->text().toFloat();
    picWin.para.frequency = ui->lineEditFre->text().toFloat();
    picWin.para.phase = ui->lineEditPha->text().toFloat();
    picWin.para.offset = ui->lineEditOff->text().toFloat();
    picWin.para.inversion = ui->checkBoxInv->isChecked() ? -1 : 1;

    update();//重新获得参数后需要更新
    picWin.repaint();//这个好像要不要都没关系
    picWin.show();
}
