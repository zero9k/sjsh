//奖励npc
//inherit F_VENDOR_SALE;

#include <ansi.h>
int give_wx();
//int give_wx2();
int answer_me();
inherit NPC;

void create()
{
       set_name(HIW"武神"NOR, ({"wu shen", "wushen"}));
       set("long", "天宫负责凡间下界的武神，他拥有很多神秘的武学功夫，你可以象他那门派比武大会奖励。\n");
           set("gender", "男性");
       set("title", HIC"纵横天界的"NOR);
        set("age", 28);
        set("per", 40);
        set("attitude", "peaceful");
        set("inquiry", ([
            "奖励"    :(:give_wx:),
            "武学奖励"    :(:give_wx:),
            "jiangli"    :(:give_wx:),
   ]));
        setup();
        carry_object("/d/lingtai/obj/faguan")->wear();
}
int answer_me()
{
        command("say 小心我扁你！嘿嘿 。\n");
        return 1;
}
int give_wx()
{
        object who=this_player();
        string family;
       family=who->query("family/family_name");
        if (!userp(who))
         {
                command("heng");
                command("say 什么小猫小狗也来要礼物？！");
                command("qi");
                return 1;
        }
        if (this_player()->query("luckyy") > 0 ){
        message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
               command("say 门派大会奖励只有一份！领过就不给了！\n");
        return 1;
        }
        if (who->query("combat_exp") < 40000 ) {
                       command("hammer "+who->query("id") );
                command("say 你的武学这么烂，还想来混？");
                return 1;
         }
        if ( family == 0 )
       {
                command("heng");
                command("say "+who->query("name")+"你是什么门派的，那里钻出来的东西！\n");
            return 1;
       }
        switch(family) {
               case "五庄观":
who->add("potential",10000);
who->set("luckyy",1);
who->add("daoxing",30000);
        command("chat 恭喜恭喜，"+who->query("name")+"得到了门派比武大会五庄观第一名qn10000,道行３０年奖励！\n",);
break;
                case "东海龙宫":  
who->add("potential",7000);
who->set("luckyy",1);
who->add("daoxing",25000);
        command("chat 恭喜恭喜，"+who->query("name")+"得到了门派比武大会东海龙宫第二名qn7000,道行２５年奖励！\n",);
break;
                case "将军府": 
who->add("potential",4000);
who->set("luckyy",1);
who->add("daoxing",20000);
        command("chat 恭喜恭喜，"+who->query("name")+"得到了门派比武大会将军府第三名qn4000,道行２０年奖励！\n",);
break;
        default:
                command("sigh");
 command("say "+who->query("name")+"我未收到你门派比胜的通知，你查查看！\n");
               return 1;
       }
                     command("addoil");
               return 1;
}
/*        if (!userp(who)){
                command("heng");
                  command("say 什么小猫小狗也来要礼物?");
                command("qi");
                return 1;
        }

         if (who->query("combat_exp") < 500000 ){
                command("hammer "+who->query("id") );
                command("say 你再努力努力，很快可以拿奖励的。");
                command("addoil "+who->query("id") );
                return 1;
         }
         if (this_player()->query("jjj") > 0 ){
         message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 奖励只有一份！领过就不给了！\n");
        return 1;
        }
        who->add("potential",50000);
        who->add("balance",5000000);
        who->add("daoxing",50000);
        who->set("jjj",1);
message_vision("$N对着$n神秘的笑了笑，$n觉得身体发生剧烈的变化，顿时晕倒在地。\n",this_object(),this_player());
        command("tell "+who->query("id")+" 
               你的道行增加了五十年!\n 
               你现在存款增加了500gold。\n");
          command("chat 恭喜恭喜，"+who->query("name")+"武学到了50万，给予奖励！\n");
        return 1;
}
int give_wx2()
{
        object who=this_player();
        if (!userp(who)){
                command("heng");
                  command("say 什么小猫小狗也来要礼物?");
                command("qi");
                return 1;
        }

         if (who->query("combat_exp") < 1500000 ){
                command("hammer "+who->query("id") );
                command("say 你再努力努力，很快可以拿奖励的。");
                command("addoil "+who->query("id") );
                return 1;
         }
         if (who->query("combat_exp") > 1900000 ){
                command("hammer "+who->query("id") );
                command("say 你都这么厉害，还需要吗？贪心！。");
                command("kick "+who->query("id") );
                return 1;
         }
         if (this_player()->query("jjjj") > 0 ){
         message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 奖励只有一份！领过就不给了！\n");
        return 1;
        }
        who->add("potential",80000);
        who->add("balance",5000000);
        who->add("daoxing",100000);
        who->set("jjjj",1);
message_vision("$N对着$n神秘的笑了笑，$n觉得身体发生剧烈的变化，顿时晕倒在地。\n",this_object(),this_player());
        command("tell "+who->query("id")+" 
               你的道行增加了一百年!\n 
               你现在存款增加了500gold。\n");
          command("chat 恭喜恭喜，"+who->query("name")+"武学到了150万，给予奖励！\n");
        return 1;
}
void init()
{
     call_out("greeting", 1, this_player());
      ::init();
   add_action("do_vendor_list", "list");
}
void die()
{
 return;
}
}  */
