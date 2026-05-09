#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//ifが続きすぎるとよくないと知る前に書いたためすごく汚いプログラミングになっています
//すみません

// Prototype declaration
int attack1();
int attack2();
int magic();
int tairyoku(int);

int main(int argc,char** argv){
    // 変数が多すぎる
    int enm,player1,player2,n,player3,mp,damage,action1,action2,action3,nerai1,nerai2,nerai3,nerai4;

    player1 = 100;
    player3 = player2 = 80;
    mp = 100;
    enm = 500;

    while(player1 > 0 || player2 > 0 || player3 > 0 && enm > 0){
        //体力等がマイナス表示にならないようにしています
        player1 = tairyoku(player1);
        player2 = tairyoku(player2);
        player3 = tairyoku(player3);
        mp = tairyoku(mp);
        if(player1 <= 0 &&player2 <= 0 && player3 <= 0){
            break;
        }
        printf("\n\nplayer1の体力は%d,player2の体力は%d,player3の体力は%d\nplayer3のmpは%dです\n",player1,player2,player3,mp);
        if(player1 > 0){     //体力がある場合
        printf("player1はどうしますか?\n(攻撃するときは1,防御をするときは2を入力してください)\n");
        scanf("%d",&action1);
        if(action1 == 1){
            printf("攻撃します\n");
            damage = attack1();
            enm = enm - damage;
            printf("%dダメージ！\n",damage);
            if(enm <= 0){
                break;
            }
        }else if(action1 == 2){
            printf("注意を引いて防御をします!\n");
        }}else{         //体力がない場合
            printf("player1は力尽きているため行動できません!\n");
        }
        if(player2 > 0){       //体力がある場合
        printf("player2はどうしますか?\n(回復をさせたいときは1,player3のmpを回復させたいときは2を入力してください)\n");
        scanf("%d",&action2);
        if(action2 == 1){
            printf("誰を回復しますか?\n");
            scanf("%d",&n);
            if(n == 1){
                player1 = player1 + 30;
                printf("player1が30回復!\n");
            }else if(n == 2){
                player2 = player2 + 30;
                printf("player2が30回復!\n");
            }else if(n == 3){
                player3 = player3 + 30;
                printf("player3が30回復!\n");
            }else{
                printf("指定先が存在しないため失敗しました\n");
            }
        }if(action2 == 2){
            printf("player3のmpを回復します!\n");
            mp = mp + 20;
            printf("player3のmpは%dです\n",mp);
        }}else{           //体力がない場合
            printf("player2は力尽きているので行動できません!\n");
        }    
        if(player3 > 0){         //体力がある場合
        if(mp <30){
            printf("player3はmpが足りないため攻撃します\n");
            enm = enm - 10;
            printf("10ダメージ！\n");
            if(enm <= 0){
                break;
            }    
        }else if(mp >= 30){
            printf("player3はどうしますか?\n(魔法を使って攻撃するときは1,物理攻撃は2を入力してください)\n");
            scanf("%d",&action3);
            if(action3 == 1){
                printf("魔法を使います\n");
                damage = magic();
                enm = enm - damage;
                printf("%dダメージ！\n",damage);
                if(enm <= 0){
                    break;
                }
                mp = mp - 30;
            }else if(action3 == 2){
                printf("攻撃します\n");
                enm = enm - 10;
                printf("10ダメージ!\n");
                if(enm <= 0){
                    break;
                }
        }}else if(player3 <= 0){       //体力がない場合
            printf("player3は力尽きているため行動できません!\n");
        }
        if(action1 == 2){       //敵のターン
            damage = attack2()/2;
            player1 = player1 - damage;
            printf("**敵の攻撃で%dダメージを受けました！**\n",damage);
        }else{         //player1が防御をしなかったとき
            printf("敵の攻撃です！\n");      
            if(player1 > 0 && player3 > 0 && player2 > 0 ){
                srand((unsigned)time(NULL));   //味方がみんな生きているとき
                nerai1 = rand()%3 + 1;
                if(nerai1 == 1){
                    damage = attack2();
                    player1 = player1 - damage;
                    printf("**player1は%dダメージを受けた！**\n",damage);
                    if(player1 <= 0){
                        printf("player1は力尽きました\n");
                    }
                }else if(nerai1 == 2){
                    damage = attack2();
                    player2 = player2 - damage;
                    printf("**player2は%dダメージを受けた！**\n",damage);
                    if(player2 <= 0){
                        printf("player2は力尽きました\n");
                    }
                }else if(nerai1 == 3){
                    damage = attack2();
                    player3 = player3 - damage;
                    printf("**player3は%dダメージを受けた！**\n",damage);
                    if(player3 <= 0){
                        printf("player3は力尽きました\n");
                    }
                }
            
            }else if(player1 <= 0 && player2 > 0 && player3 > 0){
                nerai2 = rand()%2 + 2;     //player1が死んだとき
                if(nerai2 = 2){
                    damage = attack2();
                    player2 = player2 - damage;
                    printf("**player2は%dダメージを受けた!**\n",damage);
                    if(player2 <= 0){
                        printf("player2は力尽きました\n");
                    }
                }else if(nerai2 = 3){
                    damage = attack2();
                    player3 = player3 - damage;
                    printf("**player3は%dダメージを受けた!**\n",damage);
                    if(player3 <= 0){
                        printf("player3は力尽きました\n");
                    }
                }
            }else if(player1 > 0 && player2 <= 0 && player3 > 0){
                nerai3 = rand()%2 + 1;        //player2が死んでいるとき
                if(nerai3 = 1){
                    damage = attack2();
                    player1 = player1 - damage;
                    printf("**player1は%dダメージを受けた！**\n",damage);
                    if(player1 <= 0){
                        printf("player1は力尽きました\n");
                    }
                }else if(nerai3 = 2){
                    damage = attack2();
                    player3 = player3 - damage;
                    printf("**player3は%dダメージを受けた!**\n",damage);
                    if(player3 <= 0){
                        printf("player3は力尽きました\n");
                    }
                }
            }else if(player1 > 0 && player2 > 0 && player3 <= 0){
                nerai4 = rand()%2 + 1;       //player3が死んでいるとき
                if(nerai4 = 1){
                    damage = attack2();
                    player1 = player1 - damage;
                    printf("**player1は%dダメージを受けた！**\n",damage);
                    if(player1 <= 0){
                        printf("player1は力尽きました\n");
                    }
                }else if(nerai4 = 2){
                    damage = attack2();
                    player2 = player2 - damage;
                    printf("**player2は%dダメージを受けた！**\n",damage);
                    if(player2 <= 0){
                        printf("player3は力尽きました\n");
                    }
                }
            }else if(player1 > 0 && player2 <= 0 && player3 <= 0){
                damage = attack2();        //player1のみ生きているとき
                player1 = player1 - damage;
                printf("**player1は%dダメージを受けた！**\n",damage);
                if(player1 <= 0){
                    printf("player1は力尽きました\n");
                }
            }else if(player1 <= 0 && player2 > 0 && player3 <= 0){
                damage = attack2();         //player2のみ生きているとき
                player2 = player2 - damage;
                printf("**player2は%dダメージを受けた！**\n",damage);
                if(player2 <= 0){
                    printf("player2は力尽きました\n");
                }
            }else if(player1 <= 0 && player2 <= 0&& player3 > 0){
                damage = attack2();       //player3のみ生きているとき
                player3 = player3 - damage;
                printf("**player3は%dダメージを受けた！**\n",damage);
                if(player3 <= 0){
                    printf("player3は力尽きました\n");
                }
            }

            
            
        }
    }
    }
    if(player1 <= 0 && player2 <= 0 && player3 <= 0 ){
        printf("味方の体力が0になりました\nあなたの負けです\n");
    }else if(enm <= 0){
        printf("敵の体力が0になりました！\nあなたの勝ちです！\n");
    }
return 0;
}


int attack1(){     //player1の攻撃
    int damage;
    srand((unsigned)time(NULL));
    damage = rand()%5 + 16;
    return damage;
}
int attack2(){       //敵の攻撃
    int damage;
    srand((unsigned)time(NULL));
    damage = rand()%8 + 40;
    return damage;
}
int magic(){          //player3の魔法
    int n,damage;
    srand((unsigned)time(NULL));
    n = rand()%5 + 1;
    if(n == 5){
        printf("魔法は相手には当たらなかった！\n");
        damage = 0;
    }else{
        printf("魔法が相手に当たった\n");
        damage = rand()%7 + 37;
    }
    return damage;

}
int tairyoku(int n){
    if(n <= 0){
        n = 0;
    }
    return n;
}
