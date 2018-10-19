class future{
	public:
		future(int (*func_arg) (void));
		bool is_finished();
		int get_result();

	private:
		static void wrapper(future*);
		int (*func)();
		mutex m;
		cv joiner;
		bool finished;
		int result;
}

future::future(int (*func_arg)(void)){
	finished = false;
	func = fun_arg;
	thread t((thread_startfunc_t) &future::wrapper, (void*) this);
}

future::wrapper(void *future_ptr){
	result = (*(future_ptr->func))();
	m.lock();
	future_ptr->result = result;
	future_ptr->finished = true;
	joiner.broadcast();
	m.unlock();
}

future::is_finished(){
	//can use raii()
	m.lock();
	bool f = finished;
	m.unlock();
	return f;	
}

int future::get_result(){
	m.lock();
	while(!finished){
		joiner.wait(m);
	}
	int r = result;
	m.unlock();
	return r;
}

