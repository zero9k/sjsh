#include <ansi.h>
#include <dbase.h>
#include <armor.h>
inherit F_AUTOLOAD;
inherit NECK;
void create()

  {
     set_name("����"NOR, ({ "lanhua" ,"flower","hua" }) );
     set_weight(100);
      set("long","����,fayu�͸�repoo�����������fayu����
����Ϊֻ��Ҷ�ӲŶ�������.\n");
     set("value", 0);
      set("material", "flower");
     set("no_drop", "��Ư�������Űɡ�\n");
     set("unit", "��");
  set("armor_prop/armor", 1);
  set("armor_prop/personality", 5);
     setup();
  }

int query_autoload() { return 1; }