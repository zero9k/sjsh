// jinjia.c ���
#include <armor.h>
#include <ansi.h>
inherit ARMOR;

void create()
{
        set_name(BLK"�������"NOR, ({"feiyu armor","jiazhou", "feiyu","jia", "armor"}));
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ�����������ļ��У�\n");
                set("material", "steel");
                set("value", 10000);
                set("armor_prop/armor", 150);
                set("armor_prop/dodge", -3);
        }
        setup();
}


