// cast...jingang.c

inherit SSERVER;

int cast(object me, object target)
{
        int invocation_time;
        object soldier;
        object soldier2;

        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能召唤十八罗汉！\n");

        invocation_time=60+(200-(int)me->query_skill("spells"));
        if(invocation_time<30) invocation_time=30;
        if((time()-me->query("last_invocation"))<invocation_time)
            return notify_fail("你刚叫过十八罗汉，他们都被你叫烦了！\n");

        if( (int)me->query("mana") < 500 )
                return notify_fail("你的法力不够了！无法召唤十八罗汉！\n");

        if( (int)me->query("sen") < 150 )
                return notify_fail("你的精神无法集中！无法召唤十八罗汉！\n");

        message_vision("$N喃喃地念了几句禅经。\n", me);

        me->add("mana", -300);
        me->receive_damage("sen", 150);

        if( random(me->query("max_mana")) < 800 ) {
                message("vision", "但是什么也没有发生。\n",
environment(me));
                return 1;
        }

        seteuid(getuid());
        soldier = new("/obj/npc/luohan1");
        soldier2 = new("/obj/npc/luohan2");
        soldier->move(environment(me));
        soldier2->move(environment(me));
        soldier->invocation(me);
        soldier2->invocation(me);
        soldier->set_temp("invoker",me);
        soldier2->set_temp("invoker",me);
        me->set("last_invocation",time());
        me->start_busy(1+random(1));

        return 8+random(5);
}


