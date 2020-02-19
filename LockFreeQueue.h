////
//// Created by fusionbolt on 2020/2/11.
////

/*
 * SafeQueue.hpp
 * Copyright (C) 2019 Alfredo Pons Menargues <apons@linucleus.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <queue>
#include <list>
#include <mutex>
#include <thread>
#include <cstdint>
#include <condition_variable>



/** A thread-safe asynchronous queue */
template <class T, class Container = std::list<T>>
class SafeQueue
{
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef Container container_type;

public:

    /*! Create safe queue. */
    SafeQueue() = default;
    SafeQueue (SafeQueue&& sq)
    {
        m_queue = std::move (sq.m_queue);
    }
    SafeQueue (const SafeQueue& sq)
    {
        std::lock_guard<std::mutex> lock (sq.m_mutex);
        m_queue = sq.m_queue;
    }

    /*! Destroy safe queue. */
    ~SafeQueue()
    {
        std::lock_guard<std::mutex> lock (m_mutex);
    }

    /**
     * Sets the maximum number of items in the queue. Defaults is 0: No limit
     * \param[in] item An item.
     */
    void set_max_num_items (unsigned int max_num_items)
    {
        m_max_num_items = max_num_items;
    }

    /**
     *  Pushes the item into the queue.
     * \param[in] item An item.
     * \return true if an item was pushed into the queue
     */
    bool push (const value_type& item)
    {
        std::lock_guard<std::mutex> lock (m_mutex);

        if (m_max_num_items > 0 && m_queue.size() > m_max_num_items)
            return false;

        m_queue.push (item);
        m_condition.notify_one();
        return true;
    }

    /**
     *  Pushes the item into the queue.
     * \param[in] item An item.
     * \return true if an item was pushed into the queue
     */
    bool push (const value_type&& item)
    {
        std::lock_guard<std::mutex> lock (m_mutex);

        if (m_max_num_items > 0 && m_queue.size() > m_max_num_items)
            return false;

        m_queue.push (item);
        m_condition.notify_one();
        return true;
    }

    /**
     *  Pops item from the queue. If queue is empty, this function blocks until item becomes available.
     * \param[out] item The item.
     */
    void pop (value_type& item)
    {
        std::unique_lock<std::mutex> lock (m_mutex);
        m_condition.wait (lock, [this]() // Lambda funct
        {
            return !m_queue.empty();
        });
        item = m_queue.front();
        m_queue.pop();
    }

    /**
     *  Pops item from the queue using the contained type's move assignment operator, if it has one..
     *  This method is identical to the pop() method if that type has no move assignment operator.
     *  If queue is empty, this function blocks until item becomes available.
     * \param[out] item The item.
     */
    void move_pop (value_type& item)
    {
        std::unique_lock<std::mutex> lock (m_mutex);
        m_condition.wait (lock, [this]() // Lambda funct
        {
            return !m_queue.empty();
        });
        item = std::move (m_queue.front());
        m_queue.pop();
    }

    /**
     *  Tries to pop item from the queue.
     * \param[out] item The item.
     * \return False is returned if no item is available.
     */
    bool try_pop (value_type& item)
    {
        std::unique_lock<std::mutex> lock (m_mutex);

        if (m_queue.empty())
            return false;

        item = m_queue.front();
        m_queue.pop();
        return true;
    }

    /**
     *  Tries to pop item from the queue using the contained type's move assignment operator, if it has one..
     *  This method is identical to the try_pop() method if that type has no move assignment operator.
     * \param[out] item The item.
     * \return False is returned if no item is available.
     */
    bool try_move_pop (value_type& item)
    {
        std::unique_lock<std::mutex> lock (m_mutex);

        if (m_queue.empty())
            return false;

        item = std::move (m_queue.front());
        m_queue.pop();
        return true;
    }

