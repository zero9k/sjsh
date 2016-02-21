//shulin 密林暗室

inherit ROOM;

void create ()
{
        set ("short", "密林暗道");
        set ("long", @LONG

这里四周都是石头,只有地面上依稀可见一些被刻出的图形...
洞顶上有个不大的小孔,这里可以看到一些阳光...
还有一些隐士喜欢在这里纳凉睡觉,据说很是痛快
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "enter" : "/d/calvin/milin/anshi1",
                "out" : "/d/calvin/milin/milin",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//              "/d/shulin/npc/密林使者":1,
        ]));

        set("outdoors", "changan");
  set("if_bed", 1);
  set("sleep_room", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
