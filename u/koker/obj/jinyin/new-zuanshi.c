// zuanshi.c

inherit MONEY;

void create()
{
        set_name("钻石", ({"zuanshi", "zuan", "zuanshi_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "zuanshi");
                set("long", "亮晶晶的钻石，很珍贵的东西啊！\n");
                set("unit", "些");
                set("base_value", 2000000 );
                set("base_unit", "颗");
                set("base_weight", 37);
        }
        set_amount(1);
}
