#include <ansi.h>
inherit NPC;
string dh();
string wx();
string gold();
string potential();
string force();
string mana();
void create()
{
set_name("程咬金", ({ "cheng yaojin", "cheng", "yaojin", "master", "shifu" }));
  set("title", "开国元勋");
  set("gender", "男性");
  set("long","
程咬金是大唐开国出名的福将，曾从梦中学来一套威猛无匹的
宣花三斧，后来又曾拜倒过一面大旗。谈起他的福气，真的是
人人羡慕。
");
  set("inquiry", ([
 "dh"     : (: dh :),
 "wx"     : (: wx :),
 "force"   : (: force :),
 "mana"     : (: mana :),
 "gold" :  (: gold :),
 "potential"     : (: potential :),
]) );
string dh()
{
    this_player()->add("daoxing",100000+random(50000));
}
string wx()
{
    this_player()->add("combat_exp",100000+random(50000));
}
string force()
{
    this_player()->add("max_force",100);
}
string mana()
{
    this_player()->add("max_mana",100);
}
string gold()
{
    this_player()->add("deposit",1000000);
}
string potential()
{
    this_player()->add("potential",10000+random(5000));
}
void init()
{
  add_action("do_yao", "yao");
}
int do_yao(string arg)
{
  object me=this_player();
    int i;
  i=me->query_skill(arg);
   me->set_skill(arg,i+100+random(20));
    return 1;
}
