#include <iostream>
#include <memory>
#include <string>
#include <functional> 

using namespace std;

/**
* @brief: brief
*
* @param: 
*
* @return: void
*/
void test_shared_ptr()
{
    // shared_ptr<T> sp;
    shared_ptr<int> sp1;
    shared_ptr<int> sp2(new int);
    *sp2 = 10;
    cout<< "sp1-ptr: " << sp1 <<endl;
    cout<< "sp2: " << *sp2 <<endl;
    // shared_ptr<T> sp(ptr);
    // shared_ptr<T> sp(ptr, del);
    sp1.reset(new int, [](int* p) {
                            cout<< "delete: sp1" <<endl;
                            delete p;
                          });
    sp1 = nullptr;//指针置为空，并释放所持有的对象 
    cout<< "haha" <<endl;
    // shared_ptr<T> sp(ptr, del, ac); //ac allocator
    
    // shared_ptr<T> sp(nullptr);
    shared_ptr<int> sp3(nullptr);
    cout<< "sp3: " << sp3 <<endl;
    
    // shared_ptr<T> sp(nullptr, del);
    // shared_ptr<T> sp(nullptr, del, ac);

    // shared_ptr<T> sp(sp2);
    shared_ptr<int> sp4(sp2);
    cout<< "sp2: " << *sp2 << endl;
    cout<< "sp4: " << *sp4 << endl;

    // shared_ptr<T> sp(move(sp2));
    shared_ptr<int> sp5(move(sp2));
    cout<< "sp2-ptr: " << sp2 << endl;
    cout<< "sp5: " << *sp5 << endl;

    // shared_ptr<T> sp(sp2, ptr);
    int* ptr = new int;
    *ptr = 20;
    cout<< "sp5.use_count(): " << sp5.use_count() << endl;
    shared_ptr<int> sp6(sp5, sp5.get());
    cout<< "sp5.use_count(): " << sp5.use_count() << endl;
    cout<< "sp6.use_count(): " << sp6.use_count() << endl;
    cout<< "sp5: " << *sp5 << endl;
    cout<< "sp6: " << *sp6 << endl;
    *ptr = 30;
    cout<< "sp5: " << *sp5 << endl;
    cout<< "sp6: " << *sp6 << endl;

    sp5 = nullptr;
    cout<< "sp5.use_count(): " << sp5.use_count() << endl;
    cout<< "sp6.use_count(): " << sp6.use_count() << endl;
    
    // shared_ptr<T> sp(wp);
    weak_ptr<int> wp(sp6);
    *(wp.lock()) = 40;
    shared_ptr<int> sp7(wp);
    cout<< "sp7: " << *sp7 << endl;

    // shared_ptr<T> sp(move(up));
    unique_ptr<int> up1(new int);
    *up1 = 50;
    shared_ptr<int> sp8(move(up1));
    cout<< "sp8: " << *sp8 << endl;

    // shared_ptr<T> sp(move(ap)); C++11以后，auto_ptr已经过时，不推荐使用。
    
    // sp.~shared_ptr(); Call the deleter if sp owns an object
    
    // sp = sp2;
    shared_ptr<int> sp9 = sp8;
    cout<< "sp9: " << *sp9 << endl;

    // sp = move(sp2);
    // sp = move(up);
    // sp = move(ap);
    
    // sp1.swap(sp2);
    *sp9 = 90;
    sp7.swap(sp9);
    cout<< "sp7: " << *sp7 << endl;
    cout<< "sp9: " << *sp9 << endl;

    // swap(sp1, sp2);
    std::swap(sp7, sp9);
    cout<< "sp7: " << *sp7 << endl;
    cout<< "sp9: " << *sp9 << endl;

    // sp.reset(); 首先释放对象，调用一次del函数，类比构造函数.
    // sp.reset(ptr);
    // sp.reset(ptr, del);
    // sp.reset(ptr, del, ac);
    
    // make_shared(...);//推荐使用，内存分配优化，从2次到1次
    shared_ptr<int> sp10 = make_shared<int>(100);
    cout<< "sp10: " << *sp10 << endl;

    // allocate_shared(ac, ...);
    
    // sp.get()       //Returns the stored pointer
    cout<< "sp10-ptr: " << sp10.get() << endl;
    cout<< "sp10: " << *sp10.get() << endl;

    // *sp
    // sp->... Provide member access for the owned object
    // sp->use_count()     Returns the number of shared owners
    
    // sp.unique()  是否只有一个所有者, 等效于 sp->use_count() == 1
    cout<< "sp.unique: " << sp10.unique() << endl;

    //if (sp)      Operator bool();yields whether sp is empty
    if( sp10 ){
        cout << "sp 不为空:" << sp10 << endl;
    }else{
        cout << "sp 为空:" << sp10 << endl;
    }

    // sp1 == sp2
    // sp1 != sp2
    // sp1 < sp2
    // sp1 <= sp2
    // sp1 > sp2
    // sp1 >= sp2
    shared_ptr<int> sp11 = make_shared<int>(100);
    shared_ptr<int> sp12 = make_shared<int>(100);
    shared_ptr<int> sp13(sp11);
    cout << "(sp11 == sp12):" << (sp11 == sp12) <<endl; // false
    cout << "(sp11 == sp13):" << (sp11 == sp13) <<endl; // true

    // static_pointer_cast(sp)            static_cast<> semantic for sp
    // dynamic_pointer_cast(sp)           dynamic_cast<> semantic for sp
    // const_pointer_cast(sp)             const_cast<> semantic for sp
    
    // get_deleter(sp)  返回释放函数地址，如果有就返回，否则返回nullptr
    
    // strm << sp      等价于 strm << sp.get()
    cout << "sp10:" << sp10 <<endl;

    // sp.owner_before(sp2) // 需要研究，以下都返回0. 后面构造返回1的情况。
    shared_ptr<int> sp14 = make_shared<int>(100);
    shared_ptr<int> sp15(sp14);
    shared_ptr<int> sp18(sp14, sp14.get());
    cout<< "sp14.owner_before(sp15): " << sp14.owner_before(sp15)<<endl;
    cout<< "sp14.owner_before(sp15): " << sp15.owner_before(sp14)<<endl;
    cout<< "sp14.owner_before(sp15): " << sp14.owner_before(sp18)<<endl;

    shared_ptr<int> sp16(new int);
    shared_ptr<int> sp17(new int);
    cout<< "sp17.owner_before(sp16): " << sp17.owner_before(sp16)<<endl;
    
    // sp.owner_before(wp2)
}

