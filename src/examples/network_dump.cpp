#include <iostream>
#include <cstdlib>
#include <array>
#include <memory>

std::string getConnectedSSID() {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen("iwgetid -r", "r"), pclose);

    if (!pipe) {
        printf("popen failed\n");
	}

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Remove trailing newline character if present
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}

int main() {
    std::string ssid = getConnectedSSID();

    if (!ssid.empty()) {
        printf("Not connected to network\n");
		return 1;
    }



    return 0;
}
