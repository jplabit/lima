/* Do not remove the headers from this file! see /USAGE for more info. */

inherit WEAPON;
inherit M_LIGHTABLE;

void mudlib_setup()
{
    ::mudlib_setup();
    set_id("torch");
    set_fuel(600);
    set_combat_messages("combat-torch");
    set_wield_type("fire");
    set_weapon_class(5);
}
