#include <iostream> 
#include <utility> // pair 依赖
#include <cstring> 
#include <functional> 

/**
* @brief: 输出pair
*
* @param: std::pair<T1
*       : T2> p
*
* @return: void
*/
template <typename T1, typename T2>
std::ostream& operator << (std::ostream& ostr, const std::pair<T1, T2> & p){
    ostr << p.first << "," << p.second << std::endl;
}

template <typename T>
bool operator == (const T & t1, const T & t2){
    /*
    // std::get<0>(t1),其中0不能换成变量，而必须常量
    auto count = std::tuple_size<T>::value;
    for (auto i = 0; i < count; ++i) { 
        if( std::get<i>(t1) != std::get<i>(t2) ){
            return false;
        } 
    } 
    return true;
    */
    return std::get<0>(t1) != std::get<0>(t2) || std::get<1>(t1) != std::get<1>(t2);
}



/**
* @brief: C++的一个Bug，在Release模式下会报错，而在Debug模式下不会。
*
* @param: 
*
* @return: void
*/
void A_BUG_OF_CPP()
{
    // 下面代码在Release模式下会报错，在Debug模式下正常
    std::pair<int,std::string> p0;
    std::cout<< p0 << std::endl ;

    // 下面代码始终正确，区别在于后面没有"<< std::endl "
    std::cout<< p0 ;
}

/**
* @brief: pair使用
*
* @param: 
*
* @return: void
*/
void test_pair()
{
    // pair<T1,T2> p
    std::pair<int,std::string> p0;
    std::cout<< p0 ;

    // pair<T1,T2> p(val1, val2)
    int x = 1;
    std::string str = "1234";
    std::pair<int,std::string> p1(x, str);
    std::cout<< p1 ;

    // pair<T1,T2> p(rv1, rv2)
    std::pair<int,std::string> p2(2, "4567");
    std::cout<< p2 ;

    // pair<T1,T2> p(piecewise_construct, t1, t2)
    
    // pair<T1,T2> p(p2)
    std::pair<int, std::string> p3(p1);
    std::cout<< p3 ;

    // pair<T1,T2> p(rv)
    std::pair<int, std::string> p4(std::move(p1));
    std::cout<< p4 ;
    
    // p = p2
    auto p5 = p2;
    std::cout<< p5 ;

    // p = rv
    auto p6 = std::make_pair<int, std::string>(10, "str10");
    std::cout<< p6 ;

    // p.first
    std::cout<< p6.first <<std::endl;

    // p.second
    std::cout<< p6.second <<std::endl;

    // get<0>(p)
    std::cout<< std::get<0>(p6) <<std::endl;

    // get<1>(p)
    std::cout<< std::get<1>(p6) <<std::endl;

    // p1 == p2
    std::cout<< (p3 == p1) <<std::endl;

    // p1 != p2
    std::cout<< (p3 != p1) <<std::endl;

    // p1 < p2
    std::cout<< (p1 < p3) <<std::endl;
    
    // p1 > p2
    std::cout<< (p1 > p3) <<std::endl;
    
    // p1 <= p2
    std::cout<< (p1 <= p3) <<std::endl;
    
    // p1 >= p2
    std::cout<< (p1 >= p3) <<std::endl;
    
    // p1.swap(p2)
    p1.swap(p3);
    std::cout<< p1 ;
    std::cout<< p3 ;

    // swap(p1, p2)
    std::swap(p1, p2);
    std::cout<< p1 ;
    std::cout<< p3 ;
    
    // make_pair(val1, val2)
    auto p7 = std::make_pair<int, std::string>(7, "str7");
    std::cout<< p7 ;
    auto p8 = std::make_pair(7, "str7");
    std::cout<< strlen(p8.second) <<std::endl;
    std::cout<< p7.second.length() <<std::endl;

    // 类型信息:  std::tuple_size<std::pair<int,std::string>>::value
    std::cout<< std::tuple_size<std::pair<int,std::string>>::value <<std::endl;

    // 类型信息:  std::tuple_element<1,std::pair<int,std::string>>::type
    std::cout<< std::is_same<std::tuple_element<1,std::pair<int,std::string>>::type, std::string>::value <<std::endl;

    // std::make_pair有坑(P66)，建议使用时加上类型，即std::make_pair<T1,T2>(..,..)
    
    // std::pair存储引用对象
    int i = 0;
    auto pp = std::make_pair(std::ref(i), std::ref(i));
    ++pp.first;
    ++pp.second;
    std::cout<< "i=" << i <<std::endl;

    // tie接口, 用于单次值复制。非绑定，复制完之后再无关联关系
    int j = 0;
    std::pair<int, std::string> p9(9, "str9");
    std::tie(j, std::ignore) = p9;
    std::cout<< j <<std::endl;
    j = j -2;
    std::cout<< p9.first <<std::endl;
    p9.first += 2;
    std::cout<< j <<std::endl;

    // std::pair 比较
    std::pair<int, std::string> p10(10, "str10");
    std::pair<int, std::string> p11(10, "str10");
    std::cout<< (p10 == p11)  <<std::endl;

    // 如果遇到类型转换，需要复制构造函数
}

int main(){
    test_pair();       
    return 0;
}
