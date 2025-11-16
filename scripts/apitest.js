import proxmoxApi from "proxmox-api";

process.env.PM_HOST = "127.0.0.1"
process.env.PM_USER = "root@pam"
process.env.PM_PASS = "password"
process.env.PM_PORT = "8006"
process.env.PM_NODENAME = "pve"

import 'dotenv/config' // Import PM info

(async () => {

    // Connect to host
    const proxmox = proxmoxApi({
        host: process.env.PM_HOST,
        username: process.env.PM_USER,
        password: process.env.PM_PASS,
        port: process.env.PM_PORT,
    });

    setInterval(async () => {
        // Get node info from host
        var nodeInfo = await proxmox.nodes.$(process.env.PM_NODENAME).status.$get();

        // Get network interfaces from host
        var networkInterfaces = await proxmox.nodes.$(process.env.PM_NODENAME).network.$get();

        // Show only interfaces with IPs
        networkInterfaces = networkInterfaces.filter(e => e.cidr);

        // Find main network interface (only one interface has a default gateway)
        var mainInterface = networkInterfaces.find(e => e.gateway);

        // Remove main interface from list
        networkInterfaces = networkInterfaces.filter(e => e != mainInterface);

        // Add shorthand for memory and rootfs info
        var memInfo = nodeInfo.memory;
        var rootfsInfo = nodeInfo.rootfs;

        console.log("Main interface", mainInterface.iface, ":", mainInterface.cidr);
        console.log("Other interfaces", networkInterfaces.map(e => e.iface + " : " + e.cidr));

        // Convert cpu to percentage
        console.log("CPU usage:", (nodeInfo.cpu * 100).toFixed(2));

        // Calculate memory and rootfs usage
        console.log("MEM usage:", (memInfo.used / memInfo.total * 100).toFixed(2));
        console.log("rootfs usage:", (rootfsInfo.used / rootfsInfo.total * 100).toFixed(2));

        console.log("uptime:", nodeInfo.uptime);

    }, 1000)
})().catch(console.error);