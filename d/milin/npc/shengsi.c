// 生死恶神 by Calvin

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
       set_name(HIM"生死恶神"NOR, ({"shengsi eshen", "eshen", "shen"}));
       set("long",
"三重门之一大守护神,有着高深莫测的功力。\n");
       set("title", HIC"三重门神之"NOR);
       set("gender", "女性");
       set("age", 30);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 40);
	set("int", 30);
       set("max_kee", 10000);
       set("max_gin", 10000);
       set("max_sen", 10000);
       set("force", 5000);
       set("max_force", 5000);
       set("force_factor", 300);
       set("max_mana", 5000);
       set("mana", 5000);
       set("mana_factor", 300);
       set("combat_exp", 10000000);
  set("daoxing", 8000000);


        set("eff_dx", 200000);
        set("nkgain", 350);

       set_skill("literate", 350);
       set_skill("unarmed",350);
       set_skill("dodge", 350);
       set_skill("force", 350);
       set_skill("parry", 350);
       set_skill("sword", 350);
       set_skill("spells", 350);
        set_skill("moonshentong", 350);
        set_skill("baihua-zhang", 350);
        set_skill("moonforce", 350);
        set_skill("snowsword", 350);
        set_skill("moondance", 350);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");

create_family("月宫", 1, "开山祖师");
setup();

//        carry_object("/d/milin/obj/ssd");
        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/moon/obj/feijian")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
           command("say 我们月宫只收女徒，这位" +
RANK_D->query_respect(ob) + "还是另请高就吧。\n");
           return;}
        if ( (int)ob->query("per") <30){
	  command("shake");
	command("say 以我看这位" +
RANK_D->query_respect(ob) + "的资质并不适于跳舞，还是另请高就吧。\n");
  ob->set_temp("denied_by_chang_e",1);
	return;
}

        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}


�
