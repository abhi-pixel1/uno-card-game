#include<stdio.h>
#include <stdlib.h>
#include <time.h>

struct cards
{
    int n;
    char col;
};

void clean(struct cards *p);
void shuffel(struct cards *p);
void players_cut(struct cards *p,struct cards *p1,struct cards *p2);
void stacker(struct cards *p,struct cards *stk);
int inAction(struct cards *top_card,struct cards *player,struct cards **stk,int *count,int turn);
void buy(struct cards *player,struct cards **stk,int n);

int main()
{
    // char colors[6]={'r','y','g','b','\0'};

    struct cards pack[200];// full deck
    struct cards pl1[100];//player1
    struct cards pl2[100];//player2
    struct cards stack[108];//leftover cards
    struct cards *stk=stack;



    // for(int i=0;colors[i]!=0;i++){// to popuate the full deck(all colors)
    //     for(int j=0;j<13;j++,p++){
    //         if(j==0){
    //             (*p).n=j;
    //             (*p).col=colors[i];
    //         }
    //         else if(j>=1){
    //         (*p).n=j;
    //         (*p).col=colors[i];
    //         p++;
    //         (*p).n=j;
    //         (*p).col=colors[i];
    //         }
    //     }
    // }

    // for(int i=0;i<2;i++){       // to add the wild cards to thr deck
    //     for(int j=0;j<4;j++){
    //         (*p).n=i;
    //         (*p).col='w';
    //         p++;
    //     }
    // }


    clean(pack);
    for (int i = 0; i < 108; i++)
    {
        printf(" %d%c\t",pack[i].n,pack[i].col);
    }
    printf("\n----------------\n");




    srand(time(0));   //shuffling the deck
    shuffel(pack);


    // for (int i = 0; i < 108; i++)
    // {
    //     printf(" %d%c\t",pack[i].n,pack[i].col);
    // }
    // printf("\n----------------\n");




    players_cut(pack,pl1,pl2);


    // for (int i = 0; i < 11; i++)
    // {
    //     printf(" %d%c\t",pl1[i].n,pl1[i].col);
    // }
    // printf("\n----------------\n");

    // for (int i = 0; i < 11; i++)
    // {
    //     printf(" %d%c\t",pl2[i].n,pl2[i].col);
    // }
    // printf("\n----------------\n");



    stacker(pack,stack);


    // for (int i = 0; i < 108; i++)
    // {
    //     printf(" %d%c\t",stack[i].n,stack[i].col);
    // }
    // printf("\n");
    

    struct cards top_card;
    top_card.n=-1;
    top_card.col='\0';

    int p1_card_count=7;
    int p2_card_count=7;
    int i=1;
    int valid=1;
    // inAction(&top_card,pl1,&stk,&p1_card_count,i);

    while((p1_card_count!=0)&(p2_card_count!=0)){
        if(i%2!=0){
           valid = inAction(&top_card,pl1,&stk,&p1_card_count,i);
        }
        else if(i%2==0){
            valid = inAction(&top_card,pl2,&stk,&p2_card_count,i);
        }

        if(valid==1) i++;
    }

    // printf("\n----------------\n");

    // for (int i = 0; i < 108; i++)
    // {
    //     printf(" %d%c\t",stack[i].n,stack[i].col);
    // }

    if(p1_card_count==0) printf("player 1 is the winner!!!");
    else if(p2_card_count==0) printf("player 2 is the winner!!!");





    return 0;
}


void clean(struct cards *p){
    char colors[6]={'r','y','g','b','\0'};
    for(int i=0;colors[i]!=0;i++){// to popuate the full deck(all colors)
        for(int j=0;j<13;j++,p++){
            if(j==0){
                (*p).n=j;
                (*p).col=colors[i];
            }
            else if(j>=1){
            (*p).n=j;
            (*p).col=colors[i];
            p++;
            (*p).n=j;
            (*p).col=colors[i];
            }
        }
    }

    for(int i=1;i<3;i++){       // to add the wild cards to the deck
        for(int j=0;j<4;j++){
            (*p).n=i;
            (*p).col='w';
            p++;
        }
    }
}





void shuffel(struct cards *p){
    for(int i=0;i<108;i++){
        int num = (rand() %108);
        struct cards temp = p[i];
        p[i]=p[num];
        p[num]=temp;
    }
}

void players_cut(struct cards *p,struct cards *p1,struct cards *p2){
    for(int i=0;i<100;i++){
        p1[i].n=-1;
        p1[i].col='\0';
        p2[i].n=-1;
        p2[i].col='\0';
    }
    for(int i=0;i<7;i++,p=p+2){
        p1[i]=*p;
        p2[i]=*(p+1);
    }
}

void stacker(struct cards *p,struct cards *stk){
    for(int i=0;i<108;i++){
        stk[i].n=-1;
        stk[i].col='\0';
    }
    for(int i=14;i<108;i++,stk++){
        *stk=p[i];
    }
}

