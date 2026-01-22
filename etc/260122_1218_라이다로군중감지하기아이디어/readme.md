# Crowd Detection with LiDAR

Real-time crowd detection and direction tracking system using LiDAR sensor, ROS2, and Point Cloud processing.

## Overview

This project detects people in crowded environments and tracks their movement direction using 3D LiDAR point cloud data.

## Tech Stack

| Component | Technology | Purpose |
|-----------|------------|---------|
| Middleware | **ROS2 Humble** | Robot Operating System 2 |
| Sensor | **3D LiDAR** | Point cloud data acquisition |
| Processing | **PCL / Open3D** | Point cloud library |
| Detection | **PointPillars / DBSCAN** | People detection algorithm |
| Tracking | **Kalman Filter** | Direction & velocity tracking |
| Language | **Python / C++** | Implementation |

## System Architecture

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           LiDAR Sensor                                   │
│                    (Velodyne / Ouster / Livox)                          │
└─────────────────────────────┬───────────────────────────────────────────┘
                              │ Raw Point Cloud
                              ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                         ROS2 Driver Node                                 │
│                      /velodyne_points (PointCloud2)                     │
└─────────────────────────────┬───────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                      Preprocessing Node                                  │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                  │
│  │ Ground       │  │ ROI          │  │ Downsampling │                  │
│  │ Removal      │→ │ Filtering    │→ │ (Voxel Grid) │                  │
│  └──────────────┘  └──────────────┘  └──────────────┘                  │
└─────────────────────────────┬───────────────────────────────────────────┘
                              │ Filtered Point Cloud
                              ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                      Detection Node                                      │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                  │
│  │ Clustering   │  │ Human        │  │ Bounding     │                  │
│  │ (DBSCAN)     │→ │ Classification│→ │ Box Gen     │                  │
│  └──────────────┘  └──────────────┘  └──────────────┘                  │
└─────────────────────────────┬───────────────────────────────────────────┘
                              │ Detected People
                              ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                      Tracking Node                                       │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                  │
│  │ Data         │  │ Kalman       │  │ Direction    │                  │
│  │ Association  │→ │ Filter       │→ │ Estimation   │                  │
│  └──────────────┘  └──────────────┘  └──────────────┘                  │
└─────────────────────────────┬───────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                      Output Topics                                       │
│  /crowd/detections    /crowd/tracks    /crowd/directions    /crowd/viz │
└─────────────────────────────────────────────────────────────────────────┘
```

## ROS2 Topics

### Input Topics

| Topic | Type | Description |
|-------|------|-------------|
| `/velodyne_points` | sensor_msgs/PointCloud2 | Raw LiDAR point cloud |
| `/odom` | nav_msgs/Odometry | Robot odometry (optional) |

### Output Topics

| Topic | Type | Description |
|-------|------|-------------|
| `/crowd/detections` | vision_msgs/Detection3DArray | Detected people with 3D bounding boxes |
| `/crowd/tracks` | crowd_msgs/TrackedPersonArray | Tracked people with IDs |
| `/crowd/directions` | crowd_msgs/DirectionArray | Movement direction vectors |
| `/crowd/count` | std_msgs/Int32 | Total people count |
| `/crowd/visualization` | visualization_msgs/MarkerArray | RViz visualization |

## Custom Messages

### TrackedPerson.msg

```
# crowd_msgs/msg/TrackedPerson.msg
uint32 id                          # Unique tracking ID
geometry_msgs/Point position       # Current position (x, y, z)
geometry_msgs/Vector3 velocity     # Velocity vector (vx, vy, vz)
float32 speed                      # Speed in m/s
float32 direction                  # Direction angle in radians
geometry_msgs/Vector3 dimensions   # Bounding box size (w, h, d)
float32 confidence                 # Detection confidence [0-1]
builtin_interfaces/Time first_seen # First detection time
builtin_interfaces/Time last_seen  # Last detection time
```

### Direction.msg

```
# crowd_msgs/msg/Direction.msg
uint32 person_id                   # Associated person ID
geometry_msgs/Point position       # Current position
float32 direction_angle            # Movement direction (radians, 0=forward)
float32 speed                      # Movement speed (m/s)
string direction_label             # "forward", "backward", "left", "right", "stationary"
```

## Algorithms

### 1. Ground Removal (RANSAC)

```python
def remove_ground(points, distance_threshold=0.2, num_iterations=100):
    """
    Remove ground plane using RANSAC algorithm
    """
    import open3d as o3d
    
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(points)
    
    # RANSAC plane segmentation
    plane_model, inliers = pcd.segment_plane(
        distance_threshold=distance_threshold,
        ransac_n=3,
        num_iterations=num_iterations
    )
    
    # Remove ground points
    non_ground = pcd.select_by_index(inliers, invert=True)
    return np.asarray(non_ground.points)
