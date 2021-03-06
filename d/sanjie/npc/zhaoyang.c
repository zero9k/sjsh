// zhaoyang.c 朝阳天师

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string expell_me(object me);

void create()
{
       set_name(HIR"朝阳天师"NOR, ({"master zhaoyang", "master"}));
       set("long", "天一宫掌门大师兄，德高隆重，贵为道教盟主。\n");
       set("title", HIC"天一宫"NOR);
       set("per", 40);
       set("gender", "男性");
       set("age", 70);
       set("class", "sanjie");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "老道长");
       set("max_kee", 1500);
       set("max_gin", 100);
       set("max_sen", 1500);
       set("force", 1800);
       set("max_force", 1800);
       set("force_factor", 180);
       set("max_mana", 1800);
       set("mana", 1800);
       set("mana_factor", 180);
       set("combat_exp", 1700000);
       set("daoxing", 2100000);

        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("spells", 220);  
        set_skill("tianmogong", 120);
        set_skill("literate", 120);
        set_skill("sword", 120);  
        set_skill("huxiaojian", 120);
        set_skill("zhaoyangbu", 120);
        set_skill("force", 120);   
        set_skill("huntianforce", 120);

        map_skill("spells", "tianmogong");
        map_skill("force", "huntianforce");
        map_skill("sword", "huxiaojian");
        map_skill("parry", "huxiaojian");
        map_skill("dodge", "zhaoyangbu");

	
	create_family("三界山", 2, "蓝");
	
	set("inquiry", ([
        "出门"    : (: expell_me :),
        "leave"   : (: expell_me :),
	"name"     : "我乃天一宫现任掌教大弟子，你可以称呼我朝阳天师。\n",
	"here"     : "这里是天一宫后殿，你迷路了？\n",
	]));	
	
	setup();
	carry_object("/d/sanjie/obj/jinjia")->wear();
	carry_object("/d/sanjie/obj/qinghong")->wield();
}

string expell_me(object me)
{       
        me=this_player();
        if((string)me->query("class")=="sanjie") {
                message_vision("朝阳天师胡子抖抖，好像非常生气。\n", me);
                me->set_temp("sj_betray", 2);
                message_vision("朝阳天师对$N嚷嚷着：小东西，你说话是真心话(true)？\n", me);
                return ("气死我了，气死我了！\n");
}
        return ("问什么问！自己想去！\n");
}
void init()
{     add_action("do_true", "true");
}

int do_true(string arg)
{
        if(this_player()->query("class") != "sanjie" )
                return 0;
        if(this_player()->query_temp("sj_betray") > 1 ) {
                message_vision("$N答道：弟子讲的真心话！\n\n", this_player());
                message_vision("朝阳天师叹了口气，既是如此，你便下山吧！\n", this_player());
                this_player()->set("combat_exp", this_player()->query("combat_exp")*80/100);
		this_player()->set("daoxing", this_player()->query("daoxing")*80/100);
		if( this_player()->query_skill("tianmogong") )
		    this_player()->delete_skill("tianmogong");
		if( this_player()->query_skill("huntianforce") )
	            this_player()->delete_skill("huntianforce");
                this_player()->add("betray/count", 1);
                this_player()->add("betray/sanjie", 1);
                this_player()->delete("family");
                this_player()->delete("class");
                this_player()->set("title", "普通百姓");
                this_player()->set("faith",0);
                this_player()->set_temp("sj_betray", 0);
                this_player()->save();
                message_vision("朝阳天师伸出手将$N一推，$N化作一股青烟向东而去 ... \n", this_player());
                this_player()->move("/d/sanjie/sanjiedao");
                tell_room( environment(this_player()),"天空上噗噗嗦嗦几声响，掉下个人来！\n", ({this_player()}));
                this_player()->unconcious();            
                return 1;
                }
        return 0;
}

void attempt_apprentice(object ob)
{	ob=this_player();
	if( (string)ob->query("family/family_name")=="三界山") {
	if ((int)ob->query("daoxing") < 100000 ) {
  	command("say 你的道行还不够，" + RANK_D->query_respect(ob) + "还需多加努力。\n");
	return;
	}

	if( (int)ob->query("pending/kick_out")) {
	command("say 这位" + RANK_D->query_respect(ob) + "你曾背我派，我不原再收你为徒了！\n");
	command("sigh");
	return;
	}

	if ((int)ob->query_int() < 25) {
	command("say 这位" + RANK_D->query_respect(ob) + "悟性太低，恐怕收了你也难有作为！\n");
	command("sigh");
	return;
	}
	if( (int)ob->query_skill("tianmogong", 1) < 100 ) {
	command("say 这位" + RANK_D->query_respect(ob) + "对我天魔功领会还不够深，现在收你也是勉为其难，不如作罢！\n");
	command("sigh");
	return;
	}
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
        command("recruit " + ob->query("id") );
	return;
	}
        command("shake");
        command("say 老夫不收外门弟子，" + RANK_D->query_respect(ob) + "还是另寻他人吧！\n");
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        ob->set("class", "sanjie");
}

�
