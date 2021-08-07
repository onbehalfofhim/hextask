// myServer.h

#ifndef MYSERVER_H
#define MYSERVER_H


#include <QTcpServer>
#include <QTcpSocket>

class MyServer : public QTcpServer {
	Q_OBJECT
public:
	MyServer(QObject *parent = 0);

protected:
	void incomingConnection(qintptr socket);

private slots:
	void readClient();
	void discardClient();

private:

	int socketDescriptor;
};

#endif //MYSERVER_H
