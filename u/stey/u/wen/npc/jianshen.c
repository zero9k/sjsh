// Rainy


#include <ansi.h>

inherit NPC;
string *first_name = ({ "天", "地", "人", });
string *name_words = ({ "剑神"});

void create()
{        object ob1, ob2;
	string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];


        set_name(name,({"jian shen","shen"}));
        set("age", 200);
        set("long", "一个白髯老人，却十分矍铄，两眼透出威芒。\n");
        set("str", 40);
        set("cor", 30);
        set("per", 30);
	set("con", 30);
	set("cps", 30);
	set("spi", 30);
	set("int", 30);
        set_temp("apply/damage", 25);
        set_temp("apply/armor", 120);
        set("max_kee", 1200);
        set("max_sen", 1200);
	set("force", 1000);
	set("max_force", 1000);
	set("force_factor", 10);
	set("mana", 1000);
	set("max_mana", 1000);
	set("mana_factor", 120);
	set_skill("sword", 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("zuixian-steps", 120);
	set_skill("yujianshu", 120);
	map_skill("sword", "yujianshu");
	map_skill("dodge", "zuixian-steps");
	set("combat_exp", 100000);
	set("daoxing", 100000);
        set("limbs", ({ "头部", "身体", "手臂", "后背", "肚皮", "腿部"}) );
        set("verbs", ({ "bite", "claw"}) );
	set_weight(1200000);

        setup();


        ob1=carry_object("/d/obj/armor/tianjia");
	ob1->wear();
	ob1->set("no_sell", "掌柜的瞟了一眼道：这东西一看就是劣等品，不要！不要！\n");
        ob2=carry_object("/d/shushan/obj/tianjian");
	ob2->wield();
	ob2->set("no_sell", "掌柜的瞟了一眼道：这东西一看就是劣等品，不要！不要！\n");
}

void copy_status(object me,object ob)
{
	me->set_skill("sword", (int)ob->query_skill("sword", 1));
	me->set_skill("dodge", (int)ob->query_skill("dodge", 1));
	me->set_skill("parry", (int)ob->query_skill("parry", 1));
	me->set_skill("zuixian-steps", (int)ob->query_skill("yujianshu",
1) + 20);
	me->set_skill("zuixian-steps", (int)ob->query_skill("yujianshu", 1)
+ 20);

        me->set("combat_exp",ob->query("combat_exp"));
	me->set("daoxing",ob->query("daoxing"));
}

int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
}

void leave()
{
        message("vision",
                HIM + name() +"身形周转，慢慢的化做一柄巨大的神剑直上云霄，渐渐淡去了。\n"
NOR,environment(),  this_object() );
        destruct(this_object());
}

void invocation(object who)
{       int i;
        object *enemy;

	object me=this_object();
        copy_status(me,who);
        message("vision", HIM"忽然狂风大做，一柄天剑直落而下，身形一转化做一个"+ name() +
"来！\n\n"NOR,environment(), this_object() );
        enemy = who->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) )
enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }

}

