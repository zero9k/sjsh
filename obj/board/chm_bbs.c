//chm'留言板
//made by kissess on Mar 13,2002

#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name(HIM"阿蒙工作台"NOR, ({ "board" }) );
        set("location", "/u/chm/workroom");
        set("board_id", "chm_bbs");
        set("long",     "这是巫师阿蒙的工作台。\n" );
        setup();
        set("capacity", 200);
        replace_program(BULLETIN_BOARD);
}
