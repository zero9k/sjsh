inherit NPC;
#include <ansi.h>

string *dirs1 = ({
"/d/city",
"/d/westway",
"/d/kaifeng",
"/d/lingtai",
"/d/moon",
"/d/gao",
"/d/sea", 
"/d/nanhai", 
"/d/eastway",
"/d/ourhome/honglou", 
"/d/jz",
"/d/shushan",
"/d/shuilian",
"/d/pansi",
"/d/qujing/xuanyuan",
});

string *dirs2 = ({
"/d/xueshan",
"/d/xiaoyao",
"/d/jueqinggu",
"/d/suifeng",
"/d/qujing/wuzhuang", 
"/d/qujing/baotou", 
"/d/qujing/baoxiang", 
"/d/qujing/bibotan",
"/d/qujing/biqiu",
"/d/qujing/chechi",
"/d/qujing/dudi",
"/d/qujing/fengxian",
"/d/qujing/firemount",
"/d/qujing/jilei",
"/d/qujing/jindou",
"/d/qujing/jingjiling",
"/d/qujing/jinping",
"/d/qujing/jisaiguo",
"/d/qujing/maoying",
"/d/qujing/huangfeng",
"/d/qujing/yingjian",
"/d/qujing/sanda",
"/d/qujing/heishui",
"/d/qujing/tuoshi",
"/d/qujing/village",
"/d/qujing/heifeng",
"/d/qujing/shuangcha",
"/d/qujing/liusha",
"/d/qujing/nuerguo",
"/d/qujing/pingding",
"/d/qujing/pansi",
"/d/qujing/tongtian",
"/d/qujing/qilin",
"/d/qujing/huoyun",
"/d/qujing/qinfa",
"/d/qujing/qinglong",
"/d/qujing/tianzhu",
"/d/qujing/wudidong",
"/d/qujing/wuji",
"/d/qujing/xiaoxitian",
"/d/qujing/yinwu",
"/d/qujing/yuhua",
"/d/qujing/zhujie",
"/d/qujing/zhuzi",
"/d/dntg/hgs",
"/d/dntg/sky",
"/d/penglai",
});

string *dirs3 = ({
"/d/death",  
"/d/meishan",
"/d/qujing/lingshan",
});

string ask_job();
string ask_join();
string ask_fangqi();

void create()
{
        set_name("礼仪官", ({ "liyi guan","liyi","guan","liyiguan" }));
        set("title", "大唐接待外来使节");
        set("gender", "男性");
        set("age", 33);
        set("str", 27);
        set("long", "穿着华丽的服饰，英气逼人。\n");
        set("combat_exp", 400000);
        set("attitude", "peaceful");
        set_skill("unarmed", 100);
        set_skill("force", 100);
        set_skill("whip", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);

        set("max_kee", 900);
        set("force", 900); 
        set("max_force", 900);
        set("max_sen", 900);
        set("inquiry", 
                ([
                 "送信"    : (: ask_job :),
                 "songxin" : (: ask_job :),
                 "work"    : (: ask_job :),
                 "job"     : (: ask_job :),
                 "使者"    : (: ask_join :),
                 "shizhe"  : (: ask_join :),
                 "放弃"    : (: ask_fangqi :),
                 "fangqi"  : (: ask_fangqi :),
                ]));

        set("chat_chance", 10);
        set("chat_msg", ({
                "礼仪官说道: 大唐陛下广招天下贤能之士，诚心相待。\n",
              }) );

        setup();
}

string ask_fangqi()
{
        object ob = this_player();

           if ((int)ob->query("balance") < 10000)
              return ("你的存款不够，不能清除未完成的任务？\n");
          if (!ob->query_temp("datang_songxin"))
              return ("你没有领送信的任务？\n");

        ob->add("balance",-10000);
        ob->delete_temp("datang_songxin");
        ob->delete_temp("songxin_time");
        ob->delete_temp("npc_kill");       
        ob->delete_temp("songxin_target_name");
        ob->delete_temp("songxin_target_id");
        ob->delete_temp("songxin_where"); 
        ob->delete_temp("kill_target_name");
        ob->delete_temp("kill_target_id");
              ob->delete_temp("songxin/datang_job");  
             ob->delete("songxin/job");     
      ob->delete_temp("songxin/shibai");
        ob->delete_temp("kill_where");  

        return ("你真没用，这点事情都办不到。\n");

}

string ask_join()
{
        object ob = this_player();
        string *applied_id;

         if (ob->query("combat_exp")<10000)
                     return ("你的武功太差，什么也做不了的。\n");

        if (ob->query_temp("datang_join"))
                return (RANK_D->query_respect(ob) + 
                "，你已经是大唐使者了。\n");
        ob->set_temp("datang_join",1);
        if( pointerp(applied_id = ob->query_temp("apply/id")) && sizeof(applied_id) )
               ob->set_temp("apply/short", ({HIY"大唐使者"NOR+" "+ob->name()+"("+applied_id[0]+")"}));
        else
               ob->set_temp("apply/short", ({HIY"大唐使者"NOR+" "+ob->name()+"("+ob->query("id")+")"}));       
       command("look "+ob->query("id"));
        return ("好,不错，这位" + RANK_D->query_respect(ob) + "可以为大唐陛下送信。\n");

}

