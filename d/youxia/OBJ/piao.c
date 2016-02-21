// pdan.c 飘飘丹 by piao
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"飘飘丹"NOR, ({ "dan","piao dan" }) );
        set("long",HIW"飘飘丹是巫师海上飘历经五分多钟精心炼制的丹药，用途神秘。\n"NOR);
        set("unit", "粒");
        set("weight", 5000);
}
void init()
{
        add_action("do_eat", "eat");
}
int do_eat(string arg)
{
        object ob;
        if( !id(arg) ) return notify_fail("你要吃什麽？\n");
          if( living( this_player())==0) return 0;
        ob=this_player(); 
        ob->add("daoxing",0);
        ob->add("combat_exp",0);
        ob->add("potential",180000);
        ob->set("max_force",2700);
        ob->set("max_mana",2700);
        ob->set("max_kee",1000);
        ob->set("max_sen",1000);
        ob->set("max_gin",1000);
        ob->set("age",18);
        ob->set("int",30);
//      ob->set("title","普通百姓");
      write(HIW+"你吃下一粒飘飘丹，自己也不知道到底发生了什么变化。\n"NOR);
        destruct(this_object());
        return 1;
}

