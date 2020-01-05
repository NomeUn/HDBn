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
                        last = 1;
                        P[i] = 1;
                        P[i-n] = 1;
                    }
                    else{
                        P[i] = 1;
                    }
                }
                else{
                    viol = -1;
                    if(last == -1){
                        N[i] = 1;
                    }
                    else{
                        last = -1;
                        N[i] = 1;
                        N[i-n] = 1;
                    }
                }
                nb = 0;
            }
            else{
            }
        }
        else{
            
            nb = 0;
            if(last == -1){
                P[i] = 1;
                last = 1;
            }
            else{
                N[i] = 1;
                last = -1;
            }
            
        }

    }
    

}

void decode(int x, int N[x], int P[x], int res[x], int n, int erreur[x]){
    int indice = x, viol, j;
    for (int i = x-1; i >= 0; i--){
        if(indice > i){
            if(N[i] == 0 && P[i] == 0){
                res[i] = 0;
            }
            else if(N[i] == 1 && P[i] == 1){
                erreur[i] = 1;
            }
            else if(N[i] == 1){
                if(i > 0 && N[i-1] == 1){
                    erreur[i] = 1;
                }
                else if (N[i] == 1 && i < n){
                    res[i] = 1;
                }
                else{
                    if (N[i-n] == 1){
                        viol = 1;
                        for (j = i-1; j > i-n && j >= 0 && viol == 1; j--){
                            if(P[j] == 1){
                                viol = 0;
                                res[i] = 1;
                            }
                            if(N[j] == 1){
                                erreur[j] = 1;
                            }
                        }
                        if(viol){
                            indice = j;
                        }
                    }
                    else if(N[i-n-1] == 1){
                        viol = 1;
                        for (j = i-1; j > i-n-1 && j >= 0 && viol == 1; j--){
                            if(P[j] == 1){
                                viol = 0;
                                res[i] = 1;
                            }
                            if(N[j] == 1){
                                erreur[j] = 1;
                            }
                            
                        }
                        if(viol){
                            indice = j+1;
                        }
                    }
                    else{
                        res[i] = 1;
                    }                 
                    
                }
                
                
            }
            else{
                if(i > 0 && P[i-1] == 1){
                    erreur[i] = 1;
                }
                else if (P[i] == 1 && i < n){
                    res[i] = 1;
                }
                else{
                    if (P[i-n] == 1){
                        viol = 1;
                        for (j = i-1; j > i-n && j >= 0 && viol == 1; j--){
                            if(N[j] == 1){
                                viol = 0;
                                res[i] = 1;
                            }
                            if(P[j] == 1){
                                erreur[j] = 1;
                            }
                        }
                        if(viol){
                            indice = j;
                        }
                    }
                    else if(P[i-n-1] == 1){
                        viol = 1;
                        for (j = i-1; j > i-n-1 && j >= 0 && viol == 1; j--){
                            if(N[j] == 1){
                                viol = 0;
                                res[i] = 1;
                            }
                            if(P[j] == 1){
                                erreur[j] = 1;
                            }
                        }
                        if(viol){
                            indice = j+1;
                        }
                    }
                    else{
                        res[i] = 1;
                    }
                    
                    
                }
                
                
            }
        }
        
    }
}


int main(){
    int x = 23;//taille signal
    int signal[] = {1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0}, N[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, P[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int n = 2;//HDBn
    printf("signal : ");
    for (int i = 0; i < x; i++){
        printf("%d", signal[i]);
    }
    hdbn(x, signal, N, P, n);
    printf("\n\nP : ");
    for (int i = 0; i < x; i++){
        printf("%d", P[i]);
    }
    printf("\nN : ");
    for (int i = 0; i < x; i++){
        printf("%d", N[i]);
    }
    printf("\n\n");
    int res[23], erreur[23];
    for (int i = 0; i < x; i++){
        res[i] = 0;
        erreur[i] = 0;
    }
    decode(x, N, P, res, n, erreur);

    printf("Resultat : ");
    for (int i = 0; i < x; i++){
        printf("%d", res[i]);
    }
    printf("\nErreur : ");
    for (int i = 0; i < x; i++){
        printf("%d", erreur[i]);
    }

}

