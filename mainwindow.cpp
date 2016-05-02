#include "mainwindow.h"
#include <stdlib.h>
#include "parser.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#define bookList 4000

char *outText;
int nowEnd;
int MaxList;
int CharSize = 14;
bool nightMod;
QString fontFamily = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nightMod = false;
    QString size = QString::number(CharSize);
    QString style = "font-size:" + size + "px;" + "\n" + fontFamily;
    ui->textEdit->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData(){
    char buf[2*bookList+1];
    int tmp = nowEnd;
    int i = 0;
    while (i < bookList) {
        buf[i] = outText[tmp];
        tmp++;
        i++;
    }
    if (outText[i] != ' '){
        buf[i] = '-';
    }
    buf[i+1] = '\0';

    ui->textEdit->setText(buf);
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Book File"), "/home/jana", tr("Book File (*.txt *.fb2)"));
    QByteArray conv = fileName.toLocal8Bit();
    char *path = (char*)strdup(conv.constData());
    int size;
    char *buf;
    FILE *f = fopen(path, "r");
    if (f != NULL) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        buf = (char*) malloc(size*sizeof(char));
        outText = (char*) malloc(size*sizeof(char));
        fseek(f, 0, SEEK_SET);
        fread(buf, 1, size, f);
        fclose(f);
        buf[size-1] = '\0';
        MaxList = size;
        int i = 0, n = 0;
        while (path[i] != '\0') {
            i++;
            n++;
        }

        if (path[n-1] == '2' && path[n-2] == 'b' && path[n-3] == 'f') {
            parserXMLtoTXT(buf, outText);
        } else {
            i = 0;
            while (buf[i] != '\0') {
                outText[i] = buf[i];
                i++;
            }
        }
        nowEnd = 0;
        updateData();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (nowEnd >= bookList) {
        nowEnd -= bookList;
    }
    updateData();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (nowEnd <= MaxList) {
        nowEnd += bookList;
    }
    updateData();
}

void MainWindow::on_pushButton_4_clicked()
{
    CharSize += 2;
    QString size = QString::number(CharSize);
    QString style = "font-size:" + size + "px;";
    ui->textEdit->setStyleSheet(style);
}

void MainWindow::on_pushButton_5_clicked()
{
    if (CharSize > 4) {
        CharSize -= 2;
        QString size = QString::number(CharSize);
        QString style = "font-size:" + size + "px;" + "\n" + fontFamily;
        ui->textEdit->setStyleSheet(style);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) {
         fontFamily = "font-family: 'Arial';";
    } else if (index == 1) {
        fontFamily = "font-family: 'Ubuntu';";
    } else if (index == 2) {
        fontFamily = "font-family: 'URW Palladiol';";
    } else if (index == 3) {
        fontFamily = "font-family: 'FreeMono';";
    } else if (index == 4) {
        fontFamily = "font-family: 'Tlwq Typo';";
    } else if (index == 5) {
        fontFamily = "font-family: 'KacstBook';";
    }

    QString size = QString::number(CharSize);
    QString style = "font-size:" + size + "px;" + "\n" + fontFamily;
    ui->textEdit->setStyleSheet(style);

}
