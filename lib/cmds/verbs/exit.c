/* Do not remove the headers from this file! see /USAGE for more info. */


inherit VERB_OB;


mixed can_exit_obj(object ob)
{
   return 1;
}

mixed can_exit()
{
  return 1;
}

void do_exit(object ob)
{
  mixed s;
  string err;
  object last_loc;
  

  if(objectp(ob) && ob != environment(this_body()))
    {
      write("You're not in it.\n");
      return;
    }
  last_loc = environment(this_body());

  if(s = environment(this_body())->exit())
    {
      if(!stringp(err=this_body()->move(environment(environment(this_body())))))
	{
	  if(stringp(s))
	    this_body()->simple_action(s);
	  else
	    this_body()->simple_action("$N $vexit the $o.\n", last_loc);
	}
      else
	{
	  write(err+"\n");
	}
    }
  else
    {
      if(environment(environment(this_body())))
	{
	  write("You can't seem to leave.\n");
	}
      else
	{
	  write("There is nothing to exit.\n");
	}
    }
} 

void do_exit_obj(object ob)
{
  do_exit(ob);
}


mixed * query_verb_info()
{
   return ({ ({ "OBJ", "", "STR" }) });
}
