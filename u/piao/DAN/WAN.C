// wan.c ��Ѫ����

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY"��Ѫ����"NOR, ({ "wan","dabu wan" }) );
        set("long",
HIG"��Ѫ�����ǲɼ��žŰ�ʮһ�����ҩ�ģ���ʱ��������ƶ��ɵ��鵤��\n"NOR);
        set("unit", "��");
        set("weight", 5);
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object ob;
        if( !id(arg) ) return notify_fail("��Ҫ��ʲ�᣿\n");

          if( living( this_player())==0) return 0;

          if( living( this_player())==0) return 0;

        ob=this_player(); 
        ob->add("daoxing",1000);
        ob->add("combat_exp",10000);
        ob->add("potential",2000000);
write(HIY+"�����һ����Ѫ���裬ֻ����һ�����������������!\n"NOR);

        message("vision", HIY + ob->name() + 
"����һ����Ѫ���裬ֻ����һ������������������!\n"+NOR,
                environment(ob), ob);
        destruct(this_object());
        return 1;
}