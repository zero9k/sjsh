//Cracked by Roath
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,i,lmt;
        object weapon;
        extra = me->query_skill("zui-gun",1);
        if ( extra < 100) return notify_fail("�������������������죬�޷�ʩչ��"HIB"���޺�"NOR"����\n");
        extra = me->query_skill("yijinjing",1);
        if ( extra < 80) return notify_fail("����׽�񹦻�������죬�޷���������������������\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��"HIB"���޺�"NOR"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/family_name")!="������")
  return notify_fail("��"HIB"���޺�"NOR"���������µĲ���֮�أ����������ܹ�����\n");;

        weapon = me->query_temp("weapon");
        msg = YEL "$N�ƾ��󷢣����е�"+ weapon->name()+  ""YEL"��籩������$n"YEL"Ϯ����"NOR"" NOR;
        message_vision(msg,me,target);
        me->add_temp("apply/attack",extra/10);
        me->add_temp("apply/damage",extra/10);
        lmt = random(5)+3;
        for(i=1;i<=lmt;i++)
        {
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        }
        me->add_temp("apply/attack",-extra/10);
        me->add_temp("apply/damage",-extra/10);
        me->start_busy(2+random(1));
        return 1;
}