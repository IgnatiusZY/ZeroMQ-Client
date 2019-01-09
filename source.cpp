// Parallel Source Server
// Binds PUSH Socket to tcp://localhost:5557

#include <zmq.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define within(num) (int) ((float) num * random()/(RAND_MAX + 1.0))

int main(int argc, char *argv[]) 
{
    zmq::context_t context(1); // IO Threads
    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.bind("tcp://*:5557");

    std::cout << "Parallel Source Server ON" << std::endl;
    std::cout << "Press Enter when the Workers are good to go... " << std::endl;
    getchar();
    std::cout << "Sending Tasks to Workers..." << std::endl;

    // First Message is "0" to Sink Server to Signal the Start of Batch
    zmq::socket_t sink(context, ZMQ_PUSH);
    sink.connect("tcp://localhost:5558");
    zmq::message_t message(2);
    memcpy(message.data(), "0", 1);
    sink.send(message);

    // Initialize the Random Number Generator
    srandom((unsigned) time(NULL));

    // Send 100 Tasks
    int task_nbr;
    int total_msec = 0;

    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload;
        // Random Workload from 1 to 100 ms
        workload = within(100) + 1;
        total_msec += workload;

        message.rebuild(10);
        memset(message.data(), '\0', 10);
        sprintf((char *)message.data(), "%d", workload);
        sender.send(message);
    }
    std::cout << "Total Expected Cost: " << total_msec << std::endl;
    sleep(1); // Give ZeroMQ Time to Deliver
    return 0;
}