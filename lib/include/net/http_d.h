/* Do not remove the headers from this file! see /USAGE for more info. */

/*
 * Config file for LIMA HTTP server
 * 01-05-96 Cowl
 *
 */
#ifndef __HTTP_D_H__
#define __HTTP_D_H__

// this is the port where the http server will live
#define HTTP_PORT 		__PORT__+80

// this is the directory that the http server will use as it's root
#define HTTP_ROOT 		"/WWW"

// this is the directory inside a wizard's home directory that will be
// checked for homepages etc..
#define HTTP_USER_HOME 		"/WWW"

// this is the default page if the URL given is a directory
#define DEFAULT_PAGE 		"index.html"

// this is where the server will look for all gateways, regardless of where
// thier URL claims they are located.
#define SECURE_CGI_DIR 	HTTP_ROOT + "/cgi"

#endif
