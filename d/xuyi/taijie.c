// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ROOM;

void create ()
{
  set ("short", "台阶");
  set ("long", @LONG
 
    穿过宝殿，眼前是三道平行的青石台阶。台阶上精工镂刻着麒麟，
玄龟，松鹤等瑞兽，形态逼真动人。台阶两侧整齐地排列着一人高的青
铜大香炉。香烟缭绕，瑞气氤氲。
LONG);

  set("outdoors", 1);

  set("exits", ([
  "south" : "/d/xuyi/dadian",
  "northup" : "/d/xuyi/neidian",
]));

  setup();
  replace_program(ROOM);
}

