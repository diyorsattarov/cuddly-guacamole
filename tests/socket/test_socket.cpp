#include <gtest/gtest.h>
#include <socket/socket.h>

// Define your test fixture
class SocketFixture : public ::testing::Test {
protected:
    Socket masterSocket;
    Socket slaveSocket;

    void SetUp() override {
        // Create and set up the master socket
        ASSERT_TRUE(masterSocket.create());
        ASSERT_TRUE(masterSocket.bind(12345)); // Choose any available port
        ASSERT_TRUE(masterSocket.listen());

        // Create and set up the slave socket
        ASSERT_TRUE(slaveSocket.create());
    }

    void TearDown() override {
        // Close sockets after the test
        masterSocket.close();
        slaveSocket.close();
    }
};

TEST_F(SocketFixture, SocketCommunication) {
    // In this test, the masterSocket listens on port 12345, and the slaveSocket connects to it.
    // The masterSocket sends "Hello, World!" to the slaveSocket, and the slaveSocket displays it.

    // Start the server in a separate thread
    std::thread serverThread([&]() {
        int clientSocket = masterSocket.accept();
        ASSERT_TRUE(clientSocket > 0);

        // Send a message to the connected client
        const char* message = "Hello, World!";
        int bytesSent = send(clientSocket, message, strlen(message), 0);
        ASSERT_EQ(bytesSent, strlen(message));

        // Close the client socket
        close(clientSocket);
    });

    // Connect the client to the server
    ASSERT_TRUE(slaveSocket.connect("127.0.0.1", 12345));

    // Receive the message from the server
    char buffer[1024];
    int bytesRead = recv(slaveSocket.socket_fd, buffer, sizeof(buffer), 0);
    buffer[bytesRead] = '\0'; // Null-terminate the received message

    // Display the received message
    std::cout << "Received: " << buffer << std::endl;

    // Wait for the server thread to finish
    serverThread.join();

    // Check if the received message matches
    ASSERT_STREQ(buffer, "Hello, World!");
}
