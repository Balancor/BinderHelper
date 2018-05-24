//
// Created by guoguo on 5/22/18.
//

#ifndef ELFHOOK_BINDERHELPER_H
#define ELFHOOK_BINDERHELPER_H
#include <utils/Errors.h>
#include <binderhelper/Parcel.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>
#include <utils/KeyedVector.h>

#if defined(_WIN32)
typedef  int  uid_t;
#endif



class BinderHelper : public virtual RefBase {
public:
    static  sp<BinderHelper>    self();
    static  sp<BinderHelper>    selfOrNull();
    /* initWithDriver() can be used to configure libbinder to use
     * a different binder driver dev node. It must be called *before*
     * any call to BinderHelper::self(). /dev/binder remains the default.
     */
    static  sp<BinderHelper>    initWithDriver(const char *driver);

    void                setContextObject(const sp<IBinder>& object);
    sp<IBinder>         getContextObject(const sp<IBinder>& caller);

    void                setContextObject(const sp<IBinder>& object,
                                         const String16& name);
    sp<IBinder>         getContextObject(const String16& name,
                                         const sp<IBinder>& caller);

    void                startThreadPool();

    typedef bool (*context_check_func)(const String16& name,
                                       const sp<IBinder>& caller,
                                       void* userData);

    bool                isContextManager(void) const;
    bool                becomeContextManager(
            context_check_func checkFunc,
            void* userData);

    sp<IBinder>         getStrongProxyForHandle(int32_t handle);
    wp<IBinder>         getWeakProxyForHandle(int32_t handle);
    void                expungeHandle(int32_t handle, IBinder* binder);

    void                spawnPooledThread(bool isMain);

    status_t            setThreadPoolMaxThreadCount(size_t maxThreads);
    void                giveThreadPoolName();

    String8             getDriverName();

    ssize_t             getKernelReferences(size_t count, uintptr_t* buf);

private:
    friend class IPCThreadState;

    BinderHelper(const char* driver);
    ~BinderHelper();

    BinderHelper(const BinderHelper& o);
    BinderHelper&       operator=(const BinderHelper& o);
    String8             makeBinderThreadName();

    struct handle_entry {
        IBinder* binder;
        RefBase::weakref_type* refs;
    };

    handle_entry*       lookupHandleLocked(int32_t handle);

    String8             mDriverName;
    int                 mDriverFD;
    void*               mVMStart;

    // Protects thread count variable below.
    pthread_mutex_t     mThreadCountLock;
    pthread_cond_t      mThreadCountDecrement;
    // Number of binder threads current executing a command.
    size_t              mExecutingThreadsCount;
    // Maximum number for binder threads allowed for this process.
    size_t              mMaxThreads;
    // Time when thread pool was emptied
    int64_t             mStarvationStartTimeMs;

    mutable Mutex               mLock;  // protects everything below.

    Vector<handle_entry>mHandleToObject;

    bool                mManagesContexts;
    context_check_func  mBinderContextCheckFunc;
    void*               mBinderContextUserData;

    KeyedVector<String16, sp<IBinder> >
            mContexts;


    String8             mRootDir;
    bool                mThreadPoolStarted;
    volatile int32_t            mThreadPoolSeq;





};


#endif //ELFHOOK_BINDERHELPER_H
