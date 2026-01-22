# Autonomous Manufacturing Sensor Data Collection System

## Overview

This project is a **sensor data collection and management system** for autonomous manufacturing environments. It provides a toolkit for integrating HK Vision industrial cameras and Hesai LiDAR sensors based on ROS2 to collect, store, and visualize data.

---

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                         Sensor Layer                            │
├─────────────────────────────┬───────────────────────────────────┤
│     HK Vision Camera        │         Hesai LiDAR               │
│     (192.168.1.x)           │        (192.168.1.101)            │
└─────────────────────────────┴───────────────────────────────────┘
                │                              │
                ▼                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                        ROS2 Layer                                │
├─────────────────────────────┬───────────────────────────────────┤
│   /hk_camera/rgb            │         /lidar_points             │
│   (sensor_msgs/Image)       │    (sensor_msgs/PointCloud2)      │
└─────────────────────────────┴───────────────────────────────────┘
                │                              │
                ▼                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                      Data Storage Layer                          │
├──────────────────┬──────────────────┬───────────────────────────┤
│   ROS2 Bag (db3) │    MP4 Video     │   Visualization (rviz2)   │
└──────────────────┴──────────────────┴───────────────────────────┘
```

---

## Project Structure

```
260117_1224/
├── 250905_1318_hk+rosboard/          # HK Camera + ROSBoard workspace
├── 250906_1513_hessai_ros2/          # Hesai LiDAR ROS2 driver
├── 260109_2018_FIX_Ethernet_Profiling/ # Ethernet IP fixing script
├── 260110_2117_hk/                   # HK Camera launch scripts
├── 260111_2118_hessai/               # Hesai LiDAR launch scripts
├── 260112_2132_hk+db3/               # Camera data bag recording
├── 260113_2133_hessai+db3/           # LiDAR data bag recording
├── 260114_2237_hk+hessai-db3/        # Camera+LiDAR combined bag recording
├── 260115_2242_hk+ffmpeg[failed]/    # FFmpeg attempt (failed)
├── 260116_2308_hk+mp4/               # Camera MP4 recording
└── readme.md                         # This document
```

---

## 1. Network Configuration (`260109_2018_FIX_Ethernet_Profiling/`)

### 1.1 Purpose
Resolves the issue where ethernet interface IP addresses change after system reboot.

### 1.2 Network Configuration

| Interface | MAC Address | IP Address | Gateway | Role |
|-----------|-------------|------------|---------|------|
| eno1 | 11:11:11:11:11:11 | 192.168.100.105/24 | 192.168.100.1 | Main Internet |
| enx588694fba08f | 55:55:55:55:55:55 | 192.168.1.105/24 | 192.168.1.1 | Sensor Connection |

### 1.3 Usage

```bash
cd /home/keep/glory/260109_2018_FIX_Ethernet_Profiling
chmod +x fix_ethernet.sh
sudo ./fix_ethernet.sh
```

### 1.4 Auto-run on Boot

```bash
# Create systemd service
sudo nano /etc/systemd/system/fix-ethernet.service
```

Service file contents:
```ini
[Unit]
Description=Fix Ethernet Interface IP Addresses
After=network.target NetworkManager.service
Wants=NetworkManager.service

[Service]
Type=oneshot
ExecStart=/home/keep/glory/260109_2018_FIX_Ethernet_Profiling/fix_ethernet.sh
RemainAfterExit=yes
User=root

[Install]
WantedBy=multi-user.target
```

Enable service:
```bash
sudo systemctl daemon-reload
sudo systemctl enable fix-ethernet.service
sudo systemctl start fix-ethernet.service
```

---

## 2. Hesai LiDAR Driver (`250906_1513_hessai_ros2/`)

### 2.1 Hardware Information
- **LiDAR IP**: 192.168.1.101
- **Host IP**: 192.168.1.105
- **Project Path**: `/home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0`

### 2.2 Published Topics

| Topic | Message Type | Description | Rate |
|-------|--------------|-------------|------|
| `/lidar_points` | sensor_msgs/msg/PointCloud2 | Point cloud data | ~10Hz |
| `/lidar_packets` | - | LiDAR raw packets | - |

### 2.3 Running the Driver (3 terminals required)

#### Terminal 1: Driver Execution
```bash
cd /home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
source install/setup.bash
ros2 run hesai_ros_driver hesai_ros_driver_node
```

#### Terminal 2: TF Transform Publishing (Required)
```bash
cd /home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
source install/setup.bash
ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 map hesai_lidar
```

#### Terminal 3: rviz2 Visualization
```bash
cd /home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
source install/setup.bash
rviz2 -d rviz/rviz2.rviz
```

### 2.4 Convenience Scripts

```bash
# Start
cd /home/keep/glory/260111_2118_hessai
./start_hesai_lidar.sh

