#include <ansi.h>
inherit ROOM;
void create()
{
set ("short",HIM"巧克力的竹屋"NOR);
set ("long",@LONG

巧克力的精致小房，房中摆设不多，但是一个女孩子，房间始终是那么地精雅。
窗外郁郁葱葱，一片春意昂然，书柜上放了很多书，壁柜上放着很多的布制玩具
当你来到这里，会看见巧克力灿烂的微笑和她的照片等，还有她的很多饰物，此
时她正坐在窗前，看着那满眼的春色，面露微笑，了望远方。

LONG);
set("exits",([
"moon" : "/d/moon/ontop2",
"pt" : "/d/nanhai/gate",
"kz":"/d/city/kezhan",
"kf" : "/d/kaifeng/tieta",
"fc" : "/d/lingtai/gate",
"+" : "/d/city/center",
]));
set("outdoors", 0);
set("no_clean_up", 1);
set("valid_startroom", 1);
setup();
}
