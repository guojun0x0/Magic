/*
 * @Author: INotFound
 * @Date: 2020-03-13 22:32:30
 * @LastEditTime: 2021-02-01 22:16:02
 */
#pragma once
#include "Core/Core.h"
#include "Core/Adapter.h"
namespace Magic{
    template<class T>
    class ScopedLockImpl : public Noncopyable{
    public:
        ScopedLockImpl(T& mutex)
            :m_Mutex(mutex), m_Locked(false){
            lock();
        }
        ~ScopedLockImpl(){
            unlock();
        }
    private:
        void lock(){
            if(!m_Locked){
                m_Mutex.lock();
                m_Locked = true;
            }
        }
        void unlock(){
            if(m_Locked){
                m_Mutex.unlock();
                m_Locked = false;
            }
        }
    private:
        T& m_Mutex;
        bool m_Locked;
    };

    template<class T>
    class ReadScopedLockImpl : public Noncopyable{
    public:
        ReadScopedLockImpl(T& mutex)
            :m_Mutex(mutex), m_Locked(false){
            lock();
        }
        ~ReadScopedLockImpl(){
            unlock();
        }
    private:
        void lock(){
            if(!m_Locked){
                m_Mutex.readLock();
                m_Locked = true;
            }
        }
        void unlock(){
            if(m_Locked){
                m_Mutex.unlock();
                m_Locked = false;
            }
        }
    private:
        T& m_Mutex;
        bool m_Locked;
    };

    template<class T>
    class WriteScopedLockImpl : public Noncopyable{
    public:
        WriteScopedLockImpl(T& mutex)
            :m_Mutex(mutex), m_Locked(false){
            lock();
        }
        ~WriteScopedLockImpl(){
            unlock();
        }
    private:
        void lock(){
            if(!m_Locked){
                m_Mutex.writeLock();
                m_Locked = true;
            }
        }
        void unlock(){
            if(m_Locked){
                m_Mutex.unlock();
                m_Locked = false;
            }
        }
    private:
        T& m_Mutex;
        bool m_Locked;
    };
    /**
     * @brief: 读写锁
     */
    class RWMutex : public Noncopyable {
    public:
        typedef ReadScopedLockImpl<RWMutex> ReadLock;
        typedef WriteScopedLockImpl<RWMutex> WriteLock;
        RWMutex();
        ~RWMutex();
        void readLock();
        void writeLock();
        void unlock();
    private:
        rwlock_t m_RWLock;
    };
    /**
     * @brief: 自旋锁
     */
    class Spinlock : Noncopyable {
    public:
        typedef ScopedLockImpl<Spinlock> Lock;

        Spinlock();

        ~Spinlock();

        void lock();

        void unlock();

    private:
        spinlock_t m_Mutex;
    };
    /**
     * @brief: 普通锁
     */
    class Mutex : public Noncopyable {
    public:
        typedef ScopedLockImpl<Mutex> Lock;
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
    private:
        mutex_t m_Mutex;
    };
    /**
     * @brief: 信号量
     */
    class Semaphore : public Noncopyable{
    public:
        Semaphore(uint32_t count =0);

        ~Semaphore();

        void wait();

        void notify();
    private:
        sem_t m_Semaphore;
    };
}