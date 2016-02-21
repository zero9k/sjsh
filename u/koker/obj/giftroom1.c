//by koker@sjsh 2002

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", HIG"悲惨之旅"NOR);
        set ("long", @LONG

一条长长的过道，两边都是一样的黑色的门．不知道在那个门里边
不时的传出惨叫声和阴森的嘿嘿声．
LONG);

        set("exits", 
        ([ //sizeof() == 4
              "east" : "/d/wiz/giftroom",
              "west" : "/u/koker/giftroom2",
        ]));

        set("no_clean_up", 0);
        set("no_kill", 1);
        set("no_cast", 1);
        set("no_fight", 1);
        set("no_perform", 1);
        set("no_move", 1);
        setup();
        replace_program(ROOM);
}
