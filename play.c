#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Movement
{
    int firstpile;
    int secondpile;
    int coins;
};

struct Movement my_strategy(int*, int, int, int);
int take_coins(int*, int, struct Movement, int*);
void get_rid_of_coins(int*, int*, int, int);
int max(int*,int);
void display(int*, int);
void print_the_action(int* ,int,int);
int check_whether_game_ends(int*, int);


int main()
{
    struct Movement init={-1,-1,-1},move;
    int n,*coin,turn,p,errorflag,which;
    int *coins_cpy;
    int pilenum[2],coinnum,i,tmp;
    int resid_1=1,resid_2=1,err=-1;
    char *tp,s[20];
    
    
    printf("Who do you play with?(1->cpu 2->your friend): ");
    scanf("%d",&which);
    if(!(which==1||which==2))
    {
        printf("Error!\n");
        return 0;
    }
    
    do
    {
        printf("How many piles?(1-9): ");
        scanf("%d",&n);
        if(n<1) printf("Enter a positive integer!\n");
        else if(n > 9) printf("Enter a single digit integer!\n");
        else break;
    }while(1);
    
    do{
        printf("1st or 2nd?(1->1st 2->2nd): ");
        scanf("%d",&turn);
        if(turn==1 || turn==2)
        {
            turn--;
            break;
        }
        printf("\nYou entered wrong string!\n");
    }while(1);
    
    coin = (int*)malloc(n*sizeof(int));
    coins_cpy = (int*)malloc(n*sizeof(int));
    
    srand(time(NULL));
    for(i=0;i<n;i++)
    {
        coin[i] = 4+rand()%7;
    }
    
    while(check_whether_game_ends(coin,n))
    {
        display(coin,n);
        if(turn==0)
        {
            do
            {
                p = 0;
                errorflag = 0;
                printf("-----Your turn-----\n");
                printf("Which pile?: ");
                scanf("%s",s);
                tp = strtok(s,",");
                while(tp != NULL)
                {
                    pilenum[p++] = atoi(tp)-1;
                    tp = strtok(NULL,",");
                }
                
                if(p>2 || p<0)
                {
                    printf("You entered wrong string!\n\n");
                    continue;
                }
                
                if(p==2)
                {
                    if(resid_1==0)
                    {
                        printf("You can't take the double move any more!\n\n");
                        continue;
                    }
                    if(pilenum[0] == pilenum[1])
                    {
                        printf("You entered the same piles!\n\n");
                        continue;
                    }
                    if(pilenum[0] > pilenum[1])
                    {
                        tmp = pilenum[0];
                        pilenum[0] = pilenum[1];
                        pilenum[1] = tmp;
                    }
                }
                
                for(i=0;i<p;i++)
                {
                    if(pilenum[i] < 0 || pilenum[i] >= n)
                    {
                        printf("The pile [%d] does not exist!\n\n",pilenum[i]+1);
                        errorflag = 1;
                        break;
                    }
                    
                    if(coin[pilenum[i]] == 0)
                    {
                        printf("The pile [%d] has already been empty!\n\n",pilenum[i]+1);
                        errorflag = 1;
                        break;
                    }
                }
                if(errorflag==1) continue;
                
                printf("How many coins?: ");
                scanf("%d",&coinnum);
                
                for(i=0;i<p;i++)
                {
                    if(coin[pilenum[i]] < coinnum || coinnum < 0)
                    {
                        printf("You entered wrong coin number!\n\n");
                        errorflag = 1;
                        break;
                    }
                }
                if(errorflag == 1) continue;
                
                break;
            }while(1);
            get_rid_of_coins(coin,pilenum,coinnum,p);
            if(p==2) resid_1--;
            printf("Your turn: ");
            print_the_action(pilenum,coinnum,p);
        }
        else
        {
            if(which==1)
            {
                printf("--------The cpu's turn----------\n");
                for(i=0;i<n;i++)
                {
                    coins_cpy[i] = coin[i];
                }
                move=init;
                move=my_strategy(coins_cpy,n,resid_2,resid_1);
                if(take_coins(coin,n,move,&resid_2))
                {
                    err=1;
                    break;
                }
                pilenum[0] = move.firstpile;
                pilenum[1] = move.secondpile;
                coinnum = move.coins;
                p = (pilenum[1] == -1 ? 1 : 2);
                printf("The cpu's turn: ");
                print_the_action(pilenum,coinnum,p);
            }
            else
            {
                do
                {
                    p = 0;
                    errorflag = 0;
                    printf("-----Your friend's turn-----\n");
                    printf("Which pile?: ");
                    scanf("%s",s);
                    tp = strtok(s,",");
                    while(tp != NULL)
                    {
                        pilenum[p++] = atoi(tp)-1;
                        tp = strtok(NULL,",");
                    }
                    
                    if(p>2 || p<0)
                    {
                        printf("You entered wrong string!\n\n");
                        continue;
                    }
                    
                    if(p==2)
                    {
                        if(resid_2==0)
                        {
                            printf("Your friend can't take the double move any more!\n\n");
                            continue;
                        }
                        if(pilenum[0] == pilenum[1])
                        {
                            printf("You entered the same piles!\n\n");
                            continue;
                        }
                        if(pilenum[0] > pilenum[1])
                        {
                            tmp = pilenum[0];
                            pilenum[0] = pilenum[1];
                            pilenum[1] = tmp;
                        }
                    }
                    
                    for(i=0;i<p;i++)
                    {
                        if(pilenum[i] < 0 || pilenum[i] >= n)
                        {
                            printf("The pile [%d] does not exist!\n\n",pilenum[i]+1);
                            errorflag = 1;
                            break;
                        }
                        
                        if(coin[pilenum[i]] == 0)
                        {
                            printf("The pile [%d] has already been empty!\n\n",pilenum[i]+1);
                            errorflag = 1;
                            break;
                        }
                    }
                    if(errorflag==1) continue;
                    
                    printf("How many coins?: ");
                    scanf("%d",&coinnum);
                    
                    for(i=0;i<p;i++)
                    {
                        if(coin[pilenum[i]] < coinnum || coinnum < 0)
                        {
                            printf("You entered wrong coin number!\n\n");
                            errorflag = 1;
                            break;
                        }
                    }
                    if(errorflag == 1) continue;
                    break;
                }while(1);
                get_rid_of_coins(coin,pilenum,coinnum,p);
                if(p==2) resid_2--;
                printf("Your opponent's turn: ");
                print_the_action(pilenum,coinnum,p);
            }
        }
        turn = (turn+1)%2;
    }
    
    display(coin,n);
    
    printf("\n----------------------------------------\n\n");
    
    if(err==1)
    {
        printf("The function you made should be debugged!\n");
        return 0;
    }
    if(max(coin,n)==1)
    {
        if(turn==1)
        {
            printf("You win!\n");
        }
        else
        {
            printf("You lose!\n");
        }
    }
    else
    {
        printf("You lose!\n");
    }
    free(coin);
    return 0;
}

