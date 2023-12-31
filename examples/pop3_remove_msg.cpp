/*

pop3_remove_msg.cpp
-------------------

Connects to POP3 server and removes first message in mailbox.


Copyright (C) 2016, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/


#include <iostream>
#include <cmailio/pop3.hpp>


using cmailio::pop3;
using cmailio::pop3_error;
using cmailio::dialog_error;
using std::cout;
using std::endl;


int main()
{
    try
    {
        // use a server with plain (non-SSL) connectivity
        pop3 conn("pop.mailserver.com", 110);
        // modify to use real account
        conn.authenticate("cmailio@mailserver.com", "cmailiopass", pop3::auth_method_t::LOGIN);
        // remove first message from mailbox
        conn.remove(1);
    }
    catch (pop3_error& exc)
    {
        cout << exc.what() << endl;
    }
    catch (dialog_error& exc)
    {
        cout << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
