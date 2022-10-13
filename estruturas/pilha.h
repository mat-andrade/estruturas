#include <stdbool.h>
#include <stdlib.h>

/**
 * Declara uma pilha de tipo.
 * tam, cap e buf não devem ser alterados.
 * deve_liberar_conteudo indica se a função pilha_free deve liberar os elementos de buf.
 *     Se true, free_conteudo é chamado para cada elemento da pilha e não pode ser NULL.7
 * 
 * Uso: chame o macro DECL_PILHA(tipo) com o tipo desejado (contendo apenas caracteres alfanuméricos)
 * para declarar o tipo e depois chame o macro GEN_PILHA(tipo) para gerar a implementação.
 */
#define DECL_PILHA(tipo) \
typedef struct pilha_##tipo { \
	int tam, cap; \
	tipo *buf;\
	bool deve_liberar_conteudo; \
	void (*free_conteudo)(tipo);\
} Pilha_##tipo; \
\
Pilha_##tipo nova_pilha_##tipo(bool deve_liberar_conteudo, void (*free_conteudo)(tipo));\
void pilha_free_##tipo(Pilha_##tipo *pilha);\
void pilha_push_##tipo(Pilha_##tipo *pilha, tipo x);\
tipo pilha_pop_##tipo(Pilha_##tipo *pilha);\
tipo pilha_peek_##tipo(Pilha_##tipo *pilha);
