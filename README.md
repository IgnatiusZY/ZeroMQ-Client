# ZeroMQ-Client
ZeroMQ Client
(Send-Receive, Pub-Sub, Pipelining, etc.)

- Workers connect Upstream to the Source and Downstream to the Sink

Sockets
- Create Socket `zmq_socket()` and Delete Socket `zmq_close()`
- Configure Socket `zmq_setsockopt()` & Check Socket `zmq_getsockopt()`
- Plug Socket as Endpoint (Server) `zmq_bind()` & Connect to Socket (Client) `zmq_connect()` - Auto Start Accepting Messages from Socket
- Send (Queue - so I/O Thread can send it ASYNC) Message `zmq_msg_send()` & Receive Message `zme_msg_recv()`

Multiple Incoming and Outgoing Connections to a Socket

- Socket TYPES -> Semantics, Policies for Routing Messages Inwards & Outwards, Queueing, etc. based on Messaging Patterns

- ZeroMQ Socket use Messages (Lengh specified BINARY Data) instead of Stream of BYTES as TCP 
- I/O in BAckground Thread