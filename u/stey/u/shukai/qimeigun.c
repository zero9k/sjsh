// qimeigun.c

#include <weapon.h>

inherit STICK;

void create()
{
    set_name("布棍", ({ "bugun","gun", "bang" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
		set("value", 5);
        set("material", "???");
        set("long", "一根用布沾水拧成的棍子。\n");
		set("wield_msg", "$N拿起一根$n，顺手舞了个棍花。\n");
		set("unwield_msg", "$N哼了一声，将$n插回后腰。\n");
	}
	init_stick(18);
	setup();
}
