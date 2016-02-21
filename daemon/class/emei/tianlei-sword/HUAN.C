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
                return notify_fail("��"HIM"�ý�"NOR"��ֻ����ս����ʹ�ã�\n");

        if(!me->is_fighting())
                return notify_fail("��"HIM"�ý�"NOR"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail(RED"���������Ϊ���㣬�޷����㡸�ý�����������\n"NOR);


	if((int)me->query("force") < 500 )
                   return notify_fail(HIC"����������������û�ܽ����ý���ʹ�꣡\n"NOR);

        if((int)me->query("sen") < 500 )
                return notify_fail(HIC"��ľ����㣬û����ʩ�á��ý�����\n"NOR);

        if((int)me->query_skill("tianlei-sword", 1) < 80)
                return notify_fail(HIM"�������˫��������죬��ʹ�������ý�����\n"NOR);

        if((int)me->query_skill("emeiforce", 1) < 1)
                return notify_fail(HIW"��Ķ����ķ���򲻹������ý���������ʽ��\n"NOR);

        if ((int)me->query_skill("jinding-zhang", 1) < 80 )
                return notify_fail(HIY"��Ľ����ƻ�򲻹������𽣡�������ʽ��\n"NOR);
	if(me->query_temp("last_pili")+5>time())
                return notify_fail("������ʹ�ù��ȣ���"HIM"�ý�"NOR"��������ʽ��\n");
        me->delete("env/brief_message");
	target->delete("env/brief_message");

	if (! present(target,environment(me))) return 1;
message_vision(HIM"\n$N���г�����âԾ�������Ⱪ�����ó�������ɫ�ʣ����⽥\n"NOR,me,target);
message_vision(HIM"���ƽ�$n��$n�������콣�⣬������Ծ��ֻ��һɲ�����콣\n"NOR,me,target);
message_vision(HIM"Ӱ��Ϊ����ֱ��$nǰ�أ����Ī�⣬ͻ��������\n"NOR,me,target);
        me->set_temp("QJB_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),10);

	if (! present(target,environment(me))) return 1;
        me->set_temp("QJB_perform", 1);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),10); 

	if (! present(target,environment(me))) return 1;
        me->set_temp("QJB_perform", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),10);



        me->delete_temp("QJB_perform");

        me->receive_damage("sen", 100);
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->set_temp("last_pili",time());
        return 1;
}
