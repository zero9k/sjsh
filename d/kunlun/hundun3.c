//kunlun
inherit ROOM;

void create ()
{
        set ("short", "混沌中");
        set ("long", @LONG

四周一片云雾，使你快要分不清方向，还是趁能看到
路的时候赶快走吧。
LONG);

        set("exits", 
  ([ //sizeof() == 4
                "north" : __DIR__"yuxu",
                "south" : __DIR__"hundun3",
                "east" : __DIR__"hundun2",
                "west" : __DIR__"hundun1",

        ]));
        set("objects", ([

   ]));
       setup();
	replace_program(ROOM);
}

