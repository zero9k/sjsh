// by Repoo
#include <room.h>
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short", HIY"赤龙城城门"NOR);
  set ("long", @LONG

只见这城门非金非木非石;上面雕刻这一条红彤彤
的龙，见到这架势，你胆子都吓掉了一半。

LONG);

  set("exits", ([ /* sizeof() == 1 */
  "northwest" : __DIR__"clcity",
]));

  create_door("northwest", "赤龙城城门", "southeast", DOOR_CLOSED);

  set("objects", ([
]));

  set("outdoors", 1);

  setup();
}
