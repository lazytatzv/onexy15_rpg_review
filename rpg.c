/*
 * NOTE: 今回は若干厳し目に見ています.
 * コード自体に殆ど手は加えていません.
 *
 * 指摘箇所多いですが、１つ覚えておいて欲しいのは
 * 凹まないということ.
 * 最初から上手い人なんていません.
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//ifが続きすぎるとよくないと知る前に書いたためすごく汚いプログラミングになっています
//すみません
// FB:
// 最初は誰でも汚いので謝る必要は全くありません.
// nestが深いとよくないと学んだのは良いことでしょう.

// ===== OVERVIEW ======
// CODE POINTOUT:
// 全体を通して、
// 1. インデントが微妙に揃っていない
// 2. {}ブロックのscopeを意識しきれていない
// 3. 冗長な処理やデッドコードが散見される
// 4. 空行が少ないが故にコードが読みにくい
// 5. 変数名/関数名が微妙
// 6. そもそもゲームの仕様を何処かに書いてほしい
//
// BUG:
// 1. Player1が防御を選んで死ぬとゾンビ化するバグが発生するため、
//  ゲーム開始から2とEnterを連打してれば絶対に勝ててしまう
// 2. Player1が攻撃を選んで死んだ場合も、if(nerai2 = 2)のバグにより、
// 　敵のヘイトが確実にPlayer2に向かう謎仕様となっている
// 
// PS:
// バグとは言えないかもしれないが、
// Player1が防御してPlayer2がPlayer1に回復してるだけでそもそも絶対に負けない
// ((40~47)[敵ATT] / 2[防御]) < 30[Player2回復]

// Prototype declaration
//
// TIPS:
// 関数名に気をつけるべき. 長くても説明的に命名すること.
// おすすめはverb+noun
// ex.
//  int calc_total_hp(void);
//  void print_stats(void);
//
// FB:
// attackの1/2が何の数値なのかわからない.
// tairyokuは英語にしましょう.
int attack1();
int attack2();
int magic();
int tairyoku(int);

// TIPS:
// int argc, char** argvは使っていないので不要
// int main(void)で十分です
int main(int argc,char** argv){
    // FB:
    // 不要な変数が多すぎます.
    // playerが３人要るからplayer1,2,3
    // それぞれactionがあるからaction1,2,3などと
    // 安直に考えて変数定義をしないこと.
    // これは本質的にはメモリ節約などはあまり関係なく、
    // それよりは変数(情報)の寿命について考えてほしいです.
    // "いつ"それが必要なのか、"どれくらい"長く必要なのか、etc...
    //
    // また、playerXやenm, nなど名前だけだと何をstoreする変数なのかわかりません.
    // 命名だけに限って言えば、
    // player1_hp, mp_leftなどだったらもう少し読みやすく感じます
    // 
    // actionは本当に1,2,3と要りますか？
    // neraiXもint target一つでよさそうです.
    // 変数を定義する前に本当に必要か考えましょう.
    // 何故これを言っているかと言うと、
    // 入力された数字はその場で使い切られているということを理解してほしいからです.
    // その場でしか使わないならaction一つを使い回せばよいですよね.
    // ティッシュペーパーを取る時に毎回ティッシュXとか名前つけないですよね...
    // ただ、そもそも此処で定義しなくてもplayer毎にifで生存判定をしているので
    // if (playerX > 0) {
    //   int action;
    //   scanf ...
    // }
    // とスコープ内で変数を定義してしまうという手もあるでしょう.
    //
    // neraiに関して言えば、「誰を狙うか」は本当に重要な情報でしょうか. 
    // 変数を各々に対して定義する必要性はありますか？
    // その場で生きているplayerのリストを用いて
    // int target = alive[rand() % count]
    // とかで良い気がします
    //
    // 
    // TIPS:
    // 個人的には、enmなども略さずに書くと思います
    // enemy_xxxなど
    int enm,player1,player2,n,player3,mp,damage,action1,action2,action3,nerai1,nerai2,nerai3,nerai4;

    // FB:
    // 何の数値かわかりません.
    //
    // SOLUTION:
    // 変数名をもう少し説明的にするか、
    // #defineで定数化して数値に名前をつけるか、
    // コメントをここに書いておく
    // 色々やりかたはありますが、必ず何処かで説明は必要です.
    player1 = 100;
    player3 = player2 = 80;
    mp = 100;
    enm = 500;

    while(player1 > 0 || player2 > 0 || player3 > 0 && enm > 0){

        //体力等がマイナス表示にならないようにしています
        // FB:
        // マイナスにならないようにする関数なら
        // 関数名でそれを説明してしまうべきです
        player1 = tairyoku(player1);
        player2 = tairyoku(player2);
        player3 = tairyoku(player3);
        mp = tairyoku(mp);

        // FB:
        // これ重要です
        // 早期break/returnできるとnestを浅くできる可能性があります.
        // Filterするイメージですね. これをガード節(Guard Clause)と呼んだりします.
        // 闇雲に使えば良いものではないですが可読性とのトレードオフでしょうか..
        //
        // このifを通過した時点でplayer1/2/3のhpが0より大きいことが保証されるわけです.
        // ただ、それをうまくいかせていない部分が割とあるのが惜しいです..
        // 後ろで判定するならこれは不要かも
        // ここでやるなら後ろはいらない
        if(player1 <= 0 &&player2 <= 0 && player3 <= 0){
            break;
        }

        printf("\n\nplayer1の体力は%d,player2の体力は%d,player3の体力は%d\nplayer3のmpは%dです\n",player1,player2,player3,mp);
        
        // FB:
        // 上にあったifを通過している時点でplayer1>0は保証されてますよね？
        // この一番外側のifは書く必要性がないです.
        // これでnestを一つ減らせるわけです.
        // あと、インデントが揃っていない傾向があるので気をつけましょう.
        //
        if(player1 > 0){     //体力がある場合
            printf("player1はどうしますか?\n(攻撃するときは1,防御をするときは2を入力してください)\n");
            scanf("%d",&action1);

            // FB:
            // 1とか2って分かり辛くないですか？
            // 定数宣言しておくと良いと思います
            // ex.
            // #define ATTACK 1
            // #define DEFEND 2
            // 
            // TIPS:
            // 多くなりそうな場合やまとめて管理したい場合はenumを使いましょう
            // enumを使う場合も、プレイヤー毎に作るのではなく、
            // 一つのActionを定義してしまうと使い回せて便利です.
            // これなら変数を沢山定義する必要性もありません
            // enum Action {
            //   ACTION_ATTACK,
            //   ACTION_DEFEND,
            //   ACTION_HEAL,
            // };
            // switch文とも相性が良いです.
            //
            if(action1 == 1){
                printf("攻撃します\n");
                damage = attack1();

                // FB:
                // 全く問題ないですが、
                // enm -= damage;
                // の書き方に慣れておくと良いでしょう
                enm = enm - damage;

                printf("%dダメージ！\n",damage);
                if(enm <= 0){
                    break;
                }
            } else if(action1 == 2){
                printf("注意を引いて防御をします!\n");
            }

        }else{         //体力がない場合
            printf("player1は力尽きているため行動できません!\n");
        }

        // FB:
        // ここの外のifもguard clauseがあるなら要らないです
        if(player2 > 0){       //体力がある場合
        printf("player2はどうしますか?\n(回復をさせたいときは1,player3のmpを回復させたいときは2を入力してください)\n");
        scanf("%d",&action2);
        if(action2 == 1){
            printf("誰を回復しますか?\n");
            scanf("%d",&n);

            // FB:
            // やはり-=/+=などのsyntaxに慣れていないのかなと思います.
            // 私ならここswitch文使うかもしれません
            //
            // TIPS:
            // 今更ですが1,2,3だと分かりづらいというか
            // WARRIEER, HEALER, WIZARDとか定義しておけば見やすい気がします
            // 
            // 今は未だ知らないかもしれませんが、
            // ゲーム等でキャラクター等のEntityを扱う時はstruct(C++やJavaだとclass)
            // を使うのが定石です.
            //
            // FIX:
            //  死者蘇生できるのは仕様ですか？
            //  あと、体力が無限に増やせるっぽいですが...
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
        // NOTE: このif文では既にmp<30 or mp>=30で完全に網羅できているので
        // このブロックが実行されることは絶対に無いです.
        // 所謂"デッドコード"なので処理を変えるか、消しましょう.
            printf("player3は力尽きているため行動できません!\n");
        }


        // FIX:
        // [ゾンビ盾バグ]
        // Player1が防御をした状態で死ぬと、次のターンで if(player1 > 0)がskipされ、
        // action1が直前の2(防御)のままになり、敵はPlayer1のゾンビを攻撃し続けてしまう.
        // そうなるとPlayer2/3はダメージを受けることが無いため、ハメ技が可能になってしまう
        // Player1は防御し続けているだけで実質パーティが無敵になります(笑)
        //
        // WHY:
        // 根本原因として、状態(state)と入力(input)を分けて考えられていないことが挙げられる.
        // 敵の攻撃処理の中でプレイヤーが何のキーを押したかという情報をstoreした変数を
        // 使っているのはおかしいです. 結局の所、敵は防御しているかどうかだけを知りたい.
        // そこでループの最初にint is_defending = 0;とFlag(状態変数)を用意しておき、
        // Player1が防御をした時、Flagを1(True)にする.
        // ここで重要なのは、Flagは用が住んだら必ずResetするということ.
        // Flagを降ろさないとまたゾンビバグが発生してしまう.
        //
        // action変数は１つにまとめてUserInputのみに使い、
        // DEFENDしてるかどうかは状態フラグによって管理する.
        // 
        if(action1 == 2){       //敵のターン
            damage = attack2()/2;
            player1 = player1 - damage;
            printf("**敵の攻撃で%dダメージを受けました！**\n",damage);
        }else{         //player1が防御をしなかったとき
            printf("敵の攻撃です！\n");      
            // FB:
            // 8通り書くのはちょっと長い気がしますね...
            // 例えばですが、
            // 生存者のリストを配列で用意しておいて
            // forで回して生きている人だけをそれに入れて
            // そのarrayの中からランダムで攻撃するとか
            // いくらでもやりようはあると思います
            // 
            // 今のままだと4,5人となると詰みます(2^X)
            // 
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
                if(nerai2 = 2){ // FIX: 代入になっていませんか？==です. このBugは前回もあったので要注意！！！
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


    // FB:
    // これwhileの中に同じようなものを書きましたよね.
    // そっち側にまとめて書いてしまえば問題なさそうですが、駄目ではないです
    // ただ、全体的に冗長な印象は受けます
    if(player1 <= 0 && player2 <= 0 && player3 <= 0 ){
        printf("味方の体力が0になりました\nあなたの負けです\n");
    }else if(enm <= 0){
        printf("敵の体力が0になりました！\nあなたの勝ちです！\n");
    }
return 0;
}


// FB:
// コメントを書いているのは偉いです.
// 
// TIPS:
// 関数名を工夫すればコメントを書く必要性もなければ、
// 他の人がコードを読む時にかなり見やすいです.
//
// SUGGEST:
// attack1とattack2って処理をまとめられそうじゃないですか？
//
int attack1(){     //player1の攻撃
    int damage;
    srand((unsigned)time(NULL)); // <-- FIX:srandは一回にしましょう.
    damage = rand()%5 + 16;
    return damage;
}

int attack2(){       //敵の攻撃
    int damage;
    srand((unsigned)time(NULL));
    damage = rand()%8 + 40;
    return damage;
}


// ADVANCED:
// attack1/2はダメージ計算して返すだけなのに、
// magicはprintfで喋るところまでやっています
// 関数化しているのは良いことですが、関数作成時に責任範囲がブレている気がします
// attackXとは別系統の関数ということなら駄目ではないですが...
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

// FB:
// 関数名がちょっと微妙ですね
// 私なら
// int clamp_zero(int n){};
// とかでしょうか
int tairyoku(int n){
    if(n <= 0){
        n = 0;
    }
    return n;
}
