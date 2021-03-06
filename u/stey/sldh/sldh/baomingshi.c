
//水陆大会报名使

// /d/kaifeng/npc/baomingshi.c
#include <ansi.h>
inherit NPC;
inherit F_SAVE;
#define DEBUG 0
#define DOC "/d/kaifeng/obj/sldhdoc" 
mapping JOINER=([]);

private int query_kinds(int min_num,int max_num);
private string listone(object who,int num);
void announce(string str);
int notify_failed(object ob,string str);
int start(object who,string arg);
int age(object who,string arg);
int dx(object who,string arg);
int delkind(object who,string arg);
int use(object who,string arg);
int closekind(object who);
int finish(object who);

int list(object who,string arg);
void announcing(string str)
{
  if (DEBUG) {
    object aoao = find_player ("aoao");
    if (aoao)
     if (wizardp(aoao))
       tell_object (aoao," ◇ "+str);
  }  else command_function("chat "+str);
}

void announce(string str)
{
  string s = str;
  int i, j;
  
  while ((i = strlen(s)) > 0)
  {
    j = strsrch (s, "\n");
    if (j < 0)
    {
      announcing (s);

      return;
    }  
    announcing (s[0..j]);
    s = s[j+1..i];
  }
}

int notify_failed(object ob,string str)
{
 if(!ob) return 0;
 tell_object(ob,str);
 return 1; 
}

int start(object who,string arg)
{
 string types;
 string str;
 mapping typestring;
 object me=this_object();
 object doc;
  if(!arg)
   return notify_failed(who,"请用start age或start dx来指示本次报名采用的分类。\n");


  types=lower_case(arg);
 if(types!="age"&&types!="dx") 
   return notify_failed(who,"无效的组别分类，请用age或dx来指示本次报名采用的分类。\n");

  if(types=="age") me->set("type","1");
  if(types=="dx")  me->set("type","2");
  str=me->query("type")=="1"?"年龄分组制":"武学分组制";
//initializing this_object's values
  me->set("min_combat_exp",15);
  me->set("min_age",14);
  me->delete("kinds");
  me->delete("kindlist");
  me->delete("ages");
  me->delete("dxs");
  me->delete("stop_report");
  typestring=([]);
  typestring["1"]="年龄分组";
  typestring["2"]="武学分组";
  JOINER=([]);
  me->set("typestring",typestring);
  me->save();

  doc=new(DOC);
  doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
  doc->restore();
  doc->set("typestring",typestring);
  doc->set("type",query("type"));
  doc->save();
  destruct(doc);
  
  tell_object(this_player(),"本次水陆大会报名采用"+str+"\n");
  str="本次水陆大会报名采用"+str+"\n";
  announce(str);
  return 1;
}

//查找是否有相同的组别，或者重叠的组别
int query_kinds(int min_num,int max_num)
{
 mapping kindlist;
 string kindstr;
 int kind,i;
 object me=this_object();
 

 if(!mapp(me->query("kindlist")))
   return 0;//返回false表示没有发现
 kindlist=me->query("kindlist");
 if(!(kind=me->query("kinds")))
   return 0;//返回false表示没有发现
 for(i=1;i<=kind;i++)
  {
   kindstr=sprintf("%d",i);
//大致有a1属于[a2,b2],b1属于[a2,b2],[a1,b1]包含[a2,b2]几种可能。
   if((min_num>=kindlist[kindstr]["min_num"]&&min_num<=kindlist[kindstr]["max_num"])||
      (max_num>=kindlist[kindstr]["min_num"]&&max_num<=kindlist[kindstr]["max_num"])||
      (min_num<kindlist[kindstr]["min_num"]&&max_num>kindlist[kindstr]["max_num"]))
     return 1;//返回true表示发现范围
  }
 return 0;
}

