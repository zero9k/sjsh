// 龙神枪 
#include <ansi.h>
#include <weapon.h>
inherit F_UNIQUE; 
inherit SPEAR;
void create()
{
        set_name(HIY "龙神枪" NOR, ({"longshen spear","longshen", "spear"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","这是把无数小金块制成的长枪。\n");
                set("value", 0);
                set("material", "gold");
                set("wield_msg","$N拿出一把$n握在手中，眼前闪过一道寒光．\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_spear(10);
        setup();
}
