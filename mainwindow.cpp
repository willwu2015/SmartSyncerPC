#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcoder.h"
#include "utilities.h"

#include <QTimer>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initView();

    createActions();
    createTrayIcon();

    trayIcon->show();

    connect(&mSyncServer, SIGNAL(newConnectionIncoming()), this, SLOT(newConnectionIncoming()));
    startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// protect section
void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

// private section
void MainWindow::initView() {
    QVBoxLayout *wholeLayout = new QVBoxLayout(ui->centralWidget);

    QHBoxLayout *codeLayout = new QHBoxLayout();

    // QR code layout
    mQRCodeForIPLabel = new QLabel(ui->centralWidget);
    codeLayout->addStretch();
    codeLayout->addWidget(mQRCodeForIPLabel);
    codeLayout->addStretch();
    wholeLayout->addLayout(codeLayout);

    // hint label
    QLabel *hintLabel = new QLabel(ui->centralWidget);
    hintLabel->setAlignment(Qt::AlignHCenter);
    hintLabel->setText(tr("Please scan the QR code to create the connection!"));
    wholeLayout->addWidget(hintLabel);
    QTimer::singleShot(0, this, SLOT(timerOutForInit()));
}

void MainWindow::createTrayIcon() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(mConnectionAction);
    trayIconMenu->addAction(mRecorderAction);
    trayIconMenu->addAction(mQuitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/connect.png"));
}

void MainWindow::createActions() {

    mConnectionAction = new QAction(tr("&Connect"), this);
    connect(mConnectionAction, &QAction::triggered, this, &QWidget::showNormal);

    mRecorderAction = new QAction(tr("&Recorder"), this);

    mQuitAction = new QAction(tr("&Quit"), this);
    connect(mQuitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::startServer() {
    if (!mSyncServer.listen()) {
        QMessageBox::critical(this, tr("Threaded Fortune Server"),
                                    tr("Unable to start the server: %1.")
                                    .arg(mSyncServer.errorString()));
        close();
        return;
    }

    ui->statusBar->setStatusTip(tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                         .arg(Utilities::getHostIPAddress()).arg(mSyncServer.serverPort()));
}

void MainWindow::timerOutForInit() {
    QImage code = QRCoder::encoder(Utilities::getHostIPAddress() + ":" + QString::number(mSyncServer.serverPort()));
    //code.save("/Users/willwu/Documents/qtdemo/SmartSyncer/codefilename.png");

    mQRCodeForIPLabel->setPixmap(QPixmap::fromImage(code));

    hide();
}

void MainWindow::newConnectionIncoming() {
    trayIcon->showMessage(tr("New connection"), tr("There is a new connection incoming."));
}