    /**
     *  Pops item from the queue. If the queue is empty, blocks for timeout microseconds, or until item becomes available.
     * \param[out] t An item.
     * \param[in] timeout The number of microseconds to wait.
     * \return true if get an item from the queue, false if no item is received before the timeout.
     */
    bool timeout_pop (value_type& item, std::uint64_t timeout)
    {
        std::unique_lock<std::mutex> lock (m_mutex);

        if (m_queue.empty())
        {
            if (timeout == 0)
                return false;

            if (m_condition.wait_for (lock, std::chrono::microseconds (timeout)) == std::cv_status::timeout)
                return false;
        }

        item = m_queue.front();
        m_queue.pop();
        return true;
    }

    /**
     *  Pops item from the queue using the contained type's move assignment operator, if it has one..
     *  If the queue is empty, blocks for timeout microseconds, or until item becomes available.
     *  This method is identical to the try_pop() method if that type has no move assignment operator.
     * \param[out] t An item.
     * \param[in] timeout The number of microseconds to wait.
     * \return true if get an item from the queue, false if no item is received before the timeout.
     */
    bool timeout_move_pop (value_type& item, std::uint64_t timeout)
    {
        std::unique_lock<std::mutex> lock (m_mutex);

        if (m_queue.empty())
        {
            if (timeout == 0)
                return false;

            if (m_condition.wait_for (lock, std::chrono::microseconds (timeout)) == std::cv_status::timeout)
                return false;
        }

        item = std::move (m_queue.front());
        m_queue.pop();
        return true;
    }

    /**
     *  Gets the number of items in the queue.
     * \return Number of items in the queue.
     */
    size_type size() const
    {
        std::lock_guard<std::mutex> lock (m_mutex);
        return m_queue.size();
    }

    /**
     *  Check if the queue is empty.
     * \return true if queue is empty.
     */
    bool empty() const
    {
        std::lock_guard<std::mutex> lock (m_mutex);
        return m_queue.empty();
    }

    /**
     *  Swaps the contents.
     * \param[out] sq The SafeQueue to swap with 'this'.
     */
    void swap (SafeQueue& sq)
    {
        if (this != &sq)
        {
            std::lock_guard<std::mutex> lock1 (m_mutex);
            std::lock_guard<std::mutex> lock2 (sq.m_mutex);
            m_queue.swap (sq.m_queue);

            if (!m_queue.empty())
                m_condition.notify_all();

            if (!sq.m_queue.empty())
                sq.m_condition.notify_all();
        }
    }

    /*! The copy assignment operator */
    SafeQueue& operator= (const SafeQueue& sq)
    {
        if (this != &sq)
        {
            std::lock_guard<std::mutex> lock1 (m_mutex);
            std::lock_guard<std::mutex> lock2 (sq.m_mutex);
            std::queue<T, Container> temp {sq.m_queue};
            m_queue.swap (temp);

            if (!m_queue.empty())
                m_condition.notify_all();
        }

        return *this;
    }

    /*! The move assignment operator */
    SafeQueue& operator= (SafeQueue && sq)
    {
        std::lock_guard<std::mutex> lock (m_mutex);
        m_queue = std::move (sq.m_queue);

        if (!m_queue.empty())  m_condition.notify_all();

        return *this;
    }


private:

    std::queue<T, Container> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
    unsigned int m_max_num_items = 0;
};

