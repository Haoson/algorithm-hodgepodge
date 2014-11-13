/*************************************************************************
  > File Name: function_object.h
  > Author:Haoson 
  > Created Time: Fri 26 Sep 2014 06:05:20 AM PDT
  > description:一些基本的函数对象
 ************************************************************************/

#ifndef FUNCTION_OBJECT_H_
#define FUNCTION_OBJECT_H_
namespace hds{
template <class Arg1,class Result>
struct UnaryFunction{
    typedef Arg1 argument_type;
    typedef Result result_type;
};
template <class Arg1, class Arg2, class Result>
struct BinaryFunction{
    typedef Arg1   first_argument_type;
    typedef Arg2   second_argument_type;
    typedef Result result_type;
};
template <typename T>
struct Less:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first<second;
    }
};
template <typename T>
struct Greater:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first>second;
    }
};
template <typename T>
struct LessEqual:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first<=second;
    }
};
template <typename T>
struct GreaterEqual:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first>=second;
    }
};;
template <typename T>
struct Equal:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first==second;
    }
};
template <typename T>
struct NotEqual:BinaryFunction<T,T,bool>{
    bool operator()(const T&first,const T&second)const{
        return first!=second;
    }
};
template <typename T>
struct Negate:UnaryFunction<T,T>{
    T operator()(const T&arg)const{
        return -arg;
    }
};
template <typename T>
struct LogicalNot:UnaryFunction<T,bool>{
    bool operator()(const T& arg)const{
        return !arg;
    }
};
}
#endif
