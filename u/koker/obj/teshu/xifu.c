// xifu.c
//哦麦噶的西服

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

//inherit F_UNIQUE;

void create()
{
	set_name(HIY"整蛊西服"NOR, ({ "xifu", "fu" }) );
	set("long", "象整谁就整谁的西服，还可以给你三个愿望。\n");
	set_weight(300);
	else {
		set("unit", "件");
		set("material", "cloth");
		set("armor_prop/armor", 500);
		set("armor_prop/spells", 500);
		set("armor_prop/dodge", 100);
                set("armor_prop/force", 500);
		set("value", 50000);
//愿望的代码暂时没加
	}
	setup();
}