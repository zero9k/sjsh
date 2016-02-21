// 凝霜鞭
#include <weapon.h>
#include <ansi.h>
inherit WHIP;
inherit F_UNIQUE;
void create()
{
        set_name(HIW"凝霜鞭"NOR, ({"ningshuang whip", "whip"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一条银白色的长鞭，如同霜雪，抚之有刻骨之寒意。\n");
                set("unit", "副");
                set("replace_file", "/d/obj/weapon/whip/pibian");
                set("value", 20000);
                set("wield_msg", HIW"$N冷冷一笑，左手往腰间一探，一条雪白色的长鞭在身周饶了一个圈。\n"NOR);
set("unwield_msg", HIW"$N轻叹一声，把手中$n缠回腰间。\n"NOR);
set("weapon_prop/courage", 20);
}
        init_whip(150);
        setup();
}