//查找出用户相应的组别
int query_user_kinds(object who)
{
 mapping kindlist;
 string kindstr;
 string type;
 int kind,i,num;

 object me=this_object();
 if(!who) return 0;
 if(!mapp(me->query("kindlist")))
   return 0;//返回false表示没有发现
 kindlist=me->query("kindlist");
 if(!(kind=me->query("kinds")))
   return 0;//返回false表示没有发现
 type=me->query("type");
 if(type=="1") num=who->query("age");
 else if(type=="2") num=who->query("combat_exp")/1000;
      else return 0;
      
 for(i=1;i<=kind;i++)
  {
   kindstr=sprintf("%d",i);
//玩家在[min_num,max_num]中吗？那就返回这个组别
   if(   num>=kindlist[kindstr]["min_num"] 

      && num<=kindlist[kindstr]["max_num"] )
     return i;//返回组别
  }
 return 0;
}
int age(object who,string arg)
{
 int min_age,max_age;
 int kinds;
 string kindstr;
 mapping kindlist;
 object doc;
 object me=this_object();
 
 if(!arg) 
   return notify_failed(who,"参数不能为空!\n");
 if(me->query("type")!="1")
  return notify_failed(who,"对不起，本次水陆大会使用的不是年龄分组制，不能设定年龄。\n");
 if(sscanf(arg,"%d %d",min_age,max_age)!=2)
  return notify_failed(who,"请用addage 最小年龄 最大年龄来增加年龄分组。\n"+

                           "示例：adddx 14 17 表示增加一组14到17岁的年龄组。\n");
 if(min_age>=max_age||min_age<me->query("min_age"))
  return notify_failed(who,"最小年龄必须小于最大年龄及大于等于"+
                       chinese_number(me->query("min_age"))+"岁。\n");
 if(query_kinds(min_age,max_age))
  return notify_failed(who,"设定的年龄分组与前面设定的其他组别范围有重叠的地方，"+
                          "请用lists命令看具体的分组，然后重设。\n");
 if(!(kinds=me->query("kinds")))
    kinds=1;
 else kinds=me->query("kinds")+1;
 me->set("kinds",kinds);

 kindlist=([]);
 kindstr=sprintf("%d",kinds); 
 kindlist[kindstr]=([]);
 kindlist[kindstr]["min_num"]=min_age;
 kindlist[kindstr]["max_num"]=max_age;
//加入者也加入种类组 
 JOINER[kindstr]=([]);
 if(me->query("kindlist"))
   kindlist+=me->query("kindlist");
   
 me->set("kindlist",kindlist);

 tell_object(who,"增加年龄组第"+kindstr+"组"+chinese_number(min_age)+"岁至"+chinese_number(max_age)+"岁。\n");
 me->save();
  doc=new(DOC);
  doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
  doc->restore();
  doc->set("kinds",kinds);
  doc->set("kindlist",kindlist);
  doc->save();
  destruct(doc);
  return 1;
  
}

int dx(object who,string arg)
{
 int min_dx,max_dx;
 int kinds;
 string kindstr;
 mapping kindlist;
 object doc;
 object me=this_object();
  
 if(!wizardp(who))
   return notify_failed(who,"你使用的指令不符合你的身份。\n");
 if(!arg) return notify_failed(who,"参数不能为空!\n");
 if(me->query("type")!="2")
  return notify_failed(who,"对不起，本次水陆大会使用的不是武学分组制，不能设定武学。\n");
 if(sscanf(arg,"%d %d",min_dx,max_dx)!=2)

  return notify_failed(who,"请用adddx 最小武学 最大武学来增加道行分组。\n示例：adddx 300 1000 表示增加一组300到1000年的武学组。\n");

 if(min_dx>=max_dx||min_dx<me->query("min_combat_exp"))
  return notify_failed(who,"最小武学必须小于最大武学及大于"+chinese_number(me->query("min_combat_exp"))+"年。\n");

 if(query_kinds(min_dx,max_dx))
  return notify_failed(who,"设定的武学分组与前面设定的其他组别范围有重叠的地方，请用lists命令看具体的分组，然后重设。\n");

 if(!(kinds=me->query("kinds")))
    kinds=1;
 else kinds=me->query("kinds")+1;
 me->set("kinds",kinds);

 kindlist=([]);
 kindstr=sprintf("%d",kinds); 
 kindlist[kindstr]=([]);

 kindlist[kindstr]["min_num"]=min_dx;
 kindlist[kindstr]["max_num"]=max_dx;
//加入者也加入种类组 
 JOINER[kindstr]=([]);
 if(me->query("kindlist"))
   kindlist+=me->query("kindlist");
 me->set("kindlist",kindlist);
 tell_object(who,"增加武学组第"+kindstr+"组"+chinese_number(min_dx)+"至"+chinese_number(max_dx)+"。\n");
 me->save();
  doc=new(DOC);
  doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
  doc->restore();
  doc->set("kinds",kinds);
  doc->set("kindlist",kindlist);
  doc->save();
  destruct(doc);
 
 return 1;
}