string ask_job()
{
       object me,ob,obj,newob,who,who1;
       int i, j, k,l,exp;
       string* dirs,songxin_where,kill_where,name,name1,id,id1;
       mixed*  file, exit;

       ob=this_player();
       me=this_object();
       exp=ob->query("combat_exp");

       if (!ob->query_temp("datang_join"))
          return RANK_D->query_respect(ob) +"，你不是大唐使者，此话从何说起？";

       if (ob->query_temp("datang_songxin"))
          return ("你不是已经领了送信的任务吗？还不快去做。\n");

       if (time()-ob->query_temp("songxin_time") < 600)
          return "现在暂时没有给你的任务。";

       if (ob->query("combat_exp")<80000)
          return ("你的功夫还不够啊，送信可是很危险的事，我可不敢交给你这任务。\n");
 
        if(exp<100000) {
            dirs=dirs1;
        } else if(exp<1500000) {
            dirs=dirs1+dirs2;
        } else {
            dirs=dirs1+dirs2+dirs3;
        }

        if( !sizeof(dirs) )  return 0 ;

        i = random(sizeof(dirs));    

        file = get_dir( dirs[i]+"/*.c", -1 );

        if( !sizeof(file) )
               return 0;

       who = new(__DIR__"target_npc");
       who->set("target_id",ob->query("id"));

       ob->set_temp("songxin_target_id", who->query("id"));
       ob->set_temp("songxin_target_name", who->query("name"));
       
        for(k=0;k<30;k++) { 
           j = random(sizeof(file));
           if( file[j][1] > 0 ) 
             {
             newob=load_object(dirs[i]+"/"+file[j][0]);
             if (newob) 
                 {  
                 if(newob->query("no_fight") ||
                       newob->query("no_magic") ||
                       !(exit=newob->query("exits")) ||
                       sizeof(exit)<1)
                       continue;
                 who->move(newob);
                 message_vision("$N走了过来。\n",who);
                  }
           }
        }

       ob->set_temp("songxin_where", environment(who)->query("short"));

       l = random(sizeof(dirs));    

       file = get_dir( dirs[l]+"/*.c", -1 );

       if( !sizeof(file) )
               return 0;

       who1 = new(__DIR__"kill_npc");
       who1->invocation(ob);
         who1->set("target",ob);
       who1->set("target_id",ob->query("id"));

       obj=new(__DIR__"datang_letter");
       obj->set("target_id",ob->query("id"));
       obj->move(who1);
     
         ob->set_temp("kill_target_id", who1->query("id"));
        ob->set_temp("kill_target_name", who1->query("name"));

       for(k=0;k<30;k++) { 
           j = random(sizeof(file));
           if( file[j][1] > 0 ) 
             {
             newob=load_object(dirs[l]+"/"+file[j][0]);
             if (newob) 
                 {  
                 if(newob->query("no_fight") ||
                       newob->query("no_magic") ||
                       !(exit=newob->query("exits")) ||
                       sizeof(exit)<1)
                       continue;
                   who1->move(newob);
                 message_vision("$N走了过来。\n",who1);
                  }
           }
        }

       ob->set_temp("kill_where", environment(who1)->query("short"));
       ob->set_temp("datang_songxin",1);
       ob->set_temp("songxin_time",time());

       songxin_where = environment(who)->query("short");
       name = who->query("name");
       id = who->query("id");
       kill_where = environment(who1)->query("short");
       name1 = who1->query("name");
       id1 = who1->query("id");

switch(random(5)) {
        case 0:
        tell_object(ob,kill_where+"的"+name1+"("+id1+")"+"把陛下送给"+songxin_where+"的"+name+"("+id+")"+"信抢走了。\n陛下请你去办这件事情。\n");
        break;
        case 1:
        tell_object(ob,kill_where+"的"+name1+"("+id1+")"+"把陛下送给"+songxin_where+"的"+name+"("+id+")"+"信抢走了。\n麻烦你去办这件事情。\n");
        break;
        case 2:
        tell_object(ob,kill_where+"的"+name1+"("+id1+")"+"把陛下送给"+songxin_where+"的"+name+"("+id+")"+"信抢走了。\n请你迅速去办这件事情。\n");
        break;
        case 3:
        tell_object(ob,kill_where+"的"+name1+"("+id1+")"+"把陛下送给"+songxin_where+"的"+name+"("+id+")"+"信抢走了。\n你要小心去办这件事情。\n");
        break;
        case 4:
        tell_object(ob,kill_where+"的"+name1+"("+id1+")"+"把陛下送给"+songxin_where+"的"+name+"("+id+")"+"信抢走了。\n请你去完成这件事情。\n");
        break;
        }

       return "务必小心。\n";
}
