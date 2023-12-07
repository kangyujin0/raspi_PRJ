/*chat_server.c*/
//여러사람이 쓸 수 있는 다중 서버 예제
 1 #include <stdio.h>
 2 #include <stdlib.h>
 3 #include <unistd.h>
 4 #include <string.h>
 5 #include <arpa/inet.h>
 6 #include <sys/socket.h>
 7 #include <netinet/in.h>
 8 #include <pthread.h>
 9
10 #define BUF_SIZE 100
11 #define MAX_CLNT 256
12
13 void * handle_clnt(void * arg);
14 void send_mag(char * msg, int len);
15 void error_handling(char * msg);
16
17 int clnt_cnt=0;
18 int clnt_socks[MAX_CLNT];
19 pthread_mutex_t mutx;		//pthread_mutex_t(재정의) mutx를 사용 클라이언트와 관련된 데이터에 대한 동기화 수행
20
21 int main(int argc, char *argv[])	//서버 소켓 생성, 클라이언트 연결을 기다리는 accept호출을 무한루프로 수행
22 {
23         int serv_sock, clnt_sock;
24         struct sockaddr_in serv_adr, clnt_adr;
25         int clnt_adr_sz;
26         pthread_t t_id;	//스레드타입의 변수
27         if(argc!=2){
28                 printf("Usage : %s <port>\n", argv[0]);
29                 exit(1);
30         }
31
32         pthread_mutex_init(&mutx, NULL);		//뮤텍스함수 초기화
33         serv_sock=socket(PF_INET, SOCK_STREAM, 0);	//소캣함수 1.소켓생성/PF_INET은 IPv4 인터넷 프로토콜을 사용함을 의미
34
35         memset(&serv_adr, 0, sizeof(serv_adr));	//memset함수=serv_adr구조체의 멤버들 초기화
36         serv_adr.sin_family=AF_INET;
37         serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);	//호스트 바이트 순서(Host Byte Order)를 네트워크 바이트 순서(Network Byte Order)로 변환
38         serv_adr.sin_port=htons(atoi(argv[1]));		//사용자로부터 입력된 포트 번호를 문자열로 받아 정수로 변환
39
40         if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) ==-1)	//bind2.바인더(정보할당)
41                 error_handling("bind() error");
42         if(listen(serv_sock, 5)==-1)			//listen3.리슨(개통)/동시접속 제한을 5로 할당
43                 error_handling("listen() error");
44
45                 while(1)
46                 {
47                         clnt_adr_sz=sizeof(clnt_adr);
48                         clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);	//accept4.실행/연결요청소켓, 클라이언트연결소켓
49
50                         pthread_mutex_lock(&mutx);	//pthread_mutex_lock한 후에는 해당 임계 영역에 진입
51                         clnt_sock[clnt_cnt++]=clnt_sock;
52                         pthread_mutex_unlock(&mutx);	//작업을 마친 후에는 반드시 뮤텍스를 해제pthread_mutex_unlock
53
54                         pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);	//클라이언트 소켓 형태로 스레드를 생성
55                         pthread_detach(t_id);
56                         printf("Connected client IP:%s \n", inet_ntoa(clnt_adr.sin_addr));
57                 }
58         close(serv_sock);
59         return 0;
60 }
61 void * handle_clnt(void * arg)	//각 클라이언트 소켓 관리,clnt로부터 메시지를 수신하고,다른clnt에게 전달
62 {
63         int clnt_sock=*((int*)arg);
64         int str_len=0, i;
65         char msg[BUF_SIZE];
66
67         while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
68                 send_msg(msg, str_len);
69
70         pthread_mutex_lock(&mutx);
71         for(i=0;i<clnt_cnt;i++)	//remove disconnected client
72         {
73                 if(clnt_sock==clnt_socks[i])
74                 {
75                         while(i++<clnt_cnt-1)
76                                 clnt_socks[i]=clnt_socks[i+1];
77                         break;
78                 }
79         }
80         clnt_cnt--;
81         pthread_mutex_unlock(&mutx);
82         close(clnt_sock);
83         return NULL;
84 }
85 void send_msg(char * msg, int len)		//모든 클라이언트에게 메시지를 보낸다
86 {
87         int i;
88         pthread_mutex_lock(&mutx);
89         for(i=0; i<clnt_cnt; i++)
90                 write(clnt_socks[i], msg, len);
91         pthread_mutex_unlock(&mutx);
92 }
93 void error_handling(char * msg)		//오류 발생시 오류 메시지 출력하고 프로그램 종료
94 {
95         fputs(msg, stderr);
96         fputc('\n', stderr);
97         exit(1);
98 }

