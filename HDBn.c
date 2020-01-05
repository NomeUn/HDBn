#include <stdio.h>
#include <stdlib.h>

void hdbn(int x, int signal[x], int N[x], int P[x], int n){
    int viol = -1, last = -1, nb = 0;
    for (int i = 0; i < x; i++){
        if(signal[i] == 0){
            nb ++;
            if(nb > n){
                if(viol == -1){
                    viol = 1;
                    if(last == -1){
                        printf("viol P 101\n");
                        last = 1;
                        P[i] = 1;
                        P[i-n] = 1;
                    }
                    else{
                        printf("viol P 001\n");
                        P[i] = 1;
                    }
                }
                else{
                    viol = -1;
                    if(last == -1){
                        printf("viol N 001\n");
                        N[i] = 1;
                    }
                    else{
                        printf("viol N 101\n");
                        last = -1;
                        N[i] = 1;
                        N[i-n] = 1;
                    }
                }
                nb = 0;
            }
            else{
                printf("0\n");
            }
        }
        else{
            
            nb = 0;
            if(last == -1){
                P[i] = 1;
                last = 1;
                printf("P1\n");
            }
            else{
                N[i] = 1;
                last = -1;
                printf("N1\n");
            }
            
        }

    }
    

}

void decode(int x, int N[x], int P[x], int res[x], int n, int erreur[x]){
    for (int i = 0; i < x; i++){
        if(N[i] == 0 && P[i] == 0){
            res[i] = 0;
        }
        else if(N[i] == 1 && P[i] == 1){
            erreur[i] = 1;
        }
        
    }
    
}


int main(){
    int x = 23;//taille signal
    int signal[] = {1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0}, N[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, P[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int n = 2;//HDBn
    hdbn(x, signal, N, P, n);
    for (int i = 0; i < x; i++){
        printf("%d",P[i]);
    }
    printf("\n");
    for (int i = 0; i < x; i++){
        printf("%d",N[i]);
    }
    printf("\n");

}

