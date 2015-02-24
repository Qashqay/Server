#include "myclient.h"
const QString MyClient::constNameUnknown = QString(".Unknown");
static int check=0;
static uint8_t norepete=0;
static int workint = 0;
MyClient::MyClient(int desc, MyServer *serv, QObject *parent) :QObject(parent)
{
    //храним указатель на объект-сервер
    _serv = serv;
    //клиент не прошел авторизацию
    _isAutched = false;
    _name = constNameUnknown;
    //размер принимаемого блока 0
    _blockSize = 0;
    //создаем сокет
    _sok = new QTcpSocket(this);
    //устанавливаем дескриптор из incomingConnection()
    _sok->setSocketDescriptor(desc);
    //подключаем сигналы
    connect(_sok, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

MyClient::~MyClient()
{

}
void MyClient::onConnect()
{
    //never calls, socket already connected to the tcpserver
}

void MyClient::onDisconnect()
{
    if (_isAutched)
    {
        //убирием из интерфейса
        if (_name!=".Unknown")
            emit removeUserFromGui(_name);
        //убираем из списка
        emit removeUser(this);
    }
    deleteLater();
}

void MyClient::onError(QAbstractSocket::SocketError socketError) const
{
    //w нужна для обсвобождения памяти от QMessageBox (посредством *parent = &w)
    QWidget w;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(&w, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(&w, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(&w, "Error", "The following error occurred: "+_sok->errorString());
    }
    //тут вызовутся деструктор w и соответственно QMessageBox (по правилам с++)
}

void MyClient::onReadyRead()
{

    QDataStream in(_sok);
    QFile file("error.log");
    long load;
    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(qint64))
        {
            if (file.open(QIODevice::Append))
            {
                QTextStream stream(&file);
                stream <<"Error in line 81"<<"\r\n";
                stream << endl;
                file.close();
            }
            return;
        }
        //считываем размер (2 байта)
        in>>_blockSize;
    }
    load=static_cast<long>(_blockSize);
    qDebug()<<"bytesavailable"<<_sok->bytesAvailable()<<_sok->localPort();
    qDebug()<<"_blockSize1"<<_blockSize;
    //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
    {
        if (file.open(QIODevice::Append))
        {
            QTextStream stream(&file);
            stream <<"Error in line 99"<<"\r\n";
            stream << endl;
            file.close();
        }
        return;
    }
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in>>command;
    qDebug() << "Received command " << command<<"on host"<<_sok->localPort();
    if (_sok->localPort()==FIRST_PORT)
    {
        if (!_isAutched &&command!=comMessageFromProg && command != comAutchReq && command !=comCheck  && command!=comMilReady && command!=comMilOut&&command!=comStopSendInterf&&command!=comSendInterf&&command!=comFullSendInterf)
        {
            if (file.open(QIODevice::Append))
            {
                QTextStream stream(&file);
                stream <<"Error in line 119"<<"\r\n";
                stream << endl;
                file.close();
            }
            return;
}
        switch(command)
        {
            //запрос на авторизацию
            case comAutchReq:
            {
                //считываем имя
                QString name;
                in>>name;
                //проверяем его
                if (!_serv->isNameValid(name))
                {
                    //отправляем ошибку
                    doSendCommand(comErrNameInvalid);
                    //return;
                }
                //проверяем не используется ли имя
                if (_serv->isNameUsed(name))
                {
                    //отправляем ошибку

                    doSendCommand(comErrNameUsed);
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 149"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                //авторизация пройдена
                _name = name;
                _isAutched = true;
                emit addUserToGui(name);
                if (workint == 0)
                    doSendCommand(comMilOut);
                else if (workint == 1)
                    doSendCommand(comMilReady,QString::number(norepete));
            }
            break;
            case comMessageFromProg:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char Buffer[100];
                if (load>99)
                {
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 175"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                memset(Buffer,0,100);
                _sok->read(Buffer,load);
                message=QString::fromAscii(Buffer);;
                //отправляем его всем
                _isAutched = true;
                _serv->doSendToAllMessage(message,"MainProg",_sok->localPort());
                //обновляем лог событий
                emit messageToGui(message, "MainProg", QStringList());

            }
            break;
            case comSendLastLog:
            {
                if(_serv->_logged.length()!= 0)
                {
                    _serv->doSendLastLog(_serv->_logged.at(_serv->_logged.length()-1),_sok->localPort());
                }
            }
            break;
            case comSendAllLog:
            {
                QString b;
                if(_serv->_logged.length()!= 0)
                {
                    for (int i=0;i<_serv->_logged.length();++i)
                        b +=_serv->_logged.at(i)+",";
                    _serv->doSendAllLog(b,_sok->localPort());
                }
                else
                    _serv->doSendAllLog("Empty list",_sok->localPort());
            }
            break;
            case comNormalMode:
            {
                if(check!=0 || norepete==comNormalMode)
                    doSendCommand(comNormalMode);
                else
                    check=1; norepete=comNormalMode;
            }
            break;
            case comDrop:
            {
                if(check!=0)
                    doSendCommand(comNormalMode);
                else
                    check=3; norepete=comDrop;
            }
            break;
            case comDropToNorm:
            {
                if(check!=0)
                    doSendCommand(comNormalMode);
                else
                    check=3; norepete=comDropToNorm;
            }
            break;
            case comStop:
            {
                if(check!=0 || norepete==comStop)
                    doSendCommand(comNormalMode);
                else
                    check=4; norepete=comStop;
            }
            break;
            case comPowerOff:
            {
                if(check!=0 || norepete==comPowerOff)
                    doSendCommand(comNormalMode);
                else
                {
                    check=5;
                    norepete=comPowerOff;
                }
            }
            break;
            case comSendInterf:
            {
                check=6;
            }
            break;
            case comFullSendInterf:
            {
                check=8;
            }
            break;
            case comStopSendInterf:
            {
                check=7;
            }
            break;
            case comCheck:
            {
                if (check==1)
                {
                    _serv->doSendToAllProgramMessage("11",1232);
                }
                else if (check==2)
                {
                    _serv->doSendToAllProgramMessage("22",1232);
                }
                else if (check==3)
                {
                    _serv->doSendToAllProgramMessage("33",1232);
                }
                else if (check==4)
                {
                    _serv->doSendToAllProgramMessage("44",1232);
                }
                else if (check==5)
                {
                    _serv->doSendToAllProgramMessage("5",1232);
                    system("shutdown -s -f -t 30");
                }
                else if (check==6)
                {
                    _serv->doSendToAllProgramMessage("6",1232);
                }
                else if (check==7)
                {
                    _serv->doSendToAllProgramMessage("7",1232);
                }
                else if (check==8)
                {
                    _serv->doSendToAllProgramMessage("8",1232);
                }
                else
                {
                    _serv->doSendToAllProgramMessage("0",1232);
                }
                check=0;
                workint=1;
            }
            break;
            case comMilReady:
            {
                _isAutched = true;
                _serv->doSendServCommand(comMilReady,_sok->localPort());

            }
            break;
            case comMilOut:
            {
                _isAutched = true;
                _serv->doSendServCommand(comMilOut,_sok->localPort());
                workint = 0;
                check = 0;
            }
            break;
            default:
            {
                QString message;
                in>>message;
                qDebug()<<"wow1"<<message;
            }
        }
    }
    else if(_sok->localPort()==FIRST_PORT+1)
    {
        if (!_isAutched && command != comAutchReq && command !=comMessageFromProg && command!=comStatusInt)
        {
            if (file.open(QIODevice::Append))
            {
                QTextStream stream(&file);
                stream <<"Error in line 344"<<"\r\n";
                stream << endl;
                file.close();
            }
            return;
        }
        switch (command)
        {
            case comAutchReq:
            {
                //считываем имя
                QString name;
                in>>name;
                //проверяем его
                if (!_serv->isNameValid(name))
                {
                    //отправляем ошибку
                    doSendCommand(comErrNameInvalid);
                    //return;
                }
                //проверяем не используется ли имя
                if (_serv->isNameUsed(name))
                {
                    //отправляем ошибку
                    doSendCommand(comErrNameUsed);
                    {
                        if (file.open(QIODevice::Append))
                        {
                            QTextStream stream(&file);
                            stream <<"Error in line 373"<<"\r\n";
                            stream << endl;
                            file.close();
                        }
                    return;
                    }
                }
                //авторизация пройдена
                _name = name;
                _isAutched = true;
                emit addUserToGui(name);
            }
            break;
            case comMessageFromProg:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char Buffer[100];
                memset(Buffer,0,100);
                if (load>99)
                {
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 397"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                _sok->read(Buffer,load);
                message=QString::fromAscii(Buffer);;
                //отправляем его всем
                _isAutched = true;
                _serv->doSendToAllMessage(message,"MainProg",_sok->localPort());
                //обновляем лог событий
                emit messageToGui(message, "MainProg", QStringList());

            }
            break;
            case comStatusInt:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char Buffer[128];
                if (load>127)
                {
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 423"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                memset(Buffer,0,128);
                _sok->read(Buffer,load);
                message=QString::fromAscii(Buffer);;
                _isAutched = true;
                _serv->doSendStatus(message,_sok->localPort());
                emit messageToGui(message, "CurrentStatus", QStringList());
            }
            break;
            default:
            {
                QString message;
                in>>message;
                qDebug()<<"wow2"<<message;
            }
        }
    }
    else
    {
    if (!_isAutched && command != comAutchReq && command !=comMessageFromProg && command !=comInterf&&command!=comMessageToAll&&command!=comTempStat&&command!=comContrast)
        return;
        switch(command)
        {
            case comAutchReq:
            {
                //считываем имя
                QString name;
                in>>name;
                //проверяем его
                if (!_serv->isNameValid(name))
                {
                    //отправляем ошибку
                    doSendCommand(comErrNameInvalid);
                    //return;
                }
                //проверяем не используется ли имя
                if (_serv->isNameUsed(name))
                {
                    //отправляем ошибку
                    doSendCommand(comErrNameUsed);
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 470"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                //авторизация пройдена
                _name = name;
                _isAutched = true;
                emit addUserToGui(name);
            }
            break;
            case comMessageFromProg:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char *Buffer=(char*)malloc((load)*sizeof(char));
                Buffer[load-1]=NULL;
                _sok->read(Buffer,load-1);
                message=QString::fromAscii(Buffer);
                _isAutched = true;
                _serv->doSendToAllMessage(message,"MainProg",_sok->localPort());
                emit messageToGui(message, "MainProg", QStringList());
                free(Buffer);
            }
            break;
            case comMessageToAll:
            {
                QString message;
                in>>message;
                _serv->doSendToAllMessage(message, _name,_sok->localPort());
                emit messageToGui(message, _name, QStringList());
            }
            break;
            case comInterf:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char *Buffer=(char*)malloc((load)*sizeof(char));
                Buffer[load-1]=NULL;
                _sok->read(Buffer,load-1);
                message=QString::fromAscii(Buffer);
                _isAutched = true;
                _serv->doSendFuckingMessage(message,1237);
                free(Buffer);
            }
            break;
            case comTempStat:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char Buffer[32];
                if (load>31)
                {
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 528"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                memset(Buffer,0,32);
                _sok->read(Buffer,load);
                message=QString::fromAscii(Buffer);;
                _isAutched = true;
                _serv->doSendTemp(message,_sok->localPort());
            }
            break;
            case comContrast:
            {
                QString message;
                setlocale (LC_ALL,"Russian");
                char Buffer[512];
                if (load>511)
                {
                    if (file.open(QIODevice::Append))
                    {
                        QTextStream stream(&file);
                        stream <<"Error in line 551"<<"\r\n";
                        stream << endl;
                        file.close();
                    }
                    return;
                }
                memset(Buffer,0,512);
                _sok->read(Buffer,load);
                message=QString::fromAscii(Buffer);
                if (message.toFloat())

                _isAutched = true;
                _serv->doSendContrast(message,_sok->localPort());
                qDebug()<<"send Contrast";
                emit messageToGui(message, "Contrast", QStringList());
            }
            break;
            default:
            {
                QString message;
                in>>message;
                qDebug()<<"wow3"<<message;
            }
        }
    }
}

void MyClient::doSendCommand(uint8_t comm,QString status) const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (qint64)0;
    out << comm;
    out<<status;
    out.device()->seek(0);
    out << static_cast<quint64>(block.size() - sizeof(qint64));
    _sok->write(block);
    qDebug() << "Send to" << _name << "command:" << comm;
}
