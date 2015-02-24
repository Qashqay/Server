#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThreadPool>
#include <QtGui>
#include <QRegExp>
#include <QFile>
#include <stdint.h>
//#include <sstream>
#include "myserver.h"
#define SERVER_COUNT 7
#define FIRST_PORT 1232
using namespace std;
class MyServer;

class MyClient : public QObject
{
    friend class MyServer;
    Q_OBJECT

public:
    static const QString constNameUnknown;
    static const QString constLogEmpty;
    static const uint8_t comAutchReq = 1;
    static const uint8_t comMessageToAll = 2;
    static const uint8_t comSendLastLog = 3;
    static const uint8_t comSendAllLog = 4;
    static const uint8_t comNormalMode = 5;
    static const uint8_t comCheck = 6;
    static const uint8_t comDrop = 7;
    static const uint8_t comStop = 8;
    static const uint8_t comPowerOff = 9;
    static const uint8_t comMessageFromProg=10;
    static const uint8_t comStatusInt=11;
    static const uint8_t comMilReady = 12;
    static const uint8_t comMilOut = 13;
    static const uint8_t comTempStat = 14;
    static const uint8_t comSendInterf = 15;
    static const uint8_t comFullSendInterf = 20;
    static const uint8_t comStopSendInterf = 16;
    static const uint8_t comInterf =17;
    static const uint8_t comContrast = 18;
    static const uint8_t comDropToNorm =19;
    static const uint8_t comErrNameInvalid = 200;
    static const uint8_t comErrNameUsed = 201;

    explicit MyClient(int desc, MyServer *serv, QObject *parent = 0);
    ~MyClient();
    void setName(QString name) {_name = name;}
    QString getName() const {return _name;}
    bool getAutched() const {return _isAutched;}
    void doSendCommand(uint8_t comm, QString status="") const;

signals:
    void addUserToGui(QString name);
    void removeUserFromGui(QString name);
    void removeUser(MyClient *client);
    void messageToGui(QString message, QString from, const QStringList &users);
    void errorSignal(QString message);

private slots:
    void onConnect();
    void onDisconnect();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError) const;

private:
    QTcpSocket *_sok;
    MyServer *_serv;
    qint64 _blockSize;
    QString _name;
    bool _isAutched;
};

#endif // MYCLIENT_H
