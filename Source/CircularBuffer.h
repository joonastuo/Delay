/*
  ==============================================================================

    CircularBuffer.h
    Created: 16 Oct 2018 3:17:07pm
    Author:  Tuovinen Joonas

  ==============================================================================
*/

#pragma once

#include <mutex>

template <class T>
class circular_buffer
{
public:
    //==========================================================================
    circular_buffer(size_t size) :
    mBuffer(std::unique_ptr<T[]>(new T[size])),
    mMaxSize(size)
    {
        // empty
    }
    
    //==========================================================================
    
    void put(float item)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        
        mBuffer[mHead] = item;
        
        if (mFull)
        {
            mTail = (mTail + 1) % mMaxSize;
        }
        
        mHead = (mHead + 1) % mMaxSize;
        mFull = mHead == mTail;
    }
    
    //==========================================================================
    
    T get()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (empty())
        {
            return T();
        }
        
        auto val = mBuffer[mTail];
        mFull = false;
        mTail = (mTail + 1) % mMaxSize;
        
        return val;
    }
    
    //==========================================================================
    
    void readBuffer(T* buffer)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        
        if (empty() || !full())
        {
            buffer[0] = -1;
            return;
        }
        
        size_t j = mTail;
        for (auto i = 0; i < mMaxSize; ++i)
        {
            buffer[i] = mBuffer[(j + i) % mMaxSize];
            
        }
        
        return;
    }
    
    //==========================================================================
    
    void reset()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mHead = mTail;
        mFull = false;
    }
    
    //==========================================================================
    
    bool empty()
    {
        return (!mFull && (mHead == mTail));
    }
    
    //==========================================================================
    
    bool full()
    {
        return mFull;
    }
    
    //==========================================================================
    
    size_t capacity()
    {
        return mMaxSize;
    }
    
    size_t size()
    {
        size_t size = mMaxSize;
        if (!mFull)
        {
            if (mHead >= mTail)
            {
                size = mHead - mTail;
            }
            else
            {
                size = mMaxSize + mHead - mTail;
            }
        }
        return size;
    }
    
private:
    //==========================================================================
    std::mutex mMutex;
    std::unique_ptr<T[]> mBuffer;
    size_t mHead = 0;
    size_t mTail = 0;
    const size_t mMaxSize;
    bool mFull = 0;
};

