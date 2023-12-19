#pragma once

#define MAKE_SINGLETON(T) friend Singleton<T>;

template<typename T>
class Singleton
{
public:
    virtual ~Singleton() = default;

    static T* instance()
    {
        static T self;
        return &self;
    }

protected:
    Singleton() = default;
};