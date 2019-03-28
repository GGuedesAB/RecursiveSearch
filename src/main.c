#include <stdio.h>
#include <stdlib.h>
#include "tp1lib.h"

int main(int argc, char* argv[])
{
	PGM *minha_img = LerPGM(argv[1]);

	Pilha* caminho = CriaPilha();
	FPVazia(caminho);
	IniciaCaminho(caminho, 0, 0);

	Busca (minha_img, caminho);
	
	printf("O caminho ate o pixel 0 passando pelos menores pixeis:\n");
	ImprimeCaminho(caminho);
	printf("\n");
	free (caminho);
	DesalocaPGM (minha_img);
	return 0;
}
