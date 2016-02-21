// 应dxh建议 改动 命中率和damage

#include <ansi.h>
inherit SSERVER;
#include "/daemon/skill/eff_msg.h";

int def;
int perform(object me, object target)
{       
        string msg,str;
        int damage, p,time;
        if( !target ) target = offensive_target(me);
         if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("「二重勁」只能在战斗中使用。\n");
                if(me->query("family/family_name")!="剑客联盟")
                return notify_fail("你非剑客联盟弟子，不能用此招！\n");
        if( (int)me->query_skill("kongshoudao", 1) < 100 ||
           (int)me->query_skill("unarmed", 1) < 100 )
                return notify_fail("你有的功夫还不够娴熟，不会使用「二重勁」。\n");
        if(me->query_skill("force", 1) <100)                return notify_fail("以你现在的内功修为还使不出「二重勁」。\n");        
        if (me->query_skill_mapped("unarmed") != "kongshoudao")
                return notify_fail("你现在无法使用「二重勁」进行攻击。\n");                                                                                 
        if( (int)me->query("max_force") < 1200 )
                return notify_fail("你的内力修为太弱，不能使用「二重勁」！\n");
        if( (int)me->query("force") < 600 )
                return notify_fail("你的真气不够！\n");
        msg = HIG "\n 突然$N大喝一声:「一重勁」,飞身上前,举拳前进,浑身上下充满可怕的杀气~!\n" NOR;
        message_vision(msg, me, target); 
       msg = HIB "\n  “嗡”的一声，一拳捣向$n的胸口！\n" NOR;
  if (random(me->query("combat_exp")) > random((target->query("combat_exp")/4))
         )
        {
                me->start_busy(0);
                target->start_busy(2);
                damage = (int)me->query_skill("kongshoudao", 1);
                damage = damage + random(damage/2);
 def=(int)target->query_temp("apply/armor_vs_force");
damage -=damage*def/400000000;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/2);
                               me->add("force", -(damage/4));
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                msg += damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n";
 if (target->query("eff_kee")<0 || !living(target))  
                 {str=HIW+target->name()+HIM"被"HIG+me->name()+HIM"施以的空手道"+HIY+"「二重勁」"+HIM+"劈死了，听说"+target->name()+"躲闪不及,身中多处内伤,五脏俱损！"; 
      message("channel:rumor",HIM"【"+HIC+"江湖传闻"+HIM+"】某人："+str+"\n"NOR,users()); 
      } 

               target->set_temp("last_damage_from", me);
                if(me->query_skill("kongshoudao", 1) > 149)
                   call_out("perform2", 1, me, target);                        
                      } else 
        {       me->start_busy(random(1));
                me->add("force", -200);                
                msg += HIY"可是$p伏地一滚，躲开了对手的攻击。\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
  int damage, p,skill;
          string msg,weapon,str;
    weapon = me->query_temp("weapon");          if(!living(target)) 
          return notify_fail("对手已经不能再战斗了。\n");
        if( (int)me->query("force", 1) < 300 )
                return notify_fail("你待要再出第二击，却发现自己的内力不够了！\n");     
        msg = HIW "\n只见$N突然大喝一声「二重勁」，\n" NOR;
        message_vision(msg, me, target); 
       msg = HIR "\n  $N的右拳挟风雷之势向$n的胸口击来。\n" NOR;
if (me->query("combat_exp") > target->query("combat_exp")/4)
       {
                     me->start_busy(0);
                target->start_busy(2);
                damage = (int)me->query_skill("kongshoudao", 1);
                damage = damage+(int)me->query_skill("unarmed", 1);
                damage = damage+(int)me->query_skill("guixi-force", 1);
                damage = (damage + random(damage))/2;
                
 def=(int)target->query_temp("apply/armor_vs_force");
              damage -=damage*def/800000000;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/2);
                me->add("force", -random(damage/10));
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                msg += damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                target->set_temp("last_damage_from", me);
 if (target->query("eff_kee")<0 || !living(target))  
                 {str=HIW+target->name()+HIM"被"HIG+me->name()+HIM"施以的空手道"+HIY+"「二重勁」"+HIM+"劈死了，听说"+target->name()+"躲闪不及,身中多处内伤,五脏俱损！"; 
      message("channel:rumor",HIM"【"+HIC+"江湖传闻"+HIM+"】某人："+str+"\n"NOR,users()); 
      } 


                          if(me->query_skill("kongshoudao", 1) > 179)
                   call_out("perform3", 1, me, target);                        
                      } else 
        {       me->start_busy(random(1));
                me->add("force", -200);                
                msg += HIY"可是$p伏地一滚，躲开了对手的攻击。\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int perform3(object me, object target)
{
  int damage, p,skill;
          string msg,weapon,str;
    weapon = me->query_temp("weapon");  
        if(!living(target)) 
          return notify_fail("对手已经不能再战斗了。\n");
        if( (int)me->query("force", 1) < 400 )
                return notify_fail("你待要再出第三击，却发现自己的内力不够了！\n");     
        msg = HIG "\n只见$N起身上前,来到$n的面前,n" NOR;
        message_vision(msg, me, target); 
       msg = HIC "\n 变拳为掌用出相乐佐之助的奥义决学双重极限「三重勁」。\n" NOR;
if (me->query("combat_exp") > target->query("combat_exp")/4)
       {
                me->start_busy(1);
                target->start_busy(2);
                damage = (int)me->query_skill("kongshoudao", 1);
                damage = damage+(int)me->query_skill("unarmed", 1);
                damage = damage+(int)me->query_skill("guixi-force", 1);
                damage = (damage + random(damage))/2;
                
 def=(int)target->query_temp("apply/armor_vs_force");
              damage -=damage*def/1200000000;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/2);
                me->add("force", -random(damage/10));
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                msg += damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n";
               target->set_temp("last_damage_from", me);
 if (target->query("eff_kee")<0 || !living(target))  
                 {str=HIW+target->name()+HIM"被"HIG+me->name()+HIM"施以的空手道"+HIY+"「二重勁」"+HIM+"劈死了，听说"+target->name()+"躲闪不及,身中多处内伤,五脏俱损！"; 
      message("channel:rumor",HIM"【"+HIC+"江湖传闻"+HIM+"】某人："+str+"\n"NOR,users()); 
      } 


                      } else 
        {       me->start_busy(random(1));
                me->add("force", -200);                
                msg += HIY"可是$p伏地一滚，躲开了对手的攻击。\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}
