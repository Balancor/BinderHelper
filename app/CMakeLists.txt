cmake_minimum_required(VERSION 3.4.1)

SET(CPP_SRC_ROOT ${PROJECT_SOURCE_DIR}/src/main/cpp)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")

INCLUDE_DIRECTORIES(${CPP_SRC_ROOT}/include)
INCLUDE_DIRECTORIES(${CPP_SRC_ROOT}/safe-iop/include)

FIND_LIBRARY( log-lib
        log)

ADD_LIBRARY(utils
        SHARED
        ${CPP_SRC_ROOT}/utils/ashmem-dev.c
        ${CPP_SRC_ROOT}/utils/BufferedTextOutput.cpp
        ${CPP_SRC_ROOT}/utils/Debug.cpp
        ${CPP_SRC_ROOT}/utils/RefBase.cpp
        ${CPP_SRC_ROOT}/utils/TextOutput.cpp
        ${CPP_SRC_ROOT}/utils/Threads.cpp
        ${CPP_SRC_ROOT}/utils/threads.c
        ${CPP_SRC_ROOT}/utils/Timers.cpp
        ${CPP_SRC_ROOT}/utils/sched_policy.cpp
        ${CPP_SRC_ROOT}/utils/SystemClock.cpp
        ${CPP_SRC_ROOT}/utils/SharedBuffer.cpp
        ${CPP_SRC_ROOT}/utils/Static.cpp
        ${CPP_SRC_ROOT}/utils/String16.cpp
        ${CPP_SRC_ROOT}/utils/String8.cpp
        ${CPP_SRC_ROOT}/utils/StrongPointer.cpp
        ${CPP_SRC_ROOT}/utils/Unicode.cpp
        ${CPP_SRC_ROOT}/utils/VectorImpl.cpp)

TARGET_LINK_LIBRARIES(utils
        ${log-lib})

ADD_LIBRARY(binderhelper
        SHARED
        ${CPP_SRC_ROOT}/binderhelper/Binder.cpp
        ${CPP_SRC_ROOT}/binderhelper/BinderHelper.cpp
        ${CPP_SRC_ROOT}/binderhelper/BpBinder.cpp
        ${CPP_SRC_ROOT}/binderhelper/IInterface.cpp
        ${CPP_SRC_ROOT}/binderhelper/IPCThreadState.cpp
        ${CPP_SRC_ROOT}/binderhelper/IResultReceiver.cpp
        ${CPP_SRC_ROOT}/binderhelper/IShellCallback.cpp
        ${CPP_SRC_ROOT}/binderhelper/native_handle.c
        ${CPP_SRC_ROOT}/binderhelper/NativeHandle.cpp
        ${CPP_SRC_ROOT}/binderhelper/Parcel.cpp
        ${CPP_SRC_ROOT}/binderhelper/PersistableBundle.cpp
        ${CPP_SRC_ROOT}/binderhelper/Status.cpp
        ${CPP_SRC_ROOT}/binderhelper/Value.cpp)

TARGET_LINK_LIBRARIES(binderhelper
        utils
        ${log-lib})

ADD_LIBRARY(native-lib
        SHARED
        src/main/cpp/native-lib.cpp)


TARGET_LINK_LIBRARIES( native-lib
        utils
        binderhelper
        ${log-lib})