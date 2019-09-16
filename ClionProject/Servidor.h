#ifndef SERVIDOR_H
#define SERVIDOR_H

typedef struct servidor servidor_t;

servidor_t *servidor_inicializar(char *service);

void servidor_escuchar(servidor_t *self);

void servidor_destruir(servidor_t *self);

#endif //SERVIDOR_H
