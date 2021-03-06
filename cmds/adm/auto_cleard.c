#include <ansi.h>
#pragma save_binary

inherit F_DBASE;

void auto_save();

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "内存精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "\n自动内存回收系统已经启动。\n");
        call_out("auto_clear", 10);
}

void auto_clear()
{
        int i,mem;
        object *ob, link_ob;
        string id;
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("系统自动清除 " + reclaim_objects() + " 个变数。\n"));
        remove_call_out("auto_clear");
        call_out("auto_clear", 480+random(120));
}
