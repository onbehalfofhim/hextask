#include "myServer.h"

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent)
{
	qint16 port = 1234;

	if (!this->listen(QHostAddress::LocalHost, port)) {
		qDebug() << "Could not start server";
	}
	else {
		qDebug() << "Listening to port " << port << "...";
	}
}

void MyServer::incomingConnection(qintptr socket) {
	//qDebug() << socket << " Connecting...";

	socketDescriptor = socket;

	QTcpSocket* s = new QTcpSocket(this);
	addPendingConnection(s);
	s->setSocketDescriptor(socket);
	emit newConnection();

	connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
	connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
}

void MyServer::readClient() {
	QTcpSocket* socket = (QTcpSocket*)sender();
	if (socket->canReadLine()) {
		QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
		if ((tokens[0] == "GET" || tokens[0] == "POST") && (tokens[1] == "/test")) {
			QTextStream os(socket);
			os.setAutoDetectUnicode(true);
			os << "HTTP/1.0 200 Ok\r\n"
				"Content-Type: text/html; charset=\"utf-8\"\r\n"
				"\r\n"
				"<center><h1>Hello, World!</h1></center>\n";
			socket->close();

			//qDebug() << socketDescriptor << "Wrote to client";

			if (socket->state() == QTcpSocket::UnconnectedState) {
				delete socket;

				//qDebug() << socketDescriptor << "Connection closed";
			}
		}
	}
}

void MyServer::discardClient() {
	QTcpSocket* socket = (QTcpSocket*)sender();
	socket->deleteLater();

	//qDebug() << socketDescriptor << "Connection closed";
}