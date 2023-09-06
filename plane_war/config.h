#ifndef CONFIG_H
#define CONFIG_H

#define game_width 512
#define game_height 768
#define game_title "飞机大战 v1.0"
#define game_res_path "./plane.rcc"
#define map_path ":res/img_bg_level_1.jpg"
#define map_scroll_speed 2 //图片滚动速度
#define game_rate 10  //游戏刷新率即定时器发送信号间隔，单位为ms
#define hero_plane_path ":/res/hero2.png"
#define bullet_path ":/res/bullet_11.png"
#define bullet_speed 5//子弹速度
#define bullet_num 30//弹匣中子弹总数
#define bullet_interval 20//发射间隔
#define enemy_path ":/res/img-plane_5.png"
#define enemy_speed 5//敌机速度
#define enemy_num 20//敌机总数
#define enemy_interval 30//敌机出现间隔
#define bomb_path ":/res/bomb-%1.png"  //%是占位符，因为需要有7张图
#define bomb_num 20 //爆炸数组中bomb对象个数
#define bomb_max 7 //爆炸图片最大索引
#define bomb_interval 20//爆炸切换图片时间间隔
#define sound_backgroud_path ":/res/bg.wav"
#define sound_bomb_path ":/res/bomb.wav"

#endif // CONFIG_H
