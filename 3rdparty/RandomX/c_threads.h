#pragma once

#ifdef _WIN32
#include <windows.h>
#define CTHR_MUTEX_TYPE	HANDLE
#define CTHR_MUTEX_INIT	NULL
#define CTHR_MUTEX_LOCK(x)	do { if (x == NULL) { \
    HANDLE p = CreateMutex(NULL, FALSE, NULL); \
    if (InterlockedCompareExchangePointer((PVOID*)&x, (PVOID)p, NULL) != NULL) \
      CloseHandle(p); \
  } WaitForSingleObject(x, INFINITE); } while(0)
#define CTHR_MUTEX_UNLOCK(x)	ReleaseMutex(x)
#define CTHR_THREAD_TYPE	HANDLE
#define CTHR_THREAD_RTYPE	void
#define CTHR_THREAD_RETURN	return
#define CTHR_THREAD_CREATE(thr, func, arg)	thr = (HANDLE)_beginthread(func, 0, arg)
#define CTHR_THREAD_JOIN(thr)			WaitForSingleObject(thr, INFINITE)
#else
#include <pthread.h>
#define CTHR_MUTEX_TYPE pthread_mutex_t
#define CTHR_MUTEX_INIT	PTHREAD_MUTEX_INITIALIZER
#define CTHR_MUTEX_LOCK(x)	pthread_mutex_lock(&x)
#define CTHR_MUTEX_UNLOCK(x)	pthread_mutex_unlock(&x)
#define CTHR_THREAD_TYPE pthread_t
#define CTHR_THREAD_RTYPE	void *
#define CTHR_THREAD_RETURN	return NULL
#define CTHR_THREAD_CREATE(thr, func, arg)	pthread_create(&thr, NULL, func, arg)
#define CTHR_THREAD_JOIN(thr)			pthread_join(thr, NULL)
#endif