void get_rid_of_coins(int* coin,int* pilenum,int coinnum,int p)
{
    int i;
    for(i=0;i<p;i++)
    {
        coin[pilenum[i]] -= coinnum;
    }
}

int max(int* arr,int arrlen)
{
    int i,num=arr[0];
    
    for(i=1;i<arrlen;i++)
    {
        if(num < arr[i]) num = arr[i];
    }
    return num;
}

void display(int* coin, int n)
{
    int i,j,k;
    
    for(i=0;i<n;i++)
    {
        k = coin[i];
        printf("[%d]:%2d ",i+1,k);
        for(j=0;j<k;j++)
        {
            printf("○");
        }
        printf("\n");
    }
    printf("\n");
}

void print_the_action(int *pilenum,int coinnum,int p)
{
    if(coinnum==1)
    {
        printf("1 coin ");
    }
    else
    {
        printf("%d coins ",coinnum);
    }
    if(p==1)
    {
        printf("on the pile [%d] ",pilenum[0]+1);
    }
    else
    {
        printf("on both pile [%d] and [%d] ",pilenum[0]+1,pilenum[1]+1);
    }
    if(coinnum == 1 && p==1)
    {
        printf("was removed.\n");
    }
    else
    {
        printf("were removed.\n");
    }
}

int check_whether_game_ends(int* coin,int n)
{
    int i,ones=0,zeros=0;
    
    for(i=0;i<n;i++)
    {
        if(coin[i]==0)
        {
            zeros++;
        }
        else if(coin[i]==1)
        {
            ones++;
        }
    }
    
    if(ones==1 && zeros==n-1)
    {
        return 0;
    }
    else if(zeros==n)
    {
        printf("You have mitaken!\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

int take_coins(int* arr, int n, struct Movement move, int* resid)
{
    if(move.firstpile<=-1||move.secondpile<-1||move.coins<1||move.firstpile==move.secondpile)
    {
        printf("The function take_coins incorrectly performed!\n");
        return 1;
    }
    
    if(move.secondpile==-1)
    {
        if(arr[move.firstpile] < move.coins)
        {
            printf("The function take_coins incorrectly performed!\n");
            return 1;
        }
        arr[move.firstpile] -= move.coins;
        return 0;
        
    }
    else
    {
        if(*resid==0||arr[move.firstpile]<move.coins||arr[move.secondpile]<move.coins)
        {
            printf("The function take_coins incorrectly performed!\n");
            return 1;
        }
        arr[move.firstpile]-=move.coins;
        arr[move.secondpile]-=move.coins;
        *resid -= 1;
        return 0;
    }
}
