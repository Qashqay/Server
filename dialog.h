#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QFile>
 #include <QTimer>
//#include <QtMultimedia>
#include "myserver.h"
#define SERVER_COUNT 7
#define FIRST_PORT 1232

namespace Ui {
    class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
    QFile fileOut;
    QFile fileError;
    QTimer *timerOfCorrectWork;
    QTextStream streamOut;
    QTextStream streamError;
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    MyServer **_servMany;
    void addToLog(QString text, QColor color, bool toFile=true);

signals:

public slots:
    void onAddUserToGui(QString name);
    void onRemoveUserFromGui(QString name);
    void onMessageToGui(QString message, QString from, const QStringList &users);
    void onAddLogToGui(QString string, QColor color);

private slots:
    void on_pbSend_clicked();
    void on_cbToAll_clicked();
    void on_pbStartStop_toggled(bool checked);
    void writeCurrentState(QString text = "");
};

#endif // DIALOG_H
