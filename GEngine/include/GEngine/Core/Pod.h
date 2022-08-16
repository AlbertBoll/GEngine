#pragma once

#include <new>
#include <utility>


namespace GEngine
{
    template <class T>
    struct Pod {
    private:
        T m_t;
    public:
        Pod() {}

        Pod(Pod&& p) : m_t(std::move(p.m_t)) {}

        Pod(Pod const& p) : m_t(p.m_t) {}

        Pod& operator=(Pod&& p) {
            m_t = std::move(p.m_t);
            return *this;
        }

        Pod& operator=(Pod const& p) {
            m_t = p.m_t;
            return *this;
        }

        Pod(T&& t) : m_t(std::move(t)) {}

        Pod(T const& t) : m_t(t) {}

        Pod& operator=(T&& t) {
            m_t = std::move(t);
            return *this;
        }

        Pod& operator=(T const& t) {
            m_t = t;
            return *this;
        }

        operator T const& () const {
            return m_t;
        }

        operator T& () {
            return m_t;
        }

        T const& get() const {
            return m_t;
        }

        T& get() {
            return m_t;
        }

        template <class ...Ts>
        Pod& emplace(Ts &&...ts) {
            ::new (&m_t) T(std::forward<Ts>(ts)...);
            return *this;
        }

        void destroy() {
            m_t.~T();
        }
    };


}