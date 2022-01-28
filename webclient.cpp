#include "webclient.h"
#include <thread>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(input, &QLineEdit::returnPressed, this, &Webclient::button_clicked);

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::socketconnect);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::pd);
    connect(button, &QPushButton::clicked, this, &Webclient::button_clicked);

}

void Webclient::textoutput(QString message)
{
    output->clear();
    output->setText(message);
}

void Webclient::socketconnect()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_search + "\r\n\r\n").toLocal8Bit());
}

void Webclient::pd()
{
    textoutput(m_socket->readAll());
    m_socket->disconnectFromHost();
}

void Webclient::button_clicked()
{

    m_socket->connectToHost(input->text(), m_port);

    if(!m_socket->waitForConnected(3000))
    {
        textoutput("connect failed!");
        m_socket->reset();

    }



}
