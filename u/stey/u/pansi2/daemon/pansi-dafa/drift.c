// drift_sense.c

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        if( me->query("mana") < 200 )
                return notify_fail("你的法力不够！\n");
        if( me->query("sen") < 100 )
                return notify_fail("你的精神太差！\n");
	if( me->is_ghost())
		return notify_fail("鬼魂无法使用月光宝合！\n"); 	
	if( target )
		return notify_fail("月光宝合只能对自己使用！\n");
	write("你要移动到哪一个人身边？");
	input_to( (: call_other, __FILE__, "select_target", me :));
	return 1;
}

void select_target(object me, string name)
{
	object ob;

	if( !name || name=="" ) {
		write("中止施法。\n");
		return;
	}

	ob = find_player(name);
	if( !ob || !me->visible(ob) || wizardp(ob) )
		ob = find_living(name);
	if( !ob || !me->visible(ob) || wizardp(ob) || !environment(ob)) {
		write("你无法感受到这个人的灵力 ....\n");
		write("你要移动到哪一个人身边？");
		input_to( (: call_other, __FILE__, "select_target", me :));
		return;
	}
//	if( me->is_fighting() ) {
//		write("战斗中无法使用游识神通！\n");
//		return;
//	} else 
	if( me->query("mana") < 200 ) {
		write("你的法力不够！\n");
		return;
	}

	me->add("mana", -100);
	me->receive_damage("sen", 30);
	
	message_vision( HIW "$N低头闭目，口中不断念着:般若婆罗密 ....\n" NOR, me);
	if( random(ob->query("sen")) < (int)me->query("sen") / 10 ) {
		write("你感受到对方的灵力，但是不够强烈。\n");
		return;
	}
	   if( random(50) > 
	(int)(me->query_skill("pansi-dafa",1))){
                write("你因为不够熟练而失败了。\n");
                return;
	if( random(me->query_skill("spells")) < (int)ob->query("mana") / 500 ) {
		write("你因为不够熟练而失败了。\n");
		return;
	}
        }
	message( "vision", HIW "\n一道耀眼的光芒忽然罩住" + me->name() 
		+ "，几秒钟後，光芒和人一齐消失得无影无踪！\n\n", environment(me), ({ me }) );
	me->move(environment(ob));
	message( "vision", HIY "\n你的眼前突然出现一团耀眼的光芒，光芒中浮现出一个人影！\n\n" NOR,
		environment(ob), ({ me }) );
	me->start_busy(2+random(2));
}

