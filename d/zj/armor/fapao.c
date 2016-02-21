// 天师法袍 by Calvin

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
  set_name(HIY"天师法袍"NOR, ({"tianshi fapao", "tianshi","fapao","cloth","pao"}));
  set_weight(4000);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "一件得封封官封神时专用的法袍。\n");
    set("material", "cloth");
    set("unit", "件");
    set("value", 10000);
    set("no_sell", 1);
    set("armor_prop/armor", 50);
    set("armor_prop/dodge", 50);
    set("armor_prop/spells", 50);
    set ("armor_prop/force", 50);
    set("armor_prop/parry", 50);
  }
  setup();
}
