#include <ansi.h>
mixed names = ({
        ({
        "西天门","北天门","东天门","南天门","星日宫",
        "朱雀殿","通明殿","斩妖台","御马监大门","蟠桃园园门",
        "六千年蟠桃园","皂霞亭",       
        }),
        ({
         "魔礼海","魔礼寿","魔礼红","魔礼青","天宫卫士","佑圣真君","神兵","监兵","监观",
		 "土地","打扫卫士","皂衣仙女",
        }),
        });

string ask_jianxi()
{     object guo,ob;
      object *team;
	  int i=0,count=0,minexp,maxexp;
      string where;
	  guo =this_object();
	  ob=this_player();
	  
	  if (guo->query_condition("zzz_busy"))
	  return "我没有收到任何消息。";//guo busy time 
	  
	  if(ob->query("combat_exp")<500000)
      return  "你的功夫太差了。";//too low exp
      team=ob->query_team();
      count=sizeof(team);
	 // write("\n"+sprintf("%d",count));
	  if(count<=1)
      return "就你一个人?"; //too few people
      if(count>=5)
	  return "此事不宜张扬。"; //too many people
	  minexp=team[0]->query("combat_exp");
	  maxexp=minexp;
      
	  for(i=1;i<count;i++)
      { if(team[i]!=0)
	  { if(team[i]->query("combat_exp")<minexp)
	    minexp=team[i]->query("combat_exp");
		if(team[i]->query("combat_exp")>maxexp)
        maxexp=team[i]->query("combat_exp");
	  }
	  }
	  if ((maxexp-minexp)>800000)
      return "你们的武功相差太悬殊。";//exp too far
     //check ok
      
	  where=names[0][random(40)];
	  guo->apply_condition("zzz_busy",30);
	  ob->set_temp("team_count",count);
	  ob->apply_condition("zzz_busy",60);
	  for(i=0;i<count;i++)
	 //team[i]->set_temp("zzz_job_zhuji",1);
	  team[i]->apply_condition("zzz_busy",60);
	  for(i=100;i*i*i/10<=maxexp;i++);
      call_out("job",60,ob,where,i,count+2);
     // message_vision(HIY"$N狂笑不已：就凭你们几个也想挡住我的去路?\n"NOR, obj);
	  return    "我刚得到消息，有一名魔界奸细偷盗了天界天宫的镇宫宝物。\n"+
		        "          你们赶快去"+where+"设防阻截，抢到镇宫宝物后就地祭回(jihui)。\n"+
			    "          魔界肯定会派妖神接应他，多加小心。"; 
}


void job(object ob,string where,int maxpot,int ckiller)
{    object *team,obj,gift;
      
     int i=0;
    // team=ob->query_team();
	 //for(i=0;i<sizeof(team);i++)
	 if(environment(ob)->query("short")==where&&ob->query_condition("zzz_busy"))
	 {  if (ckiller>0)
	    {if (random(20)>16)
			{ obj=new(__DIR__"mengbing");   
	          obj->do_copy(ob,maxpot,3);
	          obj->set("title",HIY"魔界大统领"NOR);     
              obj->move(environment(ob));
              obj->kill_ob(ob);
			}
		     else 
			{ obj=new(__DIR__"mengbing"); 
		      obj->do_copy(ob,maxpot,1);
	          //obj->set("title",HIY"蒙古百夫长"NOR);
	          obj->move(environment(ob));
              obj->kill_ob(ob);
	          obj=new(__DIR__"mengbing");
		      if (random(20)>10)
			  {obj->do_copy(ob,maxpot,2);
	           obj->set("title",HIY"魔界小统领"NOR);
			  }
			   else 
               obj->do_copy(ob,maxpot,1);
		       obj->move(environment(ob));
               obj->kill_ob(ob);
			 }  
	  	  call_out("job",120,ob,where,maxpot,ckiller-1);
	    }else 
		 {if (present("menggu dahan",environment(ob)))
			{//present menggu dahan,then mission failed
			 tell_room(environment(ob),HIC"魔界妖兵挥挥手，示意魔界奸细先走。\n奸细匆匆忙忙的离开了。\n"NOR);
             tell_object(ob, HIY "\n魔界奸细出城了，你任务失败！\n" NOR); 
			}
		   else{
				obj=new(__DIR__"jianxi"); 
				obj->do_copy(ob,maxpot);
				obj->set("title",HIR"魔界奸细"NOR);
				obj->move(environment(ob));
				message_vision(HIY"$N狂笑不已：就凭你们几个也想挡住我的去路?\n"NOR, obj);
				obj->kill_ob(ob);
				gift=new(__DIR__"mijian");
				gift->set_temp("host",ob->query("id"));
				gift->move(obj);
				}
		}
	 }
      else
      tell_object(ob, HIY "\n魔界奸细偷偷溜出了城，你任务失败！\n" NOR); 
	  
	  return;
}			//make killer
       
	   
       
     




