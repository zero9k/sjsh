#include <ansi.h> 
inherit ROOM; 
void create() 
{
set ("short",HIW"爱的小巢"NOR); 
set ("long",@LONG 

到不了岸的... ...
我对肢离破粹的自己说
在分甭离析前，我看见了她的眼睛。
妖娆妩媚，在大海的下面望着我...
佛噩漆黑的眸子瞬间的扩大,将我吞没
一片黑暗

LONG 
HIW @LONG 
苍龙づ野......

LONG NOR); 
set("exits",([ 
"kz":"/d/city/kezhan", 
"wr":"/d/wiz/wizroom", 
])); 
        set("objects",  
        ([ 
//           __DIR__"npc/keai" : 1, 
        ])); 
set("outdoors", 1); 
        set("no_time",1); 
        set("no_upgrade_age",1); 
        replace_program(ROOM); 
set("no_clean_up", 1); 
set("valid_startroom", 1); 
set("if_bed",1); 
setup(); 
//call_other( "obj/board/lands_b","???"); 
}
