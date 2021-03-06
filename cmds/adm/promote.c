// promote.c
//modified by kissess for log recording
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object ob;
    string old_status, new_status;
    int my_level, ob_level, level;

    if( me!=this_player(1) ) return 0;

    if( !arg || sscanf(arg, "%s %s", arg, new_status)!=2 )
        return notify_fail("指令格式：promote <使用者> <等级>\n");

    if( wiz_level(new_status) < 0 ) return notify_fail("没有这种等级。\n");

    if( !objectp(ob = present(arg, environment(me))) 
    ||   !userp(ob) )
        return notify_fail("你只能改变使用者的权限。\n");

    if( wiz_level(me) < wiz_level(new_status) )
        return notify_fail("你没有这种权力。\n");

    old_status = wizhood(ob);

    seteuid(getuid());
    if( !(SECURITY_D->set_status(ob, new_status)) )
        return notify_fail("修改失败。\n");

    message_vision(HIC""HIG"$N "HIC"将 "HIY"$n "HIC"的权限从 "HIR + old_status + HIC" 改为 "HIR + new_status + "\n"NOR, me, ob);
    message("channel:sys",HIR"【权限精灵】"HIG+me->name(1)+HIR" 改变了 "HIW+ob->name(1)+HIR" 的巫师权限等级 \n"NOR,users());
    seteuid(getuid());
    ob->setup();
log_file("static/promote",
                        sprintf("%s(%s) promote %s(%s) 新等级%s on %s\n",me->name(1), geteuid(me), ob->name(1), geteuid(ob), wizhood(ob), ctime(time()) ) );

    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : promote <某人> (权限等级)

用来提升权限等级, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
一个 admin 能提升权限至任何等级, 而 arch 只能提升至 arch。
HELP
  );
  return 1;
}

