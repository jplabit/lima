/* Do not remove the headers from this file! see /USAGE for more info. */

#include <mudlib.h>

inherit VERB_OB;

void do_wait()
{
    write("Do I have to do EVERYTHING for you?\n");
}

mixed * query_verb_info()
{
  return ({ ({ 0 }) });
}
