#include <iostream> 
#include <utility> // pair 依赖
#include <cstring> 
#include <functional> 
#include <complex> 


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

// helper: print element with index IDX of tuple with MAX elements
template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE{
    static void print( std::ostream& ostrm, const std::tuple<Args...>& t){
        ostrm << std::get<IDX>(t) << (IDX+1==MAX ? "" : ",");
        PRINT_TUPLE<IDX+1, MAX, Args...>::print(ostrm, t);
    }
};

// helper: partial specialization to end the recursion
template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...>{
    static void print( std::ostream& ostrm, const std::tuple<Args...>& t){
    }
};

// output operation for tuples
template <typename... Args>
std::ostream& operator << (std::ostream& ostrm, const std::tuple<Args...>& t)
{
    ostrm << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(ostrm, t);
    return ostrm << "]";
}

void test_tuple(){
    // tuple 许多用法跟 pair类似，而且在元素个数为2时，可以相互转换。
    // tuple 输出流需要自己重载，标准库中不支持
    
    //std::tuple<T1, T2,...,Tn> t;
    std::tuple<std::string, int, int, std::complex<double>> t0;
    std::cout<< t0 <<std::endl;//tuple打印

    //std::tuple<T1, T2,...,Tn> t(v1, v2,..., vn);
    std::tuple<std::string, int, int, std::complex<double>> t1("t1", 1, 10, std::complex<double>(10, 10));
    std::cout<< t1 <<std::endl;
    typedef std::tuple<std::string, int, int, std::complex<double>> Tuple4;
    // 下面这种用法，打印tuple部分元素。此处试验元编程。
    std::cout<< "std::tuple_size<Tuple4>::value: " << std::tuple_size<Tuple4>::value <<std::endl;
    PRINT_TUPLE<0, std::tuple_size<Tuple4>::value, std::string, int, int, std::complex<double>>::print(std::cout, t1);
    std::cout<<std::endl;
    PRINT_TUPLE<2, std::tuple_size<Tuple4>::value, std::string, int, int, std::complex<double>>::print(std::cout, t1);
    std::cout<<std::endl;
    PRINT_TUPLE<1, 3, std::string, int, int, std::complex<double>>::print(std::cout, t1);
    std::cout<<std::endl;

    //std::tuple<T1, T2> t(p); 使用std::pair对std::tuple赋值
    std::tuple<int, int> tp( std::pair<int, int>(2, 2) );
    std::cout<< tp <<std::endl;

    // std::tie
    std::tuple<int, float, std::string> t5(77, 1.1, "more light");
    int i;
    std::string s;
    std::tie(i, std::ignore, s) = t5;
    std::cout<< "tie:" << i << "," << s <<std::endl;

    // get<0>(t), 可读可写
    std::get<0>(t5) = 66;
    std::cout<< t5 <<std::endl;

    // tuple 比较，需要每个元素都支持比较或者实现了比较运算符的函数

    // 引用
    s = "old";
    auto x = std::make_tuple(s);
    std::get<0>(x) = "my value";
    std::cout<< "s = " << s <<std::endl;

    auto y = std::make_tuple(ref(s));
    std::get<0>(y) = "my value";
    std::cout<< "s = " << s <<std::endl;

    // std::pair 和 std::tuple 还有一个区别是tuple没有实现Initiallizer List转tuple的构造函数，所以出现下面情况
    std::pair<int, int> tp6 = {1, 2}; // OK
    std::cout<< tp6;
    //std::tuple<int,int> t6 = {1, 2}; // Error
    //std::tuple<int,int> t7 = {1, 2, 3 }; //Error


    //一些需要注意的地方，语法糖
    //std::vector<std::tuple<int, float>> v{ {1, 1.0}, {2, 2.0} }; //Error
    //std::tuple<int, int, int> foo(){
        //return { 1, 2, 3 };  //Error
    //}   
    //std::vector<std::tuple<int, float>> v{ std::make_tuple{1, 1.0}, std::make_tuple{2, 2.0} }; //OK
    //std::tuple<int, int, int> foo(){
        //return std::make_tuple{ 1, 2, 3 };  //OK
    //}   

    //std::vector<std::pair<int, float>> v{ {1, 1.0}, {2, 2.0} }; //OK
    //std::vector<std::vector<float, float>> v{ {1, 1.0}, {2, 2.0} }; //OK
    
    //std::vector<int> foo2(){
       //return {1, 2, 3 }; // OK 
    //}
}


int main(){
    test_pair();       
    test_tuple();
    return 0;
}
