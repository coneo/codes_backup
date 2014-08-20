/*
 * Author: LiZhaojia - dantezhu@vip.qq.com
 *
 * Last modified: 2014-07-24 17:29 +0800
 *
 * Description: 通用反射机制，通过基类指针来返回派生类对象。限制：在同一个构建器内注册的类型，其构造函数参数列表必须相同
 */

namespace water{


//反射构建器，args   
template <typename Name, typename BaseType, typename... ConstructorArgs>
class Reflector
{
private:
    //抽象构建器， 实际构建器的基类
    class AbstructCreater
    {
    public:
        virtual ~AbstructCreater(){};
        virtual BaseType* create(ConstructorArgs... args) const = 0;
        virtual BaseType* create() const = 0;
    };

    //实际对象构建器
    template <typename RealType>
    class Creater : public AbstructCreater
    {
        BaseType* create(ConstructorArgs... args) const
        {
            return new(std::nothrow) RealType(std::forward<ConstructorArgs>(args)...); 
        }

        BaseType* create() const
        {
            return new(std::nothrow) RealType();
        }

        uint32_t sizeofObj() const
        {
            return sizeof(RealType);
        }
    };

public:
    //注册一种类型
    template <typename RealType>
    bool reg(const Name& name)
    {
        if(createrMap.find(name) != createrMap.end())//name 已被注册过， 不能重复注册
            return false;

        AbstructCreater* creater = new Creater<RealType>();
        if(creater == nullptr)
            return false;

        return createrMap.insert(std::make_pair(name, creater)).second;
    }

    //取消一种类型的注册
    void unreg(const Name& name)
    {
        createrMap.erase(name);
    }

    //创建一个指定类型的对象
    BaseType* produce(const Name& name, ConstructorArgs... args) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return nullptr;

        return it->second->create(std::forward<ConstructorArgs>(args)...);
    }

    BaseType* produce(const Name& name) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return nullptr;

        return it->second->create();
    }

    //得到指定类型的sizeof
    uint32_t sizeofType(const Name& name) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return 0;

        return it->second->sizeofObj();
    }

private:
    std::map<Name, AbstructCreater*> createrMap;
};


/*
//谝特化版本， 用于创建构造函数不需参数的对象
template <typename Name, typename BaseType>
class Reflector<Name, BaseType>
{
private:
    //抽象构建器， 实际构建器的基类
    class AbstructCreater
    {
    public:
        virtual ~AbstructCreater(){};
        virtual BaseType* create() const = 0;
    };

    //实际对象构建器
    template <typename RealType>
    class Creater : public AbstructCreater
    {
        BaseType* create() const
        {
            return new(std::nothrow) RealType(); //new 失败返回nullptr, 不抛bad_alloc异常
        }

        uint32_t sizeofObj() const
        {
            return sizeof(RealType);
        }
    };

public:

    //注册一种类型
    template <typename RealType>
    bool reg(const Name& name)
    {
        if(createrMap.find(name) != createrMap.end())//name 已被注册过， 不能重复注册
            return false;

        AbstructCreater* creater = new Creater<RealType>();
        if(creater == nullptr)
            return false;

        return createrMap.insert(std::make_pair(name, creater)).second;
    }

    //取消一种类型的注册
    void unreg(const Name& name)
    {
        createrMap.erase(name);
    }

    //创建一个指定类型的对象
    BaseType* produce(const Name& name) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return nullptr;

        return it->second->create();
    }

    //得到指定类型的sizeof
    uint32_t sizeofType(const Name& name) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return 0;

        return it->second->sizeofObj();
    }

private:
    std::map<Name, AbstructCreater*> createrMap;
};
*/

}