/*! Swaps the contents of two SafeQueue objects. */
template <class T, class Container>
void swap (SafeQueue<T, Container>& q1, SafeQueue<T, Container>& q2)
{
    q1.swap (q2);
}
#endif /* SAFEQUEUE_HPP_ */
//
//#ifndef GWUI_LOCKFREEQUEUE_H
//#define GWUI_LOCKFREEQUEUE_H
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <pthread.h>
//#include <execinfo.h>
//#include <signal.h>
//
///* Obtain a backtrace and print it to stdout. */
//#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
//void dump_stack(void)
//{
//    void *array[30] = {0};
//    size_t size = backtrace(array, ARRAY_SIZE(array));
//    char **strings = backtrace_symbols(array, size);
//    size_t i;
//
//    if (strings == NULL)
//    {
//        perror("backtrace_symbols.");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Obtained %zd stack frames.\n", size);
//
//    for (i = 0; i < size; i++)
//        printf("%s\n", strings[i]);
//
//    free(strings);
//    strings = NULL;
//
//    exit(EXIT_SUCCESS);
//}
//
//void sighandler_dump_stack(int sig)
//{
//    psignal(sig, "handler");
//    dump_stack();
//    signal(sig, SIG_DFL);
//    raise(sig);
//}
//
//
////线程安全队列
//typedef struct SafeElem
//{
//    void *data;
//    struct SafeElem *next;
//} SafeElem;
//
//struct SafeQueue
//{
//    SafeElem *head;
//    SafeElem *tail;
//    int size;
//    int capacity;
//    pthread_mutex_t mutex;
//
//    SafeQueue()
//    {
//        // SafeQueue *q = (SafeQueue *)malloc(sizeof(SafeQueue));
//        head = NULL;
//        tail = NULL;
//        size = 0;
//        capacity = capacity;
//        int ret = pthread_mutex_init(&mutex, NULL);
//        if (ret != 0)
//        {
//            printf("mutex error(%d)!\n", ret);
//        }
//    }
//
//    int Size()
//    {
//        int qsize;
//        pthread_mutex_lock(&mutex);
//        qsize = size;
//        pthread_mutex_unlock(&mutex);
//        return qsize;
//    }
//
//    void Push()
//    {
//        pthread_mutex_lock(&mutex);
//        if (size == capacity)
//        {
//            pthread_mutex_unlock(&mutex);
//        }
//        SafeElem *elem = (SafeElem *)malloc(sizeof(SafeElem));
//        elem->data = data;
//        elem->next = NULL;
//        if (head == NULL)
//        {
//            head = elem;
//        }
//        else
//        {
//            tail->next = elem;
//        }
//        tail = elem;
//        size++;
//        pthread_mutex_unlock(&mutex);
//    }
//
//    void Pop()
//    {
//        pthread_mutex_lock(&mutex);
//        if (size == 0)
//        {
//            pthread_mutex_unlock(&mutex);
//            return NULL;
//        }
//        SafeElem *elem = head;
//        head = head->next;
//        if (head == NULL)
//        {
//            tail = NULL;
//        }
//        size--;
//        void *data = elem->data;
//        free(elem);
//        pthread_mutex_unlock(&mutex);
//        return data;
//    }
//};
//
////SafeQueue *mkqueue(int capacity)
////{
////    SafeQueue *q = (SafeQueue *)malloc(sizeof(SafeQueue));
////    q->head = NULL;
////    q->tail = NULL;
////    q->size = 0;
////    q->capacity = capacity;
////    int ret = pthread_mutex_init(&q->mutex, NULL);
////    if (ret != 0)
////    {
////        printf("mutex error(%d)!\n", ret);
////        return NULL;
////    }
////    return q;
////}
//
////void *dequeue(SafeQueue *q)
////{
////    pthread_mutex_lock(&q->mutex);
////    if (q->size == 0)
////    {
////        pthread_mutex_unlock(&q->mutex);
////        return NULL;
////    }
////    SafeElem *elem = q->head;
////    q->head = q->head->next;
////    if (q->head == NULL)
////    {
////        q->tail = NULL;
////    }
////    q->size--;
////    void *data = elem->data;
////    free(elem);
////    pthread_mutex_unlock(&q->mutex);
////    return data;
////}
//
////int qsize(SafeQueue *q) {
////    int size;
////    pthread_mutex_lock(&q->mutex);
////    size = q->size;
////    pthread_mutex_unlock(&q->mutex);
////    return size;
////}
//
////int enqueue(SafeQueue *q, void *data)
////{
////    pthread_mutex_lock(&q->mutex);
////    if (q->size == q->capacity)
////    {
////        pthread_mutex_unlock(&q->mutex);
////        return -1;
////    }
////    SafeElem *elem = (SafeElem *)malloc(sizeof(SafeElem));
////    elem->data = data;
////    elem->next = NULL;
////    if (q->head == NULL)
////    {
////        q->head = elem;
////    }
////    else
////    {
////        q->tail->next = elem;
////    }
////    q->tail = elem;
////    q->size++;
////    pthread_mutex_unlock(&q->mutex);
////    return 0;
////}
//
//
//#endif //GWUI_LOCKFREEQUEUE_H
