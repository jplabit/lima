/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** user.c -- a user object
**
** This object represents a particular user and that user's connection.
**
** 95-Apr-30.  Deathblade.  Created.
*/

#include <mudlib.h>
#include <config.h>
#include <security.h>

inherit M_ACCESS;

inherit __DIR__ "user/login";
inherit __DIR__ "user/sw_body";
inherit __DIR__ "user/sw_user";
inherit __DIR__ "user/failures";
inherit __DIR__ "user/inputsys";
inherit __DIR__ "user/userinfo";
inherit __DIR__ "user/messages";
inherit __DIR__ "user/shell";

/*
** This users's userid (login id).
*/
private string		userid;


/*
//### hack variable :-)... used for upgrading existing data
//###
//### 0: original format
//### 1: fixed body_fname; was unknown whether "proper"
//### 2: renamed "name" variable to "userid"
//### 3: fixed crypt() to use a real salt (FORTHCOMING)
*/

//### temp: upgrading file
private int		data_version = 2;
//### old variable
private string		name;


nomask string query_userid()
{
    /*
    ** NOTE: allow this to return 0 so that callers can know that we
    ** are still in the login sequence.
    */
    return userid;
}
static nomask void set_userid(string new_userid)
{
    userid = new_userid;
}

void remove()
{
    object body = query_body();

    if ( body )
	destruct(body);

    remove_call_out();
    stop_shell();
    destruct();
}

void quit()
{
    object body = query_body();

    if ( body )
	body->quit();

    remove();
}

static nomask void save_me()
{
    unguarded(1, (: save_object, LINK_PATH(userid) :));
}

static nomask void restore_me(string some_userid, int preserve_vars)
{
//### always "read" this variable
    data_version = 0;

    unguarded(1, (: restore_object, LINK_PATH(some_userid), preserve_vars :));

//### upgrade old files
    if(query_body_fname() == "/std/player")
        set_body_fname(BODY);
    if ( data_version == 0 )
    {
	if ( !query_body_fname() )
	    set_body_fname(BODY);
	data_version = 1;
    }
    if ( data_version == 1 )
    {
	if ( !userid )
	{
	    userid = name;
	    name = 0;
	}
	data_version = 2;
    }
}

private nomask void net_dead()
{
    object body = query_body();

    /*
    ** Tell the body about the net death.  The user object should stick
    ** around, though, so we can find it again if the user reconnects.
    ** If there is no body yet, then just torch self.
    */
    if ( body )
    {
	body->net_dead();
	call_out((: remove :), 300);
    }
    else
    {
	remove();
    }
}
