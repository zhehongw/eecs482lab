//assume already have sockets functions

void send_linked_list(int sock, const list<string> &l){
	uint32_t list_length = htonl(l.size());
	send(sock,&list_length, sizeof(list_length), 0);

	for(const &el : l){
		uint32_t size = htonl(el.size());
		send(sock, &size, sizeof(size), 0);
		send(sock, el.c_str(), el.size(), 0);
	}
	
}

list<string> receive_linked_list(int sock){
	uint32_t list_length;
	recv(sock, &list_length, sizeof(list_length), MSG_WAITALL);
	uint32_t len = ntohl(list_length);

	list<string> l;
	for(uint32_t i = 0; i < len; i++){
		uint32_t size;
		recv(sock, &size, sizeof(size), MSG_WAITALL);
		size = ntohl(size);
		string s;
		for(uint32_t i; i < size; i++){
			char c;
			recv(sock, &c, sizeof(c), MSG_WAITALL);
			s.push_back(c);
		}
		l.push_back(s);
	}
	return l;
}
