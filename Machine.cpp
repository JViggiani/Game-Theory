#include "Machine.hpp"

Machine* Machine::pinstance_{nullptr};
std::mutex Machine::mutex_;

Machine::Machine()
{
    //JOSH read reward config from file here
}

Machine* Machine::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(pinstance_ == nullptr)
    {
        pinstance_ = new Machine();
    }
    return pinstance_;
}