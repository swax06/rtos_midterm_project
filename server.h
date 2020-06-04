struct client{
	int sid;
	bool inCall, online;
	char name[10];
	int gp[10], g;
	struct session *ptr;
};
struct group{
	char name[10];
	struct client *mem[10];
	int count;
};
struct session{
	struct client *mem[10];
	int count;
};
extern struct client *clients[200];
extern struct group groups[20], *glptr;
extern int cli, temp_ind, grp;
extern void handleSigint(int sig);
extern void* clientHandler(void* input);