int delkind(object who,string arg)
{
 int num,i,j;
 mapping kindlist,joiner;
 string kindstr,kindstr1;
 object doc;
 object me=this_object();
 
 if(!arg) return notify_failed(who,"参数不能为空!\n");
 if(!(num=me->query("kinds")))
  return notify_failed(who,"非法的参数发现，可能是没有增加分组，可以使用addage或"+

                           "adddx来增加。\n请重新设置本次水陆大会报名使。\n");
 if(num<1) 
  return notify_failed(who,"你还没增加组别呢，没什么好删的。\n");

 if(sscanf(arg,"%d",i)!=1)
  return notify_failed(who,"请使用delkind 分组来删除可用的组别。\n"+
                           "例如：delkind 1表示删除当前使用组，比如14-17岁组。\n");
 if(i>num||i<1)
  return notify_failed(who,"要删除的组别超过了当前具有的组别数。\n"); 
  
  kindlist=([]);
  me->set("stop_report",1);
  kindlist=me->query("kindlist");
  //还要搬数据
  if(mapp(kindlist))
   for(j=i;j<=num;j++) {
         kindstr=sprintf("%d",j);
    map_delete(kindlist,kindstr);
    if(j+1<=num) {
       kindstr1=sprintf("%d",j+1);
       kindlist[kindstr]=([]);
       kindlist[kindstr]["min_num"]=kindlist[kindstr1]["min_num"];
       kindlist[kindstr]["max_num"]=kindlist[kindstr1]["max_num"];      
    }
   } 
  if(mapp(JOINER))
   for(j=i;j<=num;j++) {
         kindstr=sprintf("%d",j);
     map_delete(JOINER,kindstr);  
    if(j+1<=num) {
       kindstr1=sprintf("%d",j+1);
       JOINER[kindstr]=([]);
       joiner=([]);
       joiner=JOINER[kindstr1];
       JOINER[kindstr]=joiner;
    }
   } 
  me->set("kindlist",kindlist);
  num-=1;
  me->set("kinds",num);
  me->delete("stop_report");
  me->save();
//save to joiner file
  doc=new(DOC);
  doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
  doc->restore();

  doc->set("joiner",JOINER);
  doc->set("kindlist",me->query("kindlist"));
  doc->set("type",me->query("type"));
  doc->set("typestring",me->query("typestring"));
  doc->set("kinds",me->query("kinds"));
  doc->save();
  destruct(doc);
 tell_object(who,"删除第"+chinese_number(i)+"组成功！\n");
 return 1;
}

int finish(object who)
{
 object doc,env;
 string msg;
 object me=this_object();
 
   me->set("stop_report",1);
   me->save();
  if(env=environment(me))
   {
     env->delete("no_fight");
     env->delete("no_magic");

     env->delete("no_clean_up");
     env->delete("no_steal");
     env->delete("no_bian");
     env->delete("has_stand_here");
   }
   doc=new(DOC);
   doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
   doc->restore();
   doc->set("kindlist",me->query("kindlist"));
   doc->set("type",me->query("type"));
   doc->set("typestring",me->query("typestring"));
   doc->set("kinds",me->query("kinds"));
   doc->set("joiner",JOINER);
   doc->save();
   destruct(doc);   
   msg="第"+chinese_number(me->query("sldh_num"))+"届水陆大会报名工作全部完成！";

   announce(msg);
   msg="老夫愿本次大会圆满成功。\n";
   announce(msg);
 return 1;
}

