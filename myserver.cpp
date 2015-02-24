#include "myserver.h"

MyServer::MyServer(QWidget *widget, QObject *parent) :QTcpServer(parent)
{
    _widget = widget;
}

bool MyServer::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
        qDebug() << "Server not started at" << addr << ":" << port;
        return false;
    }
    else
    {
        qDebug() << "Server started at" << addr << ":" << port;
        return true;
    }
}

void MyServer::doSendToAllMessage(QString message, QString fromUsername,int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64) 0 << MyClient::comMessageToAll << fromUsername << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    qDebug()<<static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!=".Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}

void MyServer::doSendFuckingMessage(QString message, int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64) 0 << MyClient::comMessageToAll << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    qDebug()<<static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!=".Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}

void MyServer::doSendStatus(QString message, int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << MyClient::comStatusInt << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!="Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}

void MyServer::doSendTemp(QString message, int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << MyClient::comTempStat << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!="Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}
void MyServer::doSendContrast(QString message, int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << MyClient::comContrast << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!="Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}
void MyServer::doSendServCommand(uint8_t comm,int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << comm;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!=".Unknown"&&_clients.at(i)->_sok->localPort()==port)
        { _clients.at(i)->_sok->write(block);}
}

void MyServer::doSendToAllProgramMessage(const char* a, int port)
{
    for(int i=0;i<_clients.length();++i)
        if((_clients.at(i)->getName()==".Unknown")&&(_clients.at(i)->_sok->localPort()==port))
        {
            _clients.at(i)->_sok->write(a);
            return;
        }
}

void MyServer::doSendLastLog(QString message, int port )
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << MyClient::comSendLastLog << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!=".Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}

void MyServer::doSendAllLog(QString message,int port)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0 << MyClient::comSendAllLog << message;
    out.device()->seek(0);
    out << static_cast<qint64>(block.size() - sizeof(qint64));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched()&&_clients.at(i)->getName()!=".Unknown"&&_clients.at(i)->_sok->localPort()==port)
            _clients.at(i)->_sok->write(block);
}

bool MyServer::isNameValid(QString name) const
{
    if (name.length() > 20 || name.length() < 5)
        return false;
    QRegExp r("[A-Za-z0-9_]+");
    return r.exactMatch(name);
}

bool MyServer::isNameUsed(QString& name) const
{
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() == name)
        {
            return false;
        }
    return false;
}

void MyServer::incomingConnection(int handle)
{
    //создаем клиента
    MyClient *client = new MyClient(handle, this, this);
    if (_widget != 0)
    {
        connect(client, SIGNAL(addUserToGui(QString)), _widget, SLOT(onAddUserToGui(QString)));
        connect(client, SIGNAL(removeUserFromGui(QString)), _widget, SLOT(onRemoveUserFromGui(QString)));
        connect(client, SIGNAL(messageToGui(QString,QString,QStringList)), _widget, SLOT(onMessageToGui(QString,QString,QStringList)));
    }
    connect(client, SIGNAL(removeUser(MyClient*)), this, SLOT(onRemoveUser(MyClient*)));
    _clients.append(client);
}

void MyServer::onRemoveUser(MyClient *client)
{
    _clients.removeAt(_clients.indexOf(client));
}
