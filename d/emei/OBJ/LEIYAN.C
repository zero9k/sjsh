// leiyan.c   雷炎剑    created 20-08-2001 海上飘(piao)


#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIG"雷炎剑"NOR, ({ "leiyan sword", "leiyan", "sword" }) );
        set_weight(15000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","这是一把剑身上带有淡淡的绿光的长剑。\n");
                set("value", 2400);
                set("material", "blacksteel");
                set("wield_msg", "$N从银色剑鞘中抽出一把带有绿光的$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入腰间的银色剑鞘。\n");
        }
        init_sword(160);
        setup();
}
 