private string listone(object who,int num)
{
 int i;
 string msg,kindstr,str;
 mapping kindlist,joinerlist,typestr; 
 string *list,type;
 object doc;
 object me=this_object();
 
 doc=new(DOC);
 if(!doc) 
  {
   notify_failed(who,"异常出错，可能是目标文件"+DOC+"不存在。\n");
   return "异常出错。\n";
  }

 doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
 doc->restore();
 kindstr=sprintf("%d",num);
 kindlist=me->query("kindlist");
 joinerlist=doc->query("joiner");
 typestr=me->query("typestring");

 type=me->query("type");
 str="\n";
 if(mapp(kindlist))
  msg="　第"+chinese_number(num)+typestr[type]+"("+HIR+
       chinese_number(kindlist[kindstr]["min_num"])+"岁至"+
       chinese_number(kindlist[kindstr]["max_num"])+"岁"+NOR+")：\n";
 if(mapp(joinerlist)&&mapp(joinerlist[kindstr]))
  {
   list=keys(joinerlist[kindstr]);
   if(!list) msg+="　本组没有玩家参加报名。\n";
   else
   { 
     if(sizeof(list)==0) {
        msg+="　本组没有玩家参加报名。\n";
        return msg;
      } 
     
     for(i=1;i<=sizeof(list);i++) {
       string str1;
       str1=sprintf("%-10s",list[i-1]);

       if((i%7)==0) str1=str1+"\n\n";
       if((i%7)==1) str1="　"+str1;
       str+=str1;
      } 
     (i-1)%7!=0?str+="\n\n":str=str;
     msg+=HIC+str+NOR;
     msg+=HIW+"　总共"+chinese_number(sizeof(list))+"名玩家参加本组报名。"+NOR+"\n";
     if(!me->query("total_num")) me->set("total_num",sizeof(list));
     else me->set("total_num",me->query("total_num")+sizeof(list));
   }
  }
 else msg+="　本组没有玩家参加报名。\n";
 return msg;
}

int list(object who,string arg)
{
 int i,num,kinds;
 string msg,str;
 object me=this_object();
 
 me->set("total_num",0);

 msg=HIY"第"+chinese_number(me->query("sldh_num"))+"届水陆大会分组及报名者列表：\n"NOR;
 msg+=HIG"┏————————————————————————————————————————┓"NOR+"\n";
 kinds=me->query("kinds");
 if(!arg)
  if(kinds>0)
   for(i=1;i<=kinds;i++) {
    msg+=listone(who,i);
   if(i!=kinds) 
 msg+=HIG"┡———————————————————————————————————┩"NOR+"\n";    
   } 
 msg+=HIG"┗————————————————————————————————————————┛"NOR+"\n";       
 str=sprintf("%70s","总共有"+chinese_number(me->query("total_num"))+"名玩家参加本次水陆大会报名");
 str=HIY+str+NOR+"\n\n";
 msg+=str;
 tell_object(who,msg);
 return 1;
}

void create()
{

        set_name("水陆大会报名使", ({ "sldh baoming shi", "shi zhe"}) );
        set("age",500);
        set("combat_exp",8000000);
        set("force",10000);
        set("max_force",7000);
        set("mana",16000);
        set("max_mana",8000);
            set_skill("spells", 500);
        set("inquiry", ([
            "rumors":  "要报名就在这里用report命令参加。",
        ]) );
        setup();
        carry_object("/d/obj/armor/jinjia")->wear();

}

string short()
{
 object me=this_object();
 
 return "第"+chinese_number(me->query("sldh_num"))+"届水陆大会报名使"+"("+me->query("id")+")";
}

string long()
{
   object me=this_object();
return "\n水陆大会报名使执掌水陆大会报名大权，是举办水陆大会的巫师的得力助手。\n你有什么疑问可以打入help report看帮助。\n";
}

