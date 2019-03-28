#ifndef TP1LIB_H_INCLUDED
#define TP1LIB_H_INCLUDED

typedef struct {
int c;                  //número de colunas na imagem
int l;                  //número de linhas na imagem
unsigned char maximo;   //valor máximo para cada pixel
unsigned char **imagem; //variável para armazenar os pixels da imagem (matriz)
} PGM;

typedef struct C{
int l;                  // Linha de um ponto do caminho até a primeira célula de valor 0
int c;                  // Coluna de um ponto do caminho até a primeira célula de valor 0
struct C *proximo;      // Ponteiro para a próxima célula da pilha
} Celula;

typedef struct {
Celula *topo;           // Armazena somente a célula no topo da pilha
} Pilha;

/*---------------------------------------------------------------------------
Protótipo: PGM* CriaPGM (int l, int c, int maxim).
Função: Alocar um ponteiro do tipo PGM e seu elemento imagem segundo o numero
de linhas, numero de colunas e valor maximo de um pixel.
Entrada: Numero de linhas, numero de colunas, valor maximo do pixel.
Saída: Um ponteiro do tipo PGM e seu elemento imagem devidamente alocados.
-----------------------------------------------------------------------------*/
PGM* CriaPGM (int l, int c, int maxim);

/*---------------------------------------------------------------------------
Protótipo: PGM* LerPGM (char *entrada).
Função: Ler a imagem de um arquivo "*.pgm" e a retornar para um ponteiro de PGM.
Entrada: O nome do arquivo a ser lido.
Saída: A imagem do tipo pgm lida do arquivo.
-----------------------------------------------------------------------------*/
PGM* LerPGM (char *entrada);

/*---------------------------------------------------------------------------
Protótipo: PGM* DesalocaPGM (PGM *alocado).
Função: Desalocar um ponteiro do tipo PGM.
Entrada: Um ponteiro do tipo PGM que está alocado.
Saída: Um ponteiro do tipo PGM e seu elemento imagem devidamente desalocados e
apontando para NULL.
-----------------------------------------------------------------------------*/
PGM* DesalocaPGM (PGM *alocado);

/*---------------------------------------------------------------------------
Protótipo: Pilha* CriaPilha().
Função: Alocar uma pilha na memória.
Entrada: ().
Saída: Uma Pilha devidamente alocada.
-----------------------------------------------------------------------------*/
Pilha* CriaPilha();

/*---------------------------------------------------------------------------
Protótipo: Celula* Desempilha (Pilha *pilha)).
Função: Retira uma célula da pilha e a retorna.
Entrada: A pilha que será desempilhada.
Saída: A célula desempilhada.
-----------------------------------------------------------------------------*/
Celula* Desempilha (Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: Celula* Endocitose (int linha, int coluna).
Função: Inserir em uma celula o valor dos seus elementos l (linha) e c (coluna).
Entrada: Dois inteiros, um referente à linha e outra à coluna.
Saída: Um tipo célula alocado e com os valores de seus elementos atribuídos.
-----------------------------------------------------------------------------*/
Celula* Endocitose (int linha, int coluna);

/*---------------------------------------------------------------------------
Protótipo: int PVazia (Pilha *pilha).
Função: Verificar se uma pilha está vazia.
Entrada: Uma pilha a ser testada.
Saída: TRUE (1) para quando a pilha estiver vazia e FALSE (0) para quando a pi-
lha estiver cheia (não estiver vazia).
-----------------------------------------------------------------------------*/
int PVazia (Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: int CaminhoValido (int l, int c, Pilha *pilha, PGM *img).
Função: Verificar se a tentativa de analisar o valor de um pixel pode ser fei-
ta, de acordo com a linha e a coluna que estão sendo acessadas e se aquela po-
sição já não foi acessada anteriormente.
Entrada: Dois inteiros (a linha e a coluna que se está tentando analisar), a 
pilha e a imagem.
Saída: TRUE (1) para um caminho que pode ser analisado e FALSE (0) para um ca-
minho que não pode ser analisado.
-----------------------------------------------------------------------------*/
int CaminhoValido (int l, int c, Pilha *pilha, PGM *img);

/*---------------------------------------------------------------------------
Protótipo: void FPVazia (Pilha *pilha).
Função: Faz uma pilha recebida ficar vazia.
Entrada: Uma pilha qualquer.
Saída: ().
-----------------------------------------------------------------------------*/
void FPVazia (Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: void Empilha (Celula *celula, Pilha *pilha).
Função: Empilha na pilha de celulas uma célula
Entrada: Uma celula que vai ser empilhada e a pilha.
Saída: ().
-----------------------------------------------------------------------------*/
void Empilha (Celula *celula, Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: void DestroiPilhaCheia (Pilha *pilha).
Função: Desaloca uma pilha e todas as suas celulas.
Entrada: Uma pilha qualquer.
Saída: ().
-----------------------------------------------------------------------------*/
void DestroiPilhaCheia (Pilha* cheia);

/*---------------------------------------------------------------------------
Protótipo: void IniciaCaminho (Pilha *pilha).
Função: Se a busca começar na origem, essa função define o inicio da busca as
coordenadas (0,0).
Entrada: A pilha com o caminho até o pixel 0.
Saída: ().
-----------------------------------------------------------------------------*/
void IniciaCaminho (Pilha *pilha, int l, int c);

/*---------------------------------------------------------------------------
Protótipo: void ImprimeCaminho (Pilha *pilha).
Função: Imprimir o caminho até o pixel 0, partindo da origem.
Entrada: A pilha com o caminho que será impresso.
Saída: ().
-----------------------------------------------------------------------------*/
void ImprimeCaminho (Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: void ImprimeCelula (Celula *celula).
Função: Imprime uma célula.
Entrada: Uma célula.
Saída: ().
-----------------------------------------------------------------------------*/
void ImprimeCelula (Celula *celula);

/*---------------------------------------------------------------------------
Protótipo: void Busca (PGM *img, Pilha *pilha).
Função: Busca em uma imagem do formato PGM o pixel de valor 0 passando pelo ca-
minho com os píxeis de menor valor.
Entrada: A imagem que está sendo usada na busca e a pilha para empilhar o cami-
nho até o 0.
Saída: ().
-----------------------------------------------------------------------------*/
void Busca (PGM *img, Pilha *pilha);

/*---------------------------------------------------------------------------
Protótipo: void Imprimesemdesmpilhar (Pilha *pilha).
Função: Imprime uma pilha sem retirar dela suas células.
Entrada: A pilha que se deseja imprimir.
Saída: ().
-----------------------------------------------------------------------------*/
void Imprimesemdesmpilhar (Pilha *pilha);

#endif // TP1LIB_H_INCLUDED
