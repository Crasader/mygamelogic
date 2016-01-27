#ifndef __U2ThreadDefinesCpp11_H__
#define __U2ThreadDefinesCpp11_H__


#define U2_AUTO_MUTEX               mutable std::mutex    U2_AUTO_MUTEX_NAME
#define U2_LOCK_AUTO_MUTEX          std::lock_guard<std::mutex> lck(U2_AUTO_MUTEX_NAME)


#endif
