//gunseng.c
#include <ansi.h>

int ask_name(); 

inherit NPC;
inherit F_MASTER;
void create()
{

       set_name("������ʦ", ({"daozheng chanshi","daozheng","chanshi",}));
        set("gender", "����" );
        create_family("������", 3, "����");
        set("title",HIG"��������ʦ"NOR );
	set("age", 28);
set("long",
		"����һλ���ĸߴ������ɮ�ˣ����۴�׳��������Բ�����ֱֳ�\n"
		"�У�����һϮ�Ҳ�������ģ��ƺ���һ�����ա�\n"
	);
	set("class", "bonze");
	set("attitude", "heroism");

        set("force", 1700);
        set("max_force", 1700);
        set("force_factor", 70);
        set("mana", 1700);
        set("max_mana", 1700);
        set("mana_factor", 20);
        set("combat_exp", 1000000);
        set("daoxing", 1000000);

        set_skill("yijinjing", 120);
        set_skill("chanzong", 120);
        set_skill("force", 120);
        set_skill("spells", 120);
        set_skill("shaolin-shenfa", 120);
        set_skill("unarmed", 120);
        set_skill("jingang-leg", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("stick", 120);
        set_skill("zui-gun", 120);
        map_skill("unarmed", "jingang-leg");
        map_skill("stick", "zui-gun");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "shaolin-sword");
        map_skill("force", "yijinjing");
        map_skill("spells", "chanzong");

	set("max_kee", 1300);
	set("max_sen", 1300);
	setup();
        carry_object("/d/shaolin/obj/qimeigun")->wield();
        carry_object("/d/shaolin/obj/dao-cloth")->wear();


}
void attempt_apprentice(object ob)
{
	if( (string)ob->query("gender") != "����" )
	{
		command ("say �����ӷ�Ůʩ��ѽ��ƶɮ�ɲ��ҿ������Ц����");
		return;
	}

        if(((int)ob->query_skill("yijinjing",1) < 60 ))
        {
                command ("say �����ӷ�ʩ�����׽��Ϊ������ƶɮ��������Ϊͽѽ��\n�㻹��ȥ���巨����Ϊʦ�ɡ�");
                return;
        }

        if( (string)ob->query("class")!="bonze" )
	{
		command ("say �����ӷ�ƶɮ�������������׼ҵ��ӡ��ˡ�");
	}
	command("say �����ӷ����գ����գ�");
        command("recruit " + ob->query("id"));
        ob->set("title", HIG"��ɽ�����´���ʦ"NOR);
}