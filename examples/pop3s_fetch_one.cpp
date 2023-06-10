/*

pop3s_fetch_one.cpp
-------------------

Connects to POP3 server via SSL and fetches first message from mailbox.


Copyright (C) 2016, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/


#include <cmailio/message.hpp>
#include <cmailio/pop3.hpp>
#include <iostream>


using cmailio::message;
using cmailio::codec;
using cmailio::pop3s;
using cmailio::pop3_error;
using cmailio::dialog_error;
using std::cout;
using std::endl;


int main()
{
    try
    {
        // mail message to store the fetched one
        message msg;
        // set the line policy to mandatory, so longer lines could be parsed
        msg.line_policy(codec::line_len_policy_t::RECOMMENDED, codec::line_len_policy_t::MANDATORY);

        // connect to server
        pop3s conn("pop.mail.yahoo.com", 995);
        // modify to use existing yahoo account
        conn.authenticate("cmailio@yahoo.com", "cmailiopass", pop3s::auth_method_t::LOGIN);
        // fetch the first message from mailbox
        conn.fetch(1, msg);
        cout << msg.subject() << endl;
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
