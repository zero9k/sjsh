#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "��ƫԺ");
  set ("long", @LONG

����һ���ɰ���С��ƺ����ƺ����һԲʯ����������ʯ�ʡ�����
�Ǿ��´���ʯ��ʯ�Ͽ���һ�����̡����ϻ�����һ��δ��Ĳ���
���ƺ�ѧϰ������ᣩһ�¿��Եõ�����֪ʶ�����ϻ���������
�ƣ��������¡�

LONG);
  set("item_desc", ([ /* sizeof() == 1 */
  "canqi" : "һ��δ��Ĳ��壬���ư����������\n",
]));


  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
    "west" : __DIR__"yard",
]));
 set("objects", ([
__DIR__"obj/canqi" : 1,
__DIR__"npc/oldman" :1,

                       
 ]) );

  setup();
}

void init()
{
        add_action("do_study", "xia");
}

int do_study(string arg)
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;

        if( !arg || (arg != "canqi"))
                return notify_fail("��Ҫ��ʲô�壿\n");
        if( me->is_busy() )
                return notify_fail("��æ�ĺܣ����й���ȥ�о���֣�\n");
        if( me->is_fighting() )
                return notify_fail("��ѧ�������������ˣ�\n");
        if( (int)me->query_skill("literate", 1) < 100)
                return notify_fail("�㿴�˰���Ҳ�����������������Щʲô��\n");
        if( (int)me->query_skill("literate", 1) < 180)
                return notify_fail("�㿴�˰�������俴���˵�������ŵ���ȴ���������˵Ķ��֡�\n");
        if( (int)me->query_skill("literate", 1) >= 500)
                return notify_fail("����˵��:���������ˣ��Ϸ��Ѿ������ˡ�\n");
        if( (int)me->query("max_force") < 1000)
                return notify_fail("��������㣬�����ˡ�\n");

        sen_cost = 80 - (int)me->query_int();
        if( (int)me->query("sen") < sen_cost )
                return notify_fail("������ͷ��������ô���壬����Ϣ��Ϣ�ˡ�\n");

        kee_cost = 80 - (int)me->query_con();
        if( (int)me->query("kee") < kee_cost )
                return notify_fail("�����ڻ���������ô���壬����Ϣ��Ϣ�ˡ�\n");

        force_cost = 20;
        if( (int)me->query("force") < force_cost )
                return notify_fail("���������᲻��������ô���壬����Ϣ��Ϣ�ˡ�\n");

        me->receive_damage("sen", sen_cost);
        me->receive_damage("kee", kee_cost);
        me->add("force", - force_cost);

        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);

        me->improve_skill("literate", gain);

        write("���������������ʼ���������壮��������������ļ�˵����������ղ����
[33m��ġ�����ʶ�֡������ˣ�[0m\n");

        tell_room( environment(me), me->name() + "�ƺ����ں����˽����ζ���壮����\n", ({me}));

        return 1;
}
