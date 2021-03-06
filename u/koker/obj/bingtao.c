// bingtao.c 冰桃
//by koker@sjsh 2002
#include <ansi.h>
#define LAST_PAR "bt2"
#define THIS_PAR "bt1"
inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","你手里一松冰桃从指间滑落，摔得粉碎！\n");
    set("no_give","花哥不希望你这样做！\n");
    set("no_drop","冰桃掉在地上会碎的！\n");
    set("no_sell","小人那敢收花哥大人发的东西啊！你快收好，别给我找麻烦了！\n");
  }                                    
  add_action("do_eat", "eat");
}

void create()
{
  set_name("冰桃", ({"bing tao","bingtao","tao"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "块");
    set("long", "这是花哥亲手用千年寒冰雕刻的桃子，看上去可爱极了。\n");
    set("value", 50000);
    set("drug_type", "补品");
  }
  
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  
  if (!id(arg))
    return notify_fail("你要吃什么？\n");
  
  if (me->query(THIS_PAR + "_pick")) {
       tell_object(me,CYN "你吃过了啊，你怎么还能有它！\n\n");
       tell_object(me,CYN "你被花哥狠狠的踢了一脚。\n" NOR);
       return 1;
       }
  me->set("water", (int)me->max_water_capacity());
  me->add_maximum_force(20);
  me->add_maximum_mana(20);
  me->add("combat_exp",100000);
  me->add("daoxing",100000);
  me->add("potential",100000);
  message_vision(HIG "$N吃下一个冰桃，全身上下突然被白霜笼罩，牙齿不停的打颤。 \n" NOR, me);
  me->delete(LAST_PAR + "_pick");
  me->set(THIS_PAR + "_pick",1);
  destruct(this_object());
  return 1;
}
