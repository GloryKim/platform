import os
os.environ["OPENBLAS_NUM_THREADS"] = "1"  # NumPy 스레드 폭발 방지

import torch
import threading
import time
import subprocess
import psutil
import numpy as np
from datetime import datetime

LOG_FILE = "power_temp_log.csv"

def gpu_stress(device):
    if not torch.cuda.is_available():
        print(f"CUDA GPU is not available for {device}")
        return
    print(f"[GPU Stress] Starting stress on {device}")
    a = torch.randn(15000, 15000, device=device) #15000,15000, 이건 gpu 메모리 별로 확인해야합니다.
    b = torch.randn(15000, 15000, device=device)
    while True:
        for _ in range(100):
            torch.matmul(a, b)

def cpu_stress():
    a = np.random.rand(1000, 1000)
    b = np.random.rand(1000, 1000)
    while True:
        np.dot(a, b)

def get_nvidia_smi_data():
    try:
        out = subprocess.check_output([
            "nvidia-smi",
            "--query-gpu=index,power.draw,temperature.gpu,temperature.memory",
            "--format=csv,noheader,nounits"
        ], encoding='utf-8')
        data = []
        for line in out.strip().split("\n"):
            idx, p, tg, tm = [x.strip() for x in line.split(',')]
            power = float(p) if p != "N/A" else None
            tgpu  = float(tg) if tg != "N/A" else None
            tmem  = float(tm) if tm != "N/A" else None
            temp  = tgpu if tgpu is not None else tmem
            data.append((int(idx), power, temp))
        return data
    except Exception as e:
        print("[nvidia-smi error]", e)
        return []

def get_cpu_temp():
    try:
        temps = psutil.sensors_temperatures()
        for entry in temps.get("coretemp", []):
            if entry.label.startswith("Package"):
                return entry.current
    except Exception as e:
        print("[CPU temp error]", e)
    return None

def get_system_temperatures():
    try:
        out = subprocess.check_output(["sensors"], encoding="utf-8")
        return out.replace("\n",";").replace(",", ";")
    except Exception as e:
        print("[sensors error]", e)
    return "N/A"

def get_cpu_power_rapl():
    try:
        with open("/sys/class/powercap/intel-rapl:0/energy_uj") as f:
            return int(f.read().strip()) / 1e6  # Joules
    except Exception as e:
        print("[RAPL error]", e)
    return None

def logger():
    with open(LOG_FILE, "w") as f:
        # header
        gpu_cnt = torch.cuda.device_count()
        gpu_hdr = [f"gpu{i}_power_watt,gpu{i}_temp_c" for i in range(gpu_cnt)]
        hdr = ["timestamp"] + gpu_hdr + [
            "cpu_temp_c",
            "cpu_power_joules",
            "cpu_power_watt",
            "gpu_power_total_watt",
            "system_power_estimate_watt",
            "sys_temp_raw"
        ]
        f.write(",".join(hdr) + "\n")

        last_rapl = get_cpu_power_rapl()
        # wrap range
        try:
            with open("/sys/class/powercap/intel-rapl:0/max_energy_range_uj") as mf:
                max_uj = int(mf.read().strip())
        except:
            max_uj = 2**32
        wrap_j = max_uj / 1e6

        while True:
            now   = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            gdata = get_nvidia_smi_data()
            ctemp = get_cpu_temp()
            cjoule= get_cpu_power_rapl()
            sraw  = get_system_temperatures()

            # CPU power delta (J -> W)
            if cjoule is not None and last_rapl is not None:
                delta = cjoule - last_rapl
                if delta < 0:
                    delta += wrap_j
                cpu_watt = round(delta, 3)
                last_rapl = cjoule
            else:
                cpu_watt = None

            # GPU string & sum
            gpu_strs = []
            gpu_total = 0.0
            for i in range(gpu_cnt):
                m = next((x for x in gdata if x[0]==i), None)
                if m and m[1] is not None:
                    gpu_strs.append(f"{m[1]},{m[2]}")
                    gpu_total += m[1]
                else:
                    gpu_strs.append("N/A,N/A")
            gpu_total = round(gpu_total,3)

            # system estimate = CPU + GPU
            sys_est = round((cpu_watt or 0) + gpu_total, 3) if cpu_watt is not None else None

            parts = [now] + gpu_strs + [
                str(ctemp),
                str(cjoule),
                str(cpu_watt),
                str(gpu_total),
                str(sys_est),
                sraw
            ]
            f.write(",".join(parts) + "\n")
            f.flush()
            time.sleep(1)

if __name__ == "__main__":
    print(f"Logging to {LOG_FILE}")
    # GPU stress
    for i in range(torch.cuda.device_count()):
        t = threading.Thread(target=gpu_stress, args=(f"cuda:{i}",))
        t.daemon=True; t.start()
    # CPU stress
    for _ in range(min(os.cpu_count(),32)):
        t = threading.Thread(target=cpu_stress)
        t.daemon=True; t.start()
    logger()
