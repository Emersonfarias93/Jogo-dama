#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Variáveis global.
int linha = 8;
int coluna = 8;
int vazio = 1;
int branco = 2;
int preto = 3;

int matriz[8][8]={
                    {0,2,0,2,0,2,0,2},
                    {2,0,2,0,2,0,2,0},
                    {0,2,0,2,0,2,0,2},
                    {1,0,1,0,1,0,1,0},
                    {0,1,0,1,0,1,0,1},
                    {3,0,3,0,3,0,3,0},
                    {0,3,0,3,0,3,0,3},
                    {3,0,3,0,3,0,3,0}
				 };
/*
** Função que traz os nome das peças.
*/
char nomePeca(int i)
{
    switch(i)
    {
  	    case 0:
  	        return ' ';
        case 1:
            return 'X';
        case 2:
            return 'B';
        case 3:
            return 'P';
    }
}
 
/*
**
**Função para imprimir o tabuleiro da dama atraves do laço de repetição.
*
*/
void imprimirTabuleiro(int matriz[linha][coluna])
{
	system("color B");
	
	//ll = linha 
	//cc = coluna
	
    int ll = 0, cc = 0;

   printf("   +----+----+----+----+----+----+----+----+\n");
    
	for ( ll= 0; ll < linha; ++ll)
    {
    printf(" %d \x7C", ll+1);

        for (cc = 0; cc < coluna; ++cc)
        {
            printf(" %c  \x7C",nomePeca(matriz[ll][cc]));
  	    }
      printf("\n");
      printf("   +----+----+----+----+----+----+----+----+\n");
    }
     printf("      1    2    3    4    5    6    7    8\n");
}
/*
**
**Função para substituição de peça.
**
*/
void trocaPeca(int matriz[linha][coluna], int i, int j, int k, int l)
{
    int temp;

    temp = matriz[i][j];

    matriz[i][j] = matriz[k][l];

    matriz[k][l] = temp;
}

/*
**
**Função para regra do jogo.
**
*/
int regrajogada(int matriz[linha][coluna], int jogador,int i_origem,int j_origem,int k_destino,int l_destino)
{
    int jmp_l;
    int jmp_c;

    if(i_origem < 0 && linha <= i_origem){
        printf("Linha de origem está fora dos limites\n");
        return -1;
    }
    
    if(j_origem < 0 && coluna <= j_origem){
        printf("Coluna de origem está fora dos limites\n");
        return -1;
    }

    if(k_destino < 0 && linha <= k_destino){
        printf("Linha de Destino está fora dos limites\n");
        return -1;

    }
    if(l_destino < 0 && coluna<= l_destino){
        printf("Coluna de destino está fora dos limites\n");
        return -1;
    }

    if(jogador == branco){
        if(matriz[i_origem][j_origem] == preto){
            printf("Mova sua própria peça!\n");
            return -1;
        }
    } else {
        if(matriz[i_origem][j_origem] == branco){
            printf("Mova sua própria peça!\n");
            return -1;
        }
    }

    if(matriz[k_destino][l_destino] != vazio){
        printf("Você deve mover para um local com X.\n");
        return -1;
    }
	//Valida a tentativa de volta as peça.
	//i_origem = linha de origem
	//k_destino = linha de destino	
    if(jogador == branco){
        if(i_origem >= k_destino){
            printf("Jogador Branco precisar mover para baixo\n");
            return -1;
        }
    } else {
        if(i_origem <= k_destino){
            printf("Jogador Preto precisar mover para cima\n");
            return -1;
        }
    }

    if(i_origem - k_destino == -1 || i_origem - k_destino == 1){
        if(j_origem - l_destino == 1 || j_origem - l_destino == -1){
            trocaPeca(matriz,i_origem,j_origem,k_destino,l_destino);
            return 0;
        }
    }
    	
	
    if(i_origem - k_destino == -2 || i_origem - k_destino == 2){
        if(j_origem - l_destino == -2 || j_origem - l_destino == 2){
           
		    if(i_origem < k_destino){
                jmp_l = i_origem + 1;
            } else {
                jmp_l = i_origem - 1;
            }
            if(j_origem < l_destino){
                jmp_c = j_origem + 1;
            } else {
                jmp_c = j_origem - 1;
            }
			
            if(jogador == branco && matriz[jmp_l][jmp_c]!= preto)
            {
                printf("O inimigo não é preto em %d %d",jmp_l, jmp_c);
                return -1;
            }
            if(jogador == preto && matriz[jmp_l][jmp_c] != branco){
                printf("você só pode pular sobre um jogador inimigo\n");
                return -1;
            }
			
            matriz[jmp_l][jmp_c] = 1;
            trocaPeca(matriz,i_origem,j_origem,k_destino,l_destino);
            return 0;
        }
    }

    printf("Você só pode se mover na diagonal.\n");
    return -1;

}

int main()
{
	setlocale(LC_ALL, "portuguese");
	
	//i_origem = linha de origem
	//k_destino = linha de destino	
	//j_origem = coluna de origem
	//l_destino = Coluna de destino
	
	int i_origem, k_destino;	
	int j_origem, l_destino; 
    
    while(1){
	
	    system("CLS");
	    
        imprimirTabuleiro(matriz);
        
       while(1){
            printf("Branco - Escolha a peça: \n");
            printf("Linha: ");
        	scanf("%d",&i_origem);
        	printf("Coluna: ");
            scanf("%d",&j_origem);
    	    printf("Para Linha: ");
    	    scanf("%d",&k_destino);
    	    printf("Para Coluna: ");
        	scanf("%d",&l_destino);
        	
        	if(regrajogada(matriz, branco, i_origem - 1, j_origem - 1 , k_destino - 1, l_destino - 1) == 0){
	        
			break;				
	        
			}else {
				
				printf("\nMovimento errado, tente novamente.\n"); 
			}
			
			break;

		};
		
		system("CLS");
        imprimirTabuleiro(matriz);
        
        while(1){       
            printf("Preto - Escolha a peça:\n");
            printf("Linha: ");
        	scanf("%d",&i_origem);
        	printf("Coluna: ");
            scanf("%d",&j_origem);
    	    printf("Para Linha: ");
    	    scanf("%d",&k_destino);
    	    printf("Para Coluna: ");
        	scanf("%d",&l_destino);
        	
        	if(regrajogada(matriz, preto, i_origem - 1, j_origem - 1, k_destino - 1, l_destino - 1) == 0){
	        
			break;				
	        
			}else {
				printf("\nMovimento errado, tente novamente.\n"); 
			}
		};
	};
	
return 0;	

}
