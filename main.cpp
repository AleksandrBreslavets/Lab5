#include <iostream>
#include <syncstream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

void synchronizedOut(const string &s)
{
    osyncstream(cout) << s;
}

void slow (const string& name)
{
    this_thread::sleep_for(7s);
    synchronizedOut("Function with name: "+name+"\n");
}

void quick (const string& name)
{
    this_thread::sleep_for(1s);
    synchronizedOut("Function with name: "+name+"\n");
}

void work()
{
    auto start_time = chrono::system_clock::now();

    auto b1=async(launch::async, quick, "B1");
    quick("A1");
    b1.get();
    auto b2=async(launch::async, slow, "B2");
    slow("A2");
    b2.get();
    auto b3=async(launch::async, quick, "B3");
    quick("A3");
    b3.get();
    quick("C");

    auto end_time = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

    cout<<"Work is done! Total time: "<<duration<<" sec"<<endl;
}

int main() {
    work();
    return 0;
}
