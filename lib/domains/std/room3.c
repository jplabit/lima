/* Do not remove the headers from this file! see /USAGE for more info. */

 /* Do not remove the headers from this file! see /USAGE for more info. */
  
    // Beek - a simple room to demonstrate relationships and some toys
  
#include <mudlib.h>
  
inherit ROOM;
  
void setup()
{
    set_brief("Barney's Cave");
    set_long("You are standing in Barney's Cave.  It is dominated by the "
	     "presence of it's distinguished occupant.");
    set_exits( ([ "north" : "room2" ]) );
    set_objects( ([
	"/domains/std/barney" : 1
	]) );
}
