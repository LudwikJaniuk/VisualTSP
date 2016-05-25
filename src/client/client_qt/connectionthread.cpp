#include <string>
#include <iostream>
#include <random>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "common.h"
#include "connectionthread.h"

using boost::asio::ip::tcp;

ConnectionThread::ConnectionThread(QObject* parent)
{}

void ConnectionThread::sendProblem(string host, string port)
{
    cout << "Sendproblem slot with host " << host << endl;
    this->host = host;
    this->port = port;
    // TONEVERDO: This should actually check if the thread is already running etc,
    // but we dont have time for that.
    // This starts the thread, make run() run in the separate thread;
    start();
}

string make_json();
coord_t rand_coord_t(minstd_rand&);

// Handles the whole sending-receiving job.
void ConnectionThread::run()
{
    cout << "Run started." << endl;

    try
    {
        emit sendingJson(QString::fromStdString("Gonna send to " + host + port));
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        // Now the connection is open, and we need to read the response.

        boost::array<char, 128> buf;
        boost::system::error_code err;

        string msg = make_json();
        cout << "Client Sending: " << msg << endl;
        emit sendingJson(QString::fromStdString(msg));
        socket.write_some(boost::asio::buffer(msg, msg.length()), err);

        if (err) {
            cout << "Error sending data: " <<  err << endl;
        }
        cout << "Received: ";

	// We'll keep writing to this buffer as long as we're getting new data.
        ostringstream buf_stream;
        while (true)
        {
            size_t len = socket.read_some(boost::asio::buffer(buf), err);

            if (err == boost::asio::error::eof) // Clean close
            {
                break;
            }
            else if (err)
            {
                throw boost::system::system_error(err);
            }
            buf_stream.write(buf.data(), len);
        }
        string solution_json = buf_stream.str();
        emit solution(QString::fromStdString(solution_json));
    }
    catch (std::exception& e)
    {
        emit error(e.what());
    }

    cout << "Now we will exit." << endl;
}

// Generated random json problem.
// TODO: Maybe add parameters, eg. problem size?
string make_json()
{
    minstd_rand rand_eng;
    path_t nodes;
    for (int i = 0; i < 7; i++) {
        point_t pos(rand_coord_t(rand_eng)*2 - 1,
                    rand_coord_t(rand_eng)*2 - 1,
                    rand_coord_t(rand_eng)*2 - 1);
        Node node{pos, i};
        nodes.push_back(node);
    }
	random_shuffle(nodes.begin(), nodes.end());
    return path_to_json(nodes);
}

coord_t rand_coord_t(minstd_rand& eng)
{
    return eng()/(coord_t)eng.max();
}

