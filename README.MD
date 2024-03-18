# PegaScale
PegaScale is a Nintendo Switch browser exploit launcher/executor based on [PegaSwitch](https://github.com/reswitched/pegaswitch) and loosely on the now defunct [PegaScape](https://github.com/noahc3/PegaScape).

PegaScale allows for warmboot exploitation of the Nintendo Switch browser on firmware versions 1.0.0 - 4.1.0. It does so by utilizing the Switch Captive Portal page which exploits a javascript vulnerability in order to execute arbitrary code.

The main reason for the existence of this was the shutdown of PegaScape and the unmaintainability of NodeJS versioning.

PegaScale uses a custom [Drogon](https://github.com/drogonframework/drogon) based webserver to be fast, efficient and maintainable.

### Caveats
Unfortunately we still depend on javascript on the frontend in order to execute the exploitation. The exploitation framework SploitCore is written as a NodeJS package which then has to be turned into usable frontend code. For this [Browserify](https://browserify.org/) is used. Unfortunately there is no simple way to do this step without a full NodeJS installation, however it keeps NodeJS only necessary as a build step rather than as an executor engine as well.

Due to wanting to avoid too much complexity there is no DNS server built-into the program. A secondary program is built along with the main one. This program is a miniature DNS server [microdns](https://www.samiam.org/software/microdns.html) that responds with a single IP to all DNS queries which should suit the needs of most people wishing to host this themselves. Of course one can simply forgo executing this program and can setup any other DNS server for this task.

## Building
To build you need the following requirements:
```
nodejs npm gcc cmake make git g++ libjsoncpp-dev uuid-dev zlib1g-dev
```

Clone the repository:
```
git clone https://github.com/meganukebmp/PegaScale.git
cd PegaScale
```

Initialize CMake build:
```
cmake -B build
```

Build it:
```
cmake --build build
```

## Running PegaScale
Inside the `build` directory you will find the `PegaScale` binary as well as the `www` directory. If planning to move these, make sure they are together.


Running:
```
sudo ./PegaScale
```

## Running MicroDNS
To run the built DNS server and redirect all traffic to your machine (in order to trick the Switch into connecting to your page) inside the `build/microdns` directory run the `microdns` binary like so:
```
sudo ./microdns {IP to give to clients as response}
```

Where the IP you want to give out being your public IP address if hosting over the internet or your local address (not localhost) if hosting on a LAN
