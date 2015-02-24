#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "myclient.h"
class MyClient;
class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QWidget *widget = 0, QObject *parent = 0);
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllMessage(QString message, QString fromUsername,int port);
    void doSendLastLog(QString message, int port);
    void doSendAllLog(QString message, int port);
    void doSendToAllProgramMessage(const char *a, int port);
    void doSendStatus(QString message, int port);
    void doSendTemp(QString message, int port);
    void doSendContrast(QString message, int port);
    void doSendServCommand(uint8_t comm, int port);
    void doSendFuckingMessage(QString message, int port);
    bool isNameValid(QString name) const;
    bool isNameUsed(QString &name) const;
    QStringList _logged;
    QList<MyClient *> _clients;

signals:
    void addLogToGui(QString string, QColor color = Qt::black);

public slots:
    void onRemoveUser(MyClient *client);

protected:
    void incomingConnection(int handle);

private:

    QWidget *_widget;
};

#endif // MYSERVER_H
