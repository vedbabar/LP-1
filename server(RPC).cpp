#include<iostream>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int sum(int a, int b){
    return a + b;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
  
    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
  
    // Bind and listen
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    cout << "Server waiting for client...\n";
  
    // Accept client (corrected)
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    cout << "Client connected.\n";

    // Read two integers
    int nums[2];
    read(client_fd, nums, sizeof(nums));

    // RPC function call
    int res = sum(nums[0], nums[1]);

    // Send result back
    write(client_fd, &res, sizeof(res));

    cout << "RPC executed: sum(" << nums[0] << ", " << nums[1] << ") = " << res << "\n";

    close(client_fd);
    close(server_fd);

    return 0;
}
