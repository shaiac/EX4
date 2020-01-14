#include <iostream>
#include "StringReverser.h"
#include "MyClientHandler.h"
#include "SerialServer.h"

int main() {
    MyClientHandler *mch = new MyClientHandler();
    MySerialServer *mss = new MySerialServer();
    mss->open(7767, mch);

    return 0;
}
