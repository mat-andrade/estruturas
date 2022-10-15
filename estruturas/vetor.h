
#ifndef VETOR_H
#define VETOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DECL_VETOR(tipo)\
typedef struct vetor_##tipo {\
	int tam, cap;\
	tipo *buf;\
} Vetor_##tipo;\
\
Vetor_##tipo novo_vetor_##tipo();\
void vetor_free_##tipo(Vetor_##tipo *vetor);\
bool vetor_append_##tipo(Vetor_##tipo *vetor, tipo x);\
bool vetor_insert_##tipo(Vetor_##tipo *vetor, tipo x, int i);\
bool vetor_set_cap_##tipo(Vetor_##tipo *vetor, int cap);


#define GEN_VETOR(tipo) \
Vetor_##tipo novo_vetor_##tipo() {\
	tipo *buf = malloc(8 * sizeof(tipo));\
	if (buf == NULL) {\
		puts("Alocação de novo vetor de tipo #tipo falhou.");\
		exit(1);\
	}\
	Vetor_##tipo v = {\
		.tam = 0, .cap = 8, .buf = buf};\
	return v;\
}\
\
void vetor_free_##tipo(Vetor_##tipo *vetor) {\
	free(vetor->buf);\
}\
\
bool vetor_set_cap_##tipo(Vetor_##tipo *vetor, int cap) {\
	tipo *novo_buf = realloc(vetor->buf, cap * sizeof(tipo));\
	if (novo_buf != NULL) {\
		vetor->cap = cap;\
		vetor->buf = novo_buf;\
		return true;\
	} else {\
		return false;\
	}\
}\
\
bool vetor_append_##tipo(Vetor_##tipo *vetor, tipo x) {\
	if (vetor->tam == vetor->cap) {\
		bool mudou = vetor_set_cap_##tipo(vetor, vetor->cap * 2);\
		if (!mudou) return false;\
	}\
	vetor->buf[vetor->tam++] = x;\
	return true;\
}\
\
bool vetor_insert_##tipo(Vetor_##tipo *vetor, tipo x, int i) {\
	if (vetor->tam == vetor->cap) {\
		bool mudou = vetor_set_cap_##tipo(vetor, vetor->cap * 2);\
		if (!mudou) return false;\
	}\
	for (int j = vetor->tam; j > i; j++) {\
		vetor->buf[j] = vetor->buf[j - 1];\
	}\
	vetor->buf[i] = x;\
	return true;\
}

#endif
