#ifndef WATER_NET_EVENT_HPP
#define WATER_NET_EVENT_HPP

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cstdint>

template<typename CallbackType>
class Event;

template<typename RetType, typename... ArgsType>
class Event<RetType (ArgsType...)>
{
public:
    typedef std::function<RetType (ArgsType...)> Handler;
    typedef uint32_t RegID;

    enum {INVALID_REGID = 0};

    RegID reg(Handler cb)
    {
        const RegID ID = lastRegID + 1;

        const auto it = regIDs.insert(regIDs.end(), std::make_pair(ID, callbackList.size()));
        if(it == regIDs.end())
            return INVALID_REGID;

        callbackList.emplace_back(ID, cb);
        it->second = callbackList.size() - 1;

        lastRegID = ID;
        return ID;
    }

    void unreg(RegID regID)
    {
        auto it = regIDs.find(regID);
        if(it == regIDs.end())
            return;

        auto& pair = callbackList.at(it->second);

        //尾删除
        callbackList.at(it->second) = callbackList.back();
        callbackList.pop_back();

        //更新索引
        regIDs[callbackList.at(it->second).first] = it->second;

        //删掉老的索引
        regIDs.erase(it);
    }

    void operator()(ArgsType... args) noexcept
    {
        for(auto& cb : callbackList)
        {
            try
            {
                cb.second(std::forward<ArgsType>(args)...);
            }
            catch(...)
            {
            }
        }
    }

private:
    std::vector<std::pair<RegID, Handler>> callbackList;
    std::unordered_map<RegID, typename std::vector<Handler>::size_type> regIDs;
    RegID lastRegID = INVALID_REGID;
};


#endif
