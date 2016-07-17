#ifndef _HEADER_MAIL
#define _HEADER_MAIL
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

#define FROM    "hjuesa.kjjulopp@gmail.com"
#define TO      "zwesioc.gju@gmail.com"
#define CC      "zwesioc.gju@gmail.com"

static const char *payload_text[] = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: " TO "\r\n",
  "From: " FROM "(Example User)\r\n",
  "Cc: " CC "(Another example User)\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
  "rfcpedant.example.org>\r\n",
  "Subject: SMTP TLS example message for MDkey\r\n",
  "\r\n", /* empty line to divide headers from body, see RFC5322 */ 
  "The body of the message tiny learning MACRO.\r\n",
  "\r\n",
  "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
  "Check RFC5322.\r\n",
  NULL
};
 
struct upload_status {
  int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
void *send_mail();

#endif
