/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 */

#ifndef HEADER_DRIVER_H
#define HEADER_DRIVER_H

#include <sys/types.h>

#include <rpc/rpc.h>

#ifndef WITH_TIRPC
/* Glibc is missing this prototype */
SVCXPRT *svcunixfd_create(int, u_int, u_int);
#endif /* WITH_TIRPC */

#include <stdbool.h>

#include "error.h"
#include "dxcore.h"

#define SONAME_LIBCUDA "libcuda.so.1"
#define SONAME_LIBNVML "libnvidia-ml.so.1"

#define SOCK_CLT 0
#define SOCK_SVC 1

struct driver_device;
struct driver_mig_device;

struct driver {
        struct error *err;
        void *cuda_dl;
        void *nvml_dl;
        int fd[2];
        pid_t pid;
        SVCXPRT *rpc_svc;
        CLIENT *rpc_clt;
};

void driver_program_1(struct svc_req *, register SVCXPRT *);

int driver_init(struct driver *, struct error *, struct dxcore_context *, const char *, uid_t, gid_t);
int driver_shutdown(struct driver *);
int driver_get_rm_version(struct driver *, char **);
int driver_get_cuda_version(struct driver *, char **);
int driver_get_device_count(struct driver *, unsigned int *);
int driver_get_device(struct driver *, unsigned int, struct driver_device **);
int driver_get_device_minor(struct driver *, struct driver_device *, unsigned int *);
int driver_get_device_busid(struct driver *, struct driver_device *, char **);
int driver_get_device_uuid(struct driver *, struct driver_device *, char **);
int driver_get_device_arch(struct driver *, struct driver_device *, char **);
int driver_get_device_model(struct driver *, struct driver_device *, char **);
int driver_get_device_brand(struct driver *, struct driver_device *, char **);
int driver_get_device_mig_capable(struct driver *, struct driver_device *, bool *);
int driver_get_device_mig_enabled(struct driver *, struct driver_device *, bool *);
int driver_get_device_max_mig_device_count(struct driver *, struct driver_device *, unsigned int *);
int driver_get_device_mig_device(struct driver *, struct driver_device *, unsigned int, struct driver_device **);
int driver_get_device_gpu_instance_id(struct driver *, struct driver_device *, unsigned int *);
int driver_get_device_compute_instance_id(struct driver *, struct driver_device *, unsigned int *);

#endif /* HEADER_DRIVER_H */