```

### 2. Clustering (DBSCAN)

```python
def cluster_points(points, eps=0.5, min_samples=10):
    """
    Cluster point cloud using DBSCAN
    """
    from sklearn.cluster import DBSCAN
    
    clustering = DBSCAN(eps=eps, min_samples=min_samples).fit(points)
    labels = clustering.labels_
    
    clusters = []
    for label in set(labels):
        if label == -1:  # Noise
            continue
        cluster_points = points[labels == label]
        clusters.append(cluster_points)
    
    return clusters
```

### 3. Human Classification

```python
def is_human(cluster_points):
    """
    Classify cluster as human based on geometric features
    """
    # Calculate bounding box
    min_bound = cluster_points.min(axis=0)
    max_bound = cluster_points.max(axis=0)
    dimensions = max_bound - min_bound
    
    width, depth, height = dimensions[0], dimensions[1], dimensions[2]
    
    # Human geometric constraints
    MIN_HEIGHT = 0.8   # meters
    MAX_HEIGHT = 2.2
    MIN_WIDTH = 0.2
    MAX_WIDTH = 1.0
    MIN_DEPTH = 0.2
    MAX_DEPTH = 1.0
    
    if MIN_HEIGHT <= height <= MAX_HEIGHT:
        if MIN_WIDTH <= width <= MAX_WIDTH:
            if MIN_DEPTH <= depth <= MAX_DEPTH:
                return True
    return False
```

### 4. Kalman Filter Tracking

```python
import numpy as np

class KalmanTracker:
    def __init__(self, initial_position):
        # State: [x, y, z, vx, vy, vz]
        self.state = np.array([
            initial_position[0], initial_position[1], initial_position[2],
            0.0, 0.0, 0.0
        ])
        
        # State transition matrix
        self.F = np.array([
            [1, 0, 0, 1, 0, 0],  # x = x + vx*dt
            [0, 1, 0, 0, 1, 0],  # y = y + vy*dt
            [0, 0, 1, 0, 0, 1],  # z = z + vz*dt
            [0, 0, 0, 1, 0, 0],  # vx = vx
            [0, 0, 0, 0, 1, 0],  # vy = vy
            [0, 0, 0, 0, 0, 1],  # vz = vz
        ])
        
        # Measurement matrix (we only observe position)
        self.H = np.array([
            [1, 0, 0, 0, 0, 0],
            [0, 1, 0, 0, 0, 0],
            [0, 0, 1, 0, 0, 0],
        ])
        
        # Covariance matrices
        self.P = np.eye(6) * 1.0   # State covariance
        self.Q = np.eye(6) * 0.1   # Process noise
        self.R = np.eye(3) * 0.5   # Measurement noise
    
    def predict(self, dt=0.1):
        self.F[0, 3] = dt
        self.F[1, 4] = dt
        self.F[2, 5] = dt
        
        self.state = self.F @ self.state
        self.P = self.F @ self.P @ self.F.T + self.Q
        
        return self.state[:3]
    
    def update(self, measurement):
        y = measurement - self.H @ self.state
        S = self.H @ self.P @ self.H.T + self.R
        K = self.P @ self.H.T @ np.linalg.inv(S)
        
        self.state = self.state + K @ y
        self.P = (np.eye(6) - K @ self.H) @ self.P
        
        return self.state[:3]
    
    def get_velocity(self):
        return self.state[3:6]
    
    def get_direction(self):
        vx, vy = self.state[3], self.state[4]
        return np.arctan2(vy, vx)
    
    def get_speed(self):
        return np.linalg.norm(self.state[3:6])
```

### 5. Direction Classification

```python
def classify_direction(angle_rad, speed, speed_threshold=0.1):
    """
    Classify movement direction based on angle
    
    Angle convention:
        0° = Forward (+X)
        90° = Left (+Y)
        180° = Backward (-X)
        -90° = Right (-Y)
    """
    if speed < speed_threshold:
        return "stationary"
    
    import math
    angle_deg = math.degrees(angle_rad)
    
    if -45 <= angle_deg < 45:
        return "forward"
    elif 45 <= angle_deg < 135:
        return "left"
    elif angle_deg >= 135 or angle_deg < -135:
        return "backward"
    else:  # -135 <= angle_deg < -45
        return "right"
```

## Project Structure

```
260116_1211_[dtr]crowd_detect_with_lidar/
├── README.md
├── crowd_detect_ws/                    # ROS2 Workspace
│   └── src/
│       ├── crowd_msgs/                 # Custom messages
│       │   ├── msg/
│       │   │   ├── TrackedPerson.msg
│       │   │   ├── TrackedPersonArray.msg
│       │   │   ├── Direction.msg
│       │   │   └── DirectionArray.msg
│       │   ├── CMakeLists.txt
│       │   └── package.xml
│       │
│       ├── crowd_detection/            # Detection package
│       │   ├── crowd_detection/
│       │   │   ├── __init__.py
│       │   │   ├── preprocessing_node.py
│       │   │   ├── detection_node.py
│       │   │   ├── tracking_node.py
│       │   │   └── visualization_node.py
│       │   ├── launch/
│       │   │   └── crowd_detection.launch.py
│       │   ├── config/
│       │   │   └── params.yaml
│       │   ├── setup.py
│       │   └── package.xml
│       │
│       └── crowd_detection_cpp/        # C++ version (optional)
│           ├── src/
│           │   ├── preprocessing_node.cpp
│           │   └── detection_node.cpp
│           ├── include/
│           ├── CMakeLists.txt
│           └── package.xml
│
├── models/                             # Pre-trained models
│   └── pointpillars/
│
├── data/                               # Sample data
│   └── rosbags/
│
└── scripts/                            # Utility scripts
    ├── record_data.sh
    └── evaluate.py
