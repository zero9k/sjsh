// dizi.c

inherit NPC;

void create()
{
        int skill;

        set_name("神谷道场弟子", ({ "wuguan dizi", "dizi", "trainee" }) );
        set("gender", "男性" );
        set("age", 14+random(10));
        set("long", "你看到一位年轻的剑客，正在辛苦地练习着剑法。\n");

        set("combat_exp",200000);

       create_family("剑客联盟", 3, "弟子");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("spells", 50);  
        set_skill("renshu", 50);
        set_skill("literate", 50);
        set_skill("sword", 50);  
        set_skill("huoxin-sword", 50); 
        set_skill("fengyu-piaoxiang", 50);
        set_skill("dodge", 50);  
        set_skill("force", 50);   
        set_skill("guixi-force", 50);
        map_skill("spells", "renshu");
        map_skill("force", "guixi-force");
        map_skill("stick", "huoxin-sword");
        map_skill("parry", "huoxin-sword");
        map_skill("dodge", "fengyu-piaoxiang");
        set("per", 30);
        set("max_kee", 300);
        set("max_gin", 300);
        set("max_sen", 300);
        set("force", 1000);
        set("max_force", 700);
        set("force_factor", 20);
        set("mana", 1000);
        set("max_mana", 700);
        set("mana_factor", 20);
        setup();
        carry_object("/d/obj/cloth/zhanpao")->wear();
        carry_object("/d/obj/weapon/sword/changjian")->wield();
}
