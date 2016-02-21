// zhaoyaojing.c
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	int success_adj, damage_adj;

success_adj = 130;
damage_adj = 130;

	if( !target ) target = offensive_target(me);

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("��Ҫ��˭ʩչ��������\n");

	if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
		return notify_fail("��ķ���������\n");

	if((int)me->query("sen") < 50 )
		return notify_fail("���޷����о�����׼��\n");

	me->add("mana", -25-2*(int)me->query("mana_factor"));
		me->receive_damage("sen", 10);

	if( random(me->query("max_mana")) < 50 ) {
		write("��ķ��������������������ã���ʩһ�ΰɣ�\n");
		return 1;
	}

	SPELL_D->attacking_cast(
		me, 
			//attacker 
		target, 
			//target
		success_adj, 	
			//success adjustment
		damage_adj, 	
			//damage adjustment
		"both", 		
			//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "$N�������˼������ģ�����г���һλ���ˣ��ֳ�һ�汦����\nֻ�������еı�����$n��ȥ��\n" NOR,
			//initial message
		HIC "������������$n����͸���������ʱѪ���ɽ���\n" NOR, 
			//success message
		HIC "ֻ��$n����һ�������˹�ȥ��\n" NOR, 
			//fail message
        HIC "����$n�Է���һ�����������$N��\n" NOR,
			//backfire initial message
		HIC "������������$n����͸���������ʱѪ���ɽ���\n" NOR, 

			//backfire hit message. note here $N and $n!!!
	);

	me->start_busy(1+random(2));
	return 3+random(5);
}