//gcc 컴파일 후 ./chat_server <입력>8080(port)
/*chat_clnt.c*/

 1 #include <stdio.h>
 2 #include <stdlib.h>
 3 #include <unistd.h>
 4 #include <string.h>
 5 #include <arpa/inet.h>
 6 #include <sys/socket.h>
 7 #include <pthread.h>
 8
 9 #define BUF_SIZE 100
10 #define NAME_SIZE 20
11
12 void * send_msg(void * arg);
13 void * recv_msg(void * arg);
14 void error_handling(char * msg);
15
16 char name[NAME_SIZE]= "[DEFAULT]";
17 char msg[BUF_SIZE];
18
19 int main(int argc, char *argv[])
20 {
21         int sock;
22         struct sockaddr_in serv_addr;
23         pthread_t snd_thread, rcv_thread;
24         void * thread_return;
25         if(argc!=4){
26                 printf("Usage : %s <IP> <port> <name>\n", argv[0]);
27                 exit(1);
28         }
29         sprintf(name, "[%s]", argv[3]);
30         sock=socket(PF_INET, SOCK_STREAM, 0);
31
32         memset(&serv_addr, 0, sizeof(serv_addr));
33         serv_addr.sin_family=AF_INET;
34         serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
35         serv_addr.sin_port=htons(atoi(argv[2]));
36
37         if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
38                 error_handling("connect(0 error");
39
40         pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
41         pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
42         pthread_join(snd_thread, thread_return);
43         pthread_join(rcv_thread, &thread_return);
44         close(sock);
45         return 0;
46 }
47
48 void * send_msg(void * arg)
49 {
50         int sock=*((int*)arg);
51         char name_msg[NAME_SIZE+BUF_SIZE];
52         while(1)
53         {
54                 fgets(msg, BUF_SIZE, stdin);
55                 if(!strcmp(msg, "q\n")||!strcmp(msg, "Q\n"))
56                 {
57                         close(sock);
58                         exit(0);
59                 }
60                 sprintf(name_msg, "%s, %s", name, msg);
61                 write(sock, name_msg, strlen(name_msg));
62         }
63         return NULL;
64 }
65
66 void * recv_msg(void * arg)
67 {
68         int sock=*((int*)arg);
69         char name_msg[NAME_SIZE+BUF_SIZE];
70         int str_len;
71         while(1)
72         {
73               str_len=read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
74                 if(str_len==-1)
75                         return (void*)-1;
76                 name_msg[str_len]=0;
77                 fputs(name_msg, stdout);
78         }
79         return NULL;
80 }
81
82 void error_handling(char *msg)
83 {
84         fputs(msg, stderr);
85         fputc('\n', stderr);
86         exit(1);
87 }

//gcc 컴파일 후 ./chat_clnt (IP)127.0.0.1 <입력>8080(port) <입력>abc(name)

타PC와 통신(내 PC를 공유포트로 추가)
내pc-운영체제(C:)-프로그램(x86)-VMware-VMware Player
-vmnetcfg-창Virtual Network Editor
-Change Settings-Add Network-NAT Settings

// IP확인 - ipconfig

보안
제어판-Windows Defender 방화벽-고급설정-인바운드 규칙
-새규칙-Port-내PC IP번호-이름입력