int inAction(struct cards *top_card,struct cards *player,struct cards **stk,int *count,int turn){
    if(turn%2==0) printf("player two\'s turn:\n",turn);     //player no.
    else if (turn%2!=0) printf("player one\'s turn:\n",turn);
    
    for (int i = 0; i < 100; i++){      //player's cards
        if(player[i].col!='\0') printf(" %d%c\t",player[i].n,player[i].col);
    }
    printf("\n----------------------------\n");
    printf("top card: %d%c\n",(*top_card).n,(*top_card).col);
    printf("----------------------------\n");


    if((*top_card).n==-1 && (*top_card).col=='\0'){     //enters when start of game
        struct cards curr_card;
        int flg=0;
        printf("all cards are playable\n");
        printf("what card would you like to play?");

        scanf("%d%c",&(curr_card.n),&(curr_card.col));
        for(int i=0;i<100;i++){
            if(curr_card.n==player[i].n && curr_card.col==player[i].col){
                player[i].n=-1;
                player[i].col='\0';
                flg=1;
            }
        }
        if(flg==1){
            (*top_card).n=curr_card.n;
            (*top_card).col=curr_card.col;
            (*count)--;
            printf("\nvalid\n");
            return flg;
        }
        else if (flg==0){
            printf("\ninvalid card!!!\n");
            return flg;
        }

    }
    else if ((*top_card).n==10)
    {
        printf("+2\n");
        buy(player,stk,2);
        (*count)=(*count)+2;
        (*top_card).n=-1;
        return 1;
    }
    else if ((*top_card).n==11 && (*top_card).col != '\0')
    {
        printf("rev\n");
        (*top_card).n=-1;
        return 1;
        // printf("---------------------------topcard no.: %d\n",(*top_card).n);
    }
    else if ((*top_card).n==12 && (*top_card).col != '\0')
    {
        printf("miss out\n");
        (*top_card).n=-1;
        return 1;
        // printf("---------------------------topcard no.: %d\n",(*top_card).n);
    }
    else if ((*top_card).n==1 && (*top_card).col=='w')
    {
        printf("any color\n");
        (*top_card).n=-1;
        (*top_card).col='\0';
        return 1;
        // struct cards curr_card;
        // int flg=0;
        
        // printf("u can play any card:");
        // // scanf("%d%c",&((top_card->n)),&((top_card->col)));
        // // printf("U played %d%c",(*top_card).n,(*top_card).col);
        // scanf("%d%c",&(curr_card.n),&(curr_card.col));


        // for(int i=0;i<100;i++){
        //     if(curr_card.n==player[i].n && curr_card.col==player[i].col){
        //         player[i].n=-1;
        //         player[i].col='\0';
        //         flg=1;
        //     }
        // }
        // if(flg==1){
        //     (*top_card).n=curr_card.n;
        //     (*top_card).col=curr_card.col;
        //     (*count)--;
        //     printf("\nvalid\n");
        // }
        // else if (flg==0){
        //     printf("invalid card!!!");
        //     inAction(top_card,player,stk,count,turn);
        // }
    }
    else if ((*top_card).n==2 && (*top_card).col=='w')
    {
        printf("+4\n");
        buy(player,stk,4);
        (*count)=(*count)+4;
        (*top_card).n=-1;
    }
    else{
        struct cards curr_card;
        int flg=0;
        int forced=1;

        printf("playable cards are:\n");
        for (int i = 0; i < 100; i++){
            if(player[i].n != -1 && (player[i].col=='w' || (*top_card).col == player[i].col || (*top_card).n == player[i].n)){
                printf("%d%c\t",player[i].n,player[i].col);
                forced=0;
            }
        }

        if(forced==0){
            printf("what card would you like to play?");
            // scanf("%d%c",&((top_card->n)),&((top_card->col)));
            // printf("U played %d%c",(*top_card).n,(*top_card).col);
            scanf("%d%c",&(curr_card.n),&(curr_card.col));



            for(int i=0;i<100;i++){
                if(curr_card.col=='w' && curr_card.n==player[i].n && curr_card.col==player[i].col){
                    player[i].n=-1;
                    player[i].col='\0';
                    flg=1;
                }


                else if(curr_card.n==player[i].n && curr_card.col==player[i].col && (curr_card.n==(*top_card).n || curr_card.col==(*top_card).col)){
                    player[i].n=-1;
                    player[i].col='\0';
                    flg=1;
                }
            }
            if(flg==1){
                (*top_card).n=curr_card.n;
                (*top_card).col=curr_card.col;
                (*count)--;
                printf("\n valid\n");
                return flg;
            }
            else if (flg==0){
                printf("\ninvalid card!!!\n");
                return flg;
            }
        }
        else if (forced==1)
        {
            if((**stk).n==(*top_card).n || (**stk).col==(*top_card).col){
                (*top_card).n=(**stk).n;
                (*top_card).col=(**stk).col;
                (*stk)++;
                printf("no other go:%d%c\n",(*top_card).n,(*top_card).col);
            }
            else{
                buy(player,stk,1);
            }
        }
        
        printf("end");
        
    }
    printf("end");
    
    
    
    
}


void buy(struct cards *player,struct cards **stk,int n){
    int n1=0;
    for(int i=0;i<100 && n1<n;i++){
        if(player[i].col=='\0'){
            player[i]=**stk;
            n1++;
            (**stk).n=0;
            (**stk).col='\0';
            (*stk)++;
        }
    }
}


// if((*top_card).col!='\0'){
//         printf("\nplayable cards are:\n");
//         for (int i = 0; i < count; i++){
//             if((*top_card).col == player[i].col || (*top_card).n == player[i].n) printf(" %d%c\t",player[i].n,player[i].col);
//         }
//     }
//     else printf("\nall cards are playable\n");

