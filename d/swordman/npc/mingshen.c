inherit NPC;
int ask_miyan();
#include <ansi.h>

void create()
{
	 set_name("明神弥彦", ({ "mingshen miyan", "miyan", "mingshen" }) );
	 set("gender", "男性" );
        set("title", WHT"觉醒"NOR);
	 set("age", 16);
	 set("long", "为了追求最强剑技，而离开神谷道场独自修行。他的身上正散发
着一种另人窒息的杀气，在阴暗的房间里，他瘦小的身形仿佛已
与黑暗容为一体。\n");
          set("daoxing",6000000);
           set("combat_exp",4000000);
        set("attitude", "peaceful");
	 set("int", 30);
	 set("class", "swordman");
        create_family("剑客联盟", 3, "弟子");
        set_skill("unarmed", 400);
        set_skill("dodge", 400);
        set_skill("parry", 400);
        set_skill("spells", 400);  
        set_skill("renshu", 400);
        set_skill("literate", 400);
        set_skill("sword", 400);  
        set_skill("huoxin-sword", 400); 
        set_skill("fengyu-piaoxiang", 400);
        set_skill("dodge", 400);  
        set_skill("force", 400);   
        set_skill("guixi-force", 400);
        map_skill("spells", "renshu");
        map_skill("force", "guixi-force");
        map_skill("sword", "huoxin-sword");
        map_skill("parry", "huoxin-sword");
        map_skill("dodge", "fengyu-piaoxiang");
        set("per", 30);
        set("max_kee", 4000);
        set("max_gin", 4000);
        set("max_sen", 4000);
        set("force", 10000);
        set("max_force", 5000);
        set("force_factor", 0);
        set("mana", 10000);
        set("max_mana", 5000);
        set("mana_factor", 200);
              set("swordman/dead_perform",1);
        set("inquiry", ([
                      "最强剑招":(:ask_miyan :),
                      "冥界召返":(:ask_miyan :),
        ]) );
         set("chat_chance_combat", 9000);
         set("chat_msg_combat", ({
                (: perform_action, "sword", "dead" :),
         }) );
         set("chat_chance",2);
         set("chat_msg", ({
        WHT"弥彦冷冷地看着你说道：如果要成为最强剑客，就必须有放弃一切的觉悟。\n"NOR,
        WHT"弥彦冷笑着说道：神谷活心流最大的秘密就是被封印的禁招[冥界召返]。\n"NOR,
        }));
         setup();
	  carry_object("/d/obj/cloth/zhanpao")->wear();
         carry_object("/d/obj/weapon/sword/qinghong")->wield();
}


/*
void die()
{
        object ob;
        if( !ob = query_temp("last_damage_from") )
        ob = this_player(1);
        if(ob) 
        ob->set("swordman/dead_perform",1);
	  message_vision(WHT  "\n在穿越生死线的那一刹那，$N终于领悟到了[冥界召返]的秘密。\n\n" NOR,ob);
        ::die();            
}
*/

void die()
{

        object ob = query_temp("last_damage_from") ;

        if((ob&&ob->query("MKS")>=5000) && (ob&&ob->query("swordman/dead_perform")!= 1) 
              &&(ob&&ob->query_temp("swordman/jiezhao_miyan")))
        {
        ob->set("swordman/dead_perform",1);
	 message_vision(WHT  "\n在穿越生死线的那一刹那，$N终于领悟到了[冥界召返]的秘密。\n\n" NOR,ob);

        }
       ::die();
}



int ask_miyan()
{
       object ob=this_player();
       if ( (int)ob->query("MKS") <5000)
       {
	message_vision(WHT  "\n明神弥彦冷冷的看着$N说道:你根本没有学会冥界召返的资格。\n\n" NOR,this_player());
	return 1;
       }
       else
       {command("sneer");
       command("say 冥界召返是我悟出的最强剑招，要想学会它，先接住
我这一招(jiezhao)再说。\n");
        this_player()->add_temp("swordman/ask_miyan", 1);
        return 1;
        }
}

void init()
{
    ::init();
    add_action("do_jiezhao", "jiezhao");
}

int do_jiezhao(string arg)
{
    object me=this_player(), npc=this_object(), ob;
    if (!me->query_temp("swordman/ask_miyan"))
    return 0;
      if (npc->is_fighting() || npc->is_busy())
                return notify_fail("明神弥彦现在正忙，没时间理你。\n");
    me->delete_temp("swordman/ask_miyan");
    me->set_temp("swordman/jiezhao_miyan",1);
    if (!(ob=query_temp("weapon"))
     || ob->query_temp("skill_type") != "sword")

    {
	destruct(ob);
	ob=new("/d/obj/weapon/sword/qinghong");
	ob->move(npc);
	command("wield sword");
       kill_ob(me);
          command("perform dead");
       me->kill_ob(npc);
       return 1;
     }
}
