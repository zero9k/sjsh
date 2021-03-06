//By waiwai@mszj 2000/10/28

#include <ansi.h>
#include <net/daemons.h>

inherit F_DBASE;

void auto_reboot_1();
void auto_reboot_2();
void auto_reboot_3();
void auto_reboot_4();
void auto_reboot_5();
void auto_reboot_6();
void auto_reboot_7();
void auto_reboot_8();
void auto_reboot_9();
void auto_reboot_10();
void auto_reboot_11();
void auto_reboot_12();
void auto_reboot_13();
void auto_reboot_14();
void auto_reboot_15();
void auto_reboot_16();

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "启动精灵(Reboot)");
        CHANNEL_D->do_channel( this_object(), "sys", "自动定时启动已经启动。\n\n");

        call_out("auto_reboot_1", 86400*7+random(7200));//   7(+ - 2小时)天自动重启

}

void auto_reboot_1()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十五"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_1");
        call_out("auto_reboot_2", 60);
}
void auto_reboot_2()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十四"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_2");
        call_out("auto_reboot_3", 60);
}
void auto_reboot_3()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十三"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_3");
        call_out("auto_reboot_4", 60);
}
void auto_reboot_4()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十二"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_4");
        call_out("auto_reboot_5", 60);
}
void auto_reboot_5()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十一"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_5");
        call_out("auto_reboot_6", 60);
}

void auto_reboot_6()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 十"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_6");
        call_out("auto_reboot_7", 60);
}

void auto_reboot_7()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 九"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_7");
        call_out("auto_reboot_8", 60);
}

void auto_reboot_8()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 八"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_8");
        call_out("auto_reboot_9", 60);
}

void auto_reboot_9()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 七"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_9");
        call_out("auto_reboot_10", 60);
}

void auto_reboot_10()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 六"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_10");
        call_out("auto_reboot_11", 60);
}

void auto_reboot_11()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 五"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_11");
        call_out("auto_reboot_12", 60);
}

void auto_reboot_12()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 四"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_12");
        call_out("auto_reboot_13", 60);
}

void auto_reboot_13()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 三"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_13");
        call_out("auto_reboot_14", 60);
}

void auto_reboot_14()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 二"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_14");
        call_out("auto_reboot_15", 60);
}

void auto_reboot_15()
{
   shout(HIR "启动精灵(Reboot): "+HIG"三界神话 "+HIY"系统定时重新启动,还有"+HIR" 一"+HIY" 分钟！！！ \n"NOR);

        remove_call_out("auto_reboot_15");
        call_out("auto_reboot_16", 60);
}

void auto_reboot_16()
{
        int i,j;
        object *ob, link_ob;
        string id;
        j=0;
        seteuid(getuid());
        set("channel_id", "存盘精灵(AutoSave)");
        ob=users();
        i=sizeof(ob);
        for( i=0;i<sizeof(ob);i++) {
                id = (string) ob[i]->query("id");
                if (!id) continue;
                if(!environment(ob[i]) )        continue;
                if( !objectp(link_ob = ob[i]->query_temp("link_ob")) ) continue;
                if( (int)link_ob->save() && (int)ob[i]->save() ) j = 1;
                else CHANNEL_D->do_channel( this_object(), "sys", ob[i]->query("name")+"档案自动存盘失败。");
        }
	write_file("/log/static/LASTCRASH", HIY"三界神话系统自动定时重启\n"NOR, 1);

        CHANNEL_D->do_channel( this_object(), "sys", "档案自动存盘成功。");

        if( find_object(DNS_MASTER) ) 
                DNS_MASTER->send_shutdown();

        shutdown(0);
        return;
}
