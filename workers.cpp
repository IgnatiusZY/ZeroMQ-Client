// Parallel task Workers
// Connect to Source Server via tcp://localhost:5557
// PULL
// Connect to Sink Server via   tcp://localhost:5558
// PUSH

#include <zhelpers.hpp>
#include <string>

int main(int argc, char *argv[])
{
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");

    std::cout << "Parallel Workers ON" << std::endl;

    while(1) {
        int workload;
        zmq::message_t message;

        receiver.recv(&message);
        std::string smessage(static_cast<char*>(message.data()), message.size());

        std::istringstream iss(smessage);
        iss >> workload;

        // Do the Work
        s_sleep(workload);
        /*
        static void
        s_sleep (int msecs)
        {
        #if (defined (WIN32))
            Sleep (msecs);
        #else
            struct timespec t;
            t.tv_sec = msecs / 1000;
            t.tv_nsec = (msecs % 1000) * 1000000;
            nanosleep (&t, NULL);
        #endif
        */

       // Send Results to Sink
       message.rebuild();
       sender.send(message);

       // Simple Progress Indicator for Viewer
       std::cout << "." << std::flush;
    }
    return 0;
}