// based on: https://docs.arduino.cc/tutorials/mkr-nb-1500/nb-web-client/

#include <MKRNB.h>

// TODO:
const char PIN_CODE[] = "0000";

NBClient client;
GPRS gprs;
NB nbAccess;

char server[] = "154.62.108.192";
// from: https://github.com/Koalananasv2/mebc_energy_monitoring?tab=readme-ov-file#push-a-monitoring-command-using
char path[] = "/monitoringdata";
int port = 3001;

const int BUFFER_SIZE = 2048;
char buffer[BUFFER_SIZE] = "";

void setup() {
    Serial.begin(9600);

    bool connected = false;

    while (!connected) { 
        // initialize lte devices
        if ((nbAccess.begin(PIN_CODE) == NB_READY) && (gprs.attachGPRS() == GPRS_READY)) {
            connected = true;
            break;
        }

        delay(1000);
    }

    // connect to telemetry server, re-attempting every second
    while (!client.connect(server, port)) {
        delay(1000);
    }
}

void sendData() {
    client.print("POST ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Content-Type: application/json");
    client.println();
    client.println(buffer);
    client.println();
}

int receiveData() {
    int current_position = 0;
    char current_character = 0;
    
    do {
        current_character = Serial.read();
        buffer[current_position] = current_character;
        current_position++;
    } while (current_character != 0 && current_position < BUFFER_SIZE);

    if (current_position == BUFFER_SIZE && current_character != 0) {
        return 0;
    }

    return current_position;
}

void loop() {
    if (receiveData() != 0) {
        sendData();
    }

    if (!client.connected()) {
        while (!client.connect(server, port)) {
            delay(1000);
        }
    }
}
