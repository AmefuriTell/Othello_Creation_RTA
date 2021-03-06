#include <bits/stdc++.h>

class grid
{
public:
    int stat;//状態
    int can[8];//u, ur, r, dr, d, dl, l, ul
    int can_num = 0;
    grid()
    {
        stat = 0;
        for (int i = 0; i < 8; i++)can[i] = 0;
    }

};

class board
{
public:
    grid g[8][8];
    int black, white, turn;
    int can = 0;

    board()
    {
        init();
    }
    void init()
    {
        g[3][3].stat = -1;
        g[4][4].stat = -1;
        g[3][4].stat = 1;
        g[4][3].stat = 1;

        black = 2;
        white = 2;
        turn = 1;
    }
    void print()
    {
        printf("    １２３４５６７８\n");
        for (int i = 0; i < 8; i++)
        {
            printf("%d |", (i + 1) * 10);
            for (int j = 0; j < 8; j++)
            {
                printf(g[i][j].stat == 1 ? "黒" : g[i][j].stat == -1 ? "白" : "・");
            }
            printf("|\n");
        }
        printf("黒:%d 白:%d\n", black, white);
    }
    void put_stone()
    {
        //入力
        int place = 0;
        int yoko = place % 10;
        int tate = place / 10;
        while(true)
        {
            if(turn == 1)printf("黒のターンです\n");
            else printf("白のターンです\n");
            printf("入力して下さい\n例\n11\n>");
            scanf("%d", &place);
            
            yoko = place % 10 - 1;
            tate = place / 10 - 1;
            if(0 > tate || tate > 7 || 0 > yoko || yoko > 7)printf("正確な入力をしてください。\n");
            else
            {
                if(g[tate][yoko].stat != 0)printf("すでに石が置かれています\n");
                else
                {
                    check(tate, yoko);
                    if(g[tate][yoko].can_num == 0)printf("ひっくり返すことができません。\n");
                    else
                    {
                        int dtate[] = {-1, -1, -1,  0,  1,  1,  1,  0};
                        int dyoko[] = {-1,  0,  1,  1,  1,  0, -1, -1};
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j <= g[tate][yoko].can[i]; j++)
                            {
                                g[tate + dtate[i] * (j)][yoko + dyoko[i] * (j)].stat = turn;
                            }
                        }
                        black += g[tate][yoko].can_num * turn;
                        white -= g[tate][yoko].can_num * turn;
                        if(turn == 1)black += 1;
                        else white += 1;
                        break;
                    }
                }
            }
        }
    }
    void check(int tate, int yoko)
    {
        int dtate[] = {-1, -1, -1,  0,  1,  1,  1,  0};
        int dyoko[] = {-1,  0,  1,  1,  1,  0, -1, -1};

        g[tate][yoko].can_num = 0;

        for (int i = 0; i < 8; i++)
        {
            g[tate][yoko].can[i] = 0;
            int nexttate = tate + dtate[i];
            int nextyoko = yoko + dyoko[i];
            if(0 > nexttate || nexttate > 7 || 0 > nextyoko || nextyoko > 7)continue;
            if(g[nexttate][nextyoko].stat == -turn)
            {
                for (int j = 2; j <= 8; j++)
                {
                    int nexttate = tate + dtate[i] * j;
                    int nextyoko = yoko + dyoko[i] * j;
                    if(0 > nexttate || nexttate > 7 || 0 > nextyoko || nextyoko > 7)break;
                    if(g[nexttate][nextyoko].stat == 0)break;
                    //黒が見つかったら止めてcan_num, canに入れてbreak。
                    if(g[nexttate][nextyoko].stat == turn)
                    {
                        g[tate][yoko].can_num += j - 1;
                        g[tate][yoko].can[i] = j - 1;
                    }
                }
            }
            else continue;
        }
    }
    void check()
    {
        can = 0;
        for (int tate = 0; tate < 8; tate++)
        {
            for (int yoko = 0; yoko < 8; yoko++)
            {
                int dtate[] = {-1, -1, -1,  0,  1,  1,  1,  0};
                int dyoko[] = {-1,  0,  1,  1,  1,  0, -1, -1};

                g[tate][yoko].can_num = 0;

                for (int i = 0; i < 8; i++)
                {
                    g[tate][yoko].can[i] = 0;
                    int nexttate = tate + dtate[i];
                    int nextyoko = yoko + dyoko[i];
                    if(0 > nexttate || nexttate > 7 || 0 > nextyoko || nextyoko > 7)continue;
                    if(g[nexttate][nextyoko].stat == -turn)
                    {
                        for (int j = 2; j <= 8; j++)
                        {
                            int nexttate = tate + dtate[i] * j;
                            int nextyoko = yoko + dyoko[i] * j;
                            if(0 > nexttate || nexttate > 7 || 0 > nextyoko || nextyoko > 7)break;
                            if(g[nexttate][nextyoko].stat == 0)break;
                            //黒が見つかったら止めてcan_num, canに入れてbreak。
                            if(g[nexttate][nextyoko].stat == turn)
                            {
                                g[tate][yoko].can_num += j - 1;
                                g[tate][yoko].can[i] = j - 1;
                                can += j - 1;
                            }
                        }
                    }
                    else continue;
                }
            }
        }
        return;
    }
};

int main()
{
    board b;
    b.init();
    b.print();
    while(true)
    {
        b.check();
        if(b.can == 0)
        {
            b.turn *= -1;
            b.check();
            if(b.can == 0)break;
        }
        b.put_stone();
        b.turn *= -1;
        b.print();
    }

    b.print();
    if(b.black < b.white)
    {
        printf("白の勝利!\n");
    }
    else if(b.black == b.white)
    {
        printf("引き分け!\n");
    }
    else
    {
        printf("黒の勝利!\n");
    }
}