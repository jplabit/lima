/* Do not remove the headers from this file! see /USAGE for more info. */

#include <mudlib.h>
inherit ROOM;

create()
{
  function array m =({(: write("The mountains are too steep to climb.  You'd have to go around them...\n"):)});
  function array o =({ (: write("You would drown!\n") :) });
  room::create();
  set_brief("Sandy beach");
  set_long("The waves lap happily onto this sandy beach, which ends here -- the mountains barely meet the water, leaving not even a grain of sand on which to walk."); 
  set_light(1);
  set_exits( ([
	       "northeast" :  m,
	       "northwest" :  m,
	       "north" : m,
	       "west" : m,
	       "east" : m,
	       "south" : o,
	       "southeast" : o,
	       "southwest" : o,
	       ]) );

  add_item( "surf", "water", "waves", 
	 ([ 
	   "adjs" : ({ "strong", "fierce" }),
	   "look" : "The waves look fierce.",
	   "swim" : "As the tide is particularly strong, you'd prefer to "
	            "keep standing.",
	   ]));

  add_item( "tide", "You can't look at it, but if you were to wade in the "
	    "water, you sure would feel it." );

  add_item("ocean", 
	   ([ 
	     "look" :  "You strain to see the other side of the "
	   "ocean, but fail.  You do notice something, however you can't "
	   "quite make out what.  Perhaps a ship?",
	   "swim" : "As the tide is particularly strong, you'd prefer to "
	            "keep standing.", 
	     ]));


  add_item("mountains", 
	   ([
	     "adjs" : "steep", // Can also use an array...
	     "look" : "They are too steep to climb.",
	     "climb" : "They are too steep to climb." 
	     ]));

  add_item("hills", "They're not hills, they're mountains!");
	       
  set_hidden_exits("northeast","northwest","south","southeast","southwest", 
		   "north", "west", "east");
  set_objects( ([
		 "/domains/std/objects/sand_castle" : 1,
		 "/domains/std/objects/sand_with_treasure" : 1,
		 "/domains/std/objects/welcome_sign" : 1,

  ]) );
}

mixed wade(string str)
{
  switch(str)
    {
    case 0:
      write("[in the water]\n");
    case "water":
    case "waves":
    case "surf":
    case "ocean":
      write ( wrap("You wade into the ocean.  Though the undercurrent "
		   "is strong, you manage to keep your balance.  You wander "
		   "towards the east, where there is no beach, but there are "
		   "interesting mountains...\n\n"));
      this_body()->other_action("$N $vwade around in the ocean for a while, "
				"eventually wandering out of sight to the "
				"east.\n");
      this_body()->move(__DIR__ "outside_cave");
      QUEST_D->grant_points(this_body(),"pirate:foundCave");
      this_body()->do_game_command("look");
      this_body()->other_action("$N $vwade over to you.\n");
      return 1;
    default:
      return "How stupid!\n";
    }
}

