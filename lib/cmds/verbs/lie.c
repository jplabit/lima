/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** lie.c
*/


inherit VERB_OB;


void do_lie_on_obj(object ob1)
{
  ob1->lie();
}

void do_lie()
{
  this_body()->simple_action("$N $vstate that $n $vare well hung.\n");
}

mixed array query_verb_info()
{
    return ({ ({ "on OBJ", ""}) });
}

