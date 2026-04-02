#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
using namespace std;

class ThreadGuard {
private:
    thread m_thread;
    
public:
    template<typename Callable>
    ThreadGuard(Callable&& func) : m_thread(forward<Callable>(func)) {}
    
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
    
    ThreadGuard(ThreadGuard&& other) noexcept : m_thread(move(other.m_thread)) {}
    ThreadGuard& operator=(ThreadGuard&& other) noexcept {
        if (this != &other) {
            if (m_thread.joinable()) {
                m_thread.join();
            }
            m_thread = move(other.m_thread);
        }
        return *this;
    }
    
    ~ThreadGuard() {
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }
};

class AtomicCounter {
private:
    int m_value;
    mutex m_mutex;
    
public:
    AtomicCounter(int initial = 0) : m_value(initial) {}
    
    void increment() {
        lock_guard<mutex> lock(m_mutex);
        m_value++;
    }
    
    void decrement() {
        lock_guard<mutex> lock(m_mutex);
        m_value--;
    }
    
    int get() {
        lock_guard<mutex> lock(m_mutex);
        return m_value;
    }
};

void function1() {
    cout << "Поток 1 начал работу" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Поток 1 завершил работу" << endl;
}

void function2() {
    cout << "Поток 2 начал работу" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Поток 2 завершил работу" << endl;
}

void counterWorker(AtomicCounter& counter, int iterations, bool isIncrement) {
    for (int i = 0; i < iterations; i++) {
        if (isIncrement) {
            counter.increment();
        } else {
            counter.decrement();
        }
    }
}

int main() {
    {
        ThreadGuard t1(function1);
        ThreadGuard t2(function2);
        
        cout << "Потоки запущены, ожидаем автоматического завершения..." << endl;
    }
    cout << "Оба потока завершились автоматически" << endl << endl;
    
    AtomicCounter counter(0);
    
    const int ITERATIONS = 1000000;
    const int THREADS_COUNT = 4;
    
    vector<thread> threads;
    
    for (int i = 0; i < THREADS_COUNT; i++) {
        if (i % 2 == 0) {
            threads.emplace_back(counterWorker, ref(counter), ITERATIONS, true);
        } else {
            threads.emplace_back(counterWorker, ref(counter), ITERATIONS, false);
        }
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "Финальное значение счётчика: " << counter.get() << endl;
    cout << "Начальное значение было 0" << endl;
    
    if (counter.get() == 0) {
        cout << "Результат верный!" << endl;
    } else {
        cout << "Ошибка: значение должно быть 0" << endl;
    }
    
    return 0;
}