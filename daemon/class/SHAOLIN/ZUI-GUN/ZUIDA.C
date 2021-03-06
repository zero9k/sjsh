// zuida.c 少林醉棍 [八仙醉打]

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int count, count1, cnt, skill;
	
	if( !me->is_fighting() )
            return notify_fail("「"HIB"八仙醉打"NOR"」只能在战斗中使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "stick")
			return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_temp("zuida") ) 
		return notify_fail(HIY"你已经在运功中了。\n"NOR);

	if( (int)me->query_temp("powerup"))
		return notify_fail(HIG"你已经运起内功加力了，没有更多的内力使用八仙醉打。\n"NOR);

	if( (int)me->query_str() < 25 )
		return notify_fail("你的臂力不够，目前不能使用此绝技! \n");

	if( (int)me->query_skill("yijinjing", 1) < 60)
                return notify_fail("你的易筋经功力不够，不能使用此项绝技！\n");

	if( (int)me->query_skill("stick") < 90)
		return notify_fail("你的棍法修为不够，不能使用此项绝技! \n");

	if( (int)me->query("force") < 500 )
		return notify_fail("你的真气不足！\n");

	
	
        message_vision(HIY"\n$N使出少林醉棍的绝技「八仙醉打」，臂力陡然增加, 身法陡然加快！\n"NOR,me);
	skill = me->query_skill("zui-gun",1);
	count = me->query("str") * random(cnt + 2);
	count1 = me->query("dex") * random(cnt + 2);

	me->add_temp("str", count);
	me->add_temp("dex", count1);
	me->set_temp("zuida", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, count, count1 :), skill /3 );

	me->add("force", -150);
   	return 1;
}

void remove_effect(object me, int amount, int amount1)
{
	
	if ( (int)me->query_temp("zuida", 1) ) 
	{
		me->add_temp("str", -amount);
		me->add_temp("dex", -amount1);
		me->delete_temp("zuida");
		tell_object(me, HIY "你的八仙醉打运功完毕，将内力收回丹田。\n" NOR);
		me->start_busy(4);
	}
}
