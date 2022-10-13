#include "pilha.h"

#include <stdlib.h>
#include <stdio.h>

#define GEN_PILHA(tipo) \
Pilha_##tipo nova_pilha_##tipo(bool deve_liberar_conteudo, void (*free_conteudo)(tipo)) { \
	Pilha_##tipo p = { \
		.tam = 0, \
		.cap = 8, \
		.deve_liberar_conteudo = deve_liberar_conteudo, \
		.free_conteudo = free_conteudo \
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
void pilha_free_pilha_##tipo(Pilha_##tipo *pilha) { \
	if (pilha->deve_liberar_conteudo) { \
		for (int i = 0; i < pilha->tam; i++) { \
		    if (pilha->free_conteudo == NULL) { \
				fprintf(stderr, "Impossível liberar os elementos da pilha no endereco %p de tipo #tipo pois free_conteudo == NULL.\n", pilha); \
				break; \
			}\
			pilha->free_conteudo(pilha->buf[i]); \
		} \
	} \
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
tipo pilha_pop_##tipo(Pilha_##tipo *pilha) { \
	if (pilha->tam == 0) { \
		printf("Erro. pop_#tipo foi chamado na pilha %p, mas ela está vazia.\n", pilha); \
		exit(1); \
	} \
	if (pilha->cap > 8 && pilha->tam - 1 <= pilha->cap) { \
		tipo *novo_buf = realloc(pilha->buf, (pilha->cap / 2) * sizeof(tipo));\
		if (novo_buf != NULL) pilha->buf = novo_buf; \
	} \
	return pilha->buf[--pilha->tam]; \
} 
