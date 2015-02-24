#include "dialog.h"
#include "ui_dialog.h"
#include "myserver.h"
Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    _servMany = new MyServer*[SERVER_COUNT];
    for (int i=0;i<SERVER_COUNT;++i)
        _servMany[i] = new MyServer(this,this);
    for (int i=0;i<SERVER_COUNT;++i)
    {
        connect(_servMany[i], SIGNAL(addLogToGui(QString,QColor)), this, SLOT(onAddLogToGui(QString,QColor)));
    }
    QHostAddress addr;
    QFile file("../serverIP.ini");
    QString IPaddr;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream >>IPaddr;
        file.close();
    }
    else
        IPaddr="192.168.0.10";
    ui->leHost->setText(IPaddr);
    addr.setAddress(IPaddr);
    for (int i=0;i<SERVER_COUNT;++i)
    {
        if (_servMany[i]->doStartServer(addr, FIRST_PORT+i))
        {
            ui->lwLog->insertItem(0, QTime::currentTime().toString()+" working "+_servMany[i]->serverAddress().toString()+":"+QString::number(_servMany[i]->serverPort()));
            ui->lwLog->item(0)->setTextColor(Qt::green);
        }
        else
        {
            ui->lwLog->insertItem(0, QTime::currentTime().toString()+" not working "+_servMany[i]->serverAddress().toString()+":"+QString::number(_servMany[i]->serverPort()));
            ui->lwLog->item(0)->setTextColor(Qt::red);
            ui->pbStartStop->setChecked(true);
        }
    }
    _servMany[0]->doSendToAllProgramMessage("0",1232);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onAddUserToGui(QString name)
{
    ui->lwUsers->addItem(name);
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+name);
    ui->lwLog->item(0)->setTextColor(Qt::green);
}

void Dialog::onRemoveUserFromGui(QString name)
{
    for (int i = 0; i < ui->lwUsers->count(); ++i)
        if (ui->lwUsers->item(i)->text() == name)
        {
            ui->lwUsers->takeItem(i);
            ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+name+" left");
            ui->lwLog->item(0)->setTextColor(Qt::green);
            break;
        }
}

void Dialog::onMessageToGui(QString message, QString from, const QStringList &users)
{
    if (from=="Contrast")
    {
        if (users.isEmpty())
        {
            ui->lContrast->setText(message);
        }
        else
        {
            ui->lContrast->setText(message);
        }
    }
    else
    {
        if (users.isEmpty())
        {
            ui->lwLog->insertItem(0, QDate::currentDate().toString(Qt::SystemLocaleDate)+message+" dT="+ui->lContrast->text());
            _servMany[0]->_logged.append(QDate::currentDate().toString(Qt::SystemLocaleDate)+" "+message+" dT="+ui->lContrast->text());
        }
        else
        {
            ui->lwLog->insertItem(0, QDate::currentDate().toString(Qt::SystemLocaleDate)+message+" dT="+ui->lContrast->text());
            ui->lwLog->item(0)->setTextColor(Qt::blue);
            _servMany[0]->_logged.append(QDate::currentDate().toString(Qt::SystemLocaleDate)+" "+message+" dT="+ui->lContrast->text());
        }
    }
}

void Dialog::onAddLogToGui(QString string, QColor color)
{
    addToLog(string, color);
}

void Dialog::on_pbSend_clicked()
{
    if (ui->lwUsers->count() == 0)
    {
        QMessageBox::information(this, "", "No clients connected");
        return;
    }
    QStringList l;
    if (!ui->cbToAll->isChecked())
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
        {
            l << i->text();
        }
    if (l.isEmpty())
        addToLog(ui->pteMessage->document()->toPlainText(), Qt::black);
    else
        addToLog(l.join(","), Qt::black);
    ui->pteMessage->clear();
}

void Dialog::on_cbToAll_clicked()
{
    if (ui->cbToAll->isChecked())
        ui->pbSend->setText("Send");
    else
        ui->pbSend->setText("Privat");
}


void Dialog::on_pbStartStop_toggled(bool checked)
{
    if (checked)
    {
        for (int i=0;i<SERVER_COUNT;++i)
        {
            addToLog(" server stopped at "+_servMany[i]->serverAddress().toString()+":"+QString::number(_servMany[i]->serverPort()), Qt::green);
            for(int i=0;i<SERVER_COUNT;++i)
                _servMany[i]->close();
            ui->pbStartStop->setText("Start server");
        }
    }
    else
    {
        for (int i=0;i<SERVER_COUNT;++i)
        {
            QHostAddress addr;
            if (!addr.setAddress(ui->leHost->text()))
            {
                addToLog(" invalid address "+ui->leHost->text(), Qt::red);
                return;
            }
            if (_servMany[i]->doStartServer(addr, FIRST_PORT+i))
            {
                addToLog(" server strated at "+ui->leHost->text()+":"+QString::number(FIRST_PORT+i), Qt::green);
                ui->pbStartStop->setText("Change IP");
            }
            else
            {
                addToLog(" server not strated at "+ui->leHost->text()+":"+QString::number(FIRST_PORT+i), Qt::red);
                ui->pbStartStop->setChecked(true);
            }
        }
    }
}

void Dialog::addToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0,text);
    ui->lwLog->item(0)->setTextColor(color);
}
