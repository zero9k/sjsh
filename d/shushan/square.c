
inherit ROOM;

void create()
{
        set("short", "�㳡");
        set("long", @LONG
��ɽ�Ĺ㳡���������ᣬֻ��һ������ͯ
������������ʯ�̾͵ĵ��棬�����пӿ�����
�ĺۼ�������Ǽ������������������ĺۼ�
LONG
        );
        set("exits", ([ /* sizeof() == 2 */

  "north" : __DIR__"dadian",

  "northwest" : __DIR__"yongdao",
  "east" : __DIR__"jinglou",
  "south" : __DIR__"paifang",
]));

        set("objects",([
        __DIR__"npc/jiantong" : 2,
        __DIR__"npc/zhangmen" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xx" );

        setup();
        replace_program(ROOM);
      call_other("/obj/board/shushan_b", "???");
}