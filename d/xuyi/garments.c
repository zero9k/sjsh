// 神话世界·西游记之（世纪）
 
// create by night 2000.7.24

inherit ROOM;

void create ()
{
  set ("short", "薛记成衣铺");
  set ("long", @LONG

这是一家老字号的估衣庄，里面摆满了各式各样的衣物。绸、绢、丝、布、
皮袄、大红斗蓬、葱黄绫子棉裙、水绿色棉袄，秋香色团花……不一而足。
LONG);

  set("exits", ([
        "south"   : __DIR__"jiedao5",
      ]));
  set("objects", ([
        __DIR__"npc/xue"   : 1,
      ]));

  setup();
}

