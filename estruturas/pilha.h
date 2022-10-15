#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
} Pilha_##tipo; \
\
Pilha_##tipo nova_pilha_##tipo();\
void pilha_free_##tipo(Pilha_##tipo *pilha);\
void pilha_push_##tipo(Pilha_##tipo *pilha, tipo x);\
tipo *pilha_pop_##tipo(Pilha_##tipo *pilha);\
tipo *pilha_peek_##tipo(Pilha_##tipo *pilha);


#define GEN_PILHA(tipo) \
Pilha_##tipo nova_pilha_##tipo() { \
	Pilha_##tipo p = { \
		.tam = 0, \
		.cap = 8, \
	}; \
	tipo *buf = malloc(p.cap * sizeof(tipo)); \
	if (buf == NULL) { \
		puts("Alocação de buf da pilha de #tipo falhou."); \
		exit(1); \
	} \
	p.buf = buf; \
	return p; \
} \
 \
void pilha_free_##tipo(Pilha_##tipo *pilha) { \
	free(pilha->buf); \
} \
\
void pilha_push_##tipo(Pilha_##tipo *pilha, tipo x) { \
	 if (pilha->cap <= pilha->tam) { \
		pilha->buf = realloc(pilha->buf, pilha->cap * 2 * sizeof(tipo)); \
	} \
	pilha->buf[pilha->tam++] = x; \
} \
\
tipo *pilha_pop_##tipo(Pilha_##tipo *pilha) { \
	if (pilha->tam == 0) { \
		return NULL;\
	} \
	if (pilha->cap > 8 && pilha->tam - 1 <= pilha->cap) { \
		tipo *novo_buf = realloc(pilha->buf, (pilha->cap / 2) * sizeof(tipo));\
		if (novo_buf != NULL) pilha->buf = novo_buf; \
	} \
	return &pilha->buf[--pilha->tam]; \
} \
\
tipo *pilha_peek_##tipo(Pilha_##tipo *pilha) {\
	if (pilha->tam == 0) {\
		return NULL;\
	}\
	return &pilha->buf[pilha->tam - 1];\
}
#endif
