#include <iostream>
#include <thread>
#include <stack>
#include <mutex>

using namespace std;

template<typename T>
class trivial_thread_safe_stack {

	stack<shared_ptr<T>> stk;
	mutex m;

public:
	void push(T element) {
		lock_guard<mutex> lg(m);
		stk.push(make_shared<T>(element));
}	

	shared_ptr<T> pop() {
		lock_guard(mutex) lg(m);

		if (stk.empty()) {
			throw runtime_error("stack is empty");
		}
		
		shared_ptr<T> top(stk.top());
		top.pop();
		return top();
	}

	void pop(T &value) {
		lock_guard<mutex> lg(m);
		if (stk.empty()) throw runtime_error("stack is empty");
		value = *(stk.top().get());
		stk.pop();
	}

	T& top() {
		lock_guard<mutex> lg(m);
		return stk.top();
	}

	bool empty() {
		lock_guard<mutex> lg(m);
		return stk.empty();
	}

	size_t size() {
		lock_guard<mutex> lg(m);
		return stk.size();
	}

};

int main() {

}
