
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("水母娘娘", ({ "shuimu niangniang", "shuimu","niangniang" }) );
       set("loc_name", "水母娘娘");
        set("gender", "女性" );
        set("age", 26);
        set("int", 30);
        set("con", 30);
        set("per", 35);
        set("class", "hero");
        set("attitude", "friendly");
        set("rank_info/respect", "娘娘");
        set("apprentice_available", 50);
          create_family("南海普佗山", 2, "弟子");
        set("long",
                "昔年曾水底为妖，为祸人间。后被小张太子并四大神将\n"
                "收服，大圣国师王菩萨念其千年道行来之不易，遂收为\n"
                "弟子。\n"
                );
        set("force_factor", 100);
        set("chat_chance", 5);
        set("max_gin", 3000);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("eff_gin", 3000);
        set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("gin", 3000);
        set("kee", 3000);
        set("sen", 3000);
        set("max_force", 1000);
        set("force", 2000);
        set("max_mana", 1500);
        set("mana", 3000);
        set("combat_exp", 1000000);

        set_skill("unarmed", 100);
        set_skill("sword", 140);
        set_skill("force", 100);
        set_skill("literate", 60);
        set_skill("dodge", 100);
        set_skill("tianwei-shi", 100);
        set_skill("qixi-sword", 180);
        set_skill("parry", 100);
        set_skill("buddhism", 100);
        set_skill("lotusforce", 100);
        set_skill("lianhuan-tui", 100);
        set_skill("spells", 110);

        map_skill("sword", "qixi-sword");
        map_skill("dodge", "tianwei-shi");
          map_skill("spells", "buddhism");
        map_skill("force", "lotusforce");
        map_skill("unarmed", "lianhuan-tui");
        map_skill("parry", "qixi-sword");
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword","quewu" :),
                (: cast_spell, "freeze" :),
                (: exert_function, "hanxing shuimu" :),
        }) );

        setup();
        carry_object("/d/obj/cloth/skirt")->wear();
        carry_object("/d/obj/weapon/sword/wsword")->wield();
}
void reset()
{
        delete_temp("learned");
        set("apprentice_available", 1);
}
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 1, ob);
        } else {
                command("say 本夫人一天只收一个徒弟。");
        }
}
void do_recruit(object ob)
{
        if( (string)ob->query("gender") != "女性" )
          {
      command("say 我只收女弟子，你还是去拜小张太子吧！");
         return;
         }
   if (((int)ob->query("combat_exp") < 20000 )) {
   command("say 这位" + RANK_D->query_respect(ob) + "修行不足，还需多加努力才是。\n");
   return;
   }
        else {

                command("smile");
                command("say 你日后可要光大我的武功哟！");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "hero");
        add("apprentice_availavble", -1);
}
int accept_object(object me,object ob)
{
        object m;
        if (ob->query("id")=="mo li") {
                command("pat" + this_player()->query("id") );
                m=new("/d/obj/book/halberd");
                m->move(this_player());
                message_vision("水母娘娘交给$N一本书，这是师傅传我的东西，就送给你吧。\n", this_player());
                call_out("destroy", 1, ob);
        return 1;
        }
        else return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

void announce_gift()
{
        object *alluser,obj,gift;
        int s;
        object me = this_object();

        alluser=users();        

        CHANNEL_D->do_channel(this_object(),"party","七夕佳节，我派弟子可得礼物。");
        s=sizeof(alluser);
        for (int i=0;i<s;i++) {
            obj=alluser[i];
            if (obj!=me && obj->query("family/family_name")=="南海普陀山")
            {
            gift=new(__DIR__"moli");
            gift->move(obj);
            message("vision",me->query("name")+"给你一"+gift->query("unit")+gift->name()+"。\n",obj);
            }
        }

        destruct(me);
        return;
}