string query_save_file()
{

  return DATA_DIR "sldh/reporter";
}
void init()
{
  object env;
  object me=this_object();
  
 if(!(env=environment(me))) destruct(me);
 if(!env->query("has_stand_here"))
  {
   env->set("has_stand_here",1);
   env->set("no_clean_up",1);
   env->set("no_fight",1);
   env->set("no_magic",1);
   env->set("no_bian",1);
   env->set("no_steal",1);
   this_object()->restore();
   if(!me->query("sldh_num"))
     me->set("sldh_num",1);
   else me->set("sldh_num",me->query("sldh_num")+1);
   me->save();
   remove_call_out("greeting");

   call_out("greeting",5);
   me->delete("kinds");
   me->delete("kindlist");
   me->delete("ages");
   me->delete("dxs");
  }

  add_action("do_report","report");
  add_action("do_help","help");
  add_action("do_list","lists");
  
 if(wizardp(this_player())) {
  add_action("do_start","start");
  add_action("do_age","addage");
  add_action("do_dx","adddx");
  add_action("do_delkind","delkind");
  add_action("do_finish","finish");
 } 
}

void greeting()
{
 string msg;

 object me=this_object();
 
 msg="第"+chinese_number(me->query("sldh_num"))+"届水陆大会正式报名即将开始，请大家到长安城十字街头南使用report命令报名。";
 announce(msg);
 remove_call_out("greeting");
}

int do_report()
{
 object player=this_player();
 object me=this_object();
 object doc;
 int num,j,k;
 string msg,kindstr,ids,i;
 string *list;
 mapping temp=([]);
 mapping kindlist=([]);
if(!DEBUG)  
 if(wizardp(player))
  return notify_fail("巫师不能参加水陆大会。\n");

 if(userp(player))
  {

    if(!(i=me->query("type")))
      return notify_fail("对不起，巫师还没作好准备，请稍候再来。\n"); 
    if(!me->query("kinds"))
     return notify_fail("对不起，巫师还没准备好，请等候巫师准备妥当再来报名。\n");
    if(me->query("stop_report"))
     return notify_fail("对不起，已经停止报名。\n");
//进行玩家报名条件的核对   
    switch(i) {
//武学分组
     case "1":num=player->query("age");
            if(num<me->query("min_age"))
              return notify_fail("对不起，你的武学太小，至少要"+
                       chinese_number(me->query("min_age"))+"才能参加水陆大会。\n");

            if(player->query("combat_exp")/1000<me->query("min_combat_exp"))
              return notify_fail("对不起，你的武学太少，至少要"+
                       chinese_number(me->query("min_combat_exp"))+"才能参加水陆大会。\n");
            break;
//武学分组
     case "2":num=player->query("combat_exp")/1000;
            if(num<me->query("min_combat_exp"))
              return notify_fail("对不起，你的武学太少，至少要"+
                     chinese_number(me->query("min_combat_exp"))+"才能参加水陆大会。\n");
            if(player->query("age")<me->query("min_age"))

              return notify_fail("对不起，你的武学太小，至少要"+
                     chinese_number(me->query("min_age"))+"才能参加水陆大会。\n");

            break;
     default: return notify_fail("对不起，现在还没开始水陆大会报名，请稍候。\n");
    }
    doc=new(DOC);
    doc->set("file_name",DATA_DIR+"sldh/joiner"+sprintf("%d",me->query("sldh_num")));
    doc->restore();
    j=query_user_kinds(player);
    if(j==0) return notify_fail("对不起，你不符合报名条件，无法将你分到合适的分组去。\n");
    
    if(!mapp(this_object()->query("kindlist")))
      return notify_fail("对不起，你不符合报名条件，无法将你分到合适的分组去。\n");
      
     kindlist=this_object()->query("kindlist");
     kindstr=sprintf("%d",j);  
    if(i=="1") 
     msg=chinese_number(kindlist[kindstr]["min_num"])+"岁至"+
         chinese_number(kindlist[kindstr]["max_num"])+"岁年龄组";
    else if(i=="2")     
     msg=chinese_number(kindlist[kindstr]["min_num"])+"年至"+
         chinese_number(kindlist[kindstr]["max_num"])+"年武学组";
    
    ids=player->query("id");
    if(mapp(JOINER))
     for(k=1;k<=query("kinds");k++)
      {
       i=sprintf("%d",k);       
       if(mapp(JOINER[i]))
       {
         list=keys(JOINER[i]);
         for(j=0;j<sizeof(list);j++)
          if(list[j]==ids) return notify_fail("你不是已经报了名吗？\n");
        }
      }

    temp[ids]=([]);
    temp[ids]["price"]="N";//这个指示该报名者是否获得了水陆大会奖励
    temp[ids]["fight"]="N";//这个指示该报名者是否参加了水陆大会
    //还有一个参数指示该名报名者参加水陆大会获得的名次，通常只指示冠军或非就行
    temp[ids]["winnum"]=0;//1指示champion,0指示normal
    if(mapp(JOINER[kindstr]))
     JOINER[kindstr]+=temp;
    else {
        JOINER[kindstr]=([]);

        JOINER[kindstr]+=temp;
    }
    doc->set("joiner",JOINER);
    doc->save();
    msg="第"+chinese_number(me->query("sldh_num"))+"届水陆大会"+msg+
        "\n新加报名者"+player->query("name")+"("+player->query("id")+")"+"一名。";
    announce(msg);
    destruct(doc);
  }
  return 1;
}

