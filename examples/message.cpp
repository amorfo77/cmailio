/*

message.cpp
-----------

Various encodings when dealing with the message.
The example keeps code snippets in the various encodings. To see them properly, change the file encoding as marked in the snippet.


Copyright (C) 2022, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/


#include <iostream>
#include <cmailio/mailboxes.hpp>
#include <cmailio/message.hpp>


using std::cout;
using std::endl;
using std::string;
using cmailio::string_t;
using cmailio::mail_address;
using cmailio::mime;
using cmailio::message;


int main()
{
    // Set the file encoding to UTF-8 to properly see the letters in this snippet.
    {
        message msg;
        msg.header_codec(message::header_codec_t::QUOTED_PRINTABLE);
        msg.from(mail_address("mail io", "contact@cmailio.dev"));
        msg.add_recipient(mail_address("mail io", "contact@cmailio.dev"));
        // The subject is automatically determined as UTF-8 since it contains 8bit characters. It is encoded as Quoted Printable,
        msg.subject("Здраво, Свете!");
        msg.content("Hello, World!");
        string msg_str;
        msg.format(msg_str);
        cout << msg_str << endl;
    }

    // Set the file encoding to UTF-8 to properly see the letters in this snippet.
    {
        message msg;
        msg.header_codec(message::header_codec_t::UTF8);
        msg.from(mail_address("mail io", "contact@cmailio.dev"));
        msg.add_recipient(mail_address("mail io", "contact@cmailio.dev"));
        // The subject remains in 8bit because such header is set.
        msg.subject("Здраво, Свете!");
        msg.content("Hello, World!");
        string msg_str;
        msg.format(msg_str);
        cout << msg_str << endl;
    }

    // Set the file encoding to ISO-8859-2 to properly see the letters in this snippet.
    {
        message msg;
        msg.from(mail_address("mail io", "contact@cmailio.dev"));
        msg.add_recipient(mail_address("mail io", "contact@cmailio.dev"));
        msg.content_transfer_encoding(mime::content_transfer_encoding_t::QUOTED_PRINTABLE);
        msg.subject_raw(string_t("Zdravo, Sveti�u!", "iso-8859-2"));
        msg.content("Hello, World!");
        string msg_str;
        msg.format(msg_str);
        cout << msg_str << endl;
        // The subject is printed as `Zdravo, Svetiću!` in the ISO-8859-2 encoding.
    }

    // Set the file encoding to ISO-8859-5 to properly see the letters in this snippet.
    {
        message msg;
        msg.from(mail_address("mail io", "contact@cmailio.dev"));
        msg.add_recipient(mail_address("mail io", "contact@cmailio.dev"));
        msg.content_transfer_encoding(mime::content_transfer_encoding_t::BASE_64);
        msg.subject_raw(string_t("������, �����", "iso-8859-5"));
        msg.content("Hello, World!");
        string msg_str;
        msg.format(msg_str);
        cout << msg_str << endl;
        // The subject is printed as `=?ISO-8859-5?Q?=B7=D4=E0=D0=D2=DE,_=C1=D2=D5=E2=D5?=`.
    }

    // Set the file encoding to UTF-8 to properly see the letters in this snippet.
    {
        message msg;
        msg.from(mail_address("mail io", "contact@cmailio.dev"));
        msg.add_recipient(mail_address("mail io", "contact@cmailio.dev"));
        msg.content_transfer_encoding(mime::content_transfer_encoding_t::BASE_64);
        msg.subject_raw(string_t("Здраво, Свете!", "utf-8"));
        msg.content("Hello, World!");
        string msg_str;
        msg.format(msg_str);
        cout << msg_str << endl;
        // The subject is printed as `=?UTF-8?Q?=D0=97=D0=B4=D1=80=D0=B0=D0=B2=D0=BE,_=D0=A1=D0=B2=D0=B5=D1=82=D0=B5!?=`.
    }

    {
        string msg_str = "From: mail io <contact@cmailio.dev>\r\n"
            "To: mail io <contact@cmailio.dev>\r\n"
            "Date: Sat, 18 Jun 2022 05:56:34 +0000\r\n"
            "Subject: =?ISO-8859-2?Q?Zdravo,_Sveti=E6u!?=\r\n"
            "\r\n"
            "Zdravo, Svete!\r\n";
        message msg;
        msg.parse(msg_str);
        cout << msg.subject() << endl;
        // The subject is printed as `Zdravo, Svetiću!` in the ISO-8859-2 encoding.
    }

    {
        string msg_str = "From: mail io <contact@cmailio.dev>\r\n"
            "To: mail io <contact@cmailio.dev>\r\n"
            "Date: Sat, 18 Jun 2022 05:56:34 +0000\r\n"
            "Subject: =?ISO-8859-5?Q?=B7=D4=E0=D0=D2=DE,_=C1=D2=D5=E2=D5!?=\r\n"
            "\r\n"
            "Hello, World!\r\n";
        message msg;
        msg.parse(msg_str);
        cout << msg.subject() << endl;
        // The subject is printed as `Здраво, Свете!` in the ISO-8859-5 encoding.
    }

    {
        string msg_str = "From: mail io <contact@cmailio.dev>\r\n"
            "To: mail io <contact@cmailio.dev>\r\n"
            "Date: Sat, 18 Jun 2022 05:56:34 +0000\r\n"
            "Subject: =?UTF-8?Q?=D0=97=D0=B4=D1=80=D0=B0=D0=B2=D0=BE,_=D0=A1=D0=B2=D0=B5=D1=82=D0=B5!?=\r\n"
            "\r\n"
            "Hello, World!\r\n";
        message msg;
        msg.line_policy(cmailio::codec::line_len_policy_t::MANDATORY, cmailio::codec::line_len_policy_t::MANDATORY);
        msg.parse(msg_str);
        cout << msg.subject() << endl;
        // The subject is printed as `Здраво, Свете!` in the UTF-8 encoding.
    }

    return EXIT_SUCCESS;
}
