// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	object where=environment(this_player());
	me->receive_wound("kee", 20+random(10));
	me->receive_wound("sen", 20+random(10));
	me->set_temp("death_msg","火毒发作死了。\n");
	me->apply_condition("yaohuo_poison", duration - 1);
	tell_object(me, HIG "忽然一阵眩晕，脑子里一片空白！\n" NOR );
         message("vision", me->name() + "突然身体剧烈的抖动，好象马上要昏倒。\n",environment(me), me);       
	if( duration < 1 ) return 0;
	return 1;
}
