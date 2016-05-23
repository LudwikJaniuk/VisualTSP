#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <string>
#include <qthread.h>

using namespace std;

class ConnectionThread : public QThread
{
    Q_OBJECT

public:
    ConnectionThread(QObject* parent = 0);
    ~ConnectionThread() = default;

    void sendProblem(string host_name, string port);
    void run() Q_DECL_OVERRIDE;

signals:
    void sendingJson(QString json);
    void solution(QString json);
    void error(QString message);

private:
    string host;
    string port;
};

#endif // CONNECTIONTHREAD_H
