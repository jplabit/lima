/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** put.c
**
*/

#include <move.h>

inherit VERB_OB;

void do_put_obj_wrd_obj(object ob1, string p, object ob2) {
    mixed tmp;
    string prep;

    if (!try_to_acquire(ob1))
	return;

    tmp = ob1->move(ob2, p);
    if (tmp == MOVE_OK) {
	switch (p) {
	case "in":
	    prep = "into";
	    break;
	case "on":
	    prep = "onto";
	    break;
	}
	write("Done.\n");
	this_body()->other_action("$N $vput a $o " + prep + " the $o1.\n", ob1, ob2);
	return;
    }
    if (!tmp) tmp = "That doesn't seem possible.\n";
    write(tmp);
}

mixed * query_verb_info()
{
    return ({
	({ "OBS WRD OBJ", "OBJ WRD OBJ" }), ({ "insert", "place", "stuff" })
	  });
    
    /*
    ** "hide OBS next to OBJ" -> "put OBS next to OBJ"
    ** "hide OBS beside OBJ" -> "put OBS beside OBJ"
    ** "hide OBS with OBJ" -> "put OBS with OBJ"
    */
}


