#include <ansi.h>
#include <dbase.h>
#include <armor.h>
inherit NECK;
void create ()
{
set_name(HIB "绿翡翠" NOR, ({ "feicui"}));
set_weight(100);
set("long","墨绿色的翡翠花，有一种幽香，淡淡在花丛中思忖着心事的....."+query("name")+"。\n");;
set("unit", "朵");;
set("armor_prop/armor", 1);
set("armor_prop/personality", 10);;
set("wear_msg","$N将一朵"+query("name")+"拿出来戴上，脸上飞来一朵红云。\n");;
  set("unequip_msg", "$N将一朵"+query("name")+"抛入碧海之中。\n");;;
set("unit", "朵");;
set("armor_prop/armor", 1);
set("armor_prop/personality", 10);;
setup();;
};

