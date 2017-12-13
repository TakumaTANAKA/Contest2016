#include <stdio.h>
#include <stdlib.h>

struct Movement
{
    int firstpile;
    int secondpile;
    int coins;
};

struct Movement my_strategy(int *arr, int n, int my_resid, int opp_resid)
{
    int x;
    int fp, sp, c;
    int i, num, num_cpy;
    int dig, dig2;
    int dig_cpy, dig2_cpy;
    int pile[n][2];
    int base;
    char flag;
    char *vict;
    struct Movement move = {-1, -1, -1};
    
    for(fp = 0; fp < n; fp++)
    {
        pile[fp][0] = fp;
        pile[fp][1] = arr[fp];
    }
    
    for(fp = 0; fp < n-1; fp++)
    {
        for(sp = 1; sp < n - fp; sp++)
        {
            if(pile[sp][1] > pile[sp-1][1])
            {
                x = pile[sp][0];
                pile[sp][0] = pile[sp-1][0];
                pile[sp-1][0] = x;
                
                x = pile[sp][1];
                pile[sp][1] = pile[sp-1][1];
                pile[sp-1][1] = x;
            }
        }
    }
    
    base = pile[0][1] + 1;
    
    for(fp = 0, dig = 1, num = 0; fp < n; fp++, dig *= base)
    {
        num += pile[fp][1] * dig;
    }
    
    vict = (char*)malloc(num);
    
