//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#include "mntaArena.hpp"

namespace
{

    template<class T>
    struct list_member
    {
        T            value;
        list_member* next;
    };

    template<class T>
    struct list
    {
        list_member<T>*             members;
        mnta::Arena<list_member<T>> allocator;

        void push_front(T&& v) noexcept
        {
            list_member<T>* next = members;

            members = get(allocator);
            members->value = std::move(v);
            members->next  = next;
        }

        void pop_front() noexcept
        {
            if (members == nullptr) { return; }

            members = members->next;
        }
    };

}

int main(int argc, char** argv)
{
    list<int> my_list;
    my_list.push_front(123);
    my_list.push_front(321);

    my_list.pop_front();

    return 0;
}
