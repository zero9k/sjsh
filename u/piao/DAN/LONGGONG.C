// dan.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIB"�̺�������"NOR, ({ "dan" }) );
        set("long",
HIB"�������������ϳ˵��鵤��ҩ��\n"NOR);
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
        ob->set_skill("dodge",50);
        ob->set_skill("force",50);
        ob->set_skill("parry",50);
        ob->set_skill("spells",50);
        ob->set_skill("unarmed",50);
        ob->set_skill("literate",50);
        ob->set_skill("fork",50);
        ob->set_skill("hammer",50);
        ob->set_skill("dragonfight",50);
        ob->set_skill("dragonforce",50);
        ob->set_skill("dragonstep",50);
        ob->set_skill("huntian-hammer",50);
        ob->set_skill("fengbo-cha",50);
        ob->set_skill("seashentong",50);
write(HIB+"�����һ�ű̺���������ֻ����һ�����������������!��ʱ��Զ����������书��������\n"NOR);

        message("vision", HIB + ob->name() + 
"����һ�ű̺���������ֻ����һ������������������!��ʱ���Զ����������书��������\n"NOR,
                environment(ob), ob);
        destruct(this_object());
        return 1;
}