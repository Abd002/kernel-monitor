# Kernel-User Interface for Kernel Internals Visualization

## Project Overview
`kernel-monitor` is a project designed to provide a user-friendly interface for visualizing key Linux kernel internals. By developing a Linux kernel module and a user-space application, this project enables the collection and display of critical system statistics such as CPU usage, memory details, and task information, making it easier for developers and system administrators to monitor system health and performance in real-time.

## Project Goals
- **Kernel Module**: Develop a Linux kernel module to gather important kernel internals data such as CPU usage, memory statistics, and task management details.
- **Data Transfer Mechanism**: Implement a mechanism for passing collected kernel data to a user-space application efficiently.
- **User-Space Application**: Create a user-space application that receives the kernel data, processes it, and presents it in a graphical or textual format, offering insights into system performance.

## Features
- **Kernel Internals Data Collection**:
  - CPU usage statistics
  - Memory usage information (e.g., free, used, cached memory)
  - Task/process details (e.g., active tasks, resource consumption)
  
- **User-Friendly Visualization**: 
  - Display kernel data in an organized and easily understandable format
  - Potential for graphical visualizations or textual output with filtering and search capabilities
  
- **Real-time Monitoring**: Continuous updates of kernel data for live system monitoring.

## Prerequisites
1. A Linux-based system (e.g., Ubuntu, CentOS)
2. Basic understanding of Linux kernel modules and C programming
3. Development tools such as `gcc`, `make`, and `kernel headers` (ensure they are installed on your system)

## Installation and Running the Program

Follow these steps to install and run the `kernel-monitor` project:

### Step 1: Clone the Project
Clone the project repository to your system:
```bash
git clone <repository_url> kernel-monitor
cd kernel-monitor
```

### Step 2: Run the Setup Script
Run the `run` script to set up the environment:
```bash
./run
```

### Step 3: Insert the Kernel Module
Insert the kernel module to begin data collection:
```bash
insmod /root/kernel_module.ko
```

### Step 4: Create the Device Node
Create the device node required for communication with the kernel module:
```bash
mknod /dev/kernel_tasks c 235 0
```

### Step 5: Run the User-Space Application
Run the user-space application to start monitoring the kernel data:
```bash
/root/a.out
```

After completing these steps, the program will begin monitoring and visualizing key kernel data such as CPU usage, memory statistics, and task information in real-time.

```

In this `README.md`, I've included the detailed steps (from cloning the repository to running the program) under the "Installation and Running the Program" section. Make sure to replace `<repository_url>` with the actual repository URL if necessary.
