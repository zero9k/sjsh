//谈笑退天兵  wosshipg
 
#include <ansi.h>
 
inherit SSERVER;

int perform(object me, object target)
{
string msg,targetrude;
int my,him;
  int success,hurt,diff,damage;
   int myexp=(int)me->query("combat_exp")/5000+(int)me->query("daoxing")/5000;
  int mylev=(int)me->query_skill("stick")/2+ (int)me->query_skill("qianjun-bang");
  int mystr=(int)me->query("str")+(int)(me->query_skill("unarmed")/10-2);
  int targetlev, targetstr,targetkar,targetexp,targeteffkee;
  string *hitone = ({
HIY "$n急忙用手中的兵器格挡,但是$N的招式太突然了,$n哼了一声,左肩上已重重的吃了一棍.\n",
HIY "$n根本就没有想到这么平淡无奇的一招竟然有如此巨大的威力.$N一棒重重的打在$n的右臂.\n",
  });
  string *missone = ({
BLU "$n早有防备,将计就计的漏出一个破绽,待到$N打来之时,侧身退步,向$N肋间打出.$N蹙不急防,只好闪身躲避,这一招被$n尽数化解.\n",
BLU "$n哈哈大笑:雕虫小技,也来这里卖弄,不过是关公面前耍大刀!看我怎么收拾你!\n",
  });
  string *hittwo = ({
 HIW "$n毫无还手之力,眼睁睁的看着被$N当头一棒,$n顿时血流满面,形状极其可怕!\n",
 HIW "$n心知要吃亏了,急忙将兵器架于头顶之上,$N眼明手快,将腕一抖,一棒打在$n的腰间.$n一个踉跄,险些摔倒!\n",
  });
  string *misstwo = ({
CYN "原来$n故作痴呆,诱惑$N,等到$N欺身靠近,$n大喝一声:拿命来!转而攻向$N!\n",
CYN "$n突然一个虎跳,竟然跳到$N背后,$N一脸茫然,不知道发生了什么事情!\n",
  });
  string *hitthree = ({
HIR "$n大喊一声:不好!好字还没有说出口,被$N一棒打在背上,$n痛苦不堪,哇的一声喷出一口鲜血.看来伤势不轻!\n",
HIR "$N大喊一声:送你上西天!将手中的棒子舞做一团彩雾,劈头盖脸的打了过来.$n看不出破绽,又吃了重重的一棒!\n",
  });
  string *missthree = ({
HIG "说时迟,那时快.$n举起手中的兵器奋力一架,乒的一声,接住了$N劈下来的棒子!\n",
HIG "$n狂笑一声:你也太小瞧我了!\n",
  });
  string *hit=({
     HIW "$N道：那里来的毛神,在我面前卖弄?！\n"NOR,
     HIW "这一招着实厉害,$n连反应都没有来得急就被$N重击一棒,手臂乌黑,伤势严重!\n"NOR,
  });
  string *miss;
  
  if( !target ) target = offensive_target(me);
  if( !target
     ||      !target->is_character()
     ||      !me->is_fighting(target) )
    return notify_fail("千均棒不是练着好看的，只能对战斗对手施用。\n");
  targetrude=RANK_D->query_self_rude(target);
  miss=({
 BLU"$n哈哈大笑道："+targetrude+"听说这千均棒有多少威力，现在一看，也不过如此嘛！\n"NOR,
    BLU"$n长笑一声，对$N不屑地说道：就这点本事，"+targetrude+"还没放在眼里！\n"NOR,
    BLU"$n仰天大笑道：还有什么本事，尽管拿出来吧！\n"NOR,
  });
  if((string)me->query_skill_mapped("force")!="wuxiangforce")
     return notify_fail("谈笑退天兵必须以wuxiangforce为底子。\n");
      if(me->query_skill("wuxiangforce",1) < 150)
     return notify_fail("你的内功底子不足，无法使用谈笑退天兵。\n");
   if(me->query_skill("qianjun-bang",1)<150)
     return notify_fail("你对千均棒的理解不够，无法一气呵成地使出！\n");
  if(me->query("max_force") < 1000 || me->query("force")<500)
     return notify_fail("你的内力不足，难以使出这么精妙的招数。\n");
 targetexp=(int)target->query("combat_exp")/5000+(int)target->query("daoxing")/5000;
  targetlev=(int)target->query_skill("parry")/2+(int)target->query_skill("dodge");
targetstr=(int)target->query("str")+(int)(target->query_skill("unarmed")/10-2);
my=mystr+mylev+myexp;
him=targetstr+targetlev+targetexp;
 msg = CYN "$N一声暴喝：迎门三不过！三招一气呵成！\n\n只见一道青影划过，手中的棒子直劈$n顶门！\n" NOR;
if( random(my) > him*3/4)
    {
      msg += hitone[random(sizeof(hitone))];
      success+=1;
if(random(mystr+targetstr)>targetstr) hurt+=1;
   damage=50+random(mystr/5);
    }
  else msg+=missone[random(sizeof(missone))];
   msg+=CYN"\n$N似乎什么都没有看见,全然不顾眼前的危险,在$n悄悄靠近的时候怒喝一声,挥棒打出$n被打了个措手不及！\n"NOR;
 if( random(my+him) > him)
    {
      msg += hittwo[random(sizeof(hittwo))];
      success+=1;
     if(random(mystr+targetstr)>targetstr) hurt+=1;
   damage=50+random(mystr/5);
    }
  else msg+=misstwo[random(sizeof(misstwo))];
   msg+=CYN"\n$N待到$n明白是怎么回事的时候,又是迅猛无比的一击!\n"NOR;
    if(random(my+him)>(him/2))
    {
      msg+=hitthree[random(sizeof(hitthree))];
      success+=1;
     if(random(mystr+targetstr)>targetstr) hurt+=1;
   damage=50+random(mystr/5);
    }
  else msg+=missthree[random(sizeof(missthree))];
  diff=3-success;
  if (diff<0) diff = 0;
  if (success) hurt=damage*hurt/success;
  else hurt=0;
  me->add("force", -(150*success+70*diff));
  targeteffkee=(int)target->query("eff_kee");
  target->receive_wound("kee", targeteffkee*hurt/100);
  target->receive_damage("kee", target->query("kee")*(damage-hurt)/100);
  if(success)
    {
me->start_busy(1+random(4-(mystr)/50));
   target->start_busy(3+random(4-(mystr)/50));
  target->add("force",-200);
      msg+=hit[random(sizeof(hit))];
    }
  else
    {
me->start_busy(1+random(4-(mystr)/50));
      msg+=miss[random(sizeof(miss))];
    }
  message_vision(msg, me, target);
  return 1;
}
