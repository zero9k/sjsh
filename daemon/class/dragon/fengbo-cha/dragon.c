#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「群龙聚首」？\n");

        if(!me->is_fighting())
                return notify_fail("「群龙聚首」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

	if((int)me->query("force") < 500 )
		return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("fengbo-cha", 1) < 100)
                return notify_fail("你的风波十二叉级别还不够，使用这一招会有困难！\n");

  	if (me->query_temp("dragon_pfm_busy")) return notify_fail("绝招用的太多太滥就不灵了。\n");

        me->delete("env/brief_message");
	target->delete("env/brief_message");

	message_vision(HIC"\n$N幻化成龙，群龙飞舞，向$n攻了过去！\n"NOR,me,target);

        me->set_temp("QJB_perform", 10);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("QJB_perform", 11);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

        me->set_temp("QJB_perform", 12);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->delete_temp("QJB_perform");

        me->receive_damage("sen", 100);
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

	me->set_temp("dragon_pfm_busy",1);
	me->set_temp("no_move",1);
	call_out("remove_no_move",3,me);
        call_out("remove_effect",5+random(3),me);
        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("dragon_pfm_busy");
}
void remove_no_move(object me) {
  if (me) me->delete_temp("no_move");
}
