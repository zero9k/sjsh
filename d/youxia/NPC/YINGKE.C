// yingke.c       created 17-06-2001 piao
#include <ansi.h>


inherit NPC;

void create()
{
        set_name("С���", ({"huoji"}));
        set("gender", "����" );
        set("age", 13);
	set("title", HIR"��÷ɽׯӭ��"NOR);
        set("long", "һ����ͯ��ÿ�츺����ׯ��ǰӭ��Զ�������Ŀ��ˣ�\n");
        set("combat_exp", 200);
        set("attitude", "friendly");
        set_skill("dodge", 10);
        set("per", 30);
        set("max_kee", 150);
        set("max_gin", 150);
        set("max_sen", 150);
        setup();
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
        say( "С���˵������λ" + RANK_D->query_respect(ob) +
"����ӭ��������÷ɽׯ�����������ݼ�����ׯ�����Ŵ�ѩ�İɣ�\n");
}
