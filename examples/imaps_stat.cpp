/*

imaps_stat.cpp
--------------
  
Connects to IMAP server and gets number of messages in mailbox.


Copyright (C) 2016, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/


#include <iostream>
#include <cmailio/imap.hpp>


using cmailio::imaps;
using cmailio::imap_error;
using cmailio::dialog_error;
using std::cout;
using std::endl;


int main()
{
    try
    {
        // connect to server
        imaps conn("imap.zoho.com", 993);
        // modify to use an existing zoho account
        conn.authenticate("cmailio@zoho.com", "cmailiopass", imaps::auth_method_t::LOGIN);
        // query inbox statistics
        imaps::mailbox_stat_t stat = conn.statistics("inbox");
        cout << "Number of messages in mailbox: " << stat.messages_no << endl;
    }
    catch (imap_error& exc)
    {
        cout << exc.what() << endl;
    }
    catch (dialog_error& exc)
    {
        cout << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
