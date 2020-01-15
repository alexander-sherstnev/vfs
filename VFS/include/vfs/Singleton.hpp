//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>

namespace VFS
{
    /**
     * Generic Singleton Implementation.
     * @tparam T
     */
    template <class T>
    class Singleton
    {
    public:
        /**
         * Default virtual destructor.
         */
        virtual ~Singleton() = default;

        /**
         * Singleton Implementation.
         * @return {T&} The instance.
         */
        static T& GetInstance()
        {
            static const std::unique_ptr<T> instance(new T());
            return *instance;
        }

        // Preventing copy or assign.
        Singleton(const Singleton&) = delete;
        Singleton& operator= (const Singleton) = delete;

    protected:
        /**
         * Default constructor
         */
        Singleton() = default;
    };
}
