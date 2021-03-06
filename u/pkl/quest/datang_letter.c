#include <ansi.h>
inherit ITEM;
inherit __DIR__"skill_reward";

void create()
{
        set_name(RED"信件"NOR, ({ "secret letter","xin","letter" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long",
                        "这是一封大唐国王邀请贵宾的信函。\n");
                set("value", 1);
                set("material", "paper");
         }
        set("no_give","这是大唐陛下的信函,怎么能随便给人！\n");
        set("no_sell","这是大唐陛下的信函,怎么能卖！\n");
}

void init()
{       
        call_out("dest",(random(100)+900));
        add_action("do_send", "songxin");
        add_action("do_look", "kan");
        add_action("do_look", "chakan");
}

int do_look(string arg)
{
        int now_time, time;
        object me;

        me = this_player();
        now_time =time() - me->query_temp("songxin_time"); 
        time = 900;

        if(!arg) return 0;
        if( (arg=="letter"||arg=="xin")&&me->query_temp("datang_songxin")) {
                write(
                        "\n这是一封由大唐国王发出的信件，上面写着"
                        HIR" 「"+me->query_temp("songxin_target_name")+"」 亲启。\n"NOR);
                if(now_time >0 && now_time < time/8) write("你现在有充足的时间去送信。\n");
                else if(now_time < time/4 ) write("已经过去一小半时间了。\n");
                else if(now_time < time/2 ) write("你还有一半的时间去送信。\n");
                else if(now_time < time*3/4 ) write("你的时间已经不多了。\n");
                else write("时间将至，任务即将失败。\n");
        }else{
        if( (arg=="letter"||arg=="xin")&&!me->query_temp("datang_songxin")) 
        write("这是一封大唐国王邀请贵宾的信函。\n");
         }
                return 1;

}

int do_send(string arg)
{
        int i,j,exp,pot,number,silver,num;
        object me,target;
        string t_name,msg,msg1,skill;

        me=this_player();
        number = (int)me->query("combat_exp");
          for(i=0;i*i*i <(number/10);i++);

        if(!arg) 
               {
          me->add_temp("songxin/shibai",30);
           return notify_fail("你的基本潜能和道行减少三十点。\n你要送给谁？\n");
            }
        if(!objectp(target = present(arg, environment(me))) || !target) 
           {
           me->add_temp("songxin/shibai",30);
               return notify_fail("你的基本潜能和道行减少三十点。\n看清楚点，你要送信的人不在这里！\n");
           }
        t_name = target->query("name");
 
        if(userp(target) || me->query("id") != target->query("target_id"))
          {
          me->add_temp("songxin/shibai",30);
           return notify_fail("你的基本潜能和道行减少三十点。\n嘿嘿，想作弊？！\n");
           }
        if (!present("secret letter", me) )
           return notify_fail("你身上没有携带信件。\n"); 
        if (!me->query_temp("datang_join"))
           return notify_fail(t_name+"道：你不是大唐使者，怎么会送大唐陛下的信给我？\n");
        if (!me->query_temp("datang_songxin") || me->query("id") !=query("target_id") )
           return notify_fail(t_name+"道：这是大唐皇宫亲自交给你,要你送的？\n你是不是从别人那里抢来的？\n");
        if(me->query_temp("songxin_target_name") != t_name) 
           return notify_fail(t_name+"道：这封信不是给我的，你是不是送错了？\n");
        message_vision(HIY"$N擦了一把额头的汗，从怀中掏出信交给$n说道，这是大唐陛下\n让在下送给您的信，请您收好。\n"NOR, me, target);
        message_vision("$N交给了$n一封信。\n",me, target);
        message_vision(HIY "$N接过信看了看，点了点头说道：这位"+RANK_D->query_respect(me)+"辛苦你了。\n"NOR, target, me);
        
        if(number<300000) {
            exp=3500+number/600;
            pot=2000+number/3000;
        } else if(number<3000000) {
            exp=4000+number/6000;
            pot=2500+number/60000;
        } else if(number<30000000) {
            exp=4500+number/60000;
            pot=3000+number/600000;
        } else {
            exp=5000;
            pot=3500;
        }
       
         exp -= me->query_temp("songxin/shibai");
         pot -= me->query_temp("songxin/shibai");

     if(me->query_temp("npc_kill"))
       {
       me->add_temp("songxin/datang_job",1);
       me->add("songxin/job",1);
       num = (int)me->query_temp("songxin/datang_job");
   pot=150+pot*num/20;
      exp=250+exp*num/20;
       silver = (random(i)+num);
       }
      else
       {
       me->delete_temp("songxin/datang_job");
       me->delete("songxin/job");
         pot = pot/15 + random(100);
        exp = exp/15 + random(200);
         silver = random(i);
       }

       me->add("potential",pot);
       me->add("combat_exp",exp);
       me->add("balance",(silver*100));
       me->add("songxin/potential",pot);
       me->add("songxin/combat_exp",exp);
       me->add("songxin/silver",silver);
       me->add("songxin/number",1);
      
       tell_object(me,HIW"好！任务完成,奖励如下：\n" + 
                       "你的道行增加了"+COMBAT_D->chinese_daoxing(exp)+"\n" +
                       "你的潜能增加了"+chinese_number(pot) + "点\n"+
                       "你的存款增加了"+chinese_number(silver)+"两白银\n"
                       NOR);

       msg="为大唐陛下送信给"+me->query_temp("songxin_where")+"的"+me->query_temp("songxin_target_name")+"，\n获得exp："+exp+"，pot："+pot+ "，silver："+silver+"，";

       if (me->query("songxin/job") > 24) 
       {
       me->delete("songxin/job");
       if(number <= 300000)    j=2+random(4);
       if(number > 300000 && number <= 6000000)   j=3+random(4);
       if(number > 6000000 && number <= 18000000) j=4+random(4);
       if(number > 18000000)              j=5+random(4);
       me->add("potential",5000+250*j);
       me->add("combat_exp",5000+250*j);
       me->add("songxin/job1",1);
       me->add("songxin/potential",5000+250*j);
       me->add("songxin/combat_exp",5000+250*j);
       msg +="连续二十五次另外奖励：exp：" + (5000+250*j) + "，pot：" + (5000+250*j) + "，\n";
       tell_object(me,"你连续二十五次为大唐陛下送信，奖励：\n道行"+ COMBAT_D->chinese_daoxing(5000+250*j)+ "，\n潜能"+chinese_number(5000+250*j) + "点。\n");
       }

       if (me->query_temp("songxin/datang_job") > 8) 
       {
       me->delete_temp("songxin/datang_job");
       skill=give_reward(me);
       msg+= "and rewarded 1 lvl of "+skill+".\n";
       if(skill != "none")
                 {
       me->add("songxin/skill",1);
       msg1="听说"+ me->query("name")+ "连续九次为大唐陛下送信，特奖励一级"+ to_chinese(skill)+ "。\n";
       CHANNEL_D->do_channel(this_object(),"rumor",msg1);
                }
       }
      else msg+= "and rewarded 1 lvl of "+skill+".\n";

      MONITOR_D->report_quests_object_msg(me, msg);
  
      me->delete_temp("datang_songxin");
      me->delete_temp("songxin_time");
      me->delete_temp("npc_kill");       
      me->delete_temp("songxin_target_name");
      me->delete_temp("songxin_target_id");
      me->delete_temp("songxin_where"); 
      me->delete_temp("kill_target_name");
      me->delete_temp("kill_target_id");
      me->delete_temp("kill_where");  
      me->delete_temp("songxin/shibai");  
      destruct(target);
      destruct(this_object());
      return 1;
}

void dest()
{
      tell_object(this_player(),"书信忽然掉落在路上不见了。\n");  
      destruct(this_object());
}

