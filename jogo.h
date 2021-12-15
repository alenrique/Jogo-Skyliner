#define LINHA 5
#define COLUNA 5

typedef struct jogador Jogador;

typedef struct matriz Matriz;

Jogador* criar_jogador(int);

int qtd_peca(Jogador *, int);

Matriz *criar_tabuleiro();

int imprimir_tabuleiro(Matriz *);

int inserir_peca(Matriz *,int, int, int);

int distribuir(Matriz *);

int linha_tabuleiro(char);

int coluna_tabuleiro(char);

int validar_jogada(Jogador *, Matriz *, int);

int pontos(Jogador *, Matriz *, int);
