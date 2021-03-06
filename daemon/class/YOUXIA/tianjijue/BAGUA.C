// bagua.c 八卦阵 海上飘(piao)

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        int bagua, ap, dp;
        if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
                return notify_fail("「"HIC"八卦阵"NOR"」只有在战斗中才能使用。\n");
        if( (int)me->query_skill("tianjijue", 1) < 150 ) 
                return notify_fail("你的天机咒修为不够深，还使不出这一招！\n");
        if( (int)me->query_skill("spells", 1) < 150 ) 
                return notify_fail("你的法术修为不够深，还使不出这一招！\n");
	if( (int)me->query("mana") < 400 )
		return notify_fail("你的法力不够了！\n");
        if( (int)me->query("max_mana") < 1960 )
                return notify_fail("你的法力不足！\n");
	if( (int)me->query("sen") < (int)me->query("max_sen")/2 )
		return notify_fail("你现在头脑不清醒，哪里使得出「八卦阵」！\n");

               message_vision(HIW"$N念了几句咒语，大喝一声：看我「"HIY"八卦阵"HIW"」!只见一团白雾拢向$n。\n"NOR,me, target);
	ap = me->query_skill("spells");
	ap = ap * ap * ap /10 ;
	ap += (int)me->query("daoxing");
	ap = 3*ap; 
	dp = target->query("daoxing");
	if( random(ap + dp) < dp ) bagua = 0;
	ap = (int)me->query("max_mana");
	dp = (int)target->query("max_mana");
	if( ap < random(dp) ) bagua = 0;

	if( bagua == 0 )
	{
       message_vision(HIW"\n白雾消失之后$n被移到了八卦阵中。\n"NOR, me, target);
                target->move("/d/youxia/bagua/bagua0.c");
                target->start_busy(2);
                me->start_busy(1);
                me->add("mana",-500);
                me->add("sen",-100);

	}
	else
	{
                message_vision(HIR"$N的「八卦阵」失败了!"NOR"\n"NOR,me, target);
                me->start_busy(2);
                me->add("mana",-300);
                me->add("sen",-100);
	}

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
                me->kill_ob(target);
        }
	return 1;
}

