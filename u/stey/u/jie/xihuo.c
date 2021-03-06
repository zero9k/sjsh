// xihuo.c 息火

#include <ansi.h>

int exert(object me, object target)
{

	if ( !target
      ||      !userp(target)
      ||      target->is_corpse()
      ||      target==me)
		return notify_fail("你想替谁解除妖火？\n");
	if (!target->query_condition("yaohuo_poison"))
        return notify_fail("没中妖火瞎搅和什么！\n");
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");

	if( (int)me->query("force") - (int)me->query("max_force") <  600 )
		return notify_fail("你的真气不够。\n");

    if ((int)me->query_skill("huomoforce",1)<80)
		return notify_fail("你的内功修为不足以替人解除妖火。\n");
	
	message_vision(
		HIY "$N运起神功，往$n天灵盖使劲一拍。\n\n"NOR,
		me, target );
    if (random(me->query_skill("huomoforce", 1)-60)>10){
		target->apply_condition("yaohuo_poison",0);
		message_vision(
		HIY "$N骈指急点，$n张口狂喷出一滩淤血。\n"NOR,
		me, target );
			}
	else {
		message_vision(
		HIY "$N突然脸色苍白，似乎体力不支，竟呕出一口血来……\n"NOR,
		 me, target );
	}	
 
	target->receive_cuiring("kee", 10 + (int)me->query_skill("force")/3 );
	me->add("force", -150);
	me->set("force_factor", 0);
	return 1;
}
