
#include <ansi.h>
 
inherit F_DBASE;
inherit SSERVER;
 
void delay_effect(object me, object target, object weapon,int power);
 
int perform(object me, object target)
{
        int delay,skill;
        object weapon=me->query_temp("weapon");
        if (!target) return notify_fail("打谁？\n");
        if (!me->is_fighting(target))
        return notify_fail("你们不在打架。\n");
        if(me->query("family/family_name")!="剑客联盟")
        return notify_fail("[牙突·零式］只有剑客联盟弟子才可以使用！\n");
        skill=me->query_skill("lixin-sword",1);        
        if (skill<100) return notify_fail("你天然理心流的等级不够，无法使出[牙突·零式]。\n");
        if( (int)me->query("force") < 600 )      
        return notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("ling_delay") )
        return notify_fail("你正在施展[牙突·零式]了。\n");    
        me->add("force", -200);
        delay=3;
        message_vision(WHT"\n$N身形突然退后，左腿向前微踏一步，剑向前平指，剑尖微向下，左手中指
平贴在剑尖之上，整个人也如同出鞘的利剑般蓄势待发。\n\n"NOR, me);
        me->set_temp("ling_delay", 1);
        me->start_busy(delay);
        me->start_call_out( (: call_other, __FILE__, "delay_effect", me, target,weapon,delay:), delay);
         return 1;
}
 
void delay_effect(object me,object target,object weapon,int power)
{
        mapping action;
        mapping new_act=([]);
	 int extra;    
        me->delete_temp("ling_delay");
        if (!target) return;
        if (environment(me)!=environment(target)) return;
        if (me->query_temp("weapon")!=weapon) return;
        message_vision(WHT"\n只见$N手中"+weapon->name()+"带着一道凄厉的剑光，闪电般向$n的要害刺来。\n"NOR,me,target);
        me->set("actions", (: call_other, SKILL_D("lixin-sword"), "query_pfm_action" :) );
	 extra = me->query_skill("sword");
	 me->add_temp("apply/attack", extra);	
	 me->add_temp("apply/damage", extra);
        COMBAT_D->do_attack(me, target, weapon);
	  me->add_temp("apply/attack", -extra);
	  me->add_temp("apply/damage", -extra);
         me->reset_action();
         target->start_busy(2);
         me->start_busy(1);
}