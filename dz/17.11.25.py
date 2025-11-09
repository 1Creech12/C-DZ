import time
import random
import psutil

MEMORY_THRESHOLD_MB = 1024

def generate_load():
    load_list = []
    for _ in range(1000000):
        load_list.append(random.random())
    return load_list

def monitor_memory(interval=1):
    start_time = time.time()
    max_mem_usage=0
    total_mem_inctese = 0
    prev_mem_usage = None

    try:
        while True:
            current_mem_usage = psutil.Process().memory_info().rss / (1024*1024)

            if prev_mem_usage is not None:
                mem_increase = current_mem_usage - prev_mem_usage
                total_mem_inctese += mem_increase

            max_mem_usage = max(max_mem_usage, current_mem_usage)

            elapsed_time = time.time() - start_time
            avg_mem_increase_per_second = total_mem_inctese / elapsed_time if elapsed_time > 0 else 0

            print(f"Время: {elapsed_time:.2f}s\n"
                  f"Текущая нагрузка на память: {current_mem_usage:.2f} MB\n"
                  f"Максимальная нагрузка на память: {max_mem_usage:.2f} МБ\n"
                  f"Среднее увеличение памяти/секунду: {avg_mem_increase_per_second:.2f} МB/s\n")
            
            if current_mem_usage >= MEMORY_THRESHOLD_MB:
                print("n!!! Аварийный сигнал !!!\nПревышен порог допустимого потребления памяти!")

                prev_mem_usage = current_mem_usage
                generate_load()
                time.sleep(interval)
    except KeyboardInterrupt:
        pass
if __name__ == "__main__":
    monitor_memory()