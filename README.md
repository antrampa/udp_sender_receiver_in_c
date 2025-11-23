Compile with gcc in Windows:


UDP Message Receiver 

gcc udp_receiver.c -o udp_receiver -lws2_32

To run:
Go to the directory, open a CMD terminal and run 
./udp_receiver <port>

Example 
./udp_receiver 5000


UDP Message Sender 

gcc udp_sender.c -o udp_sender -lws2_32

To run:
Go to the directory, open a CMD terminal and run 
./udp_sender <local_ip_address> <port> <Message> 

Example 
./udp_sender 192.168.1.2 5000 "Hello Lil bro <den exo na fao dose moy lefta na fao :p>"


