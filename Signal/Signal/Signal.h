#ifndef SIGNAL_H
#define SIGNAL_H

#include<vector>
#include<functional>

template<typename... Args> class Signal
{
public:
    using slotType = std::function<void(Args...)>;

    void connect(slotType slot){
        slots.push_back(slot);
    }

    template<typename T> 
    void connect(T* instance, void (T::*method)(Args...)){
        slots.push_back([=](Args... args){
            (instance->*method)(args...);
        });
    }

    void emit(Args... args) {
        for(auto& slot : slots){
            slot(args...);
        }
    }
private:
    std::vector<slotType> slots;
};

#endif