# Stop
./stop_hesai_lidar.sh
```

### 2.5 Configuration File
- **Location**: `config/config.yaml`
- **Key Settings**:
  - `source_type: 1` (real-time connection mode)
  - `lidar_ip: 192.168.1.101`
  - `host_ip: 192.168.1.105`
  - `frame_id: hesai_lidar`

---

## 3. HK Vision Camera (`260110_2117_hk/`)

### 3.1 Published Topics

| Topic | Message Type | Description |
|-------|--------------|-------------|
| `/hk_camera/rgb` | sensor_msgs/msg/Image | RGB image data |

### 3.2 Running the Camera

```bash
# Start
cd /home/keep/glory/260110_2117_hk
./start_camera.sh

# Stop
./stop_camera.sh
```

### 3.3 tmux Session Management

```bash
# List sessions
tmux ls

# Attach to session
tmux attach -t hk_camera

# Detach from session (keep running in background)
# Ctrl+B, D

# Kill session
tmux kill-session -t hk_camera
```

---

## 4. Data Recording

### 4.1 Recording Options Comparison

| Folder | Data | Format | Split Interval |
|--------|------|--------|----------------|
| `260112_2132_hk+db3/` | Camera only | ROS2 Bag (db3) | 1 min |
| `260113_2133_hessai+db3/` | LiDAR only | ROS2 Bag (db3) | 1 min |
| `260114_2237_hk+hessai-db3/` | Camera + LiDAR | ROS2 Bag (db3) | 1 min |
| `260116_2308_hk+mp4/` | Camera | MP4 Video | 1 min |

### 4.2 Camera + LiDAR Combined Recording (`260114_2237_hk+hessai-db3/`)

#### Prerequisites
```bash
# 1. Start HK Camera
cd /home/keep/glory/260110_2117_hk
./start_camera.sh

# 2. Start Hesai LiDAR driver
cd /home/keep/glory/260111_2118_hessai
./start_hesai_lidar.sh

# 3. Verify topics
ros2 topic list | grep -E "hk_camera|lidar"
```

#### Start/Stop Recording
```bash
# Start
cd /home/keep/glory/260114_2237_hk+hessai-db3
./start_bag_record.sh

# Check progress
tmux attach -t hk_hesai_bag

# Stop
./stop_bag_record.sh
```

#### Saved File Format
```
hk_hesai_YYYYMMDD_HHMMSS/
├── metadata.yaml
└── hk_hesai_YYYYMMDD_HHMMSS_0.db3
```

### 4.3 MP4 Video Recording (`260116_2308_hk+mp4/`)

```bash
# Start
cd /home/keep/glory/260116_2308_hk+mp4
./start_mp4_record.sh

# Stop
./stop_mp4_record.sh

# Check saved files
ls -lh *.mp4
```

---

## 5. Data Playback

### 5.1 ROS2 Bag Playback

#### Environment Setup
```bash
# HK Camera workspace
cd /home/keep/glory/250905_1318_hk+rosboard
source install/setup.bash

# Hesai LiDAR workspace
cd /home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
source install/setup.bash
```

#### Playback Commands
```bash
# Play from directory
ros2 bag play /home/keep/glory/260114_2237_hk+hessai-db3/hk_hesai_20260116_223730

# Play individual .db3 file
ros2 bag play /home/keep/glory/260114_2237_hk+hessai-db3/hk_hesai_20260116_223730/hk_hesai_20260116_223730_0.db3

# Loop playback
ros2 bag play <bag_file> --loop

# Speed control
ros2 bag play <bag_file> --rate 0.5  # 0.5x speed
ros2 bag play <bag_file> --rate 2.0  # 2x speed

# Play specific topics only
ros2 bag play <bag_file> --topics /lidar_points
```

### 5.2 rviz2 Visualization During Playback

**Important**: TF publishing is **required** when playing bag files.

```bash
# Terminal 1: TF Publishing (Required!)
cd /home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
source install/setup.bash
ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 map hesai_lidar

# Terminal 2: Bag Playback
ros2 bag play <bag_file> --loop