int do_start(string arg)
{
 object me=this_player();
 if(!me) return 0;
  start(me,arg);
 return 1;
}

int do_age(string arg)
{
 object me=this_player();

 if(!me) return 0;
 age(me,arg);
 return 1;
}

int do_dx(string arg)
{
 object me=this_player();
 if(!me) return 0;
 dx(me,arg);
 return 1;
}

int do_delkind(string arg)
{
  object me=this_player();
 if(!me) return 0;
  delkind(me,arg);
 return 1;
}

void destroy_me()
{

 message_vision(HIG"只见一阵青烟从地底冒起，报名使倏忽间居然不见了！\n"NOR,this_object());
 destruct(this_object());
}

int do_finish()
{
 object me=this_player();
 if(!me) return 0;
  finish(me);
  remove_call_out("destroy_me");
  call_out("destroy_me",2);
 return 1;
}

int do_list(string arg)
{
 object me=this_player();
 if(!me) return 0;
 list(me,arg);
 return 1;
}

int help(object who)

{
 string msg;
 msg ="\n\n水陆大会报名须知：\n";
 msg+="水陆大会报名者在报名使所在的房间使用report命令即可报\n";
 msg+="名，当然报名成功与否要看你是否符合当时报名条件。\n";
 msg+="报名过程中，可以使用lists命令查看当前分组情况以及报名\n";
 msg+="情况。\n\n";
if(wizardp(who))
 {
 msg+="
做为巫师可使用的指令按执行的先后顺序依次为：\n";
 msg+="
1、start：每次采用新的分组类别就必须使用start age或
start dx来判别，这个命令会清除原来的设定。\n";
 msg+="
2、addage,adddx：addage或adddx都是用来增加一个分组的
，你可以不带参数使用看使用帮助。\n";
 msg+="
3、delkind：delkind是用来删除多余的组别或错误的组别，
发现分组有错误就用delkind来修正，delkind指令会删除该
组别的一切当前设置包括已报名的玩家。\n";
 msg+="
4、lists：lists主要用来观看当前的报名情况，它可以列出
组别，每个组别报名者，报名人数，总的报名人数。\n";
 msg+="
5、finish：这个指令指示当前报名一切结束,报名使的身上数
据应该存盘,包括报名者数据,并清扫报名使在当前环境设下的
变化，然后毁灭报名使。\n";
 }
 tell_object(who,msg);
 return 1;
}

int do_help(string arg)
{
 object me=this_player();
 if(!me) return 0;
 if(!arg) return 0;
 if(lower_case(arg)=="report")
  help(me);
 else return 0;

 return 1;
}
