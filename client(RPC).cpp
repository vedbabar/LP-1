#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    int nums[2] = {a, b};

    write(sockfd, nums, sizeof(nums));

    int result;
    read(sockfd, &result, sizeof(result));
    cout << "Result from remote procedure: " << result << "\n";

    close(sockfd);
    return 0;
}