# Terminal 3: rviz2
rviz2 -d rviz/rviz2.rviz
```

### 5.3 Bag File Information

```bash
ros2 bag info <bag_directory>
```

Example output:
```
Files:             hk_hesai_20260116_223730_0.db3
Bag size:          125.3 MiB
Duration:          60.0s
Messages:          1200
Topic information:
  Topic: /hk_camera/rgb | Type: sensor_msgs/msg/Image | Count: 600
  Topic: /lidar_points | Type: sensor_msgs/msg/PointCloud2 | Count: 600
```

### 5.4 MP4 File Playback

```bash
# Play with VLC
vlc /home/keep/glory/260116_2308_hk+mp4/hk_camera_20260116_230800.mp4

# Play with ffplay
ffplay /home/keep/glory/260116_2308_hk+mp4/hk_camera_20260116_230800.mp4
```

---

## 6. Topic and Status Verification

### 6.1 List Topics
```bash
ros2 topic list
```

### 6.2 Topic Information
```bash
ros2 topic info /lidar_points
ros2 topic info /hk_camera/rgb
```

### 6.3 Topic Publishing Rate
```bash
ros2 topic hz /lidar_points
ros2 topic hz /hk_camera/rgb
```

### 6.4 TF Transform Verification
```bash
ros2 topic echo /tf_static --once
```

### 6.5 Data Sample Check
```bash
ros2 topic echo /lidar_points --once
ros2 topic echo /hk_camera/rgb --once
```

---

## 7. Troubleshooting

### 7.1 Library Path Issue
**Error**: `libsource_lib.so: cannot open shared object file`

**Solution**:
```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/hesai_ros_driver/src/driver/HesaiLidar_SDK_2.0/libhesai
```

### 7.2 TF Frame Issue
**Error**: "No tf data" in rviz2 or point cloud not visible

**Solution**:
1. Verify TF publishing: `ros2 topic echo /tf_static --once`
2. Set Fixed Frame to `hesai_lidar`
3. Restart TF publisher

### 7.3 Topics Not Publishing
**Solution**:
1. Verify driver is running: `ps aux | grep hesai_ros_driver_node`
2. Check network connection: `ping 192.168.1.101`
3. Verify config.yaml settings
4. Restart the driver

### 7.4 "Message Filter dropping message" Error
**Cause**: TF transform is missing, rviz2 cannot process messages

**Solution**: TF must be published before playing bag files.

---

## 8. Quick Reference

### Start Full System

```bash
# 1. Network configuration (once after reboot)
cd /home/keep/glory/260109_2018_FIX_Ethernet_Profiling
sudo ./fix_ethernet.sh

# 2. Start HK Camera
cd /home/keep/glory/260110_2117_hk
./start_camera.sh

# 3. Start Hesai LiDAR
cd /home/keep/glory/260111_2118_hessai
./start_hesai_lidar.sh

# 4. Start data recording
cd /home/keep/glory/260114_2237_hk+hessai-db3
./start_bag_record.sh
```

### Stop Full System

```bash
# 1. Stop data recording
cd /home/keep/glory/260114_2237_hk+hessai-db3
./stop_bag_record.sh

# 2. Stop Hesai LiDAR
cd /home/keep/glory/260111_2118_hessai
./stop_hesai_lidar.sh

# 3. Stop HK Camera
cd /home/keep/glory/260110_2117_hk
./stop_camera.sh
```

### Force Kill All Processes

```bash
pkill -9 -f hesai_ros_driver_node
pkill -9 -f static_transform_publisher
pkill -9 -f rviz2
tmux kill-server
```

---

## 9. Path Summary

| Component | Path |
|-----------|------|
| HK Camera Workspace | `/home/keep/glory/250905_1318_hk+rosboard` |
| Hesai LiDAR Project | `/home/keep/glory/250906_1513_hessai_ros2/HesaiLidar_ROS_2.0` |
| Ethernet IP Fixing | `/home/keep/glory/260109_2018_FIX_Ethernet_Profiling` |
| HK Camera Launch | `/home/keep/glory/260110_2117_hk` |
| Hesai LiDAR Launch | `/home/keep/glory/260111_2118_hessai` |
| Combined Bag Recording | `/home/keep/glory/260114_2237_hk+hessai-db3` |
| MP4 Recording | `/home/keep/glory/260116_2308_hk+mp4` |

---

## 10. Environment Information

- **OS**: Ubuntu (ROS2 Humble recommended)
- **ROS2 Version**: Humble
- **Sensors**:
  - Hesai LiDAR (IP: 192.168.1.101)
  - HK Vision Industrial Camera
- **Network**:
  - Main Internet: 192.168.100.x subnet
  - Sensor Connection: 192.168.1.x subnet
