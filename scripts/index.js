const os = require("os")
const { SerialPort } = require("serialport");

(async () => {
    var ports = await SerialPort.list();

    console.log(`Found ${ports.length} ports:`, ports);

    var usablePorts = ports.filter(e => e.vendorId == "303A" && e.productId == "1001");

    if (usablePorts.length < 1) return console.log("No usable ports found, exiting!");

    var path = usablePorts[0].path;

    console.log(`opening port ${path} with 115200 baud...`);

    // to be defined in a function
    var sp;
    var loop;

    openPort();

    function openPort() {
        sp = new SerialPort({ path: `\\\\.\\${path}`, baudRate: 115200, autoOpen: false });
        sp.on("open", portOpen);
        setTimeout(()=>{}, 3000); // Small delay to allow the port to open before the script exits
        sp.open();
        sp.on("close", portClose);
    }
    function portOpen() {
        console.log("Port open!");
        loop = setInterval(() => {
            // Get non internal interfaces
            var networkInterfaces = os.networkInterfaces();
            ifs = [];
            Object.keys(networkInterfaces).forEach((ifName, index) => {
                ifs.push(Object.assign({ name: ifName }, networkInterfaces[ifName].find(e=>e.family == "IPv4")));
            });
            var interfaces = ifs.filter((e) => !e.internal);

            // Get memory usage percentage (used/total*100)
            var memPercent = (((os.totalmem() - os.freemem()) / os.totalmem()) * 100).toFixed(2);

            var dataToSend = {
                cpu: 0, //TODO
                mem: memPercent * 1,
                if1: {
                    name: interfaces[0].name,
                    ip: interfaces[0].address,
                },
                if2: {
                    name: interfaces[1].name,
                    ip: interfaces[1].address,
                }
            };
                sp.write(JSON.stringify(dataToSend) + "\n");
            console.log(dataToSend);

        }, 1000)
    }
    function portClose() {
        portOpen();
        clearInterval(loop);
    }
})();