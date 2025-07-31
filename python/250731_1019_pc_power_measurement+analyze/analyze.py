import os
import re
import pandas as pd
import matplotlib.pyplot as plt

LOG_FILE = "power_temp_log.csv"
GRAPH_DIR= "graphs"
os.makedirs(GRAPH_DIR, exist_ok=True)

df = pd.read_csv(LOG_FILE, parse_dates=["timestamp"]).set_index("timestamp")

# 1. GPU 개당 전력을 나타냅니다 :)
gp_cols = [c for c in df.columns if c.startswith("gpu") and "power" in c]
if gp_cols:
    df[gp_cols].plot(figsize=(12,5), title="GPU Power Usage (W)")
    plt.ylabel("Watt"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/gpu_power.png"); plt.close()

# 2. GPU 온도
gt_cols = [c for c in df.columns if c.startswith("gpu") and "_temp_c" in c]
if gt_cols:
    df[gt_cols].plot(figsize=(12,5), title="GPU Temperature (°C)")
    plt.ylabel("°C"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/gpu_temp.png"); plt.close()

# 3. CPU 온도 2
if "cpu_temp_c" in df.columns:
    df["cpu_temp_c"].plot(figsize=(12,5), title="CPU Temperature (°C)", color="orange")
    plt.ylabel("°C"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/cpu_temp.png"); plt.close()

# 4. CPU 전력 (W)
if "cpu_power_watt" in df.columns:
    df["cpu_power_watt"].plot(figsize=(12,5),
        title="CPU Power Consumption (W, Rollover-corrected)", color="red")
    plt.ylabel("Watt"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/cpu_power.png"); plt.close()

# 5. GPU 전체 & System Estimate
if "gpu_power_total_watt" in df.columns:
    df["gpu_power_total_watt"].plot(figsize=(12,5), title="Total GPU Power (W)", color="purple")
    plt.ylabel("Watt"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/gpu_total_power.png"); plt.close()

if "system_power_estimate_watt" in df.columns:
    df["system_power_estimate_watt"].plot(figsize=(12,5),
        title="Estimated System Power (CPU+GPU, W)", color="black")
    plt.ylabel("Watt"); plt.grid(True)
    plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/system_power.png"); plt.close()

# 6. 시스템 센서 온도
if "sys_temp_raw" in df.columns:
    pat = re.compile(r'([A-Za-z0-9_: \-/]+):\s*\+?(-?\d+(\.\d+)?)°C')
    sens = {}
    for ts, row in df.iterrows():
        for name,val,_ in pat.findall(str(row["sys_temp_raw"])):
            key = re.sub(r'\W+', '_', name.strip()).lower()
            sens.setdefault(key, {})[ts] = float(val)
    for sensor, data in sens.items():
        pd.Series(data).reindex(df.index,method='nearest')\
            .plot(figsize=(12,5), title=f"{sensor} Temperature (°C)")
        plt.ylabel("°C"); plt.grid(True)
        plt.tight_layout(); plt.savefig(f"{GRAPH_DIR}/sys_sensor_{sensor}.png"); plt.close()