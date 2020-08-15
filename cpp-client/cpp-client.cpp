#include "lib/sioclient/sio_client.h"

#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <boost/math/constants/constants.hpp>

#ifdef WIN32
#define HIGHLIGHT(__O__) std::cout<<__O__<<std::endl
#define EM(__O__) std::cout<<__O__<<std::endl

#include <stdio.h>
#include <tchar.h>
#define MAIN_FUNC int _tmain(int argc, _TCHAR* argv[])
#else
#define HIGHLIGHT(__O__) std::cout<<"\e[1;31m"<<__O__<<"\e[0m"<<std::endl
#define EM(__O__) std::cout<<"\e[1;30;1m"<<__O__<<"\e[0m"<<std::endl

#define MAIN_FUNC int main(int argc ,const char* args[])
#endif

using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
bool connect_finish = false;

class connection_listener
{
    sio::client& handler;

public:

    connection_listener(sio::client& h) :
        handler(h)
    {
    }


    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
        std::cout << "sio closed " << std::endl;
        exit(0);
    }

    void on_fail()
    {
        std::cout << "sio failed " << std::endl;
        exit(0);
    }
};

socket::ptr current_socket;

void bind_events()
{
    current_socket->on("cpp-ping", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck, message::list& ack_resp)
        {
            current_socket->emit("cpp-pong");
        }));

    current_socket->on("slider-value", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck, message::list& ack_resp)
        {
            string value = data->get_string();
            double perimeter = 2 * boost::math::constants::pi<double>() * std::stoi(value);      
            string change = boost::lexical_cast<string>(perimeter);
            current_socket->emit("circle-change", change);
        }));
}

MAIN_FUNC
{

    sio::client h;
    connection_listener l(h);

    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
    h.connect("http://127.0.0.1:9000");
    _lock.lock();
    if (!connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
    current_socket = h.socket();
    bind_events();

    std::cout << "Enter \"exit\" to kill process." << std::endl;
    for (std::string line; std::getline(std::cin, line);) {
        if (line.length() > 0)
        {
            if (line == "exit")
            {
                break;
            }
        }
    }
    HIGHLIGHT("Closing...");
    h.sync_close();
    h.clear_con_listeners();
    return 0;
}
