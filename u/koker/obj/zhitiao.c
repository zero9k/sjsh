//by koker@sjsh 2002/01/14 阴历初二 
//妈妈今天64岁生日，所以是64声钟声。

#include <ansi.h>
inherit ITEM;
void create()
{
set_name("纸条", ({ "zhi tiao" }) );
set_weight(5);
set("unit", "张");
set("long", "一张透明的纸条，你可以(list)看看上边有什么可以看的东西。\n");
set("value", 0);
setup();
}
void init()
{
 if (!wizardp(this_player())) {
    set("no_get",1);
    set("no_give",1);
    set("no_drop",1);
    set("no_sell",1);
  }                                    
add_action("do_list","list");
add_action("do_base","base");
call_out ("becoming_old",600);

}

void becoming_old ()
{
  object me = this_object();
  object who = this_player();
  tell_object(who,HIW"只听到远处好象敲响了64声钟声，你口袋内的纸条突然化做一道白光不见了。\n"NOR);
  destruct (me);
}

int do_list(string arg)
{
object who=this_player();
message_vision("
  $N对着光线终于在纸条上找到点东西。\n
  base : 查看自己的所有基本属性。\n
",who);
return 1;
}
int do_base(string arg)
{
object me;
object ob;
mapping my;
string str1;
string str2;
string str3;
string str4;
string str5;
seteuid(geteuid());
me = this_player();
if(!arg) ob = me;
else
if (wizardp(me))
{
ob = present(arg, environment(me));
if (!ob) ob = find_player(arg);
if (!ob) ob = find_living(arg);
if (!ob) return notify_fail("您要察看谁的状态？\n");
}
else return notify_fail("你现在还不能察看别人的状态。\n");
if (my = ob->query_entire_dbase())
{
str1 = "  〖姓名〗  "+ob->name()+"  〖性别〗  "+ob->query("gender")+"  〖ＩＤ〗  "+ob->query("id");
str2 = "  〖容貌〗  "+ob->query("per")+"  〖胆识〗  "+ob->query("cor")+"  〖定力〗  "+ob->query("cps")+"  〖福缘〗  "+ob->query("kar");
str3 = "  〖体格〗  "+ob->query("str")+"  〖筋骨〗  "+ob->query("con")+"  〖悟性〗  "+ob->query("per")+"  〖灵性〗  "+ob->query("spi");
str4 = "  〖ＰＫ〗  "+ob->query("PKS")+"  〖ＮＫ〗  "+ob->query("MKS")+"  〖道路〗  "+ob->query("ziyouchoose");
str5 = "  〖捐钱〗  "+(ob->query("donation")/1000000);
message_vision(HIW"$N要查的信息如下:\n"+str1+"\n"+str2+"\n"+str3+"\n"+str4+str5+"\n"NOR,me);
return 1;
}
}