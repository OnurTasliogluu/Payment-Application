#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ot_epoll.h"

struct epoll_event event;

static int32_t ot_epoll_create_fd()
{
    printf("ot_epoll_create_fd\n");
    int32_t epoll_fd;
    epoll_fd = epoll_create1(0);

    if(epoll_fd == -1)
    {
        fprintf(stderr, "Failed to create epoll file descriptor\n");
        return -1;
    }
    printf("ot_epoll_create_fd-2\n");
    return epoll_fd;
}

int32_t ot_epoll_add_fd(ot_epoll_t *this, int32_t events, int32_t fd)
{
    event.events = events;
    event.data.fd = fd;

    if(epoll_ctl(this->epoll_poll_fd, EPOLL_CTL_ADD, 0, &event))
    {
        fprintf(stderr, "Failed to add file descriptor to epoll\n");
        return 1;
    }
    return 0;
}

int32_t ot_epoll_del_fd(ot_epoll_t *this, int32_t events, int32_t fd)
{
    event.events = events;
    event.data.fd = fd;

    if(epoll_ctl(this->epoll_poll_fd, EPOLL_CTL_DEL, 0, &event))
    {
        fprintf(stderr, "Failed to add file descriptor to epoll\n");
        return 1;
    }
    return 0;
}

void ot_epoll_init(ot_epoll_t *this, uint32_t client_size) {
    printf("ot_epoll_init-1\n");
    this->epoll_poll_fd = ot_epoll_create_fd();
    printf("ot_epoll_init-2\n");
    //this->events = malloc(sizeof(epoll_event_t)*client_size);
    printf("ot_epoll_init-3\n");
}

void ot_epoll_deinit(ot_epoll_t *this) {
    if(close(this->epoll_poll_fd))
    {
        fprintf(stderr, "Failed to close epoll file descriptor\n");
    }
}

void ot_epoll_destroy(ot_epoll_t *this) {
    ot_epoll_deinit(this);
    free(this);
}

void ot_epoll_test() {
    ot_epoll_t *this = ot_epoll_create();
    ot_epoll_init(this, 15);
    ot_epoll_destroy(this);
}

ot_epoll_t *ot_epoll_create() {
    ot_epoll_t *this = malloc(sizeof(ot_epoll_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    this->epoll_poll_fd = -1;

    return this;
}

