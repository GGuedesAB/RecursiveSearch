#include "tp1lib.h"
#include <stdlib.h>
#include <stdio.h>

PGM* CriaPGM (int l, int c, int maximo)
{
    int i;
    PGM* novo_PGM = (PGM*)malloc(sizeof(PGM));
    if (NULL == novo_PGM)
    {
        fprintf(stderr, "\nErro, nao foi possivel alocar memoria para o programa.\n");
        exit(1);
    }
    novo_PGM->l = l;
    novo_PGM->c = c;
    novo_PGM->maximo = maximo;
    novo_PGM->imagem = (unsigned char**)malloc(l*sizeof(unsigned char*));
    if (NULL == novo_PGM->imagem)
    {
        fprintf(stderr, "\nErro, nao foi possivel alocar memoria para o programa.\n");
        exit(1);
    }
    for (i=0;i<l;i++)
    {
        novo_PGM->imagem[i] = (unsigned char*)malloc(c*sizeof(unsigned char));
        if (NULL == novo_PGM->imagem[i])
        {
            fprintf(stderr, "\nErro, nao foi possivel alocar memoria para o programa.\n");
            exit(1);
        }
    }
    return novo_PGM;
}

PGM* LerPGM(char *entrada)
{
    int i, j;
    char img_format[3];
    FILE *img_original = fopen(entrada, "r");
    if (NULL == img_original)
    {
        printf("\nO arquivo nao foi encontrado no diretorio, nao pode ser lido ou nao existe.\n");
        exit(1);
    }
    fscanf(img_original, "%s", img_format);
    int linha = 0;
    int coluna = 0;
    unsigned char max = 0;
    fscanf(img_original,"%d %d %hhu", &coluna, &linha, &max);
    PGM* img_retornada = CriaPGM(linha, coluna, max);
    for (i=0; i<img_retornada->l; i++)
    {
        for (j=0; j<img_retornada->c; j++)
        {
            fscanf(img_original, "%hhu", &img_retornada->imagem[i][j]);
        }
    }
    fclose(img_original);
    return img_retornada;
}

PGM* DesalocaPGM(PGM *alocado)
{
    int i;
    for (i=0;i<alocado->c;i++)
    {
        free(alocado->imagem[i]);
    }
    free(alocado->imagem);
    free(alocado);
    alocado = NULL;
    return alocado;
}

Celula* CriaCelula ()
{
	Celula *celula = (Celula*)malloc(sizeof(Celula));
	if (NULL == celula)
	{
		printf("Nao foi possivel alocar memoria para o programa.\n");
		exit (1);
	}
	celula->l = 0;
	celula->c = 0;
	return celula;
}

Pilha* CriaPilha()
{
	Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
	if (NULL == pilha)
	{
		printf("Nao foi possivel alocar memoria para o programa.\n");
		exit (1);
	}
	return pilha;
}

void FPVazia (Pilha *pilha)
{
	pilha->topo = NULL;
}

int PVazia (Pilha *pilha)
{
	if (NULL == pilha->topo) return 1;
	else return 0;
}

void Empilha (Celula *celula, Pilha *pilha)
{
	celula->proximo = pilha->topo;
	pilha->topo = celula;
}

Celula* Desempilha (Pilha *pilha)
{
	if (PVazia(pilha))
	{
		printf("A pilha esta vazia.\n");
		exit(1);
	}
	Celula* aux = pilha->topo;
	pilha->topo = pilha->topo->proximo;
	return aux;
}

Celula* Endocitose (int linha, int coluna)
{
	Celula* celula = CriaCelula();
	celula->l = linha;
	celula->c = coluna;
	return celula;
}

void ImprimeCelula (Celula* celula)
{
	printf("(%d, %d), ", celula->l, celula->c);
}

void ImprimeCaminho (Pilha *pilha)
{
	Pilha *inversao = CriaPilha();
	FPVazia(inversao);
	while (!PVazia(pilha))
	{
		Empilha(Desempilha(pilha), inversao);
	}
	Celula *desempilhada = NULL;
	while (!PVazia(inversao))
	{
		desempilhada = Desempilha(inversao);
		ImprimeCelula(desempilhada);
		free (desempilhada);
	}
	free(inversao);
}

void DestroiPilhaCheia (Pilha* cheia)
{
	Celula *destruidora;
	while(!PVazia(cheia))
	{
		destruidora = Desempilha(cheia);
		free (destruidora);
	}
	FPVazia(cheia);//Agora vazia
}

void IniciaCaminho (Pilha* pilha, int l, int c)
{
	Celula *celula = Endocitose(l, c);
	Empilha(celula, pilha);
}

int CaminhoValido (int l, int c, Pilha *pilha, PGM *img)
{
	//Se a posição não tiver sido visitada ainda, nem estiver fora do espaço de memoria da imgem, o caminho é valido.
	Celula *busca = pilha->topo;
	if (l < 0 || l > img->l-1 || c < 0 || c > img->c-1)
	{
		return 0;
	}
	while(busca)
	{
		if (busca->l == l && busca->c == c)
		{
			return 0;
		}
		busca = busca->proximo;
	}
	return 1;
}

void Imprimesemdesempilhar (Pilha *pilha)
{
	Celula *c;
	c = pilha->topo;
	while(!PVazia(pilha))
	{
		if (c==NULL) 
		{
			printf("(NULL)-||\n");
			return;
		}

		printf("||-(%d | %d) ", c->l, c->c);
		c = c->proximo;
	}
}

void Busca (PGM *img, Pilha *pilha)
{
	Celula *celula_menor_val;
	Pilha *caminho_possivel;
	int min_pixel = 256;
	int l, c;
	
	//Se o pixel for 0
	if (0 == img->imagem[pilha->topo->l][pilha->topo->c])
	{
		return;
	}	
	else
	{
		if (CaminhoValido(pilha->topo->l, pilha->topo->c+1, pilha, img))
		{
			if (img->imagem[pilha->topo->l][pilha->topo->c+1] < min_pixel)
			{
				min_pixel = img->imagem[pilha->topo->l][pilha->topo->c+1];
				l = pilha->topo->l;
				c = pilha->topo->c+1;
			}
		}
		if (CaminhoValido(pilha->topo->l+1, pilha->topo->c, pilha, img))
		{
			if (img->imagem[pilha->topo->l+1][pilha->topo->c] < min_pixel)
			{
				min_pixel = img->imagem[pilha->topo->l+1][pilha->topo->c];
				l = pilha->topo->l+1;
				c = pilha->topo->c;
			}
		}
		if (CaminhoValido(pilha->topo->l, pilha->topo->c-1, pilha, img))
		{
			if (img->imagem[pilha->topo->l][pilha->topo->c-1] < min_pixel)
			{
				min_pixel = img->imagem[pilha->topo->l][pilha->topo->c-1];
				l = pilha->topo->l;
				c = pilha->topo->c-1;
			}
		}
		if (CaminhoValido(pilha->topo->l-1, pilha->topo->c, pilha, img))
		{
			if (img->imagem[pilha->topo->l-1][pilha->topo->c] < min_pixel)
			{
				min_pixel = img->imagem[pilha->topo->l-1][pilha->topo->c];
				l = pilha->topo->l-1;
				c = pilha->topo->c;
			}
		}
		celula_menor_val = Endocitose(l, c);
		Empilha(celula_menor_val, pilha);
		Busca(img, pilha);
	}
}