#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpacket.h"
#include "qcustomplot.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList specialFuncsList;
    specialFuncsList << "Sine integral" << "Cosine integral" << "Bessel function" << "Fresnel integral S" << "Fresnel integral C";
    ui->specialFuncsComboBox->addItems(specialFuncsList);

    // Pipe handling
    QObject::connect(m_localSocket, SIGNAL(connected()), this, SLOT(on_ServerConnected()));
    QObject::connect(m_localSocket, SIGNAL(disconnected()), this, SLOT(on_ServerDisconnected()));
    QObject::connect(m_localSocket, SIGNAL(readyRead()), this, SLOT(on_DataArrived()));

    QObject::connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(on_connectBtn_clicked()));
    QObject::connect(ui->disconnectBtn, SIGNAL(clicked()), this, SLOT(on_disconnectBtn_clicked()));
    QObject::connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(on_sendBtn_clicked()) );
    // QObject::connect(ui->specialFuncs, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onSpecialFuncChanged(const QString &)));

}

MainWindow::~MainWindow()
{
    delete ui;

    // Closing and deleting the socket/named pipe connection
    delete m_localSocket;



}
// on_Server_connected caused an error because of ambiguity
// changed to on_ServerConnected

void MainWindow::on_ServerConnected()
{
    ui->disconnectBtn->setEnabled(true);
    ui->connectBtn->setEnabled(false);
}


void MainWindow::on_ServerDisconnected()
{
    ui->disconnectBtn->setEnabled(false);
    ui->connectBtn->setEnabled(true);
}

void MainWindow::on_connectBtnClicked()
{
    // Connecting to pipe server
    QString strServerAddress = "\\.\pipe\ICS0025";
    m_localSocket->connectToServer(strServerAddress, QIODevice::ReadWrite);

}

void MainWindow::on_disconnectBtnClicked()
{
    // Disconnecting from pipe server
    m_localSocket->disconnectFromServer();
}

void MainWindow::on_sendBtnClicked()
{
    QString functionName = ui->specialFuncsComboBox->currentText();
    QString minStr = ui->minLineEdit->text().trimmed();
    QString maxStr = ui->maxLineEdit->text().trimmed();
    QString pointsStr = ui->pointsLineEdit->text().trimmed();
    QString orderStr = ui->orderLineEdit->text().trimmed();

    // Check if correct values are entered
    bool isCorrect = true;
    double dfStart = minStr.toDouble(&isCorrect);
    double dfEnd = maxStr.toDouble(&isCorrect);
    qint32 nPoints = pointsStr.toInt(&isCorrect);
    qint32 nOrder = orderStr.toInt(&isCorrect);

    // Writing all data to a packet

    QByteArray btarrayData;
    QPacket packet(&btarrayData, QDataStream::LittleEndian, m_localSocket);
    packet.writeWStringData(functionName);
    packet.writeDoubleData(dfStart);
    packet.writeDoubleData(dfEnd);
    packet.writeInt32Data(nPoints);

    if (ui->orderLineEdit->isEnabled())
        packet.writeInt32Data(nOrder);

    packet.setPacketLengthField();
    packet.flushData();

}

void MainWindow::on_DataArrived() {

    QByteArray btarrayPacket = m_localSocket->readAll();
    QDataStream dataArrived(btarrayPacket);
    dataArrived.setByteOrder(QDataStream::LittleEndian);

    qint32 len = 0;
    dataArrived >> len;

    QVector<double> vctXsamples, vctYsamples;
    double minX = 0, maxX = 0, minY = 0, maxY = 0;
    while (!dataArrived.atEnd())
    {
        double dfX, dfY;
        dataArrived >> dfX >> dfY;
        vctXsamples.push_back(dfX);
        vctYsamples.push_back(dfY);

        if (dfX > maxX) maxX = dfX;
        if (dfX < minX) minX = dfX;
        if (dfY > maxY) maxY = dfY;
        if (dfY < minY) minY = dfY;
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(vctXsamples, vctYsamples);
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->xAxis->setRange(minX, maxX);
    ui->customPlot->yAxis->setRange(minY, maxY);
    ui->customPlot->replot();

}


void MainWindow::on_exitBtn_clicked()
{
    QApplication::exit();
}
