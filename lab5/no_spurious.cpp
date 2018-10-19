class newcv{
	newcv();
	void wait(mutex&);
	void signal();
	queue<Item*> q;
	mutex internal_mutex;
}
struct Item{
	bool signalled;
	cv w;
}
newcv::newcv(){
}

void newcv::wait(mutex& m){
	internal_mutex.lock();
	m.unlock();
	//sleep
	Item item;
	item.signalled = false;
	q.push_back(&item);
	whilec(！item.signalled){
		item.w.wait(internal_mutex);
	}
	internal_mutex.unlock();
	m.lock();
}
void newcv::signal(){
	internal_mutex.lock();
	if(!q.empty()){
		q.front()->w.signal();
		q.front()->signalled = true;
		q.pop()
	}
	internal_mutex.unlock();
}
