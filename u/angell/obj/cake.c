// by night
// fid 修改

#include <ansi.h>


inherit ITEM; 

int do_eat(string);
void init();
void init()
{
  if(!wizardp(this_player())) {
    set("no_get","蛋糕掉在地上就不能吃了！\n");
    set("no_give","这是生日蛋糕啊，怎么能随便给人呢？\n");
    set("no_drop","生日蛋糕扔了多可惜呀！\n");
    set("no_sell","这是定做的，卖不掉了。\n");
  }
  add_action("do_eat", "chi"); 
  add_action("do_wish", "wish");
  }

void create()
{
  set_name( HIY "生日蛋糕" NOR , ({"shengri dangao","cake", "dangao"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "块");
    set("long", "一块高级奶油蛋糕，你一看就想吃(chi)了它，上面有几个字：\n\n"
HIR"                  祝你生日快乐\n"NOR);
    set("value", 10000);
    set("no_beg",1);
    set("no_get",1);
    set("no_give",1);
    set("no_steal",1);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me, ob;
  int age,gain;
   me = this_player(); 
    //vkar=(int)me->query("age"); 
    //本来用福缘判断给多少礼物，现在改为年龄
   age=(int)me->query("age");
   if (age<20) gain=5000;
   else if(age<30) gain=6000;
   else if(age<40) gain=7000;
   else if(age<50) gain=8000;
   else if(age<60) gain=9000;
   else if(age<70) gain=10000;
   else gain=11000;
   
  
  if (!id(arg))
            return notify_fail("你要吃什么？\n");
  if(this_object()->query("owner")!=this_player()->query("id"))
           return notify_fail("这好象不是你的生日蛋糕哦?\n");
  if (!me->query("fired") )
  return notify_fail("别太谗了，点生日蜡烛先！\n");
  if (!me->query("wished") ){
       tell_object(me,"吃蛋糕前先许个愿(wish)吧。\n"
"可以许愿要武学(exp)、潜能(pot)、或者道行(dx)。\n");
       return 1; 
}
if(!me->query_temp("marks")) {
        tell_object(me,"吃蛋糕前先许个愿(wish)吧。\n"
"可以许愿要武学(exp)、潜能(pot)、或者道行(dx)。\n");
       return 1; 
}
  me->set("food", (int)me->max_food_capacity());
  me->set("water", (int)me->max_water_capacity()); 
  if (me->query("gender")=="男性")
  message_vision(HIG "$N三口两口地把蛋糕吃了下去，打了个饱嗝。\n\n" NOR, me);  
  else if(me->query("gender")=="女性")
  message_vision(HIG "$N满怀憧憬地吃下蛋糕，脸上泛起一抹红晕。\n\n" NOR, me); 
  message_vision(HIG "$N的愿望实现啦！\n" NOR, me);  
    me->set("fired",0);  
       
   if ( me->query_temp("marks/exp") ){ 
   
    me->add("combat_exp",gain); 
    me->set("wished",0);
    me->set_temp("marks/exp",0); 
    destruct(this_object());
    return 1;
         }
      if ( me->query_temp("marks/pot") ){ 
   
    me->add("potential",gain);
    me->set("wished",0);
    me->set_temp("marks/pot",0); 
    destruct(this_object());
    return 1;
         }
    
      if ( me->query_temp("marks/dx") ){ 
   
    me->add("daoxing",gain);
    me->set("wished",0);
    me->set_temp("marks/force",0); 
    destruct(this_object());
    return 1;
          } 
 
}
 
int do_wish(string arg) 
{
    object me;
    me = this_player();
  if(!me->query("fired"))
    return notify_fail("蜡烛还没点许愿不灵验哦！\n");
  if (arg=="pot") { 
  message_vision(HIY "$N闭上眼睛，默默地许了个愿。\n" NOR, me);  

    me->set("wished",1);
    me->delete_temp("marks");
    me->set_temp("marks/pot",1);
    return 1;
    }  
  if (arg=="exp") { 
  message_vision(HIY "$N闭上眼睛，默默地许了个愿。\n" NOR, me);  
me->start_busy(random(5));
    me->set("wished",1);   
     me->delete_temp("marks");
      me->set_temp("marks/exp",1);
    return 1;
    } 
  if (arg=="dx") {
  message_vision(HIY "$N闭上眼睛，默默地许了个愿。\n" NOR, me);  
me->start_busy(random(5));
    me->set("wished",1);
     me->delete_temp("marks");
    me->set_temp("marks/dx",1);
    return 1;
    } 
 
  return notify_fail("你想许什么愿？可以许愿要武学(exp)、潜能(pot)、或者道行(dx)。\n"); 
}

void owner_is_killed()
{
        object me = this_player();
        write(HIM"只见一阵烟雾闪过...尸体上什么东西消失了。\n"NOR);
        destruct(this_object());
        return;
}

