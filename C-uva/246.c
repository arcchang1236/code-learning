#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_length = 52;
int input[55];
int deck[10][60];
int deck_num[10];
int empty[10];
int round;
int freq;

int initial_input[55];

int save_input[55];
int save[10][60];
int tmp[10][60];
int save_num[10];
int save_empty[10];
int save_length;
int round_temp;

int judge_draw(int save[60], int length)
{
    int i;
    if(save[0] + save[1] + save[length-1] == 10 ||
        save[0] + save[1] + save[length-1] == 20 ||
        save[0] + save[1] + save[length-1] == 30){
        for(i = save_length-1; i >=0; i--){
            save_input[i+3] = save_input[i];
        }
        save_input[0] = save[length-1];
        save_input[1] = save[1];
        save_input[2] = save[0];
        save_length += 3;
        save[length-1] = -1;
        length -= 1;
        for(i = 0; i < length - 2; i++){
            save[i] = save[i+2];
        }
        save[length-2] = -1;
        save[length-1] = -1;
        length -= 2;
        return length;
    }

    if(save[0] + save[length-1] + save[length-2] == 10 ||
        save[0] + save[length-1] + save[length-2] == 20 ||
        save[0] + save[length-1] + save[length-2] == 30){
        for(i = save_length-1; i >=0; i--){
            save_input[i+3] = save_input[i];
        }
        save_input[0] = save[length-1];
        save_input[1] = save[length-2];
        save_input[2] = save[0];
        save_length += 3;
        save[length-1] = -1;
        save[length-2] = -1;
        length -= 2;
        for(i = 0; i < length - 1; i++){
            save[i] = save[i+1];
        }
        save[length-1] = -1;
        length -= 1;
        return length;
    }

    if(save[length-1] + save[length-2] + save[length-3] == 10||
        save[length-1] + save[length-2] + save[length-3] == 20||
        save[length-1] + save[length-2] + save[length-3] == 30){
        for(i = save_length-1; i >=0; i--){
            save_input[i+3] = save_input[i];
        }
        save_input[0] = save[length-1];
        save_input[1] = save[length-2];
        save_input[2] = save[length-3];
        save_length += 3;
        save[length-1] = -1;
        save[length-2] = -1;
        save[length-3] = -1;
        length -= 3;
        return length;
    }
    return length;
}

void giveCards_draw(int ii)
{
    save[ii][save_num[ii]] = save_input[save_length-1];
    save_length -= 1;
    save_num[ii] += 1;

    while(save_num[ii] >= 3){
        int tmp = save_num[ii];
        save_num[ii] = judge_draw(save[ii], save_num[ii]);
        if(tmp == save_num[ii]){
            break;
        }
    }
    if(save_num[ii] == 0){
        save_empty[ii] = 1;
    }
    return;
}

void remain()
{
    int i, j;
    input_length = 52;
    save_length = 52;
    round = 0;
    for(i=0; i < 7; i++){
        for(j=0; j < 60; j++){
            deck[i][j] = -1;
        }
    }
    for(i=0; i<10; i++){
        deck_num[i] = 0;
    }
    for(i=0; i<10; i++){
        empty[i] = 0;
    }
    for(i = 0; i<52; i++){
        input[i] = initial_input[i];
        save_input[i] = initial_input[i];
    }
    for(i=0; i < 7; i++){
        for(j=0; j < 60; j++){
            save[i][j] = -1;
        }
    }
    for(i=0; i<10; i++){
        save_num[i] = 0;
    }
    for(i = 0; i<10; i++){
        save_empty[i] = 0;
    }

    int now = 0;
    while(1)
    {
        round ++;
        giveCards(now);
        now++;
        if(round == freq){
            break;
        }
        if(now > 6){
            now = 0;
        }
        while(empty[now] == 1)
        {
            now++;
            if(now > 6){
                now = 0;
            }
        }
    }
    int save_now;
    for(save_now = 0;draw()==0; )
    {
        if(now > 6){
            now = 0;
        }
        if(save_now > 6){
            save_now = 0;
        }
        while(empty[now] == 1)
        {
            now++;
            if(now > 6){
                now = 0;
            }
        }
        round++;
        giveCards(now++);

        while(save_empty[save_now] == 1)
        {
            save_now++;
            if(save_now > 6){
                save_now = 0;
            }
        }
        giveCards_draw(save_now++);
    }

}

