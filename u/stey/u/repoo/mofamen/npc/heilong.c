// repoo
#include <ansi.h>
inherit NPC;
void create()
{
        set_name(HIB"黑龙"NOR, ({ "hei long", "long", "dragon" }) );
        set("gender", "男性" );
        set("long",HIC
                "黑龙城守卫！\n"NOR);
 
        set("age",50);
         set("nickname", HIW"『龙城护卫』"NOR);
         set("title", HIB"八部天龙"NOR);
        set("attitude", "heroism");
        set("str",40);
        set("int",30);
        set("max_kee",3100);
        set("kee",3100);
        set("max_sen",3100);
        set("sen",3100);
        set("combat_exp",1800000);
        set("daoxing",3500000);
        set("force",5000);
        set("max_force",3000);
        set("mana",5000);
        set("max_mana",3000);
        set("force_factor", 20);
        set("mana_factor",120);
        set("eff_dx", 4500000);
        set("nkgain", 1500);
        set_skill("unarmed",180);
        set_skill("dragonfight", 180);
        set_skill("parry",180);
        set_skill("dodge",180);
              set_skill("dragonstep",180);
        set_skill("fork",180);
        set_skill("fengbo-cha",180);
        set_skill("force",180);
              set_skill("dragonforce",200);
        set_skill("spells", 180);
        set_skill("seashentong", 180);
              map_skill("force","dragonforce");
              map_skill("spells", "seashentong");
        map_skill("dodge", "dragonstep");
        map_skill("parry", "fengbo-cha");
        map_skill("fork","fengbo-cha");
        map_skill("unarmed", "dragonfight");
        set("inquiry", ([
                "name" : "在下黑龙，奉谕把守黑龙城。",
                        ]) );
        set("chat_chance_combat", 50);
              set("chat_msg_combat", ({
                (: perform_action,"unarmed","sheshen" :),
       //         (: cast_spell, "dragonfire" :),                
        }) );
              setup();
        carry_object("/d/sea/obj/longpao")->wear();
   //     carry_object("/d/obj/weapon/hammer/jingua")->wield();
}
void kill_ob (object ob)
{
  object me = this_object();
  set_temp("my_killer",ob);
  call_out ("huo",5+random(5),me,ob);  
  ::
kill_ob(ob);
}
void huo (object me, object ob)
{
  object huobing;
  int damage;
  if (! me)
    return;
  if( !living(me) )
    return;
  if (! ob)
    return;
  if (environment(ob) != environment(me))
    return;
  message_vision ("$N"HIC"从口中吐出"HIR"三"HIB"味"HIM"真气 "HIC"祭在空中，化作一道"HIW"火墙"
       HIR+"只觉热浪滚滚，向$n扑来！\n"NOR,me,ob);
  if ( (ob->query("force")+random(1000)) > 4000 )
     message_vision (HIY"$N大喝一声：去！\n"
       +HIR"这道火墙"+HIY" 霎时烟消云散。\n"NOR,ob,me);
  else 
    {
     message_vision (HIR"结果$N被火墙完全吞没了！\n"NOR,ob,me);
     damage=(me->query("force"))/2; 
     if ( ob->query("kee") < damage ) ob->unconcious();
     else ob->add("kee",-damage);
    } 
  remove_call_out ("huo");  
  call_out ("huo",random(10)+9,me,ob);  
}
void die ()
{
    object me = this_object();
   object ob = query_temp("my_killer");
  object zhua;
  string zhua_given;
  zhua_given = "/u/repoo/mofamen/obj/longzhua.c";
      ob->set_temp("heilong_killed",1);
   if (!zhua_given->in_mud())
    {
  zhua = new("/u/repoo/mofamen/obj/longzhua");
  zhua->move(ob);
 message_vision ("\n$N"HIY"刚想逃走，$n从怀中掏出一把马刀，手起刀落，剁下了它的龙爪....\n\n"NOR,me,ob);
message("channel:rumor",YEL+"\n【"+HIB" 八部天龙 "NOR+YEL"】某人："+ob->query("name")+"拿到"+HIB"黑龙"+HIR"之爪"NOR+YEL"了！\n\n"+NOR,users() );
  destruct (this_object());
  return ;
  }
else
  {
  message_vision ("$N"HIY"消失在火光中......\n"NOR,me);
  destruct (this_object());
  return ;
}
}
