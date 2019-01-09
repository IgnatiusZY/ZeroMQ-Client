// Parallel Sink Server
// Binds PULL Socket to tcp://localhost:5558

#include <zmq.hpp>
#include <iostream>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]) 
{
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.bind("tcp://*:5558");

    std::cout << "Parallel Sink Server ON" << std::endl;

    // Wait for Start of Batch
    zmq::message_t message;
    receiver.recv(&message);

    // Start our Clock Now
    struct timeval tstart;
    gettimeofday(&tstart, NULL);

    // Process 100 Confirmations
    int task_nbr;
    int total_msec = 0;

    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        receiver.recv(&message);
        if ((task_nbr / 10) * 10 == task_nbr)
            std::cout << ":" << std::flush;
        else 
            std::cout << "." << std::flush;
    }

    struct timeval tend, tdiff;
    gettimeofday(&tend, NULL);

    if (tend.tv_usec < tstart.tv_usec) {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
        tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
    } else {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
        tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
    }
    total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000; // Convert to ms
    std::cout << "\nTotal Elapsed Time: " << total_msec << " msec" << std::endl;
    return 0;
}