    if(my_resid == 0 && opp_resid == 0)
    {
        vict[0] = 1;
        
        for(i = 1; i < num; i++)
        {
            flag = 0;
            
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                if(i / dig % base > pile[fp][1])
                {
                    x = i / base / dig % base + 1;
                    i = i / base / dig + 1;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                if(i / dig % base < i / base / dig % base)
                {
                    x = i / base / dig % base;
                    i = i / base / dig;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            vict[i] = 0;
            
            for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
            {
                num_cpy = i;
                dig_cpy = dig;
                
                for(c = 1; c <= i / dig % base; c++)
                {
                    while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                    {
                        dig_cpy *= base;
                    }
                    num_cpy -= dig_cpy;
                    
                    if(vict[num_cpy] == 0)
                    {
                        vict[i] = 1;
                        flag = 1;
                        break;
                    }
                }
                
                if(flag) break;
            }
        }
        
        flag = 0;
        
        for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
        {
            num_cpy = num;
            dig_cpy = dig;
            
            for(c = 1; c <= pile[fp][1]; c++)
            {
                while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                {
                    dig_cpy *= base;
                }
                num_cpy -= dig_cpy;
                
                if(vict[num_cpy] == 0)
                {
                    flag = 1;
                    break;
                }
            }
            
            if(flag) break;
        }
        
        if(flag)
        {
            move.firstpile = pile[fp][0];
            move.coins = c;
        }
        else
        {
            srand(num);
            for(c = 0; c < base; c++) rand();
            move.firstpile = pile[0][0];
            move.coins = rand() % pile[0][1] / 2 + 1;
        }
    }
    else if(my_resid == 0 && opp_resid == 1)
    {
        flag = 0;
        
        for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
        {
            num_cpy = num;
            dig_cpy = dig;
            
            for(c = 1; c <= pile[fp][1]; c++)
            {
                while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                {
                    dig_cpy *= base;
                }
                num_cpy -= dig_cpy;
                
                if(num_cpy == 1 || num_cpy == 2 * base + 2)
                {
                    flag = 1;
                    break;
                }
            }
            
            if(flag) break;
        }
        
        if(flag)
        {
            move.firstpile = pile[fp][0];
            move.coins = c;
        }
        else
        {
            srand(num);
            for(c = 0; c < base; c++) rand();
            move.firstpile = pile[0][0];
            move.coins = rand() % pile[0][1] / 2 + 1;
        }
    }
    else if(my_resid == 1 && opp_resid == 0)
    {
        vict[0] = 2;
        
        for(i = 1; i < num; i++)
        {
            flag = 0;
            
            for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
            {
                if(i / dig % base > pile[fp][1])
                {
                    x = i / base / dig % base + 1;
                    i = i / base / dig + 1;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                if(i / dig % base < i / base / dig % base)
                {
                    x = i / base / dig % base;
                    i = i / base / dig;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            vict[i] = 0;
            
            for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
            {
                num_cpy = i;
                dig_cpy = dig;
                
                for(c = 1; c <= i / dig % base; c++)
                {
                    while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                    {
                        dig_cpy *= base;
                    }
                    num_cpy -= dig_cpy;
                    
                    if(vict[num_cpy] == 0)
                    {
                        vict[i] = 1;
                        flag = 1;
                        break;
                    }
                }
                
                if(flag) break;
            }
            
            if(vict[i] == 1)
            {
                flag = 0;
                
                for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
                {
                    num_cpy = i;
                    dig_cpy = dig;
                    
                    for(c = 1; c <= i / dig % base; c++)
                    {
                        while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                        {
                            dig_cpy *= base;
                        }
                        num_cpy -= dig_cpy;
                        
                        if(num_cpy == 1 || num_cpy == 2 * base + 2)
                        {
                            vict[i] = 2;
                            flag = 1;
                            break;
                        }
                    }
                    
                    if(flag) break;
                }
            }
        }
        
        flag = 0;
        
        for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
        {
            num_cpy = num;
            dig_cpy = dig;
            
            for(c = 1; c <= pile[fp][1]; c++)
            {
                while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                {
                    dig_cpy *= base;
                }
                num_cpy -= dig_cpy;
                
                if(vict[num_cpy] != 2)
                {
                    flag = 1;
                    break;
                }
            }
            
            if(flag)
            {
                move.firstpile = pile[fp][0];
                move.coins = c;
                break;
            }
        }
        if(!flag)
        {
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                for(sp = fp + 1, dig2 = dig * base; sp < n; sp++, dig2 *= base)
                {
                    num_cpy = num;
                    dig_cpy = dig;
                    dig2_cpy = dig2;
                    
                    for(c = 1; c <= pile[sp][1]; c++)
                    {
                        while((num_cpy - num_cpy / base) / dig2_cpy % base == 0)
                        {
                            dig2_cpy *= base;
                        }
                        while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                        {
                            if(dig2_cpy != dig_cpy * base) dig_cpy *= base;
                            else break;
                        }
                        num_cpy -= dig_cpy + dig2_cpy;
                        
                        if(vict[num_cpy] == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    
                    if(flag) break;
                }
                
                if(flag) break;
            }
            
            if(flag)
            {
                move.firstpile = pile[fp][0];
                move.secondpile = pile[sp][0];
                move.coins = c;
            }
            else
            {
                srand(num);
                for(c = 0; c < base; c++) rand();
                move.firstpile = pile[0][0];
                move.coins = rand() % pile[0][1] / 2 + 1;
            }
        }
    }
    else
    {
        vict[0] = 1;
        
        for(i = 1; i < num; i++)
        {
            flag = 0;
            
            for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
            {
                if(i / dig % base > pile[fp][1])
                {
                    x = i / base / dig % base + 1;
                    i = i / base / dig + 1;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                if(i / dig % base < i / base / dig % base)
                {
                    x = i / base / dig % base;
                    i = i / base / dig;
                    for(sp = 0; sp < fp + 1; sp++)
                    {
                        i = i * base + x;
                    }
                    i--;
                    flag = 1;
                    break;
                }
            }
            
            if(flag) continue;
            
            vict[i] = 0;
            
            for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
            {
                num_cpy = i;
                dig_cpy = dig;
                
                for(c = 1; c <= i / dig % base; c++)
                {
                    while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                    {
                        dig_cpy *= base;
                    }
                    num_cpy -= dig_cpy;
                    
                    if(vict[num_cpy] == 0)
                    {
                        vict[i] = 1;
                        flag = 1;
                        break;
                    }
                }
                
                if(flag) break;
            }
            
            if(!flag)
            {
                for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
                {
                    for(sp = fp + 1, dig2 = dig * base; sp < n; sp++, dig2 *= base)
                    {
                        num_cpy = i;
                        dig_cpy = dig;
                        dig2_cpy = dig2;
                        
                        for(c = 1; c <= i / dig2 % base; c++)
                        {
                            while((num_cpy - num_cpy / base) / dig2_cpy % base == 0)
                            {
                                dig2_cpy *= base;
                            }
                            while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                            {
                                if(dig2_cpy != dig_cpy * base) dig_cpy *= base;
                                else break;
                            }
                            num_cpy -= dig_cpy + dig2_cpy;
                            
                            if(num_cpy == 1 || num_cpy == 2 * base + 2)
                            {
                                vict[i] = 1;
                                flag = 1;
                                break;
                            }
                        }
                        
                        if(flag) break;
                    }
                    
                    if(flag) break;
                }
            }
        }
        
        flag = 0;
        
        for(fp = 0, dig = 1; fp < n; fp++, dig *= base)
        {
            num_cpy = num;
            dig_cpy = dig;
            
            for(c = 1; c <= pile[fp][1]; c++)
            {
                while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                {
                    dig_cpy *= base;
                }
                num_cpy -= dig_cpy;
                
                if(vict[num_cpy] == 0)
                {
                    flag = 1;
                    break;
                }
            }
            
            if(flag)
            {
                move.firstpile = pile[fp][0];
                move.coins = c;
                break;
            }
        }
        if(!flag)
        {
            for(fp = 0, dig = 1; fp < n-1; fp++, dig *= base)
            {
                for(sp = fp + 1, dig2 = dig * base; sp < n; sp++, dig2 *= base)
                {
                    num_cpy = num;
                    dig_cpy = dig;
                    dig2_cpy = dig2;
                    
                    for(c = 1; c <= pile[sp][1]; c++)
                    {
                        while((num_cpy - num_cpy / base) / dig2_cpy % base == 0)
                        {
                            dig2_cpy *= base;
                        }
                        while((num_cpy - num_cpy / base) / dig_cpy % base == 0)
                        {
                            if(dig2_cpy != dig_cpy * base) dig_cpy *= base;
                            else break;
                        }
                        num_cpy -= dig_cpy + dig2_cpy;
                        
                        if(num_cpy == 1 || num_cpy == 2 * base + 2)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    
                    if(flag) break;
                }
                
                if(flag) break;
            }
            
            if(flag)
            {
                move.firstpile = pile[fp][0];
                move.secondpile = pile[sp][0];
                move.coins = c;
            }
            else
            {
                srand(num);
                for(c = 0; c < base; c++) rand();
                move.firstpile = pile[0][0];
                move.coins = rand() % pile[0][1] / 2 + 1;
            }
        }
    }
    
    free(vict);
    
    return move;
}
