/* Do not remove the headers from this file! see /USAGE for more info. */

#include <mudlib.h>

inherit CMD;
inherit M_GLOB;
inherit M_REGEX;

/*
** Pairs of info for each column.  ( header-index, field-width )
** The header indices can be seen from the headers[] array below.
**
** NOTE: at the moment, the first two elements must specify the "Up"
**       state and the mud name
*/
#define INFO_DEFAULT	({ \
    ({ 0, 2 }), ({ 11, 16 }), \
    ({ 1, 15 }), ({ 2, 5 }), ({ 5, 15 }), ({ 9, 19 }) })

#define INFO_MUDTYPE	({ \
    ({ 0, 2 }), ({ 11, 20 }), \
    ({ 1, 15 }), ({ 2, 5 }), ({ 8, 8 }), ({ 9, 19 }) })


static private string * headers = ({
    "Up",
    "Address",
    "",		/* port */
    "",		/* TCP OOB port */
    "",		/* UDP OOB port */
    "Lib",
    "Base Lib",
    "Driver",
    "Type",
    "Open Status",
    "Admin Email",

    "Mud",	/* special... mudname. not part of the mud info */
});


private void main(mixed *arg, mapping flags)
{
    mapping	mudlist = IMUD_D->query_mudlist();
    string*	muds = keys(mudlist);
    string*	matches;
    int		matched;
    int		upcount;
    string	match;
    mixed*	mudinfo;
    string	output;
    mixed *	info;
    string	format;
    string	search_str;

    if ( !arg || stringp(arg) )
    {
	arg = ({ 0 });
	flags = ([ ]);
    }

    if ( !arg[0] )
	matches = muds;
    else
    {
	matches = insensitive_regexp(muds, "^" + translate(arg[0]));
	if ( !sizeof(matches) )
	{
	    printf("No muds out of %d match that pattern.\n", sizeof(mudlist));
	    return;
	}
    }

    if ( flags["t"] )
	info = INFO_MUDTYPE;
    else
	info = INFO_DEFAULT;

    search_str = flags["s"];

	

    format = implode(info, (: $1 + sprintf("%%-%ds ", $2[1]) :), "");
    format[<1] = '\n';

    matched = sizeof(matches);

    if ( flags["a"] )
    {
	upcount = implode(matches, (: $1 + ($(mudlist)[$2][0] == -1) :), 0);
    }
    else
    {
	matches = filter_array(matches, (: $(mudlist)[$1][0] == -1 :));
	upcount = sizeof(matches);
    }
    output = "";
    if ( wizardp(this_user()) )
	output += "Type mudinfo <mudname> for more info on a mud.\n";
    output += sprintf(format + "%76'-'s\n",
		      map_array(info, (: $(headers)[$1[0]] :))...,
		      "");

    foreach ( match in sort_array(matches, 1) )
    {
        string	line;
	mudinfo = mudlist[match];
	line = sprintf(format,
			  mudinfo[0] == -1 ? "U" : "D",
			  match[0..info[1][1]-1],
			  map_array(info[2..],
				    (: ($(mudinfo)[$1[0]]+"")[0..$1[1]-1] :)
					)...);
	if (search_str)
	  {
	    if(regexp(line,search_str))
	      {
		output += line;
	      }
	    else
	      {
		matched--; mudinfo[0] == -1 ? upcount-- : 0;
	      }
	  }
	else
	  {
	    output += line;
	  }

    }
    output = sprintf("%d matches out of %d muds. %d are UP.\n",
		     matched, sizeof(mudlist), upcount) + output;

    more(output);
}
