
inherit ROOM;
#include <ansi.h>
#include <room.h>

void create ()
{
  set ("short", "少林寺");
        set ("long", @LONG

    这里是少林寺。正前方黄墙碧瓦，飞檐翘檩，正中一道二丈来
宽，三丈来高的朱红杉木包铜大门。上方一块大匾，龙飞凤舞地书
着『少林寺』三个大字。寺前三三两两的站着几个僧人。
LONG);

  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/yingke" : 1,
]));
  set("outdoors", __DIR__"");
  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"smdian",
  "southdown" : __DIR__"shijie8",
]));

  create_door("north", "石门", "south", DOOR_CLOSED);
set("valid_startroom", 1);
setup();

        "obj/board/shaolin_b"->foo();
}

