
#include <ansi.h>
#include <combat.h>

inherit SSERVER;

void duanqin_ok(object);

int perform(object me, object target)
{
    mapping duanqin= ([
       "damage": 1000,
       "dodge" : -30,
       "parry" : -30,
       "damage_type" :  "����",
       "action" :  HIM"$w"+HIM"�ڿ��з�ת��һ��,ͻȻ��$n"HIM"��$l��ȥ"NOR,
    ]);

      object weapon=me->query_temp("weapon");
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("��Ҫ����˭��\n");
      if (!target->is_fighting(me))
             return notify_fail("����û���ڴ�ܣ�\n");
      if (me->query_temp("no_duanqin") )
          return notify_fail("������״̬���ѣ�����ʹ�÷��١�\n");      
      if (me->query_skill("wuji-force",1)<50)
          return notify_fail("����ڹ�̫��ٷɲ���ȥ��\n");
      if (me->query_skill("xiaohunqin",1)<50) 
          return notify_fail("�����������ô�ã����İ��ٲ��Լ����ϡ�\n");
      if (me->query("force")<100)
           return notify_fail("���������̣����Լ������١�\n");
     
      me->add("force", -100);
          me->start_busy(2);
      me->set("actions",duanqin);
       message_vision(HIM"$N����"+weapon->query("name")+HIM"�ڿ��з�ת��һ��,ͻȻ��$n"HIM"�ķ�ȥ��"NOR,me,target);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                weapon->unequip();
                weapon->move(environment(target));
                weapon->set("name","�ϳ����ص�"+weapon->query("name"));
                weapon->set("no_get",1);
                weapon->set("long","һ���ϳ����ص�"+weapon->query("name"));
      me->set_temp("no_duanqin",1);
      call_out("duanqin_ok",10,me);
      me->reset_action();
      return 1;
}

void duanqin_ok(object me) {
      if (!me) return;
      me->delete_temp("no_duanqin");
}         
