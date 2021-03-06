// worker.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("小和尚", ({"monk"}));
        set("gender", "男性" );
        set("class", "bonze" );
        create_family("少林寺", 16, "弟子");
        set("age", 13);
        set("title", HIG"少林寺山门迎客"NOR);
        set("long", "一个小和尚，每天负责在山门迎接远道而来的客人．\n");
        set("combat_exp", 200);
        set("attitude", "friendly");
        set_skill("dodge", 10);
        set("per", 30);
        set("max_kee", 150);
        set("max_gin", 150);
        set("max_sen", 150);
        setup();
        carry_object("/d/shaolin/obj/cloth.c")->wear();

}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting()
	&& !this_player()->query("env/invisibility") ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
        say( "小和尚说道：这位" + RANK_D->query_respect(ob) +
"，欢迎到我们嵩山少林寺来！\n");
}

