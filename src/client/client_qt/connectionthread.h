#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <string>
#include <qthread.h>

using namespace std;

// A new thread to be started when submitting a solution to server. 
// Sends the problem, receives the response, and then emits the appropriate signal.
class ConnectionThread : public QThread
{
    Q_OBJECT

public:
    ConnectionThread(QObject* parent = 0);
    ~ConnectionThread() = default;

    // Use to submit a new problem.
    void sendProblem(string host_name, string port);
    void run() Q_DECL_OVERRIDE;

    // Listen to these for results.
signals:
    void sendingJson(QString json);
    void solution(QString json);
    void error(QString message);

private:
    string host;
    string port;
};

#endif // CONNECTIONTHREAD_H