int draw()
{
    int i, j;
    if(save_length != input_length)
        return 0;
    for(i = 0; i < save_length; i++){
        if(save_input[i] != input[i])
            return 0;
    }
    for(i = 0; i < 10; i++){
        if(save_num[i] != deck_num[i])
            return 0;
        for(j = 0; j < 60; j++){
            if(save[i][j] != deck[i][j])
                return 0;
        }
    }
    return 1;
}

void record()
{
    int i, j;
    for(i = 0; i < 10; i++){
        save_num[i] = deck_num[i];
        for(j = 0; j < 60; j++){
            save[i][j] = deck[i][j];
        }
    }
    save_length = input_length;
    for(i = 0; i < save_length; i++){
        save_input[i] = input[i];
    }
}

void giveCards(int now)
{
    deck[now][deck_num[now]] = input[input_length-1];
    input_length -= 1;
    deck_num[now] += 1;

    while(deck_num[now] >= 3){
        int tmp = deck_num[now];
        deck_num[now] = judge(deck[now], deck_num[now]);
        if(tmp == deck_num[now]){
            break;
        }
    }
    if(deck_num[now] == 0){
        empty[now] = 1;
    }
    return;
}

int judge(int deck[60], int length)
{
    int i;
    if(deck[0] + deck[1] + deck[length-1] == 10 ||
        deck[0] + deck[1] + deck[length-1] == 20 ||
        deck[0] + deck[1] + deck[length-1] == 30){
        for(i = input_length-1; i >=0; i--){
            input[i+3] = input[i];
        }
        input[0] = deck[length-1];
        input[1] = deck[1];
        input[2] = deck[0];
        input_length += 3;
        deck[length-1] = -1;
        length -= 1;
        for(i = 0; i < length - 2; i++){
            deck[i] = deck[i+2];
        }
        deck[length-2] = -1;
        deck[length-1] = -1;
        length -= 2;
        return length;
    }

    if(deck[0] + deck[length-1] + deck[length-2] == 10 ||
        deck[0] + deck[length-1] + deck[length-2] == 20 ||
        deck[0] + deck[length-1] + deck[length-2] == 30){
        for(i = input_length-1; i >=0; i--){
            input[i+3] = input[i];
        }
        input[0] = deck[length-1];
        input[1] = deck[length-2];
        input[2] = deck[0];
        input_length += 3;
        deck[length-1] = -1;
        deck[length-2] = -1;
        length -= 2;
        for(i = 0; i < length - 1; i++){
            deck[i] = deck[i+1];
        }
        deck[length-1] = -1;
        length -= 1;
        return length;
    }

    if(deck[length-1] + deck[length-2] + deck[length-3] == 10||
        deck[length-1] + deck[length-2] + deck[length-3] == 20||
        deck[length-1] + deck[length-2] + deck[length-3] == 30){
        for(i = input_length-1; i >=0; i--){
            input[i+3] = input[i];
        }
        input[0] = deck[length-1];
        input[1] = deck[length-2];
        input[2] = deck[length-3];
        input_length += 3;
        deck[length-1] = -1;
        deck[length-2] = -1;
        deck[length-3] = -1;
        length -= 3;
        return length;
    }
    return length;

}

int main()
{
    int i, j;
    int D;
    while(scanf("%d", &D) && D)
    {
        input_length = 52;
        round = 0;
        for(i=0; i < 7; i++){
            for(j=0; j < 60; j++){
                deck[i][j] = -1;
            }
        }
        for(i=0; i<10; i++){
            deck_num[i] = 0;
        }
        for(i=0; i<10; i++){
            empty[i] = 0;
        }

        input[51] = D;
        for(i = 50; i >= 0; i--){
            scanf("%d", &input[i]);
        }

        for(i = 0; i<52; i++){
            initial_input[i] = input[i];
        }

        int now = 0;
        while(1)
        {
            round ++;
            giveCards(now);

            if(input_length == 0){
                printf("Loss: %d\n", round);
                break;
            }
            else if(input_length == 52){
                printf("Win : %d\n", round);
                break;
            }

            else if(draw() == 1){
                freq=round-round_temp;
                remain();
                printf("Draw: %d\n",round);
                break;
            }

            if(round==2 || round==4 || round==8 || round==16 || round==32 || round==64 ||
               round==128 || round==256 || round==512 || round==1024 || round==2048){
                round_temp=round;
                record();
            }

            now++;
            if(now > 6){
                now = 0;
            }
            while(empty[now] == 1)
            {
                now++;
                if(now > 6){
                    now = 0;
                }
            }
        }
    }
    return 0;
}
