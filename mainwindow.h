#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>

#include "syncserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void initView();

    void createTrayIcon();
    void createActions();

    void startServer();

private slots:
    void timerOutForInit();
    void newConnectionIncoming();

private:
    Ui::MainWindow *ui;
    QLabel* mQRCodeForIPLabel;

    QAction *mConnectionAction;
    QAction *mRecorderAction;
    QAction *mQuitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    SyncServer mSyncServer;
};

#endif // MAINWINDOW_H