void test_weak_ptr(){
    //weak_ptr<T> wp
    //weak_ptr<T> wp(sp)
    //weak_ptr<T> wp(wp2)
    //wp.~weak_ptr()
    //wp = wp2
    //wp = sp
    //wp.swap(wp2)
    //swap(wp1,wp2)
    //wp.reset()             //Gives up ownership of owned object, if any, and reinitializes as empty weak pointer
    //wp.use_count()         //Returns the number of shared owners (shared_ptrs owning the object) or 0 if the weak pointer is empty
    shared_ptr<int> sp0(new int);
    shared_ptr<int> sp1(sp0);
    cout<< "sp0.use_count():" << sp0.use_count() <<endl;
    weak_ptr<int> wp0(sp0);  //weak_ptr 不增加引用计数， 而shared_ptr会。
    weak_ptr<int> wp1(sp0);
    cout<< "wp0.use_count():" << wp0.use_count() <<endl;
    cout<< "wp1.use_count():" << wp1.use_count() <<endl;
    //wp.expired()           //Returns whether wp is empty
    //wp.lock()              //获取对象,Returns a shared pointer sharing ownership of the pointer owned by the weak pointer (or an empty shared pointer if none)
    //wp.owner_before(wp2)
    //wp.owner_before(sp)
} 


class D
{
public:
    void operator () (int * p) {
        cout << "deleter " << endl;
        delete p;
    }
};

void test_unique_ptr(){
    //unique_ptr<...> up
    //unique_ptr<T> up(nullptr)
    //unique_ptr<...> up(ptr)
    //unique_ptr<...> up(ptr,del)
    D d; // instance of the deleter type
    unique_ptr<int, D> p1(new int, D()); // D must be MoveConstructible
    unique_ptr<int, D> p2(new int, d);   // D must be CopyConstructible
    unique_ptr<int, D&> p3(new int, d);  // p3 holds a reference to d
    //unique_ptr<int, const D&> p4(new int, D()); // Error: rvalue deleter object, can’t have reference deleter type

    //unique_ptr<T> up(move(up2))
    //unique_ptr<T> up(move(ap))
    //up.~unique_ptr()
    //up = move(up2)
    //up = nullptr
    //up1.swap(up2)
    //swap(up1,up2)
    //up.reset()    
    //up.reset(ptr)
    //up.release()  
    //up.get()
    //*up
    //up->...
    //up[idx]
    //if (up)
    //up1 == up2
    //up1 != up2
    //up1 < up2
    //up1 <= up2
    //up1 > up2
    //up1 >= up2
    //up.get_deleter()

}
