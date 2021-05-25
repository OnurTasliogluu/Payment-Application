#ifndef OT_EPOLL_H
#define OT_EPOLL_H

#include <sys/epoll.h>
#include <stdint.h>

typedef struct epoll_event epoll_event_t;

typedef struct 
{
    int32_t epoll_poll_fd;
    epoll_event_t events[75000];
} ot_epoll_t;

ot_epoll_t *ot_epoll_create();
void ot_epoll_init(ot_epoll_t *this, uint32_t client_size);
void ot_epoll_deinit(ot_epoll_t *this);
void ot_epoll_destroy(ot_epoll_t *this);
void ot_epoll_test();

#endif