```

## Configuration

### params.yaml

```yaml
crowd_detection:
  ros__parameters:
    # LiDAR settings
    lidar_topic: "/velodyne_points"
    frame_id: "velodyne"
    
    # Preprocessing
    ground_removal:
      enabled: true
      distance_threshold: 0.2
      ransac_iterations: 100
    
    roi_filter:
      enabled: true
      x_min: -20.0
      x_max: 20.0
      y_min: -20.0
      y_max: 20.0
      z_min: -0.5
      z_max: 3.0
    
    voxel_grid:
      enabled: true
      leaf_size: 0.05
    
    # Clustering
    clustering:
      algorithm: "dbscan"  # "dbscan" or "euclidean"
      eps: 0.5
      min_samples: 10
    
    # Human classification
    human_filter:
      min_height: 0.8
      max_height: 2.2
      min_width: 0.2
      max_width: 1.0
      min_points: 50
    
    # Tracking
    tracking:
      max_age: 10              # Frames before track deletion
      min_hits: 3              # Hits before track confirmation
      iou_threshold: 0.3
      max_distance: 2.0        # Max association distance (m)
    
    # Direction
    direction:
      speed_threshold: 0.1     # m/s threshold for "stationary"
      smoothing_window: 5      # Frames for direction smoothing
    
    # Output
    publish_rate: 10.0         # Hz
    visualization: true
```

## Launch File

```python
# launch/crowd_detection.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('crowd_detection'),
        'config',
        'params.yaml'
    )
    
    return LaunchDescription([
        # Preprocessing node
        Node(
            package='crowd_detection',
            executable='preprocessing_node',
            name='preprocessing_node',
            parameters=[config],
            output='screen'
        ),
        
        # Detection node
        Node(
            package='crowd_detection',
            executable='detection_node',
            name='detection_node',
            parameters=[config],
            output='screen'
        ),
        
        # Tracking node
        Node(
            package='crowd_detection',
            executable='tracking_node',
            name='tracking_node',
            parameters=[config],
            output='screen'
        ),
        
        # Visualization node
        Node(
            package='crowd_detection',
            executable='visualization_node',
            name='visualization_node',
            parameters=[config],
            output='screen'
        ),
        
        # RViz
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', os.path.join(
                get_package_share_directory('crowd_detection'),
                'config', 'crowd_detection.rviz'
            )]
        ),
    ])
```

## Getting Started

### Prerequisites

```bash
# ROS2 Humble
sudo apt install ros-humble-desktop

# Point Cloud Library
sudo apt install libpcl-dev ros-humble-pcl-conversions

# Python dependencies
pip install open3d numpy scipy scikit-learn
```

### Build

```bash
cd crowd_detect_ws
colcon build --symlink-install
source install/setup.bash
```

### Run

```bash
# Launch all nodes
ros2 launch crowd_detection crowd_detection.launch.py

# Or run individual nodes
ros2 run crowd_detection preprocessing_node
ros2 run crowd_detection detection_node
ros2 run crowd_detection tracking_node
```

### Test with ROS Bag

```bash
# Play recorded data
ros2 bag play data/rosbags/crowd_sample/

# Record new data
ros2 bag record /velodyne_points /crowd/detections /crowd/directions
```

## Visualization (RViz2)

Add these displays in RViz2:

| Display Type | Topic | Description |
|--------------|-------|-------------|
| PointCloud2 | /velodyne_points | Raw LiDAR data |
| PointCloud2 | /crowd/filtered_points | Preprocessed points |
| MarkerArray | /crowd/visualization | Bounding boxes & arrows |

## Performance

| Metric | Target | Notes |
|--------|--------|-------|
| Detection Rate | 10+ Hz | Real-time processing |
| Detection Range | 0.5 - 30m | Depends on LiDAR |
| Accuracy | > 90% | In typical crowd density |
| Tracking ID Switch | < 5% | Stable tracking |

## References

- [PointPillars Paper](https://arxiv.org/abs/1812.05784)
- [ROS2 Documentation](https://docs.ros.org/en/humble/)
- [PCL Library](https://pointclouds.org/)
- [Open3D](http://www.open3d.org/)

## License

MIT License
